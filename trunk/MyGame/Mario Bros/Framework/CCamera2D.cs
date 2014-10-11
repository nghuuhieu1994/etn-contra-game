using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Mario_Bros.Framework
{
    class CCamera2D
    {
        Vector2 m_Position; // vị trí camera

        Vector2 viewSize; // kích thước camera

        public CCamera2D(Game _game)
        {
            viewSize = new Vector2(_game.GraphicsDevice.Viewport.Width, _game.GraphicsDevice.Viewport.Height);
            m_Position = new Vector2(0, 0); // vị trí nằm chính giữa màn hình
        }

        public Rectangle Rectangle
        {
            get { return new Rectangle((int)(m_Position.X), (int)(m_Position.Y), (int)viewSize.X, (int)viewSize.Y); }
            // so sánh rectangle lấy vị trí top-left
        }

        public void Update(CAnimationObject _Object, int _WidthMap, int _HeightMap)
        {
            //if (_Object.Velocity.X > 0.0f)
            float _positionX;
            _positionX = m_Position.X;
             m_Position.X = _Object.Position.X - viewSize.X / 2;


             if (m_Position.X >= _WidthMap - viewSize.X) // điểm dừng trong con mario
             {
                   m_Position.X = _WidthMap - viewSize.X;
                    
             }

            m_Position.Y = _Object.Position.Y - viewSize.Y / 3;

            if (m_Position.Y >= _HeightMap - viewSize.Y)
                m_Position.Y = _HeightMap - viewSize.Y;
            if (m_Position.Y <= 0.0f)
                m_Position.Y = 0;
            
            if (m_Position.X < 0)
                m_Position.X = 0;

            if (_Object.Position.X < m_Position.X)
            {
                
            }
            GlobalValue.CAMERA_RECTANGLE = new Rectangle((int)m_Position.X, (int)m_Position.Y, (int)viewSize.X, (int)viewSize.Y);
        }

        public Matrix get_matrix_transform()
        {
            Matrix transform;
            transform = Matrix.Identity * Matrix.CreateTranslation(new Vector3(-m_Position.X, -m_Position.Y, 0)) *
                Matrix.CreateTranslation(new Vector3(1.0f, 1.0f, 0));
            return transform;
        }
    }
}
