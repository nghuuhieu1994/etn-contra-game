using Mario_Bros.Framework;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Mario_Bros.Object.Item
{
    public class ItemSuperMushroom: CAnimationObject
    {
        private Vector2 oldPosition;
        private IDDir m_Dir;

        public ItemSuperMushroom(Vector2 _Position)
            : base(_Position)
        {
            m_IDObject = IDObject.ITEM_SUPER_MUSHROOM;
            m_Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.ITEM_SUPER_MUSHROOM));
            m_Status = IDStatus.UNACTIVATE;
            m_Sprite.Depth = 0.1f;
            oldPosition = _Position;
        }

        public override void UpdateMovement(GameTime _GameTime, CInput _Input)
        {
            if (m_Status == IDStatus.ACTIVATE)
            {
                m_Velocity = new Vector2(0, -0.05f);
            }

            if (oldPosition.Y - m_Position.Y > Sprite.FrameHeight && m_Status == IDStatus.ACTIVATE)
            {
                m_Status = IDStatus.RUN;
                //m_Velocity = Vector2.Zero;
                m_Dir = IDDir.RIGHT;
            }

            if (m_Status == IDStatus.RUN)
            {
                m_Accel.Y = 0.0098f;
                if (m_Dir == IDDir.LEFT)
                {
                    //m_Status = IDStatus.RUN;
                    m_Velocity = new Vector2(-0.2f, m_Velocity.Y);
                }

                if (m_Dir == IDDir.RIGHT)
                {
                    //m_Status = IDStatus.RUN;
                    m_Velocity = new Vector2(0.2f, m_Velocity.Y);
                }
            }

            if (m_Velocity.Y > 1.0f)
                m_Velocity.Y = 1.0f;

            if (m_Velocity.X > 0.2f)
                m_Velocity.X = 0.2f;

            if (m_Velocity.X < -0.2)
                m_Velocity.X = -0.2f;

            base.Update(_GameTime, _Input);
        }

        public override void UpdateCollision(CAnimationObject _Object)
        {
            if (CheckCollision(_Object) != DirectCollision.NONE && m_Status != IDStatus.UNACTIVATE)
            {   
                switch (_Object.IDObject)
                {
                    case IDObject.MISC_IRON_BRICK:
                    case IDObject.MISC_BASE_BRICK:
                    case IDObject.MISC_HARD_BRICK:
                        if (CheckCollision(_Object) == DirectCollision.TOP)
                        {
                            m_Velocity.Y = 0.0f;
                            m_Position.Y = _Object.Position.Y - Sprite.FrameHeight;
                        }
                        else if (CheckCollision(_Object) == DirectCollision.RIGHT)
                        {
                            m_Dir = IDDir.RIGHT;
                        }
                        else if (CheckCollision(_Object) == DirectCollision.LEFT)
                        {
                            m_Dir = IDDir.LEFT;
                        }
                        else if (CheckCollision(_Object) == DirectCollision.BOTTOM)
                        {
                            m_Velocity.Y = -m_Velocity.Y;
                        }
                        break;
                    default:
                        break;
                }
            }
            base.UpdateCollision(_Object);
        }

        public override void Draw(SpriteBatch _SpriteBatch)
        {
            if (m_Status != IDStatus.UNACTIVATE)
            {
                base.Draw(_SpriteBatch);
            }
        }
    }
}
