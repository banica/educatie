using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Windows.Forms;

namespace api
{
    static class global
    {
        static public int matrix(int i, int j, int[][] matr)
        {
            int lines = matr.Length;
            int columns = matr[0].Length;
            if ((i < 0) || (j < 0) || (i >= lines) || (j >= columns))
            {
                return 0;
            }
            else
            {
                return matr[i][j];
            }
        }

        static public int[][] readImageFromFile(string filename)
        {
            string buffer;
            int[][] tmpMatrix = new int[15][];

            try
            {
                FileStream fp = new FileStream(@filename, FileMode.Open, FileAccess.Read);
                StreamReader reader = new StreamReader(fp);

                int j = 0;
                while (!reader.EndOfStream)
                {
                    buffer = reader.ReadLine();
                    tmpMatrix[j] = new int[buffer.Length];
                    for (int i = 0; i < buffer.Length; i++)
                    {
                        tmpMatrix[j][i] = Convert.ToInt16(buffer.Substring(i, 1));
                    }
                    j++;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
            return tmpMatrix;
        }

        static public int[] sortArray(int[] a)
        {
            int i, j;
            int x = a.Length;
            int min, temp;

            for (i = 0; i < x - 1; i++)
            {
                min = i;

                for (j = i + 1; j < x; j++)
                {
                    if (a[j] < a[min])
                    {
                        min = j;
                    }
                }

                temp = a[i];
                a[i] = a[min];
                a[min] = temp;
            }

            return a;
        }

        static public int[][] binarizareCuPrag(int[][] mi, int p)
        {
            int[] ta = new int[10];
            int[][] tm = new int[15][];
            int lines = mi.Length;

            for (int i = 0; i < lines; i++)
            {
                tm[i] = new int[mi[i].Length];
                for (int j = 0; j < mi[i].Length; j++)
                {
                    if (mi[i][j] >= p)
                    {
                        tm[i][j] = 1;
                    }
                    else
                    {
                        tm[i][j] = 0;
                    }
                }
            }
            return tm;
        }

        static public int determinarePragOptim(int[][] mi, int[][] morig)
        {
            int[][][] comp = new int[10][][];

            for (int i = 0; i < 10; i++)
            {
                comp[i] = global.binarizareCuPrag(mi, i);    
            }

            return filtre.matriceaCeaMaiIdeala(morig, comp);
        }
    }


    static class filtre
    {
        /// <summary>
        /// eliminare zgomot din mi utilizand filtrul bazat pe valoare medie
        /// neponderata FM1. Rezultatul e I1.
        /// </summary>
        /// <param name="mi"></param>
        /// <returns></returns>
        static public int[][] fm1(int[][] mi)
        {
            int[][] tm = new int[15][];
            int lines = mi.Length;

            for (int i = 0; i < lines; i++)
            {
                tm[i] = new int[mi[i].Length];
                for (int j = 0; j < mi[i].Length; j++)
                {
                    tm[i][j] = global.matrix(i, j, mi) +
                        global.matrix(i - 1, j - 1, mi) +
                        global.matrix(i - 1, j, mi) +
                        global.matrix(i - 1, j + 1, mi) +
                        global.matrix(i, j + 1, mi) +
                        global.matrix(i + 1, j + 1, mi) +
                        global.matrix(i + 1, j, mi) +
                        global.matrix(i + 1, j - 1, mi) +
                        global.matrix(i, j - 1, mi);
                    tm[i][j] = Convert.ToUInt16(Math.Round((double)tm[i][j] / 9));
                }

            }

            return tm;
        }


        /// <summary>
        /// eliminare zgomot din I0 utilizand filtrul bazat pe valoare medie
        /// ponderata FM2. Rezultatul e I2.
        /// </summary>
        /// <param name="I1"></param>
        /// <returns></returns>
        static public int[][] fm2(int[][] mi)
        {
            int[][] tm = new int[15][];

            int lines = mi.Length;

            for (int i = 0; i < lines; i++)
            {
                tm[i] = new int[mi[i].Length];
                for (int j = 0; j < mi[i].Length; j++)
                {
                    tm[i][j] = 2 * global.matrix(i, j, mi) +
                        global.matrix(i - 1, j - 1, mi) +
                        global.matrix(i - 1, j, mi) +
                        global.matrix(i - 1, j + 1, mi) +
                        global.matrix(i, j + 1, mi) +
                        global.matrix(i + 1, j + 1, mi) +
                        global.matrix(i + 1, j, mi) +
                        global.matrix(i + 1, j - 1, mi) +
                        global.matrix(i, j - 1, mi);
                    tm[i][j] = Convert.ToUInt16(Math.Round((double)tm[i][j] / 10));
                }

            }

            return tm;
        }

        /// <summary>
        /// eliminare zgomot din I0 utilizand filtrul bazat pe valoare medie
        /// ponderata FM3. Rezultatul e I3.
        /// </summary>
        /// <param name="mi"></param>
        /// <returns></returns>
        static public int[][] fm3(int[][] mi)
        {
            int[][] tm = new int[15][];

            int lines = mi.Length;

            for (int i = 0; i < lines; i++)
            {
                tm[i] = new int[mi[i].Length];
                for (int j = 0; j < mi[i].Length; j++)
                {
                    tm[i][j] = 4 * global.matrix(i, j, mi) +
                        global.matrix(i - 1, j - 1, mi) +
                        2 * global.matrix(i - 1, j, mi) +
                        global.matrix(i - 1, j + 1, mi) +
                        2 * global.matrix(i, j + 1, mi) +
                        global.matrix(i + 1, j + 1, mi) +
                        2 * global.matrix(i + 1, j, mi) +
                        global.matrix(i + 1, j - 1, mi) +
                        2 * global.matrix(i, j - 1, mi);
                    tm[i][j] = Convert.ToUInt16(Math.Round((double)tm[i][j] / 16));
                }

            }

            return tm;
        }

        static public int[][] vecinatatile5puncte(int[][] mi)
        {
            int[][] tm = new int[15][];
            int[] ta = new int[5];

            int lines = mi.Length;

            for (int i = 0; i < lines; i++)
            {
                tm[i] = new int[mi[i].Length];
                for (int j = 0; j < mi[i].Length; j++)
                {
                    ta[0] = global.matrix(i, j, mi);
                    ta[1] = global.matrix(i-1, j, mi);
                    ta[2] = global.matrix(i, j+1, mi);
                    ta[3] = global.matrix(i+1, j, mi);
                    ta[4] = global.matrix(i, j-1, mi);

                    ta = global.sortArray(ta);
                   
                    tm[i][j] = ta[2];
                }
            }
            return tm;
        }

        /// <summary>
        /// binarizarea lui I0 cu un prag P convenabil ales astfel incat imaginea
        /// obtinuta I5 sa se apropie cat mai mult de imaginea ideala
        /// </summary>
        /// <param name="mi"></param>
        /// <returns></returns>
        static public int[][] binarizareCuPragP(int[][] mi)
        {
            int[][] tm = new int[15][];
            int lines = mi.Length;
            // pragul ales este 1
            int p = 1;

            for (int i = 0; i < lines; i++)
            {
                tm[i] = new int[mi[i].Length];
                for (int j = 0; j < mi[i].Length; j++)
                {
                    if (mi[i][j] >= p)
                    {
                        tm[i][j] = 1;
                    }
                    else
                    {
                        tm[i][j] = 0;
                    }
                }
            }
            return tm;
        }

        /// <summary>
        /// eliminarea zgomotului din I5 folosind filtru de netezire logica 
        /// (filtru binar)
        /// </summary>
        /// <param name="mi"></param>
        /// <returns></returns>
        static public int[][] filtruNetezireLogica_1(int[][] mi)
        {
            int[][] tm = new int[15][];
            int lines = mi.Length;
            

            for (int i = 0; i < lines; i++)
            {
                tm[i] = new int[mi[i].Length];
                for (int j = 0; j < mi[i].Length; j++)
                {
                    if (global.matrix(i, j, mi) == 1 &&
                            global.matrix(i - 1, j, mi) == 0 &&
                            global.matrix(i - 1, j + 1, mi) == 0 &&
                            global.matrix(i, j + 1, mi) == 0 &&
                            global.matrix(i + 1, j + 1, mi) == 0 &&
                            global.matrix(i + 1, j, mi) == 0 &&

                            global.matrix(i + 1, j - 1, mi) == 0 &&
                            global.matrix(i, j - 1, mi) == 0 &&
                            global.matrix(i - 1, j - 1, mi) == 0)
                    {
                        tm[i][j] = 0;
                    }
                    else
                    {
                        tm[i][j] = mi[i][j];
                    }
                }
            }

            return tm;
        }


        /// <summary>
        /// eliminarea zgomotului din I5 folosind filtru de netezire logica 
        /// (filtru binar)
        /// </summary>
        /// <param name="mi"></param>
        /// <returns></returns>
        static public int[][] filtruNetezireLogica_2(int[][] mi)
        {
            int[][] tm = new int[15][];
            int lines = mi.Length;


            for (int i = 0; i < lines; i++)
            {
                tm[i] = new int[mi[i].Length];
                for (int j = 0; j < mi[i].Length; j++)
                {
                    if (global.matrix(i, j, mi) == 0 &&
                            global.matrix(i - 1, j, mi) == 1 &&
                            global.matrix(i - 1, j + 1, mi) == 1 &&
                            global.matrix(i, j + 1, mi) == 1 &&
                            global.matrix(i + 1, j + 1, mi) == 1 &&
                            global.matrix(i + 1, j, mi) == 1 &&

                            global.matrix(i + 1, j - 1, mi) == 1 &&
                            global.matrix(i, j - 1, mi) == 1 &&
                            global.matrix(i - 1, j - 1, mi) == 1)
                    {
                        tm[i][j] = 1;
                    }
                    else
                    {
                        tm[i][j] = mi[i][j];
                    }
                }
            }

            return tm;
        }

        /// <summary>
        /// histograma lui I1 
        /// </summary>
        /// <param name="mi"></param>
        /// <returns></returns>
        static public int[] histogramaI1(int[][] mi)
        {
            int[] ta = new int[10];
            int lines = mi.Length;

            for (int c = 0; c<10; c++)
            {
                ta[c] = 0;
            }

            for (int i = 0; i < lines; i++)
            {
                
                for (int j = 0; j < mi[i].Length; j++)
                {
                    ta[mi[i][j]]++; 
                }
            }
            return ta;
        }



        /// <summary>
        /// binarizarea lui I1 cu un prag P convenabil ales 
        /// astfel incat imaginea obtinuta I7 sa se apropie cat mai mult de 
        /// imaginea ideala
        /// </summary>
        /// <param name="mi"></param>
        /// <returns></returns>
        static public int[][] binarizareI1(int[][] mi)
        {
            int[] ta = new int[10];
            int[][] tm = new int[15][];
            int lines = mi.Length;
            int p = 1;

            for (int i = 0; i < lines; i++)
            {
                tm[i] = new int[mi[i].Length];
                for (int j = 0; j < mi[i].Length; j++)
                {
                    if (mi[i][j] >= p)
                    {
                        tm[i][j] = 1;
                    }
                    else
                    {
                        tm[i][j] = 0;
                    }
                }
            }
            return tm;
        }

        /// <summary>
        /// sa se aleaga cea mai buna imagine intre I6,I7,I8,I9,I10
        /// </summary>
        /// <param name="mi"></param>
        /// <param name="comparare"></param>
        /// <returns></returns>
        static public int matriceaCeaMaiIdeala(int[][] mi, int[][][] comparare)
        {
            int[] diferente = new int[comparare.Length];

            for (int i = 1; i < mi.Length; i++)
            {
                for (int j = 1; j < mi[i].Length; j++)
                {
                    for (int c = 0; c < diferente.Length; c++)
                    {
                        if (comparare[c][i][j] != mi[i][j])
                        {
                            diferente[c]++;

                        }
                    }

                }
            }

            int minVal = 15*15;
            int minInd = 0;

            for (int c = 0; c < diferente.Length; c++)
            {
                if (diferente[c] < minVal)
                {
                    minInd = c;
                    minVal = diferente[c];
                }
            }

            return minInd;
        }

        /// <summary>
        /// utilizand filtrul Roberts 2x2 se determina conturul din I4 punand in
        /// evidenta matricile intermediare
        /// </summary>
        /// <param name="mi"></param>
        /// <param name="p"></param>
        /// <returns></returns>
        static public int[][] filtruRoberts2x2(int[][] mi, int p)
        {
            int[][] tm = new int[15][];
            int lines = mi.Length;

            int[][] r1 = new int[15][];
            int[][] r2 = new int[15][];
            int[][] a = new int[15][];

            for (int i = 0; i < lines; i++)
            {
                r1[i] = new int[mi[i].Length];
                for (int j = 0; j < mi[i].Length; j++)
                {
                    r1[i][j] = global.matrix(i + 1, j, mi) - global.matrix(i, j + 1, mi);
                }
            }

            for (int i = 0; i < lines; i++)
            {
                r2[i] = new int[mi[i].Length];
                for (int j = 0; j < mi[i].Length; j++)
                {
                    r2[i][j] = global.matrix(i + 1, j + 1, mi) - global.matrix(i, j, mi);
                }
            }


            for (int i = 0; i < lines; i++)
            {
                a[i] = new int[mi[i].Length];
                for (int j = 0; j < mi[i].Length; j++)
                {
                    a[i][j] = Convert.ToInt16(System.Math.Sqrt(r1[i][j] * r1[i][j] + r2[i][j] * r2[i][j] ));
                }
            }


            tm = global.binarizareCuPrag(a, p);

            return tm;
        }

        /// <summary>
        /// determinam conturu folosind filtru binar cu vecinatati de 5 
        /// puncte din I11
        /// </summary>
        /// <param name="mi"></param>
        /// <returns></returns>
        static public int[][] conturVecintati(int[][] mi)
        {
            int[][] tm = new int[15][];
            int lines = mi.Length;


            for (int i = 0; i < lines; i++)
            {
                tm[i] = new int[mi[i].Length];
                for (int j = 0; j < mi[i].Length; j++)
                {
                    if (global.matrix(i, j, mi) == 1 &&
                            global.matrix(i - 1, j, mi) == 1 &&
                            global.matrix(i, j + 1, mi) == 1 &&
                            global.matrix(i+1, j , mi) == 1 &&
                            global.matrix(i , j - 1, mi) == 1
                            )
                    {
                        tm[i][j] = 0;
                    }
                    else
                    {
                        tm[i][j] = mi[i][j];
                    }
                }
            }

            return tm;
        }

        /// <summary>
        /// determinam aria lui I11 direct
        /// </summary>
        /// <param name="mi"></param>
        /// <returns></returns>
        static public int aria(int[][] mi)
        {
            int lines = mi.Length;
            int aria = 0;

            for (int i = 0; i < lines; i++)
            {
                for (int j = 0; j < mi[i].Length; j++)
                {
                    if (mi[i][j] == 1)
                    {
                        aria++;
                    }
                }
            }

            return aria;
        }

        /// <summary>
        /// calculam aria si perimetrul lui I11 utilizand forme patratice binare
        /// </summary>
        /// <param name="mi"></param>
        /// <param name="?"></param>
        /// <param name="?"></param>
        static public void ariaSIperimetrul(int[][] mi, ref int aria, ref int perimetrul)
        {
            int lines = mi.Length;
            int n1 = 0;
            int n2 = 0;
            int n3 = 0;
            int n4 = 0;

            for (int i = 0; i < lines-1; i++)
            {
                for (int j = 0; j < mi[i].Length - 1; j++)
                {
                    if ( 
                            (mi[i][j] == 1 && mi[i][j+1] == 0 && mi[i+1][j+1] == 0 && mi[i+1][j] == 0) ||
                            (mi[i][j] == 0 && mi[i][j+1] == 1 && mi[i+1][j+1] == 0 && mi[i+1][j] == 0) ||
                            (mi[i][j] == 0 && mi[i][j+1] == 0 && mi[i+1][j+1] == 1 && mi[i+1][j] == 0) ||
                            (mi[i][j] == 0 && mi[i][j+1] == 0 && mi[i+1][j+1] == 0 && mi[i+1][j] == 1) 
                        )
                    {
                        n1++;
                    }

                    if (
                            (mi[i][j] == 1 && mi[i][j + 1] == 1 && mi[i + 1][j + 1] == 0 && mi[i + 1][j] == 0) ||
                            (mi[i][j] == 1 && mi[i][j + 1] == 0 && mi[i + 1][j + 1] == 0 && mi[i + 1][j] == 1) ||
                            (mi[i][j] == 0 && mi[i][j + 1] == 1 && mi[i + 1][j + 1] == 1 && mi[i + 1][j] == 0) ||
                            (mi[i][j] == 0 && mi[i][j + 1] == 0 && mi[i + 1][j + 1] == 1 && mi[i + 1][j] == 1)
                        )
                    {
                        n2++;
                    }

                    if (
                            (mi[i][j] == 1 && mi[i][j + 1] == 1 && mi[i + 1][j + 1] == 0 && mi[i + 1][j] == 1) ||
                            (mi[i][j] == 1 && mi[i][j + 1] == 1 && mi[i + 1][j + 1] == 1 && mi[i + 1][j] == 0) ||
                            (mi[i][j] == 0 && mi[i][j + 1] == 1 && mi[i + 1][j + 1] == 1 && mi[i + 1][j] == 1) ||
                            (mi[i][j] == 1 && mi[i][j + 1] == 0 && mi[i + 1][j + 1] == 1 && mi[i + 1][j] == 1)
                        )
                    {
                        n3++;
                    }

                    if (
                            (mi[i][j] == 1 && mi[i][j + 1] == 1 && mi[i + 1][j + 1] == 1 && mi[i + 1][j] == 1)
                        )
                    {
                        n4++;
                    }

                }
            }
            //tm[i][j] = Convert.ToUInt16(Math.Round((double)tm[i][j] / 16));;
            aria = Convert.ToUInt16(Math.Round((double)(n1 + 2 * n2 + 3 * n3 + 4 * n4) / 4));
            perimetrul = Convert.ToInt16(Math.Round((double)n2 + (double)n3 * System.Math.Sqrt(2)));
        }

        /// <summary>
        /// determinarea centrului de greutate a imaginii I11
        /// </summary>
        /// <param name="mi"></param>
        /// <param name="aria"></param>
        /// <param name="x"></param>
        /// <param name="y"></param>
        static public void centrulDeGreutate(int[][] mi, int aria, ref int x, ref int y)
        {
            int lines = mi.Length;
            int nrlinii = 0;
            int nrcoloane = 0;
            int I = 0;
            int J = 0;

            for (int i = 0; i < lines-1; i++)
            {
                for (int j = 0; j < mi[i].Length; j++)
                {
                    if (mi[i + 1][j] == 1)
                    {
                        nrlinii++;
                    }
                }
                nrlinii = i * nrlinii;
                I = I + nrlinii;
                nrlinii = 0;
            }
            J = 0;

            for (int i = 0; i < lines - 1; i++)
            {
                for (int j = 0; j < mi[i].Length; j++)
                {
                    if (mi[i + 1][j] == 1)
                    {
                        nrcoloane++;
                    }
                }
                nrcoloane = J * nrcoloane;
                J = J + nrcoloane;
                nrcoloane = 0;
            }

            x = Convert.ToInt16(I / aria) + 1;
            y = Convert.ToInt16(J / aria) + 1;
        }

        /// <summary>
        /// determinarea razei minime/maxime/medii pe baza a ce s-a obtinut mai sus
        /// pentru I11
        /// </summary>
        /// <param name="mi"></param>
        /// <param name="IG"></param>
        /// <param name="JG"></param>
        /// <param name="raza_minima"></param>
        /// <param name="raza_maxima"></param>
        /// <param name="raza_med"></param>
        static public void calculeazaMulteChestii(int[][] mi, int IG, int JG, ref int raza_minima, ref int raza_maxima, ref int raza_med)
        {
        
            int[] raza_min = new int[4];
            int[] raza_max = new int[4];
            int raza = 0;


            while ((IG + raza) <= mi.Length || (IG - raza) >= 0 || (JG + raza) < mi[0].Length || (JG - raza) >= 0){
               if (mi[IG+raza][JG] != 1)
               {
                    raza++;
               }
               else
               {
                    raza_min[0] = raza;
                    break;
               }
            }

            raza = 0;
            while ((IG + raza) <= mi.Length || (IG - raza) >= 0 || (JG + raza) < mi[0].Length || (JG - raza) >= 0){
                   if(mi[IG-raza][JG] != 1)
                   {
                        raza ++;
                   }
                   else
                   {
                        raza_min[1] = raza;
                        break;
                   }
            }

            raza = 0;
            while ((IG + raza) <= mi.Length || (IG - raza) >= 0 || (JG + raza) < mi[0].Length || (JG - raza) >= 0){    
                if(mi[IG][JG+raza] != 1)
                {
                    raza ++;
                }
                else
                {
                    raza_min[2] = raza;
                    break;
                }
            }

            raza = 0;
            while ((IG + raza) <= mi.Length || (IG - raza) >= 0 || (JG + raza) < mi[0].Length || (JG - raza) >= 0){    
                   if(mi[IG][JG-raza] != 1)
                   {
                        raza ++;
                   }
                   else
                   {
                        raza_min[3] = raza;
                        break;
                   }
            }
             
            raza_min = global.sortArray(raza_min);
            raza_minima = raza_min[0];

            raza = 0;
            while ((IG + raza) <= mi.Length || (IG - raza) >= 0 || (JG + raza) < mi[0].Length || (JG - raza) >= 0){    
                   if(mi[IG+raza][JG+raza] != 1)
                        raza ++;
                   else
                   {
                        raza_max[0] = Convert.ToInt16(raza* System.Math.Sqrt(2));
                        break;
                   }
            }

            raza = 0;
            while ((IG + raza) <= mi.Length || (IG - raza) >= 0 || (JG + raza) < mi[0].Length || (JG - raza) >= 0){    
                   if(mi[IG-raza][JG-raza] != 1)
                        raza ++;
                   else
                   {
                        raza_max[1] = Convert.ToInt16(raza* System.Math.Sqrt(2));
                        break;
                   }
            }
            raza = 0;
            while ((IG + raza) <= mi.Length || (IG - raza) >= 0 || (JG + raza) < mi[0].Length || (JG - raza) >= 0){    
                   if(mi[IG-raza][JG+raza] != 1)
                        raza ++;
                   else
                   {
                         raza_max[2] = Convert.ToInt16(raza* System.Math.Sqrt(2));
                        break;
                   }
            }
            raza = 0;
            while ((IG + raza) <= mi.Length || (IG - raza) >= 0 || (JG + raza) < mi[0].Length || (JG - raza) >= 0){    
                   if(mi[IG+raza][JG-raza] != 1)
                        raza ++;
                   else
                   {
                         raza_max[3] = Convert.ToInt16(raza* System.Math.Sqrt(2));
                        break;
                   }
            }

             raza_max = global.sortArray(raza_max);
            raza_maxima = raza_max[3];

            raza = 0;
            for (int i = 1; i < mi.Length; i++)
            {

                for (int j = 1; j < mi[i].Length; j++)
                {
                    if (mi[i][j] == 1)
                    {
                        raza++;
                        raza_med = raza_med + Convert.ToInt16(System.Math.Sqrt((IG - i) * (IG - i) + (JG - j) * (JG - j)));
                    }
                }
            }
        }

    }
}



