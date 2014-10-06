using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace TileMap
{
    public partial class Form1 : Form
    {
        private CMap _TileMap;
        private Bitmap _TileMapPicture;
        private bool IsDouble = false;

        public Form1()
        {
            InitializeComponent();

            this.pnSourcePicture.AutoScroll = true;
            this.pbSourcePicture.SizeMode = PictureBoxSizeMode.AutoSize;

            this.pnTileMapPic.AutoScroll = true;
            this.pbTileMapPic.SizeMode = PictureBoxSizeMode.AutoSize;

            this.progressbarCreateTile.Visible = true;
            this.progressbarCreateTile.Minimum = 0;
            this.progressbarCreateTile.Value = 0;
            this.progressbarCreateTile.Step = 1;
            _TileMap = null;
        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialogSourcePicture = new OpenFileDialog();
            openFileDialogSourcePicture.Filter = "PNG (*.png)|*.png| BMP (*.bmp)|*.bmp| All File (*.*)|*.*";
            openFileDialogSourcePicture.FilterIndex = 3;
            openFileDialogSourcePicture.RestoreDirectory = true;

            if (openFileDialogSourcePicture.ShowDialog() == DialogResult.OK)
            {
                CTile.CountID = 0;
                this.progressbarCreateTile.Value = 0;
                Reset();
                this.tbPathPicture.Text = openFileDialogSourcePicture.FileName;
                if (new Bitmap(this.tbPathPicture.Text).Width >= 32 && new Bitmap(this.tbPathPicture.Text).Height >= 32)
                {
                    this.pbSourcePicture.Image = new Bitmap(this.tbPathPicture.Text);

                    _TileMap = new CMap(new Bitmap(this.tbPathPicture.Text));
                }
                else
                {
                    _TileMap = null;
                    pbSourcePicture.Image = null;
                    CTile.CountID = 0;
                    this.progressbarCreateTile.Value = 0;
                    Reset();
                    this.tbPathPicture.Text = "";
                    MessageBox.Show("Size of WidthMap >= 32 & HeighMap >= 32");
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (_TileMap == null)
            {
                MessageBox.Show("Map is not value - Please choose a map");
            }
            else if (CTile.CountID == 0)
            {
                IsDouble = true;
                if (((_TileMap.BitMap.Height / CTile.HEIGHT_TILE) * (_TileMap.BitMap.Width / CTile.WIDTH_TILE)) > 500)
                    this.progressbarCreateTile.Maximum = ((_TileMap.BitMap.Height / CTile.HEIGHT_TILE) * (_TileMap.BitMap.Width / CTile.WIDTH_TILE)) - 500;
                else
                    this.progressbarCreateTile.Maximum = ((_TileMap.BitMap.Height / CTile.HEIGHT_TILE) * (_TileMap.BitMap.Width / CTile.WIDTH_TILE));

                _TileMap.CreateTileMap(this.progressbarCreateTile);
                WriteAFileMatrix();
                GetATileMap();
                this.tbAmoutTiles.Text = _TileMap.TileMap.Count.ToString();
                this.tbWidth.Text = (_TileMap.TileMap.Count * CTile.WIDTH_TILE).ToString();
                this.tbHeight.Text = CTile.HEIGHT_TILE.ToString();
                this.pbTileMapPic.Image = _TileMapPicture;
            }
            else if(IsDouble == true)
            {
                MessageBox.Show("This map was read - Please choose other map");
            }
        }

        private void pbSourceImage_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void WriteAFileMatrix()
        {
            StreamWriter _writeFile = new StreamWriter("array.map");
            _writeFile.WriteLine(_TileMap.BitMap.Width);
            _writeFile.WriteLine(_TileMap.BitMap.Height);
            
            _writeFile.WriteLine(_TileMap.BitMap.Height / CTile.HEIGHT_TILE);
            _writeFile.WriteLine(_TileMap.BitMap.Width / CTile.WIDTH_TILE);

            for (int i = 0; i < _TileMap.BitMap.Height / CTile.HEIGHT_TILE; ++i)
            {
                for (int j = 0; j < _TileMap.BitMap.Width / CTile.WIDTH_TILE; ++j)
                {
                    _writeFile.Write(_TileMap.ArrMap[i, j] + "\t");
                }

                _writeFile.WriteLine();
            }

            _writeFile.Close();
        }

        private void GetATileMap()
        {
            _TileMapPicture = new Bitmap(_TileMap.TileMap.Count * CTile.WIDTH_TILE, CTile.HEIGHT_TILE);

            int _OffSetX = 0;
            int _OffSetY = 0;
            for (int i = 0; i < _TileMap.TileMap.Count; ++i)
            {
                _OffSetX = _TileMap.TileMap[i].ID;
                _TileMap.TileMap[i].ExportBitMap(_OffSetX, _OffSetY, _TileMapPicture);
            }

            _TileMapPicture.Save("tilemap.png");
        }

        private void pnTileMapPic_Paint(object sender, PaintEventArgs e)
        {

        }

        private void Reset()
        {
            tbAmoutTiles.Text = "";
            tbWidth.Text = "";
            tbHeight.Text = "";
            pbTileMapPic.Image = null;
            IsDouble = false;
        }
    }
}
