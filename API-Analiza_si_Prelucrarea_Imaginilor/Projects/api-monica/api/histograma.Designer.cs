namespace api
{
    partial class histograma
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.histograma1 = new SoftwareFX.ChartFX.Lite.Chart();
            this.SuspendLayout();
            // 
            // histograma1
            // 
            this.histograma1.Location = new System.Drawing.Point(12, 12);
            this.histograma1.Name = "histograma1";
            this.histograma1.Size = new System.Drawing.Size(850, 244);
            this.histograma1.TabIndex = 1;
            this.histograma1.Load += new System.EventHandler(this.histograma1_Load);
            // 
            // histograma
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(874, 266);
            this.Controls.Add(this.histograma1);
            this.Name = "histograma";
            this.Text = "Histograma";
            this.Load += new System.EventHandler(this.histograma_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private SoftwareFX.ChartFX.Lite.Chart histograma1;
    }
}