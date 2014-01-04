using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using SoftwareFX.ChartFX.Lite;

namespace api
{
    public partial class main : Form
    {
        int[][] mi = new int[15][];
        int[][] mideal = new int[15][];
        int[][][] arr = new int[20][][];
        bool[] hasArray = new bool[20];
        int aria = 0;

        int x = 0;
        int y = 0;

        imagine frmImagine = new imagine();
        histograma frmHistograma = new histograma();
        public main()
        {
            InitializeComponent();
            
        }

        private void main_Load(object sender, EventArgs e)
        {
            mi = global.readImageFromFile("imagine.txt");
            mideal = global.readImageFromFile("ideal.txt");
            
            frmImagine.Show();
            frmImagine.Focus();
            frmImagine.umpleMatrice(mi);
            frmHistograma.Show();

            arr[0] = mi;
            hasArray[0] = true;
        }

        private void despreToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Program realizat de George Enciu, 345AA", "Despre");
            
        }

        private void incarcareToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void cerinta1ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (hasArray[0])
            {
                arr[1] = filtre.fm1(arr[0]);
                frmImagine.umpleMatrice(arr[1]);
                hasArray[1] = true;
            }
            else
            {
                MessageBox.Show("Pentru cerinta 1 trebuie sa incarcati imaginea.", "Eroare",MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void cerinta2ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (hasArray[0])
            {
                arr[2] = filtre.fm2(arr[0]);
                frmImagine.umpleMatrice(arr[2]);
                hasArray[2] = true;
            }
            else
            {
                MessageBox.Show("Pentru cerinta 2 trebuie sa rulati cerinta 1.", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void cerinta3ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (hasArray[2])
            {
                arr[3] = filtre.fm3(arr[0]);
                frmImagine.umpleMatrice(arr[3]);
                hasArray[3] = true;
            }
            else
            {
                MessageBox.Show("Pentru cerinta 3 trebuie sa rulati cerinta 2.", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void cerinta4ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (hasArray[3])
            {
                arr[4] = filtre.vecinatatile5puncte(arr[0]);
                frmImagine.umpleMatrice(arr[4]);
                MessageBox.Show("Apasati OK pentru a afisa cea de-a 2-a matrice", "Cerinta 4", MessageBoxButtons.OK, MessageBoxIcon.Information);
                
                arr[4] = filtre.vecinatatile5puncte(arr[4]);
                frmImagine.umpleMatrice(arr[4]);
                hasArray[4] = true;
            }
            else
            {
                MessageBox.Show("Pentru cerinta 4 trebuie sa rulati cerinta 3.", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void cerinta5ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (hasArray[0])
            {
                arr[5] = global.binarizareCuPrag(arr[0], 1);
                frmImagine.umpleMatrice(arr[5]);
                hasArray[5] = true;
            }
            else
            {
                MessageBox.Show("Pentru cerinta 5 trebuie sa incarcati imaginea.", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void cerinta6ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (hasArray[5])
            {
                arr[6] = filtre.filtruNetezireLogica_1(arr[5]);
                //frmImagine.umpleMatrice(arr[6]);
                //MessageBox.Show("Apasati OK pentru a afisa cea de-a 2-a matrice", "Cerinta 6", MessageBoxButtons.OK, MessageBoxIcon.Information);

                arr[6] = filtre.filtruNetezireLogica_2(arr[6]);
                frmImagine.umpleMatrice(arr[6]);
                hasArray[6] = true;
            }
            else
            {
                MessageBox.Show("Pentru cerinta 6 trebuie sa rulati cerinta 5.", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void cerinta7ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (hasArray[1])
            {
                int[] histData = filtre.histogramaI1(arr[1]);
                frmHistograma.deseneaza(histData);

                arr[7] = global.binarizareCuPrag(arr[1], 5);
                frmImagine.umpleMatrice(arr[7]);

                hasArray[7] = true;
            }
            else
            {
                MessageBox.Show("Pentru cerinta 7 trebuie sa rulati cerinta 1.", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void cerinta8ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (hasArray[2])
            {
                int[] histData = filtre.histogramaI1(arr[2]);
                frmHistograma.deseneaza(histData);

                arr[8] = global.binarizareCuPrag(arr[2], 5);
                frmImagine.umpleMatrice(arr[8]);

                hasArray[8] = true;
            }
            else
            {
                MessageBox.Show("Pentru cerinta 8 trebuie sa rulati cerinta 2.", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void cerinta9ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (hasArray[3])
            {
                int[] histData = filtre.histogramaI1(arr[3]);
                frmHistograma.deseneaza(histData);

                arr[9] = global.binarizareCuPrag(arr[3], 5);
                frmImagine.umpleMatrice(arr[9]);

                hasArray[9] = true;
            }
            else
            {
                MessageBox.Show("Pentru cerinta 9 trebuie sa rulati cerinta 3.", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void cerinta10ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (hasArray[4])
            {
                int[] histData = filtre.histogramaI1(arr[4]);
                frmHistograma.deseneaza(histData);

                arr[10] = global.binarizareCuPrag(arr[4], 1);
                frmImagine.umpleMatrice(arr[10]);

                hasArray[10] = true;
            }
            else
            {
                MessageBox.Show("Pentru cerinta 10 trebuie sa rulati cerinta 4.", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void cerinta11ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (hasArray[6] && hasArray[7] && hasArray[8] && hasArray[9] && hasArray[10])
            {
                int[][][] data = new int[5][][];
                data[0] = arr[6];
                data[1] = arr[7];
                data[2] = arr[8];
                data[3] = arr[9];
                data[4] = arr[10];
                int celMai = filtre.matriceaCeaMaiIdeala(mideal, data);
                celMai += 6;

                arr[11] = arr[celMai];
                MessageBox.Show("Cea mai buna imagine este I" + celMai.ToString(), "Cerinta 11", MessageBoxButtons.OK, MessageBoxIcon.Information);
                frmImagine.umpleMatrice(arr[11]);

                hasArray[11] = true;
            }
            else
            {
                MessageBox.Show("Pentru cerinta 10 trebuie sa rulati cerintele 6, 7, 8, 9 si 10.", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void cerinta12ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (hasArray[4])
            {
                arr[12] = filtre.filtruRoberts2x2(arr[4], 4);
                frmImagine.umpleMatrice(arr[12]);

                hasArray[12] = true;
            }
            else
            {
                MessageBox.Show("Pentru cerinta 12 trebuie sa rulati cerinta 4.", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void cerinta13ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (hasArray[11])
            {
                arr[13] = filtre.conturVecintati(arr[11]);
                frmImagine.umpleMatrice(arr[13]);

                hasArray[13] = true;
            }
            else
            {
                MessageBox.Show("Pentru cerinta 13 trebuie sa rulati cerinta 11.", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void cerinta14ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (hasArray[11])
            {
                int aria = filtre.aria(arr[11]);

                MessageBox.Show("Aria imaginii I11 este" + aria.ToString(), "Cerinta 14", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            {
                MessageBox.Show("Pentru cerinta 14 trebuie sa rulati cerintele 11.", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void cerinta15ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (hasArray[13])
            {
                int perim = filtre.aria(arr[13]);

                MessageBox.Show("Perimetrul imaginii I13 este" + perim.ToString(), "Cerinta 15", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            {
                MessageBox.Show("Pentru cerinta 15 trebuie sa rulati cerintele 13.", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void cerinta16ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (hasArray[11])
            {
                int perim = 0;
                filtre.ariaSIperimetrul(arr[11], ref aria, ref perim);
                hasArray[16] = true;

                MessageBox.Show("Perimetrul imaginii I11 este " + perim.ToString() + " iar aria este " + aria.ToString(), "Cerinta 16", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            {
                MessageBox.Show("Pentru cerinta 16 trebuie sa rulati cerintele 11.", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void cerinta17ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (hasArray[11] && hasArray[16])
            {
                
                filtre.centrulDeGreutate(arr[11], aria, ref x,ref y);

                MessageBox.Show("Centrul de greutatea al imaginii I11 este in punctul (" + x.ToString() + ", " + y.ToString() + ")", "Cerinta 17", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            {
                MessageBox.Show("Pentru cerinta 17 trebuie sa rulati cerintele 11 si 16.", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void cerinta18ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (hasArray[11])
            {
                int raza_min = 0;
                int raza_max = 0;
                int raza_med = 0;
                filtre.calculeazaMulteChestii(arr[11], x, y, ref raza_min, ref raza_max, ref raza_med);
                /*raza_max = 9;
                raza_med = 2;
                raza_min = 1;*/

                MessageBox.Show("Raza minima=" + raza_min.ToString() + ", Raza maxima=" + raza_max.ToString() + ", Raza medie=" + raza_med.ToString(), "Cerinta 18", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            {
                MessageBox.Show("Pentru cerinta 18 trebuie sa rulati cerinta 11.", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void pragOptimToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int parg = global.determinarePragOptim(arr[4], mideal);

            MessageBox.Show("aia optima: " + parg.ToString());
        }

 
    }
      
}