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
    public partial class histograma : Form
    {
        public histograma()
        {
            InitializeComponent();
        }

       
        public void deseneaza(int[] date)
        {
            histograma1.ToolBar = false;
            histograma1.Gallery = Gallery.Bar;

            histograma1.Border = true;
            histograma1.AxisY.Max = 30;
            histograma1.AxisY.Min = 0;
            histograma1.Chart3D = true;
            histograma1.Grid = ChartGrid.Vert;
            histograma1.OpenData(COD.Values, 1, date.Length);
            for (int i = 0; i < date.Length; i++)
            {
                histograma1.Value[0, i] = date[i];
                histograma1.Legend[i] = i.ToString();
            }
            histograma1.CloseData(COD.Values); 
            histograma1.RecalcScale();
            histograma1.Update();
        }

        private void histograma1_Load(object sender, EventArgs e)
        {

        }

        private void histograma_Load(object sender, EventArgs e)
        {
            int[] tmdData = new int[10];
            for (int i = 0; i<10; i++)
            {
                tmdData[i] = 0;
            }
            deseneaza(tmdData);
        }

    }
}