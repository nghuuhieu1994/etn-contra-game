//using Mario_Bros.Framework;
//using Microsoft.Xna.Framework;
//using Microsoft.Xna.Framework.Graphics;
//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;

//namespace Mario_Bros.Object.Enemy
//{
//    public class Koopa : CAnimationObject
//    {
//        float CoolDown = 0;
//        public Koopa(Vector2 _Position)
//            : base(_Position)
//        {
//            m_IDObject = IDObject.ENEMY_KOOPA_OW;
//            m_Position = _Position;
//            m_Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.ENEMY_KOOPA_OW));
//            m_Status = IDStatus.ALIVE;
//            m_Direction = IDDir.RIGHT;
//            Sprite.Depth = GlobalValue.ENEMY_SPRITE_DEPTH;
//        }

//        public override void UpdateAnimation(GameTime _GameTime, CInput _Input)
//        {
//            if (m_Status == IDStatus.ALIVE)
//            {
//                m_Sprite.Animation.FrameStart = 0;
//                Sprite.Animation.FrameEnd = 1;
//            }
//            if (m_Status == IDStatus.SPIN)
//            {
//                //Sprite.FrameHeight = 16;
//                //Sprite.Animation.CurFrame = 4;
//            }
//            if (m_Status == IDStatus.HIDE)
//            {
//                //Sprite.FrameHeight = 16;
//                //Sprite.Animation.SetLocalAnimation();
//                //Sprite.Animation.CurFrame = 4;
//            }

            

//            #region.Chuyển hướng
//            if (Status == IDStatus.ALIVE || Status == IDStatus.SPIN)
//            {
//                if (m_Direction == IDDir.LEFT)
//                {
//                    m_Sprite.Effect = SpriteEffects.None;
//                }
//                if (m_Direction == IDDir.RIGHT)
//                {
//                    m_Sprite.Effect = SpriteEffects.FlipHorizontally;
//                } 
//            }
//            #endregion

//            base.UpdateAnimation(_GameTime, _Input);
//        }

//        private void CheckShooted(GameTime _GameTime)
//        {
//            if (Status == IDStatus.SHOOTED)
//            {
//                Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.ENEMY_HIDE_KOOPA_OW));
//                //Console.WriteLine("xoay hinh");
//                Sprite.Effect = SpriteEffects.FlipVertically;
//                Sprite.Depth = GlobalValue.MARIO_SPRITE_DEPTH;
//            //}
//            //if (Status == IDStatus.SHOOTED)
//            //{
//                m_Accel = new Vector2(0, 0.00098f);
//                CoolDown += (float)_GameTime.ElapsedGameTime.TotalMilliseconds;
//            }
//        }

//        public override void UpdateMovement(GameTime _GameTime, CInput _Input)
//        {
//            // Gia tốc trọng trường
//            if (m_Status == IDStatus.ALIVE)
//            {
//                m_Accel = new Vector2(0, 0.0098f);
//                if (m_Direction == IDDir.LEFT)
//                {
//                    m_Velocity = new Vector2(-0.03f, m_Velocity.Y);
//                }
//                else if (m_Direction == IDDir.RIGHT)
//                {
//                    m_Velocity = new Vector2(0.03f, m_Velocity.Y);
//                }
//            }

//            CheckShooted(_GameTime);

//            if (CoolDown > 600)
//            {
//                Status = IDStatus.DIE;
//            }

//            if (m_Status == IDStatus.SPIN)
//            {
//                if (m_Direction == IDDir.LEFT)
//                {
//                    m_Velocity = new Vector2(-0.2f, m_Velocity.Y);
//                }
//                else if (m_Direction == IDDir.RIGHT)
//                {
//                    m_Velocity = new Vector2(0.2f, m_Velocity.Y);
//                }
//            }

//            if (m_Status == IDStatus.HIDE)
//            {
//                m_Velocity = new Vector2(0, m_Velocity.Y);
//            }
//            //if (_Input.KeyDown(Microsoft.Xna.Framework.Input.Keys.Space))
//            //{
//            //    m_Status = IDStatus.DIE_CAN_ATTACK;
//            //}
//            if (m_Velocity.Y > 1.0f)
//            {
//                m_Velocity.Y = 1.0f;
//            }

//            if (m_Velocity.X > 1f)
//            {
//                m_Velocity.X = 1f;
//            }

//            if (m_Velocity.X < -1f)
//            {
//                m_Velocity.X = -1f;
//            }
//            base.Update(_GameTime, _Input);
//        }

//        public override void UpdateCollision(CAnimationObject _Object)
//        {
//            if (CheckCollision(_Object) != DirectCollision.NONE && Status != IDStatus.SHOOTED && _Object.Index != Index)
//            {
//                switch (_Object.IDObject)
//                {
//                    case IDObject.MISC_BASE_BRICK:
//                    case IDObject.MISC_IRON_BRICK:
//                    case IDObject.MISC_QUESTION_BRICK:
//                    case IDObject.MISC_STOCK_PIPE:
//                        if (CheckCollision(_Object) == DirectCollision.TOP)
//                        {
//                            m_Velocity.Y = 0.0f;
//                            m_Position.Y = _Object.Position.Y - m_Sprite.FrameHeight;
//                            break;
//                        }
//                        else if (CheckCollision(_Object) == DirectCollision.BOTTOM)
//                        {

//                        }
//                        else if (CheckCollision(_Object) == DirectCollision.RIGHT)
//                        {
//                            m_Direction = IDDir.RIGHT;
//                            break;
//                        }
//                        else if (CheckCollision(_Object) == DirectCollision.LEFT)
//                        {
//                            m_Direction = IDDir.LEFT;
//                            break;
//                        }
//                        break;
//                    case IDObject.ENEMY_GOOMBA_OW:
//                    case IDObject.ENEMY_KOOPA_OW:
//                        if (CheckCollision(_Object) == DirectCollision.TOP)
//                        {
//                            m_Velocity.Y = 0.0f;
//                            m_Position.Y = _Object.Position.Y - m_Sprite.FrameHeight;
//                            break;
//                        }
//                        else if (CheckCollision(_Object) == DirectCollision.BOTTOM)
//                        {

//                        }
//                        else if (CheckCollision(_Object) == DirectCollision.RIGHT && Status != IDStatus.SPIN)
//                        {
//                            m_Direction = IDDir.RIGHT;
//                            break;
//                        }
//                        else if (CheckCollision(_Object) == DirectCollision.LEFT && Status != IDStatus.SPIN)
//                        {
//                            m_Direction = IDDir.LEFT;
//                            break;
//                        }
//                        if (CheckCollision(_Object) == DirectCollision.RIGHT || CheckCollision(_Object) == DirectCollision.LEFT && Status == IDStatus.SPIN)
//                        {
//                            _Object.Velocity = new Vector2(0, -0.2f);
//                            _Object.Status = IDStatus.SHOOTED;
//                            break;
//                        }
//                        break;
//                    default:
//                        break;
//                }
//            }
//            //base.UpdateCollision(_Object);
//        }
//    }
//}
