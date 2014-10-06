namespace TileMap
{
    partial class Form1
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
            this.pbSourcePicture = new System.Windows.Forms.PictureBox();
            this.tbPathPicture = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.pbTileMapPic = new System.Windows.Forms.PictureBox();
            this.label2 = new System.Windows.Forms.Label();
            this.tbAmoutTiles = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.tbWidth = new System.Windows.Forms.TextBox();
            this.tbHeight = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.progressbarCreateTile = new System.Windows.Forms.ProgressBar();
            this.pnSourcePicture = new System.Windows.Forms.Panel();
            this.pnTileMapPic = new System.Windows.Forms.Panel();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            ((System.ComponentModel.ISupportInitialize)(this.pbSourcePicture)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbTileMapPic)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.pnSourcePicture.SuspendLayout();
            this.pnTileMapPic.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // pbSourcePicture
            // 
            this.pbSourcePicture.Location = new System.Drawing.Point(3, 3);
            this.pbSourcePicture.Name = "pbSourcePicture";
            this.pbSourcePicture.Size = new System.Drawing.Size(527, 122);
            this.pbSourcePicture.TabIndex = 0;
            this.pbSourcePicture.TabStop = false;
            this.pbSourcePicture.Click += new System.EventHandler(this.pbSourceImage_Click);
            // 
            // tbPathPicture
            // 
            this.tbPathPicture.Enabled = false;
            this.tbPathPicture.Location = new System.Drawing.Point(103, 157);
            this.tbPathPicture.Name = "tbPathPicture";
            this.tbPathPicture.ReadOnly = true;
            this.tbPathPicture.Size = new System.Drawing.Size(475, 20);
            this.tbPathPicture.TabIndex = 4;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(584, 154);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 5;
            this.button1.Text = "Chọn Ảnh";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(536, 360);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(123, 78);
            this.button2.TabIndex = 6;
            this.button2.Text = "Tạo Bộ Tile";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // pbTileMapPic
            // 
            this.pbTileMapPic.Location = new System.Drawing.Point(3, 3);
            this.pbTileMapPic.Name = "pbTileMapPic";
            this.pbTileMapPic.Size = new System.Drawing.Size(302, 63);
            this.pbTileMapPic.TabIndex = 7;
            this.pbTileMapPic.TabStop = false;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(11, 33);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(40, 13);
            this.label2.TabIndex = 8;
            this.label2.Text = "Số Tile";
            // 
            // tbAmoutTiles
            // 
            this.tbAmoutTiles.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.tbAmoutTiles.Enabled = false;
            this.tbAmoutTiles.Location = new System.Drawing.Point(78, 26);
            this.tbAmoutTiles.Name = "tbAmoutTiles";
            this.tbAmoutTiles.ReadOnly = true;
            this.tbAmoutTiles.Size = new System.Drawing.Size(100, 20);
            this.tbAmoutTiles.TabIndex = 9;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(11, 65);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 13);
            this.label3.TabIndex = 10;
            this.label3.Text = "Chiều Dài";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(11, 100);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(56, 13);
            this.label4.TabIndex = 11;
            this.label4.Text = "Chiều Cao";
            // 
            // tbWidth
            // 
            this.tbWidth.Enabled = false;
            this.tbWidth.Location = new System.Drawing.Point(78, 62);
            this.tbWidth.Name = "tbWidth";
            this.tbWidth.ReadOnly = true;
            this.tbWidth.Size = new System.Drawing.Size(100, 20);
            this.tbWidth.TabIndex = 12;
            // 
            // tbHeight
            // 
            this.tbHeight.Enabled = false;
            this.tbHeight.Location = new System.Drawing.Point(78, 97);
            this.tbHeight.Name = "tbHeight";
            this.tbHeight.ReadOnly = true;
            this.tbHeight.Size = new System.Drawing.Size(100, 20);
            this.tbHeight.TabIndex = 13;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.tbHeight);
            this.groupBox1.Controls.Add(this.tbAmoutTiles);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.tbWidth);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Location = new System.Drawing.Point(441, 208);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(218, 128);
            this.groupBox1.TabIndex = 14;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Thông Tin";
            // 
            // progressbarCreateTile
            // 
            this.progressbarCreateTile.Location = new System.Drawing.Point(103, 360);
            this.progressbarCreateTile.Name = "progressbarCreateTile";
            this.progressbarCreateTile.Size = new System.Drawing.Size(427, 78);
            this.progressbarCreateTile.TabIndex = 15;
            // 
            // pnSourcePicture
            // 
            this.pnSourcePicture.Controls.Add(this.pbSourcePicture);
            this.pnSourcePicture.Location = new System.Drawing.Point(11, 17);
            this.pnSourcePicture.Name = "pnSourcePicture";
            this.pnSourcePicture.Size = new System.Drawing.Size(533, 128);
            this.pnSourcePicture.TabIndex = 16;
            // 
            // pnTileMapPic
            // 
            this.pnTileMapPic.Controls.Add(this.pbTileMapPic);
            this.pnTileMapPic.Location = new System.Drawing.Point(6, 33);
            this.pnTileMapPic.Name = "pnTileMapPic";
            this.pnTileMapPic.Size = new System.Drawing.Size(308, 68);
            this.pnTileMapPic.TabIndex = 17;
            this.pnTileMapPic.Paint += new System.Windows.Forms.PaintEventHandler(this.pnTileMapPic_Paint);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.pnTileMapPic);
            this.groupBox2.Location = new System.Drawing.Point(103, 208);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(332, 128);
            this.groupBox2.TabIndex = 18;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Bộ Tile";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.pnSourcePicture);
            this.groupBox3.Location = new System.Drawing.Point(103, 3);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(556, 148);
            this.groupBox3.TabIndex = 19;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Map";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(752, 467);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.progressbarCreateTile);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.tbPathPicture);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "TileMapv1.0.0";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pbSourcePicture)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbTileMapPic)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.pnSourcePicture.ResumeLayout(false);
            this.pnTileMapPic.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pbSourcePicture;
        private System.Windows.Forms.TextBox tbPathPicture;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.PictureBox pbTileMapPic;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox tbAmoutTiles;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox tbWidth;
        private System.Windows.Forms.TextBox tbHeight;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ProgressBar progressbarCreateTile;
        private System.Windows.Forms.Panel pnSourcePicture;
        private System.Windows.Forms.Panel pnTileMapPic;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
    }
}

