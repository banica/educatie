using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace api
{
    public partial class imagine : Form
    {
        protected Button[][] elem = new Button[15][];
        public imagine()
        {
            InitializeComponent();
        }

        private void imagine_Load(object sender, EventArgs e)
        {
            deseneaza();
        }

        private void deseneaza()
        {
            
            panel1.Width = 15 * 25;
            panel1.Height = 15 * 25;

            this.Width = panel1.Width + 24;
            this.Height = panel1.Height + 50;

            for (int i = 0; i < 15; i++)
            {
                elem[i] = new Button[15];
                for (int j = 0; j < 15; j++)
                {
                    elem[i][j] = new Button();
                    elem[i][j].BackColor = Color.White;
                    elem[i][j].Parent = panel1;
                    elem[i][j].Width = 25;
                    elem[i][j].Height = 25;
                    elem[i][j].Top = 25 * i;
                    elem[i][j].Left = 25 * j;
                    elem[i][j].Visible = true;
                    elem[i][j].Enabled = false;
                }
            }
        }

        public void umpleMatrice(int[][] mi)
        {
            int decAgain;
            string[] culori = new string[10];
            culori[0] = "000000";
            culori[1] = "202020";
            culori[2] = "404040";
            culori[3] = "606060";
            culori[4] = "808080";
            culori[5] = "A0A0A0";
            culori[6] = "C0C0C0";
            culori[7] = "B0B0B0";
            culori[8] = "C0C0C0";
            culori[9] = "FFFFFF";

            for (int i = 0; i < 15; i++)
            {
                for (int j = 0; j < 15; j++)
                {
                    decAgain = int.Parse(culori[mi[i][j]], System.Globalization.NumberStyles.HexNumber);

                    elem[i][j].BackColor = Color.FromArgb(decAgain);
                    elem[i][j].Text = mi[i][j].ToString();
                }
            }
        }
    }
}