using Mario_Bros.Framework;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Mario_Bros.Object.Item
{
    public class ItemStarman : CAnimationObject
    {
        private Vector2 oldPosition;

        public ItemStarman(Vector2 _Position)
            : base(_Position)
        {
            m_IDObject = IDObject.ITEM_STARMAN;
            m_Sprite = CResourceManager.GetInstance().GetResource(IDResource.ITEM_STARMAN);
            m_Status = IDStatus.UNACTIVATE;
            Sprite.Depth = GlobalValue.ENEMY_SPRITE_DEPTH;
            oldPosition = _Position;
        }

        public override void UpdateMovement(GameTime _GameTime, CInput _Input)
        {
            if (m_Status == IDStatus.ACTIVATE)
            {
                m_Velocity = new Vector2(0, -0.05f);
            }

            if (oldPosition.Y - m_Position.Y > Sprite.FrameHeight - 1 && m_Status == IDStatus.ACTIVATE)// && Status != IDStatus.UNACTIVATE)//dung animation chay len
            {
                m_Status = IDStatus.RUN;
                m_Velocity = Vector2.Zero;
                Direction = IDDir.RIGHT;
            }

            if (Status == IDStatus.RUN)
            {
                m_Accel.Y = 0.00098f;
                if (Direction == IDDir.LEFT)
                {
                    //m_Status = IDStatus.RUN;
                    m_Velocity = new Vector2(-0.1f, m_Velocity.Y);
                }

                if (Direction == IDDir.RIGHT)
                {
                    //m_Status = IDStatus.RUN;
                    m_Velocity = new Vector2(0.1f, m_Velocity.Y);
                }
            }

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
                    case IDObject.MISC_SOFT_BRICK:
                    //case IDObject.MISC_GATE_PIPE:
                    //case IDObject.MISC_UP_PIPE:
                    case IDObject.MISC_STOCK_PIPE:
                    case IDObject.MISC_HARD_BRICK:
                        if (CheckCollision(_Object) == DirectCollision.TOP)
                        {
                            m_Velocity.Y = -m_Velocity.Y;
                            m_Position.Y = _Object.Position.Y - Sprite.FrameHeight;
                        }
                        else if (CheckCollision(_Object) == DirectCollision.RIGHT)
                        {
                            Direction = IDDir.RIGHT;
                        }
                        else if (CheckCollision(_Object) == DirectCollision.LEFT)
                        {
                            Direction = IDDir.LEFT;
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
