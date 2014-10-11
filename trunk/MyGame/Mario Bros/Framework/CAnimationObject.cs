using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Mario_Bros.Algorithm;

namespace Mario_Bros.Framework
{
    public enum DirectCollision
    { 
        LEFT,
        RIGHT,
        TOP,
        BOTTOM,
        NONE
    }

    public enum IDDir
    {
        LEFT,RIGHT,BOTTOM,TOP,
    }

    public class CAnimationObject : CObject
    {
        protected Vector2 m_Velocity;
        protected Vector2 m_Accel;
        protected float m_Gravity;
        private float m_GameTime;
        protected IDDir m_Direction;

        public float m_MoveX;
        public float m_MoveY;



        public Vector2 Velocity
        {
            get { return m_Velocity; }
            set { m_Velocity = value; }
        }

        public Vector2 Accel
        {
            get { return m_Accel; }
            set { m_Accel = value; }
        }
        
        public float Gravity
        {
            get { return m_Gravity; }
            set { m_Gravity = value; }
        }

        // lấy vùng khoanh hình chữ nhật xung quanh đối tượng
        public Rectangle GetBound()
        {
            return new Rectangle((int)Position.X, (int)Position.Y, Sprite.FrameWidht, Sprite.FrameHeight);
        }

        // lấy thuộc tính Box để cài đặt sweptAABB
        public Box GetBox()
        {
            return new Box((float)GetBound().X, (float)GetBound().Y, (float)GetBound().Width, (float)GetBound().Height, m_Velocity.X * m_GameTime, m_Velocity.Y * m_GameTime);
        }

        // lấy thuộc tính Box có tham số là velocity, dùng để trừ hai vận tốc
        public Box GetBox(Vector2 velocity)
        {
            return new Box((float)GetBound().X, (float)GetBound().Y, (float)GetBound().Width, (float)GetBound().Height, velocity.X * m_GameTime, velocity.Y * m_GameTime);
        }

        // chuyển từ Box sang Broadphase dùng để khoanh vùng đối tượng
        public Box BoxToBroadPhase(Box b)
        {
            return SweptAABB.GetBroadPhaseBox(b);
        }

        public CAnimationObject(Vector2 _Position) : base(_Position)
        {
            m_Velocity = Vector2.Zero;
            m_Accel = Vector2.Zero;
            m_Gravity = 0.0f;
            m_MoveX = 0.0f;
            m_MoveY = 0.0f;
        }

