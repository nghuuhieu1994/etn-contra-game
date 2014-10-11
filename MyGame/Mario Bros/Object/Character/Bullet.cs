using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Mario_Bros.Framework;
using Microsoft.Xna.Framework;

namespace Mario_Bros.Object
{
    public class Bullet : CAnimationObject
    {
        private bool isContact = false;

        public Bullet(Vector2 _Position, IDDir _Dir)
            : base(_Position)
        {
            m_IDObject = IDObject.BULLET;
            m_Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.BULLET));
            Direction = _Dir;
            Sprite.Depth = GlobalValue.MARIO_SPRITE_DEPTH;
        }

        public override void UpdateAnimation(GameTime _GameTime, CInput _Input)
        {
            m_Sprite.Animation.FrameStart = 0;
            m_Sprite.Animation.FrameEnd = 3;
            m_Sprite.Animation.TimeAnimation = 80.0f;
            base.UpdateAnimation(_GameTime, _Input);
        }

        public override void UpdateMovement(GameTime _GameTime, CInput _Input)
        {
            m_Accel = new Vector2(0.0f, 0.00098f);
            if (Direction == IDDir.RIGHT)
                m_Velocity.X = 0.25f;
            if (Direction == IDDir.LEFT)
                m_Velocity.X = -0.25f;

            if (m_Velocity.Y > 0.5f)
                m_Velocity.Y = 0.5f;
            if (m_Velocity.Y < -0.2f)
                m_Velocity.Y = -0.2f;
            base.Update(_GameTime, _Input);
        }

        public override void UpdateCollision(CAnimationObject _Object)
        {
            if (CheckCollision(_Object) != DirectCollision.NONE)
            {
                switch (_Object.IDObject)
                {
                    case IDObject.MISC_BASE_BRICK:
                    case IDObject.MISC_GATE_PIPE:
                    case IDObject.MISC_STOCK_PIPE:
                    case IDObject.MISC_UP_PIPE:
                    case IDObject.MISC_SOFT_BRICK:
                    case IDObject.MISC_HARD_BRICK:
                        if (CheckCollision(_Object) == DirectCollision.TOP)
                        {
                            m_Velocity.Y = -0.1f;
                            break;
                        }
                        if (CheckCollision(_Object) == DirectCollision.RIGHT || CheckCollision(_Object) == DirectCollision.LEFT)
                        {
                            Status = IDStatus.DIE;
                            break;
                        }
                        break;
                    case IDObject.ENEMY_KOOPA_OW:
                    case IDObject.ENEMY_GOOMBA_OW:
                        if (CheckCollision(_Object) != DirectCollision.NONE && _Object.Status != IDStatus.SHOOTED)
                        {
                            _Object.Status = IDStatus.SHOOTED;
                            if (!isContact)
                            {
	                            SoundManager.PlaySound(ESound.SFX_KICK);
                                isContact = true;
                            }
                            _Object.Velocity = new Vector2(0, -0.2f);
                            Status = IDStatus.DIE;
                            break;
                        }
                        break;
                    //case IDObject.MISC_HARD_BRICK:
                    //    if (CheckCollision(_Object) == DirectCollision.RIGHT || CheckCollision(_Object) == DirectCollision.LEFT)
                    //    {
                    //        Status = IDStatus.DIE;
                    //        break;
                    //    }
                    //    if (CheckCollision(_Object) == DirectCollision.TOP)
                    //    {
                    //        m_Velocity.Y = -0.1f;
                    //        break;
                    //    }
                    //    break;
                    //case IDObject.MISC_STOCK_PIPE:
                    //    if (CheckCollision(_Object) == DirectCollision.RIGHT || CheckCollision(_Object) == DirectCollision.LEFT || CheckCollision(_Object) == DirectCollision.TOP)
                    //    {
                    //        Status = IDStatus.DIE;
                    //        break;
                    //    }
                    //    break;
                    case IDObject.ENEMY_BOSS:
                        if (CheckCollision(_Object) == DirectCollision.TOP || CheckCollision(_Object) == DirectCollision.BOTTOM || CheckCollision(_Object) == DirectCollision.RIGHT || CheckCollision(_Object) == DirectCollision.LEFT && _Object.Status != IDStatus.SHOOTED)
                        {
                            if (!isContact)
                            {
	                            SoundManager.PlaySound(ESound.SFX_KICK);
                                isContact = true;
                            }
                            Status = IDStatus.DIE;
                            break;
                        }
                        break;
                    default:
                        break;
                }
            }
            base.UpdateCollision(_Object);
        }
    }
}
