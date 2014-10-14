using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace TileMap
{
    public class CTile
    {
        public static int WIDTH_TILE = 64;
        public static int HEIGHT_TILE = 64;
        public static int CountID = 0;
        private Color[,] m_ArrPixel;

        public Color[,] ArrPixel
        {
            get { return m_ArrPixel; }
            set { m_ArrPixel = value; }
        }

        private int m_ID;

        public int ID
        {
            get { return m_ID; }
            set { m_ID = value; }
        }

        public CTile(Color[,] _ArrPixel, int _ID)
        {
            this.m_ArrPixel = _ArrPixel;
            this.m_ID = _ID;
        }

        public static bool CompareTile(CTile _paraFirst, CTile _paraSecond)
        {
            for (int i = 0; i < CTile.HEIGHT_TILE; ++i)
            {
                for (int j = 0; j < CTile.WIDTH_TILE; ++j)
                {
                    if (_paraFirst.ArrPixel[i, j] != _paraSecond.ArrPixel[i, j])
                        return false;
                }
            }

            return true;
        }
        
        public void ExportBitMap(int _OffSetX, int _OffSetY, Bitmap _bmp)
        {
            int _IndexI = 0;
            int _IndexJ = 0;

            for (int i = _OffSetY * CTile.HEIGHT_TILE; i < _OffSetY * CTile.HEIGHT_TILE + CTile.HEIGHT_TILE; ++i)
            {
                for (int j = _OffSetX * CTile.WIDTH_TILE; j < _OffSetX * CTile.WIDTH_TILE + CTile.WIDTH_TILE; ++j)
                {
                    _bmp.SetPixel(j, i, this.m_ArrPixel[_IndexI, _IndexJ]);
                    ++_IndexJ;
                }
                ++_IndexI;
                _IndexJ = 0;
            }
        }
    }
}
