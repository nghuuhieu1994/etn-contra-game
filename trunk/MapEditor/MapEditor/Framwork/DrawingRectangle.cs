using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;

namespace MapEditor.Framwork
{
    public class DrawingRectangle
    {
        private bool mIsDragged;
        private Point mStartPosition;
        private Point mLastPosition;
        private int mWidht;
        private int mHeight;

        public DrawingRectangle()
        {
            mIsDragged = false;
            mStartPosition = new Point(0, 0);
            mLastPosition = new Point(0, 0);
            mWidht = 0;
            mHeight = 0;
        }



    }
}
