using MapEditor.Framwork;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;
using TileMap;

namespace MapEditor
{
    public struct VECTOR2D
    {
        public float cX;
        public float cY;

        public VECTOR2D(float _X, float _Y)
        {
            this.cX = _X;
            this.cY = _Y;
        }
    }

    public struct RECTANGLE
    {
        public float cX;
        public float cY;
        public int width;
        public int height;

        public RECTANGLE(float _cX, float _cY, int _width, int _height)
        {
            this.cX = _cX;
            this.cY = _cY;
            this.width = _width;
            this.height = _height;
        }
    }

    public struct Point
    {
        public int cX;
        public int cY;

        public Point(int _x, int _y)
        {
            this.cX = _x;
            this.cY = _y;
        }
    }

    public partial class Support
    {
        /* Global Variable Of Program */
        public static string stringPathFile = @"pack://application:,,,/Resource/";
        public static int WIDTH_OF_TILE = 64;
        public static int HEIGHT_OF_TILE = 64;
        public static bool GRIDLINE = false;
        public static int WIDHT_MAP =  896;
        public static int HEIGHT_MAP = 448;
        public static int WIDTH_SCREEN = 800;
        public static int HEIGHT_SCREEN = 600;
        public static CMap map = null;
        public static List<OBJECT> listObject;
        public static bool IsExportXml = false;


        /* Implement Function For Bitmap */
        public static Color GetPixel(int _x, int _y, byte[] _buffer, int _stride)
        {
            if (_buffer != null)
            {
                int indexX = _x * 4;
                int indexY = _y * _stride;

                Color temp = new Color();
                temp.B = _buffer[indexX + indexY + 0];
                temp.G = _buffer[indexX + indexY + 1];
                temp.R = _buffer[indexX + indexY + 2];
                temp.A = _buffer[indexX + indexY + 3];

                return temp;
            }

            Color failTemp = new Color();

            return failTemp;
        }

        public static bool SetPixel(int _x, int _y, Color _color, byte[] _buffer, int _stride)
        {
            if (_buffer != null)
            {
                int indexX = _x * 4;
                int indexY = _y * _stride;

                _buffer[indexX + indexY + 0] = _color.B;
                _buffer[indexX + indexY + 1] = _color.G;
                _buffer[indexX + indexY + 2] = _color.R;
                _buffer[indexX + indexY + 3] = _color.A;

                return true;
            }

            return false;
        }

        public static VECTOR2D ConvertCoordination(VECTOR2D _position)
        {
            VECTOR2D temp = new VECTOR2D(_position.cX, _position.cY);
            temp.cY = Support.HEIGHT_MAP - _position.cY;
            temp.cX = temp.cX + Support.WIDTH_OF_TILE / 2;
            temp.cY = temp.cY - Support.HEIGHT_OF_TILE / 2;
            return temp;
        }
    }
}
