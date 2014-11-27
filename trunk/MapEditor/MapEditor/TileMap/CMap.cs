using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using MapEditor;

namespace TileMap
{
    /// <summary>
    /// The code in old version
    /// </summary>
    public class CMap
    {
        #region.Properties
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

        private BitmapSource m_BitMap;

        public BitmapSource BitMap
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

        private byte[] m_ArrColor;

        public byte[] ArrColor
        {
            get { return m_ArrColor; }
            set { m_ArrColor = value; }
        }

        private List<Point> m_ListLedPosition;

        public List<Point> ListLedPosition
        {
            get { return m_ListLedPosition; }
            set { m_ListLedPosition = value; }
        }
        #endregion

        public CMap(BitmapSource _BitMap)
        {
            this.m_BitMap = _BitMap;
            this.m_TileMap = new List<CTile>();
            this.m_ArrMap = new int[(int)(this.m_BitMap.PixelHeight)/ Support.HEIGHT_OF_TILE, (int)(this.m_BitMap.PixelWidth)/ Support.WIDTH_OF_TILE];
            this.m_ArrColor = new byte[((int)(this.m_BitMap.PixelWidth) * this.m_BitMap.Format.BitsPerPixel / 8) * (int)(this.m_BitMap.PixelHeight)];
            this.m_BitMap.CopyPixels(m_ArrColor, ((int)(this.m_BitMap.PixelWidth) * this.m_BitMap.Format.BitsPerPixel) / 8, 0);
            this.m_WidthTileMap = Support.WIDTH_OF_TILE;
            this.m_HeightTileMap = Support.HEIGHT_OF_TILE;
            this.m_ListLedPosition = new List<Point>();
        }

        public void CreateTileMap()
        {
            CTile _Tile = null;

            for (int i = 0; i < (int)(this.m_BitMap.PixelHeight)/ Support.HEIGHT_OF_TILE; ++i)
            {
                for (int j = 0; j < (int)(this.m_BitMap.PixelWidth) / Support.WIDTH_OF_TILE; ++j)
                {
                    _Tile = new CTile(GetTile(j, i), CTile.CountID);

                    if (this.m_TileMap.Count == 0)
                    {
                        this.m_TileMap.Add(_Tile);
                        this.m_ArrMap[i, j] = CTile.CountID;
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
                                ++CTile.CountID;
                            }
                        }
                    }
                }
            }
        }

        public Color[,] GetTile(int _OffSetX, int _OffSetY)
        {
            Color[,] _TempTile = new Color[Support.HEIGHT_OF_TILE, Support.WIDTH_OF_TILE];
            int _IndexI = 0;
            int _IndexJ = 0;
            int tempNew = 0;
            int tempOld = 0;

            for (int i = _OffSetY * Support.HEIGHT_OF_TILE; i < _OffSetY * Support.HEIGHT_OF_TILE + Support.HEIGHT_OF_TILE; ++i)
            {
                for (int j = _OffSetX * Support.WIDTH_OF_TILE; j < _OffSetX * Support.WIDTH_OF_TILE + Support.WIDTH_OF_TILE; ++j)
                {
                    _TempTile[_IndexI, _IndexJ] = Support.GetPixel(j, i, this.m_ArrColor, (int)(this.m_BitMap.PixelWidth)* this.m_BitMap.Format.BitsPerPixel / 8);

                    //if (_TempTile[_IndexI, _IndexJ].A == 255 && _TempTile[_IndexI, _IndexJ].R == 60 && _TempTile[_IndexI, _IndexJ].G == 188 && _TempTile[_IndexI, _IndexJ].B == 253 && _OffSetY < 2)
                    //{
                    //    tempNew = j;
                    //    if(tempNew - tempOld != 1)
                    //    this.m_ListLedPosition.Add(new Point(j, i));
                    //}

                    ++_IndexJ;
                }
                ++_IndexI;
                _IndexJ = 0;
            }

            return _TempTile;
        }
    }
}
