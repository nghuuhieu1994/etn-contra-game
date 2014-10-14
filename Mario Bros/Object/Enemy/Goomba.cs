using Mario_Bros.Framework;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Mario_Bros.Object.Enemy
{
    public class Goomba : CAnimationObject
    {
        private float CoolDown = 0;

        public Goomba(Vector2 _Position,IDDir _Dir)
            : base(_Position)
        {
            m_IDObject = IDObject.ENEMY_GOOMBA_OW;
            m_Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.ENEMY_GOOMBA_OW));
            Direction = _Dir;
            m_Status = IDStatus.ALIVE;
            Sprite.Depth = GlobalValue.ENEMY_SPRITE_DEPTH;
        }

        public override void UpdateAnimation(GameTime _GameTime, CInput _Input)
        {
            if (m_Status == IDStatus.ALIVE)
            {
                m_Sprite.Animation.FrameStart = 0;
                m_Sprite.Animation.FrameEnd = 1;
            }
       
            if (m_Status == IDStatus.BEFORE_DIE)
            {
                m_Sprite.Animation.CurFrame = 2; 
            }

            if (Status == IDStatus.SHOOTED)
            {
                Sprite.Animation.CurFrame = 0;
                Sprite.Effect = SpriteEffects.FlipVertically;
            }

            base.UpdateAnimation(_GameTime, _Input);
        }

        private void CheckShooted(GameTime _GameTime)
        {
            if (Status == IDStatus.SHOOTED)
            {
                Sprite.Animation.CurFrame = 0;
                //Console.WriteLine("xoay hinh");
                Sprite.Effect = SpriteEffects.FlipVertically;
                Sprite.Depth = GlobalValue.MARIO_SPRITE_DEPTH;
                //}
                //if (Status == IDStatus.SHOOTED)
                //{
                m_Accel = new Vector2(0, 0.00098f);
                CoolDown += (float)_GameTime.ElapsedGameTime.TotalMilliseconds;
            }
        }

        public override void UpdateMovement(GameTime _GameTime, CInput _Input)
        {
            
            // Gia tốc trọng trường
            

            //if (Status == IDStatus.SHOOTED)
            //{
            //    m_Velocity.X = 0;
                
            //}
            CheckShooted(_GameTime);
            #region.Nếu mushroom còn sống
            if (m_Status == IDStatus.ALIVE)
            {
                m_Accel = new Vector2(m_Accel.X, 0.0098f);
                if (Direction == IDDir.LEFT)
                {
                    m_Status = IDStatus.ALIVE;
                    m_Velocity = new Vector2(-0.03f, m_Velocity.Y);
                }

                if (Direction == IDDir.RIGHT)
                {
                    m_Status = IDStatus.ALIVE;
                    m_Velocity = new Vector2(0.03f, m_Velocity.Y);
                }
            }
            #endregion

            if (m_Status == IDStatus.BEFORE_DIE)
            {
                m_Velocity = Vector2.Zero;
                CoolDown += (float)_GameTime.ElapsedGameTime.TotalMilliseconds;
            }

            if (CoolDown > 700)
            {
                m_Status = IDStatus.DIE;
            }

            if (m_Velocity.Y > 1f)
                m_Velocity.Y = 1f;

            if (m_Velocity.X > 0.09f)
                m_Velocity.X = 0.09f;

            if (m_Velocity.X < -0.09f)
                m_Velocity.X = -0.09f;

            base.Update(_GameTime, _Input);

        }

        public override void UpdateCollision(CAnimationObject _Object)
        {
            if (CheckCollision(_Object) != DirectCollision.NONE)
            {
                switch (_Object.IDObject)
                { 
                    case IDObject.MISC_BASE_BRICK:
                    case IDObject.MISC_IRON_BRICK:
                    case IDObject.MISC_QUESTION_BRICK:
                    case IDObject.MISC_STOCK_PIPE:
                    case IDObject.MISC_SOFT_BRICK:
                    case IDObject.MISC_GATE_PIPE:
                    case IDObject.MISC_HARD_BRICK:
                        if (CheckCollision(_Object) == DirectCollision.TOP && m_Status != IDStatus.SHOOTED)
                        {
                            m_Velocity.Y = 0.0f;
                            m_Position.Y = _Object.Position.Y - Sprite.FrameHeight;
                            break;
                        }
                        else if (CheckCollision(_Object) == DirectCollision.RIGHT)
                        {
                            Direction = IDDir.RIGHT;
                            break;
                        }
                        else if (CheckCollision(_Object) == DirectCollision.LEFT)
                        {
                            Direction = IDDir.LEFT;
                            break;
                        }
                        else if (CheckCollision(_Object) == DirectCollision.BOTTOM)
                        {
                            
                        }
                        break;
                    //case IDObject.MARIO_FIRE:
                    //    if(CheckCollision(_Object) == DirectCollision.BOTTOM)
                    //         m_Status = IDStatus.BEFORE_DIE;
                    //    break;
                    case IDObject.ENEMY_GOOMBA_OW:
                    case IDObject.ENEMY_KOOPA_OW:
                        //if ((CheckCollision(_Object) == DirectCollision.LEFT || CheckCollision(_Object) == DirectCollision.RIGHT) && _Object.Status == IDStatus.SPIN && Status != IDStatus.SHOOTED)
                        //{
                        //    CResourceManager.GetInstance().GetSoundEffect(IDResource.SFX_KICK).Play();
                        //   // _Object.Velocity = new Vector2(0, -0.2f);
                        //    m_Status = IDStatus.SHOOTED;
                        //}
                        if ((CheckCollision(_Object) == DirectCollision.LEFT || CheckCollision(_Object) == DirectCollision.RIGHT) && (_Object.Status == IDStatus.HIDE || _Object.Status == IDStatus.ALIVE))
                        {
                            if (CheckCollision(_Object) == DirectCollision.RIGHT)
                            {
                                Direction = IDDir.RIGHT;
                            }
                            if (CheckCollision(_Object) == DirectCollision.LEFT)
                            {
                                Direction = IDDir.LEFT;
                            }
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
