using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Windows.Forms;

namespace TileMap
{
    public class CMap
    {
        private List<CTile> m_TileMap;

        public List<CTile> TileMap
        {
            get { return m_TileMap; }
            set { m_TileMap = value; }
        }

        private int[,] m_ArrMap;

        public int[,] ArrMap
        {
            get { return m_ArrMap; }
            set { m_ArrMap = value; }
        }

        private Bitmap m_BitMap;

        public Bitmap BitMap
        {
            get { return m_BitMap; }
            set { m_BitMap = value; }
        }

        private int m_WidthTileMap;

        public int WidthTileMap
        {
            get { return m_WidthTileMap; }
            set { m_WidthTileMap = value; }
        }

        private int m_HeightTileMap;

        public int HeightTileMap
        {
            get { return m_HeightTileMap; }
            set { m_HeightTileMap = value; }
        }

        public CMap(Bitmap _BitMap)
        {
            this.m_BitMap = _BitMap;
            this.m_TileMap = new List<CTile>();
            this.m_ArrMap = new int[this.m_BitMap.Height / CTile.HEIGHT_TILE, this.m_BitMap.Width / CTile.WIDTH_TILE];
            this.m_WidthTileMap = CTile.WIDTH_TILE;
            this.m_HeightTileMap = CTile.HEIGHT_TILE;
        }

        public void CreateTileMap(ProgressBar _progressbarProcess)
        {
            CTile _Tile = null;

            for (int i = 0; i < this.m_BitMap.Height / CTile.HEIGHT_TILE; ++i)
            {
                for (int j = 0; j < this.m_BitMap.Width / CTile.WIDTH_TILE; ++j)
                {
                    _Tile = new CTile(GetTile(j, i), CTile.CountID);

                    if (this.m_TileMap.Count == 0)
                    {
                        this.m_TileMap.Add(_Tile);
                        this.m_ArrMap[i, j] = CTile.CountID;
                        Bitmap a = new Bitmap(CTile.WIDTH_TILE, CTile.HEIGHT_TILE);
                        for (int y = 0; y < CTile.HEIGHT_TILE; y++)
                        {
                            for (int x = 0; x < CTile.WIDTH_TILE; x++)
                            {
                                a.SetPixel(x, y, _Tile.ArrPixel[y, x]);
                            } 
                        }
                        a.Save(CTile.CountID.ToString() + ".png");
                        ++CTile.CountID;
                    }
                    else
                    {
                        for (int k = 0; k < this.m_TileMap.Count; ++k)
                        {
                            if (CTile.CompareTile(_Tile, this.m_TileMap[k]) == true)
                            {
                                this.m_ArrMap[i, j] = this.m_TileMap[k].ID;
                                break;
                            }

                            if (k == this.m_TileMap.Count - 1)
                            {
                                this.m_TileMap.Add(_Tile);
                                this.m_ArrMap[i, j] = CTile.CountID;
                                Bitmap a = new Bitmap(CTile.WIDTH_TILE, CTile.HEIGHT_TILE);
                                for (int y = 0; y < CTile.HEIGHT_TILE; y++)
                                {
                                    for (int x = 0; x < CTile.WIDTH_TILE; x++)
                                    {
                                        a.SetPixel(x, y, _Tile.ArrPixel[y, x]);
                                    }
                                }
                                a.Save(CTile.CountID.ToString() + ".png");
                                ++CTile.CountID;
                            }
                        }
                    }

                    _progressbarProcess.PerformStep();
                }

            }
        }

        public Color[,] GetTile(int _OffSetX, int _OffSetY)
        {
            Color[,] _TempTile = new Color[CTile.HEIGHT_TILE, CTile.WIDTH_TILE];
            int _IndexI = 0;
            int _IndexJ = 0;

            for (int i = _OffSetY * CTile.HEIGHT_TILE; i < _OffSetY * CTile.HEIGHT_TILE + CTile.HEIGHT_TILE; ++i)
            {
                for (int j = _OffSetX * CTile.WIDTH_TILE; j < _OffSetX * CTile.WIDTH_TILE + CTile.WIDTH_TILE; ++j)
                {
                    _TempTile[_IndexI, _IndexJ] = this.m_BitMap.GetPixel(j, i);
                    ++_IndexJ;
                }
                ++_IndexI;
                _IndexJ = 0;
            }

            return _TempTile;
        }
    }
}
