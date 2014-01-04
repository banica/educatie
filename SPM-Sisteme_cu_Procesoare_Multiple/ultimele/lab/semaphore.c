/* semaphore.c
   Copyright Mark Watson, 1988.  Open Source Software License
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#define Vdim 10
#define IPC_WAIT 0

union SEMUN {
    int val;
    struct semid_ds *buf;
    ushort *array;
    struct SEMINFO *__bufi;
    void *__pad;
  };

int main() {
  key_t unique_key;
  struct sembuf lock_it;
  union SEMUN options;
  int id,i,k,a[Vdim],b[Vdim];
  pid_t pid;

  for (i=0;i<Vdim;i++){
    a[i]=b[i]=i;
  }
  
  // Start by creating a semaphore:
  unique_key = ftok(".", 'a'); // 'a' can be any character
  // Create a new semaphore with 1 member of the set; Note that
  // if you want to use a semaphore created by another program
  // then use 0 instead of 1 for the second argument:
  id = semget(unique_key, 1, IPC_CREAT | IPC_EXCL | 0666);
  printf("semaphore id=%d\n", id);
  options.val = 1;
  semctl(id, 0, SETVAL, options);

  // make sure that everything is set up OK:
  if (semctl(id, 0, GETVAL, 0) == 0) {
    printf("can not lock semaphore.\n");
    exit(1);
  }

  // Now print out the value of the semaphore:
  i = semctl(id, 0, GETVAL, 0);
  printf("value of semaphore at index 0 is %d\n", i);

  int f=open("shared_mem",O_RDWR);
  int *mem_pointer=(int *)mmap(0,(Vdim+1)*sizeof(int), PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED,f,0);
  mem_pointer[0]=0;
  pid=fork();

  while (mem_pointer[0]<Vdim){
    if (pid==0) { //child
    
        // Now set the semaphore:
        lock_it.sem_num = 0; // semaphore index
        lock_it.sem_op  = -1; // operation
        lock_it.sem_flg = IPC_NOWAIT; // operation flags
        if (semop(id, &lock_it, 1) == -1) {
         printf("can not lock semaphore.\n");
         exit(1);
        }

        // Now print out the value of the semaphore:
        i = semctl(id, 0, GETVAL, 0);
        printf("value of semaphore at index 0 is %d\n", i);

        k=mem_pointer[0];
        mem_pointer[0]++;

        // now un-set the semaphore:
        lock_it.sem_num = 0;
        lock_it.sem_op  = 1;
        lock_it.sem_flg = IPC_NOWAIT;
        if (semop(id, &lock_it, 1) == -1) {
            printf("could not unlock semaphore.\n");
            exit(1);
        }

        // Now print out the value of the semaphore:
        i = semctl(id, 0, GETVAL, 0);
        printf("value of semaphore at index 0 is %d\n", i);

        mem_pointer[k++]=a[k]+b[k];

    }
    else {
        // Now set the semaphore:
        lock_it.sem_num = 0; // semaphore index
        lock_it.sem_op  = -1; // operation
        lock_it.sem_flg = IPC_NOWAIT; // operation flags
        if (semop(id, &lock_it, 1) == -1) {
            printf("can not lock semaphore.\n");
            exit(1);
        }

        // Now print out the value of the semaphore:
        i = semctl(id, 0, GETVAL, 0);
        printf("value of semaphore at index 0 is %d\n", i);

        k=mem_pointer[0];
        mem_pointer[0]++;

        // now un-set the semaphore:
        lock_it.sem_num = 0;
        lock_it.sem_op  = 1;
        lock_it.sem_flg = IPC_NOWAIT;
        if (semop(id, &lock_it, 1) == -1) {
            printf("could not unlock semaphore.\n");
            exit(1);
        }

        // Now print out the value of the semaphore:
        i = semctl(id, 0, GETVAL, 0);
        printf("value of semaphore at index 0 is %d\n", i);

        mem_pointer[k++]=a[k]+b[k];
    }
  }
  if (pid==0) {
    exit(0);
  }

  for (i=1;i<Vdim+1;i++){
    printf ("%d",mem_pointer[i]);
  }
  munmap(mem_pointer,(Vdim+1));
  // Now remove the semaphore:
  semctl(id, 0, IPC_RMID, 0);

  return 42;
};
