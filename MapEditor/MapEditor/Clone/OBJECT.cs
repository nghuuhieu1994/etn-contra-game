using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace MapEditor.Framwork
{
    public partial class OBJECT
    {
        /// <summary>
        /// Type
        /// 0: tilemap
        /// 1: virtual object
        /// 2: static object (v = 0)
        /// 3: dynamic object (v != 0)
        /// </summary>
        
        private int mType;
        private int mID;
        private VECTOR2D mPosition;
        private RECTANGLE mBound;
        private Image mImage;
        private RECTANGLE mRangeOfMovement;

        public RECTANGLE RangeOfMovement
        {
            get { return mRangeOfMovement; }
            set { mRangeOfMovement = value; }
        }
        private int mIndex;

        public int Index
        {
            get { return mIndex; }
            set { mIndex = value; }
        }

        public int Type
        {
            get { return mType; }
            set { mType = value; }
        }
        public int ID
        {
            get { return mID; }
            set { mID = value; }
        }
        public VECTOR2D Position
        {
            get { return mPosition; }
            set { mPosition = value; }
        }
        public RECTANGLE Bound
        {
            get { return new RECTANGLE(mBound.cX - mBound.width / 2, mBound.cY + mBound.height / 2, mBound.width, mBound.height); }
            set { mBound = value; }
        }
        public Image image
        {
            get { return mImage;}
            set { mImage = value; }
        }

        public OBJECT()
        {
            this.mType = -1;
            this.mID = -1;
            this.mPosition = new VECTOR2D(0, 0);
            this.mBound = new RECTANGLE(0, 0, 0, 0);
            this.mImage = null;
        }

        public OBJECT(int _type, int _id, int _index, VECTOR2D _position, RECTANGLE _bound)
        {
            this.mType = _type;
            this.mID = _id;
            this.mIndex = _index;
            this.mPosition = _position;
            this.mBound = _bound;

            if ((ObjectType)_type == ObjectType.TILE_MAP)
            {
                this.mImage = new Image();

                // Set atribute for image object
                if (Support.map != null)
                {
                    BitmapSource bmpSource;
                    JpegBitmapEncoder bmpCreate = new JpegBitmapEncoder();

                    byte[] arrPixel = new byte[((Support.WIDTH_OF_TILE * Support.map.BitMap.Format.BitsPerPixel) / 8) * Support.HEIGHT_OF_TILE];
                    Support.map.TileMap[this.mID].ExportBitMap(0, 0, arrPixel, (Support.WIDTH_OF_TILE * Support.map.BitMap.Format.BitsPerPixel / 8));
                    bmpSource = BitmapSource.Create(Support.WIDTH_OF_TILE, Support.HEIGHT_OF_TILE, 96, 96, Support.map.BitMap.Format, null, arrPixel, ((Support.WIDTH_OF_TILE * Support.map.BitMap.Format.BitsPerPixel) / 8));
                    this.mImage.Source = bmpSource;
                    this.mImage.Width = bmpSource.Width;
                    this.mImage.Height = bmpSource.Height;
                    this.mImage.Tag = this.mType;
                }
            }

            if (Support.IsDynamic((ObjectID)this.mID) && (ObjectType)(this.mType) == (ObjectType.NORMAL_OBJECT))
            {
                this.mRangeOfMovement = new RECTANGLE(this.mBound.cX, this.mBound.cY, this.mBound.width + 600, this.mBound.height + 600);
            }
            else
            {
                this.mRangeOfMovement = new RECTANGLE(this.mBound.cX - this.mBound.width / 2, this.mBound.cY + this.mBound.height / 2, this.mBound.width, this.mBound.height);
            }
        }

    }
}
