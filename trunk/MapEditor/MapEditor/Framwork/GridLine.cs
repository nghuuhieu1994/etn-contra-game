using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Shapes;

namespace MapEditor.Framwork
{
    public class GridLine
    {
        private static GridLine mInstance;
        public Dictionary<Point, Rectangle> mListElements;
        public int mCols;
        public int mRows;

        private GridLine()
        {
            mListElements = new Dictionary<Point, Rectangle>();
            mCols = 0;
            mRows = 0;
        }

        public static GridLine getInstance()
        {
            if (mInstance == null)
            {
                mInstance = new GridLine();    
            }

            return mInstance;
        }

        public bool CreateGridline()
        {
            if (Support.GRIDLINE == true)
            {
                if (mListElements != null)
                {
                    mCols = (int)Support.WIDHT_MAP / Support.WIDTH_OF_TILE;
                    mRows = (int)Support.HEIGHT_MAP / Support.HEIGHT_OF_TILE;

                    if (mCols > 0 && mRows > 0)
                    {
                        for (int i = 0; i < mRows; ++i)
                        {
                            for (int j = 0; j < mCols; ++j)
                            {
                                /* Create a element to add listElemet */
                                Rectangle tempRect = new Rectangle();
                                tempRect.Tag = Support.gridLine;
                                tempRect.Width = Support.WIDTH_OF_TILE;
                                tempRect.Height = Support.HEIGHT_OF_TILE;
                                tempRect.Stroke = new SolidColorBrush(Colors.Yellow);

                                /* Detect elemet position */
                                Point tempPoint = new Point(j * Support.WIDTH_OF_TILE, i * Support.HEIGHT_OF_TILE);

                                if (tempRect != null)
                                {
                                    mListElements.Add(tempPoint, tempRect);
                                    tempRect = null;
                                    tempPoint.cX = 0;
                                    tempPoint.cY = 0;
                                }
                                else
                                {
                                    return false;
                                }
                            }
                        }
                    }
                    else
                    {
                        return false;
                    }
                }

                return true;
            }

            return false;
        }

        public bool DestroyGridline()
        {
            if (mListElements != null)
            {
                mListElements.Clear();

                if (mListElements.Count == 0)
                {
                    return true;
                }
            }
            
            return false;
        }
    }
}
