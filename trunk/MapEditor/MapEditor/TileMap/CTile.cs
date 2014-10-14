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
    /// The code in old verrsion
    /// </summary>
    public class CTile
    {
        #region.Properties
        public static int CountID = 0;
        private Color[,] m_ArrPixel;
        #endregion

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
            for (int i = 0; i < Support.HEIGHT_OF_TILE; ++i)
            {
                for (int j = 0; j < Support.WIDTH_OF_TILE; ++j)
                {
                    if (_paraFirst.ArrPixel[i, j] != _paraSecond.ArrPixel[i, j])
                        return false;
                }
            }

            return true;
        }

        public void ExportBitMap(int _OffSetX, int _OffSetY, byte[] _bmp, int _stride)
        {
            int _IndexI = 0;
            int _IndexJ = 0;

            for (int i = _OffSetY * Support.HEIGHT_OF_TILE; i < _OffSetY * Support.HEIGHT_OF_TILE + Support.HEIGHT_OF_TILE; ++i)
            {
                for (int j = _OffSetX * Support.WIDTH_OF_TILE; j < _OffSetX * Support.WIDTH_OF_TILE + Support.WIDTH_OF_TILE; ++j)
                {
                    Support.SetPixel(j, i, this.m_ArrPixel[_IndexI, _IndexJ], _bmp, _stride);
                    ++_IndexJ;
                }
                ++_IndexI;
                _IndexJ = 0;
            }
        }

    }
}
