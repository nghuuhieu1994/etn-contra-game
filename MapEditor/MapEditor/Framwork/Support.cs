using MapEditor.Algorithm;
using MapEditor.Framwork;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;
using System.Windows.Shapes;
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

        public static RECTANGLE Intersec(RECTANGLE r1, RECTANGLE r2)
        {
            RECTANGLE rect = new RECTANGLE(0, 0, 0, 0);

            if (r1.cX <= r2.cX) // r1 ben trai r2
            {
                rect.cX = r2.cX;
                if (r2.cX + r2.width < r1.cX + r1.width) // th r2 nho hon r1 va nam trong r1
                {
                    rect.width = r2.width;
                }
                else
                {
                    rect.width = (int)((r1.cX + r1.width) - r2.cX);
                }
            }
            else
            {
                rect.cX = r1.cX;
                if (r1.cX + r1.width < r2.cX + r2.width)
                {
                    rect.width = r1.width;
                }
                else
                {
                    rect.width = (int)((r2.cX + r2.width) - r1.cX);
                }
            }

            //if (r2.cY <= r1.cY) // r1 ben tren r2
            //{
            //    rect.cY = r2.cY;
            //    if (r1.cY + r1.height > r2.cY + r2.height)
            //    {
            //        rect.height = r1.height;
            //    }
            //    else
            //    {
            //        rect.height = (int)(r1.cY - (r2.cY + r2.height));
            //    }
            //}
            //else
            //{
            //    rect.cY = r1.cY;
            //    if (r2.cY + r2.height > r1.cY + r1.height)
            //    {
            //        rect.height = r2.height;
            //    }
            //    else
            //    {
            //        rect.height= (int)(r2.cY - (r1.cY + r1.height));
            //    }
            //}

            if (r1.cY <= r2.cY)
            {
                rect.cY = r1.cY;
                if (r1.cY - r1.height > r2.cY - r2.height)
                {
                    rect.height = r1.height;
                }
                else
                {
                    rect.height = (int)(r1.cY - (r2.cY - r2.height));
                }
            }
            else
            {
                rect.cY = r2.cY;
                if (r2.cY - r2.height > r1.cY - r1.height)
                {
                    rect.height = r2.height;
                }
                else
                {
                    rect.height = (int)(r2.cY - (r1.cY - r1.height));
                }
            }

            if (rect.width <= 0 || rect.height <= 0)
            {
                return new RECTANGLE(0, 0, 0, 0);
            }
            else
            {
                return rect;
            }
        }

        public static RECTANGLE IntersectCanvas(RECTANGLE r1, RECTANGLE r2)
        {
            RECTANGLE rect = new RECTANGLE(0, 0, 0, 0);
            if (r1.cX <= r2.cX)
            {
                rect.cX = r2.cX;
                if (r2.cX + r2.width < r1.cX + r1.width)
                {
                    rect.width = r2.width;
                }
                else
                {
                    rect.width = (int)(r1.cX + r1.width - r2.cX);
                }
            }
            else
            {
                rect.cX = r1.cX;
                if (r1.cX + r1.width < r2.cX + r2.width)
                {
                    rect.width = r1.width;
                }
                else
                {
                    rect.width = (int)(r2.cX +  r2.width - r1.cX);
                }
            }


            if (r1.cY <= r2.cY)
            {
                rect.cY = r2.cY;
                if (r1.cY + r1.height > r2.cY + r2.height)
                {
                    rect.height = r2.height;
                }
                else
                {
                    rect.height = (int)(r1.cY + r1.height - r2.cY);
                }
            }
            else
            {
                rect.cY = r1.cY;
                if (r2.cY + r2.height > r1.cY + r1.height)
                {
                    rect.height = r1.height;
                }
                else
                {
                    rect.height = (int)(r2.cY + r2.height - r1.cY);
                }
            }

            if (rect.width <= 0 || rect.height <= 0)
            {
                return new RECTANGLE(0, 0, 0, 0);
            }
            else
            {
                return rect;
            }
        }

        public bool IsContain(System.Windows.Point point)
        {
            if (cX <= point.X && cX + width >= point.X && cY <= point.Y && cY + height >= point.Y)
            {
                return true;
            }
            return false;
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

    public enum ObjectType
    {
        TILE_MAP = 0,
        VIRTUAL_OBJECT = 1,
        LED_OBJECT = 2,
        GRID_LINE = 3,
        NORMAL_OBJECT = 4,
    }

    public enum ObjectID
    {
        TILE_BASE,
        VIRTUAL_OBJECT_WATER,
        RAMBO,
        BULLET_RAMBO,
        BULLET_ENEMY,
        SNIPER_STANDING,
        SNIPER_HIDING,
        WEAPON_SENSOR, WEAPON_CAPSULE,
        OBJECT_BARRIER, OBJECT_FLAME_GUN, OBJECT_LASER_GUN, OBJECT_MACHINE_GUN, OBJECT_RAPID_GUN, OBJECT_SPREAD_GUN,
        GUN_ROTATING,
        BIG_GUN_ROTATING,
        ENEMY_RUN,
        BOSS_GUN, BOSS_CENTER, BIG_BOSS_1, // Boss Map 1
        BULLET, //  Cai nay de lam gi???
        LED_OBJECT_STAR,
        TILE_BACKGROUND,
        BRIDGE_HEAD, BRIDGE_TAIL, BRIDGE_BODY, BRIDGE,
        VIRTUAL_OBJECT_JUMP,
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
        public static bool IsAlign = false;
        public static int WIDHT_OF_VIRTUALOBJECT = 16;
        public static int HEIGHT_OF_VIRTUALOBJECT = 16;
        public static CNode quadTree = null;
        public static int Count = -1;
        public static Rectangle gridLine = new Rectangle();
        public static Rectangle virtualObject = new Rectangle();
        public static bool IsBackground = false;
        public static bool IsEraser = false;
        public static bool IsVirtualObject = false;
        //public static bool IsPointer = true;
        public static bool IsVirtualWater = false;
        public static bool IsSave = false;
        public static bool IsJump = false;
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

        public static VECTOR2D ConvertCoordination(OBJECT _object)
        {
            VECTOR2D temp = new VECTOR2D(_object.Position.cX, _object.Position.cY);
            temp.cY = (int)(Support.HEIGHT_MAP - _object.Position.cY);
            temp.cX = temp.cX + _object.Bound.width / 2;
            temp.cY = temp.cY - _object.Bound.height / 2;

            return temp;
        }

        public static bool IsDynamic(ObjectID id)
        {
            switch (id)
            {
                case ObjectID.RAMBO:
                case ObjectID.ENEMY_RUN:
                case ObjectID.WEAPON_CAPSULE:
                    return true;
                default:
                    return false;
            }

            return false;
        }
    }
}
