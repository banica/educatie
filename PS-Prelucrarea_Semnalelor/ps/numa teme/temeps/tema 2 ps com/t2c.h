// Matrici imagine
extern	float			**r;
extern	float			**g;
extern	float			**b;	

// Dimensiune imagine
extern	unsigned short	dx;
extern	unsigned short	dy;

// Proceduri compresie aritmetica
extern	void scrie_bit(char bit);
extern	void start_compresie(void);
extern	void comprima_bit(char bit,int context);
extern	void stop_compresie(void);