        public DirectCollision CheckCollision(CAnimationObject _Object)
        {
            #region. Thuật toán sweptAABB cũ
            //float DisMinX, DisMaxX;
            //float DisMinY, DisMaxY;

            //Vector2 tempVelocity;
            //tempVelocity = new Vector2(m_Velocity.X - _Object.Velocity.X, m_Velocity.Y - _Object.Velocity.Y);
            //if (tempVelocity.X > 0.0f)
            //{
            //    DisMinX = _Object.Position.X - (Position.X + m_Sprite.FrameWidht);
            //    DisMaxX = (_Object.Position.X + _Object.Sprite.FrameWidht) - (Position.X);
            //}
            //else
            //{
            //    DisMinX = (_Object.Position.X + _Object.Sprite.FrameWidht) - (Position.X);
            //    DisMaxX = _Object.Position.X - (Position.X + m_Sprite.FrameWidht);
            //}

            //if (tempVelocity.Y > 0.0f)
            //{
            //    DisMinY = _Object.Position.Y - (Position.Y + m_Sprite.FrameHeight);
            //    DisMaxY = (_Object.Position.Y + _Object.Sprite.FrameHeight) - (Position.Y);
            //}
            //else
            //{
            //    DisMinY = (_Object.Position.Y + _Object.Sprite.FrameHeight) - (Position.Y);
            //    DisMaxY = _Object.Position.Y - (Position.Y + m_Sprite.FrameHeight);
            //}

            //float EntryTimeX, ExitTimeX;
            //float EntryTimeY, ExitTimeY;

            //if (m_Velocity.X == 0.0f)
            //{
            //    EntryTimeX = float.NegativeInfinity;
            //    ExitTimeX = float.PositiveInfinity;
            //}
            //else
            //{
            //    EntryTimeX = DisMinX / (tempVelocity.X * m_GameTime);
            //    ExitTimeX = DisMaxX / (tempVelocity.X * m_GameTime);
            //}

            //if (m_Velocity.Y == 0.0f)
            //{
            //    EntryTimeY = float.NegativeInfinity;
            //    ExitTimeY = float.PositiveInfinity;
            //}
            //else
            //{
            //    EntryTimeY = DisMinY / (tempVelocity.Y * m_GameTime);
            //    ExitTimeY = DisMaxY / (tempVelocity.Y * m_GameTime);
            //}

            //if (m_Velocity.X == 0.0f && _Object.Velocity.X != 0)
            //{
            //    EntryTimeX = DisMinX / (tempVelocity.X * m_GameTime);
            //    ExitTimeX = DisMaxX / (tempVelocity.X * m_GameTime);
            //}

            //if (m_Velocity.Y == 0.0f && _Object.Velocity.Y != 0)
            //{
            //    EntryTimeY = DisMinY / (tempVelocity.Y * m_GameTime);
            //    ExitTimeY = DisMaxY / (tempVelocity.Y * m_GameTime);
            //}

            //float EntryTime;
            //float ExitTime;

            //EntryTime = Math.Max(EntryTimeX, EntryTimeY);
            //ExitTime = Math.Min(ExitTimeX, ExitTimeY);

            //if (EntryTime > ExitTime)
            //    return DirectCollision.NONE;
            //if (EntryTimeX < 0.0f && EntryTimeY < 0.0f)
            //    return DirectCollision.NONE;
            //if (EntryTimeX > 1.0f || EntryTimeY > 1.0f)
            //    return DirectCollision.NONE;

            //if (EntryTimeX < 0.0f)
            //{
            //    if (Position.X + Sprite.FrameWidht < _Object.Position.X || Position.X > _Object.Position.X + _Object.Sprite.FrameWidht)
            //        return DirectCollision.NONE;
            //}
            //if (EntryTimeY < 0.0f)
            //{
            //    if (Position.Y + Sprite.FrameHeight < _Object.Position.Y || Position.Y > _Object.Position.Y + _Object.Sprite.FrameHeight)
            //        return DirectCollision.NONE;
            //}


            //if (EntryTimeX > EntryTimeY && Position.Y + Sprite.FrameHeight != _Object.Position.Y)
            //{
            //    if (DisMinX < 0.0f)
            //    {
            //        return DirectCollision.RIGHT;
            //    }
            //    else
            //    {
            //        return DirectCollision.LEFT;
            //    }
            //}
            //else
            //{
            //    if (DisMinY < 0.0f)
            //    {
            //        return DirectCollision.BOTTOM;
            //    }
            //    else
            //    {
            //        return DirectCollision.TOP;
            //    }
            //}
            #endregion

            float moveX = 0.0f;
            float moveY = 0.0f;
            float normalX = 0.0f;
            float normalY = 0.0f;
            float timeCollsion = 0.0f;
            Vector2 velocity = Vector2.Zero;

            // kiểm tra 2 vật có va chạm với nhau không (không tính trường hợp có vận tốc)
            if (SweptAABB.CheckAABB(this.GetBox(), _Object.GetBox(), ref moveX, ref moveY) == false)
            {
                // nếu vật thứ 2 có vận tốc thì ta trừ vận tốc với nhau, xem vật thứ 2 là vật tĩnh
                velocity = new Vector2(this.Velocity.X - _Object.Velocity.X, this.Velocity.Y - _Object.Velocity.Y);
                // kiểm tra xem vật thứ 2 có nằm trong vùng di chuyển của vật 1 hay không ?
                if (SweptAABB.CheckAABB(this.BoxToBroadPhase(GetBox(velocity)), _Object.GetBox(), ref moveX, ref moveY) == true)
                {
                    // chạy sweptAABB, nếu có khả năng xảy ra va chạm
                    timeCollsion = SweptAABB.Swept_AABB(GetBox(velocity), _Object.GetBox(), ref normalX, ref normalY);
                    if (timeCollsion < 1.0f && timeCollsion > 0.0f)
                    {
                        if (Math.Abs(m_MoveX) >= Math.Abs(velocity.X * m_GameTime * timeCollsion + normalX))
                        {
                            m_MoveX = velocity.X * m_GameTime * timeCollsion + normalX;
                        }

                        if (Math.Abs(m_MoveY) >= Math.Abs(velocity.Y * m_GameTime * timeCollsion + normalY))
                        {
                            m_MoveY = velocity.Y * m_GameTime * timeCollsion + normalY; // trong collision tao lam += move Y ma, ko chuyên position
                        }

                        if (normalX != 0)
                        {
                            if (moveX != 0)
                            {
                                if (normalX == 1)
                                {
                                    return DirectCollision.RIGHT;
                                }
                                else if (normalX == -1)
                                {
                                    return DirectCollision.LEFT;
                                }
                            }
                        }
                        else
                        {
                            if (moveY != 0)
                            {
                                if (normalY == -1)
                                {
                                    return DirectCollision.TOP;
                                }
                                else if (normalY == 1)
                                {
                                    return DirectCollision.BOTTOM;
                                }
                            }
                        }
                    }
                }
                else
                {
                    // làm cái gì đó tùy thích !!!!!
                }
            }
            else
            {
                m_MoveX = moveX;
                m_MoveY = moveY;

                //if (m_MoveX <= moveX)
                //    m_MoveX = moveX;

                //if (m_MoveY <= moveY)
                //    m_MoveY = moveY;

                if (moveX != 0)
                {

                    if (moveX < 0.0f)
                    {
                        return DirectCollision.LEFT;
                    }
                    else
                    {
                        return DirectCollision.RIGHT;
                    }
                }
                else if (moveY != 0)
                {

                    if (moveY <= 0.0f)
                    {
                        return DirectCollision.TOP;
                    }
                    else
                    {
                        return DirectCollision.BOTTOM;
                    }
                }
                else
                {
                    if ((GetBound().X + GetBound().Width == _Object.GetBound().X && GetBound().Y + GetBound().Height == _Object.GetBound().Y)
                        || (GetBound().X == _Object.GetBound().X + _Object.GetBound().Width && GetBound().Y + GetBound().Height == _Object.GetBound().Y))
                        return DirectCollision.NONE;

                    if (GetBound().Y + GetBound().Height == _Object.GetBound().Y)
                    {
                        m_Position.Y -= 0.0001f;
                        return DirectCollision.TOP;
                    }
                    else if (_Object.GetBound().Y + _Object.GetBound().Height == GetBound().Y)
                    {
                        m_Position.Y += 0.0001f;
                        return DirectCollision.BOTTOM;
                    }
                    else if (GetBound().X + GetBound().Width == _Object.GetBound().X)
                    {
                        m_Position.X -= 0.0001f;
                        return DirectCollision.LEFT;
                    }
                    else if (_Object.GetBound().X + _Object.GetBound().Width == GetBound().X)
                    {
                        m_Position.X += 0.0001f;
                        return DirectCollision.RIGHT;
                    }
                }
            }

            return DirectCollision.NONE;
        }

        public void Update(GameTime _GameTime, CInput _Input)
        {

            m_GameTime = (float)_GameTime.ElapsedGameTime.TotalMilliseconds;
            m_Position.X += m_Velocity.X * (float) _GameTime.ElapsedGameTime.TotalMilliseconds;
            m_Position.Y += m_Velocity.Y * (float) _GameTime.ElapsedGameTime.TotalMilliseconds;
            m_Velocity.X += m_Accel.X * (float) _GameTime.ElapsedGameTime.TotalMilliseconds;
            m_Velocity.Y += m_Accel.Y * (float)_GameTime.ElapsedGameTime.TotalMilliseconds;
        }
    }
}
