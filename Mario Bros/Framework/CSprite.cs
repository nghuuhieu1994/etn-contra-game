using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;

namespace Mario_Bros.Framework
{
    public class CSprite
    {
        private IDResource m_IDResource;
        private Rectangle m_SoureRectangle;
        private int m_TotalFrame;
        private int m_FrameWidth;
        private int m_FrameHeight;
        private int m_Cols;
        private Texture2D m_Texture;
        private CAnimation m_Animation;
        private Vector2 m_Origin;
        private Vector2 m_Position;
        private Color m_Color;
        private float m_Rotation; // Radius;
        private Vector2 m_Scale;
        private SpriteEffects m_Effect;
        private float m_Depth;

        // Danh's code
        public float Alpha = 1;

        #region.Get & Set Propertiese
        public IDResource IDResource
        {
            get { return m_IDResource; }
            set { m_IDResource = value; }
        }

        public Rectangle SoureRectangle
        {
            get { return m_SoureRectangle; }
            set { m_SoureRectangle = value; }
        }

        public int TotalFrame
        {
            get { return m_TotalFrame; }
            set { m_TotalFrame = value; }
        }

        public int FrameWidht
        {
            get { return m_FrameWidth; }
            set { m_FrameWidth = value; }
        }

        public int FrameHeight
        {
            get { return m_FrameHeight; }
            set { m_FrameHeight = value; }
        }

        public int Cols
        {
            get { return m_Cols; }
            set { m_Cols = value; }
        }

        public Texture2D Texture
        {
            get { return m_Texture; }
            set { m_Texture = value; }
        }

        public CAnimation Animation
        {
            get { return m_Animation; }
            set { m_Animation = value; }
        }

        public Vector2 Origin
        {
            get { return m_Origin; }
            set { m_Origin = value; }
        }

        public Vector2 Position
        {
            get { return m_Position; }
            set { m_Position = value; }
        }

        public Color Color
        {
            get { return m_Color; }
            set { m_Color = value; }
        }

        public float Rotation
        {
            get { return m_Rotation; }
            set { m_Rotation = value; }
        }
        /// <summary>
        /// Scale
        /// </summary> 
        public Vector2 Scale
        {
            get { return m_Scale; }
            set { m_Scale = value; }
        }

        public SpriteEffects Effect
        {
            get { return m_Effect; }
            set { m_Effect = value; }
        }

        public float Depth
        {
            get { return m_Depth; }
            set { m_Depth = value; }
        }
        #endregion

        public CSprite(IDResource _IDResouce, int _TotalFrame, int _FrameWidth, int _FrameHeight, int _Cols)
        {
            m_IDResource = _IDResouce;
            m_TotalFrame = _TotalFrame;
            m_FrameWidth = _FrameWidth;
            m_FrameHeight = _FrameHeight;
            m_SoureRectangle = new Rectangle(0, 0, m_FrameWidth, m_FrameHeight);
            m_Cols = _Cols;
            m_Origin = Vector2.Zero;
            m_Position = Vector2.Zero;
            m_Rotation = 0.0f;
            m_Scale = new Vector2(1.0f, 1.0f);
            m_Effect = SpriteEffects.None;  
            m_Depth = 0.0f;
            m_Color = Color.White;
            m_Animation = new CAnimation();
        }

        public CSprite(CSprite _Copy)
        {
            m_IDResource = _Copy.m_IDResource;
            m_SoureRectangle = _Copy.m_SoureRectangle;
            m_FrameWidth = _Copy.m_FrameWidth;
            m_FrameHeight = _Copy.m_FrameHeight;
            m_Cols = _Copy.m_Cols;
            m_Texture = _Copy.m_Texture;
            m_Animation = new CAnimation(_Copy.m_Animation);
            m_Origin = _Copy.m_Origin;
            m_Position = _Copy.m_Position;
            m_Color = _Copy.m_Color;
            m_Rotation = _Copy.m_Rotation;
            m_Scale = _Copy.m_Scale;
            m_Effect = _Copy.m_Effect;
            m_Depth = _Copy.m_Depth;
        }

        public void Init(ContentManager _ContentManager, string _FilePath, int _FrameStart, int _FrameEnd, float _TimeAnimation)
        { 
            m_Texture = _ContentManager.Load<Texture2D>(_FilePath);
            m_Animation.CreateAnimation(m_IDResource, _FrameStart, _FrameEnd, _TimeAnimation);
        }
        
        public void UpdateAnimation(GameTime _GameTime)
        {
            if (m_Animation.TimeAnimation == 0.0f)
                Update();
            else
            {
                m_Animation.UpdateAnimation(_GameTime, ref m_SoureRectangle, m_FrameWidth, m_FrameHeight, m_Cols);
            }
        }

        public void Update()
        { 
            m_SoureRectangle.X = m_Animation.CurFrame % m_Cols * m_FrameWidth;
            m_SoureRectangle.Y = m_Animation.CurFrame / m_Cols * m_FrameHeight;
        }

        public void Update(GameTime _GameTime, int _CurFrame)
        {
            m_SoureRectangle.X = _CurFrame % m_Cols * m_FrameWidth;
            m_SoureRectangle.Y = _CurFrame / m_Cols * m_FrameHeight;
        }

        public void Draw(SpriteBatch _SPriteBatch)
        {
            _SPriteBatch.Draw(m_Texture, m_Position, m_SoureRectangle, Color*Alpha, m_Rotation, m_Origin, m_Scale, m_Effect, m_Depth);
        }

        public Rectangle GetBounding()
        {
            Rectangle BoundRect;
            BoundRect = new Rectangle(0, 0, m_FrameWidth, m_FrameHeight);
            BoundRect.X =(int) m_Position.X;
            BoundRect.Y = (int)m_Position.Y;
            return BoundRect;
        }
    }
}
