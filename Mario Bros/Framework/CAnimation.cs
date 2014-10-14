using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Mario_Bros.Framework
{
    public class CAnimation
    {
        private IDResource m_IDResouce;
        private int m_FrameStart;
        private int m_FrameEnd;
        private int m_CurFrame;
        private float m_LocalTime;
        private float m_TimeAnimation;
        private int m_NumLoop;

        public IDResource IDResource
        {
            get { return m_IDResouce; }
            set { m_IDResouce = value; }
        }

        public int FrameStart
        {

            get { return m_FrameStart; }
            set { m_FrameStart = value; }
        }

        public int FrameEnd
        {
            get { return m_FrameEnd;}
            set { m_FrameEnd = value; }
        }

        public int CurFrame
        {
            get { return m_CurFrame; }
            set { m_CurFrame = value; }
        }

        public float LocalTime
        {
            get { return m_LocalTime; }
            set { m_LocalTime = value; }
        }

        public float TimeAnimation
        {
            get { return m_TimeAnimation; }
            set { m_TimeAnimation = value; }
        }

        public int NumLoop
        {
            get { return m_NumLoop; }
            set { m_NumLoop = value; }
        }

        public CAnimation()
        { 
            
        }

        public CAnimation(CAnimation _Copy)
        {
            m_IDResouce = _Copy.m_IDResouce;
            m_FrameStart = _Copy.m_FrameStart;
            m_FrameEnd = _Copy.m_FrameEnd;
            m_LocalTime = _Copy.m_LocalTime;
            m_TimeAnimation = _Copy.m_TimeAnimation;
            m_CurFrame = _Copy.m_CurFrame;
            m_NumLoop = _Copy.m_NumLoop;
        }

        public void NextFrame()
        {
            m_CurFrame++;
            if (m_CurFrame > m_FrameEnd)
            {
                m_NumLoop++;
                m_CurFrame = m_FrameStart;
            }
        }

        public void CreateAnimation(IDResource _IDResource, int _FrameStart, int _FrameEnd, float _TimeAnimation)
        {
            m_IDResouce = _IDResource;
            m_FrameStart = _FrameStart;
            m_FrameEnd = _FrameEnd;
            m_CurFrame = _FrameStart;
            m_LocalTime = 0.0f;
            m_TimeAnimation = _TimeAnimation;
            m_NumLoop = 0;
        }

        public void SetLocalAnimation()
        {
            if (m_LocalTime < m_TimeAnimation)
                m_LocalTime = m_TimeAnimation;
        }

        public void UpdateAnimation(GameTime _GameTime, ref Rectangle _SourceRectangle, int _FrameWidth, int _FrameHeight, int _Cols)
        {
            m_LocalTime += (float)_GameTime.ElapsedGameTime.TotalMilliseconds;

            if (m_LocalTime >= m_TimeAnimation)
            {
                _SourceRectangle.X = m_CurFrame % _Cols * _FrameWidth;
                _SourceRectangle.Y = m_CurFrame / _Cols * _FrameHeight;
                _SourceRectangle.Width = _FrameWidth;
                _SourceRectangle.Height = _FrameHeight;

                NextFrame();
                m_LocalTime = 0.0f;
            }
        }
    }
}
