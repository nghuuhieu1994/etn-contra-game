using Mario_Bros.Framework;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Mario_Bros.Object.Item
{
    public class ItemGrowUp : CAnimationObject
    {
        private Vector2 oldPosition;
        private IDDir m_Dir;

        public ItemGrowUp(Vector2 _Position)
            : base(_Position)
        {
            m_IDObject = IDObject.ITEM_GROW_UP;
            m_Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.ITEM_SUPER_MUSHROOM));
            m_Status = IDStatus.UNACTIVATE;
            oldPosition = _Position;
        }

        public override void UpdateMovement(GameTime _GameTime, CInput _Input)
        {
            if (m_IDObject == IDObject.ITEM_SUPER_MUSHROOM)
            {
                if (m_Status == IDStatus.ACTIVATE)
                {
                    m_Velocity = new Vector2(0, -0.01f);
                }

                if (oldPosition.Y - m_Position.Y > Sprite.FrameHeight && m_Status == IDStatus.ACTIVATE)
                {
                    m_Status = IDStatus.RUN;
                    //m_Velocity = Vector2.Zero;
                    m_Dir = IDDir.RIGHT;
                }

                if (m_Status == IDStatus.RUN)
                {
                    m_Accel.Y = 0.00098f;
                    if (m_Dir == IDDir.LEFT)
                    {
                        //m_Status = IDStatus.RUN;
                        m_Velocity = new Vector2(-0.1f, m_Velocity.Y);
                    }

                    if (m_Dir == IDDir.RIGHT)
                    {
                        //m_Status = IDStatus.RUN;
                        m_Velocity = new Vector2(0.1f, m_Velocity.Y);
                    }
                }

                if (m_Velocity.Y > 1.0f)
                    m_Velocity.Y = 1.0f;

                if (m_Velocity.X > 0.1f)
                    m_Velocity.X = 0.1f;

                if (m_Velocity.X < -0.1)
                    m_Velocity.X = -0.1f; 
            }

            if (IDObject == IDObject.ITEM_FIRE_FLOWER)
            {
                if (m_Status == IDStatus.ACTIVATE)
                {
                    m_Velocity = new Vector2(0, -0.01f);
                }

                if (oldPosition.Y - m_Position.Y > Sprite.FrameHeight - 1 && m_Status == IDStatus.ACTIVATE && Status != IDStatus.UNACTIVATE)//dung animation chay len
                {
                    m_Status = IDStatus.ALIVE;
                    m_Velocity = Vector2.Zero;
                }
            }

            base.Update(_GameTime, _Input);
        }

        public override void UpdateCollision(CAnimationObject _Object)
        {
            if (CheckCollision(_Object) != DirectCollision.NONE && m_Status != IDStatus.UNACTIVATE && Status != IDStatus.ACTIVATE)
            {
                switch (_Object.IDObject)
                {
                    //case IDObject.MISC_IRON_BRICK:
                    case IDObject.MISC_BASE_BRICK:
                    case IDObject.MISC_STOCK_PIPE:
                    case IDObject.MISC_QUESTION_BRICK:
                    case IDObject.MISC_SOFT_BRICK:
                    case IDObject.MISC_HARD_BRICK:
                    case IDObject.MISC_GATE_PIPE:
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
                m_Sprite.Depth = GlobalValue.ITEM_SPRITE_DEPTH;
                base.Draw(_SpriteBatch);
            }
        }
    }
}
