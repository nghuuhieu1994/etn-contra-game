using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Mario_Bros.Framework;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Mario_Bros.Object.Enemy.Boss
{
    public class Boss : CAnimationObject
    {
        //List<BossBullet> List_Of_Bullet;
        float CoolDownFire = 0;
        float CoolDownMove = 0;
        float CoolDownBullet = 0;
        bool CanFire = false;
        float Boss_Heath_Point = 1000;
        //IDDir tempDirection = IDDir.LEFT;
        public Boss(Vector2 _Position)
            : base(_Position)
        {
            IDObject = IDObject.ENEMY_BOSS;
            Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.ENEMY_BOSS));
            Sprite.Depth = GlobalValue.ENEMY_SPRITE_DEPTH;
            //List_Of_Bullet = new List<BossBullet>();
            
            Direction = IDDir.LEFT;
            Status = IDStatus.MOVE;
        }

        public override void UpdateAnimation(GameTime _GameTime, CInput _Input)
        {
            if (Status == IDStatus.MOVE)
            {
                Sprite.Animation.FrameStart = 2;
                Sprite.Animation.FrameEnd = 3;
            }

            if (Status == IDStatus.FIRE)
            {
                Sprite.Animation.FrameStart = 1;
                Sprite.Animation.FrameEnd = 3;
            }

            if (Direction == IDDir.LEFT)
            {
                Sprite.Effect = SpriteEffects.None;
            }

            if (Direction == IDDir.RIGHT)
            {
                Sprite.Effect = SpriteEffects.FlipHorizontally;
            }

            //for (int i = 0; i < List_Of_Bullet.Count; i++)
            //{
            //    List_Of_Bullet[i].UpdateAnimation(_GameTime, _Input);
            //}

            base.UpdateAnimation(_GameTime, _Input);
        }

        bool CoolDown(ref float _CD, float _CDTime, GameTime _GameTime)
        {
            _CD += (float)_GameTime.ElapsedGameTime.TotalMilliseconds;
            if (_CD > _CDTime)
            {
                _CD = 0;
                return true;
            }
            return false;
        }

        public override void UpdateMovement(GameTime _GameTime, CInput _Input)
        {
            //CoolDownFire += (float)_GameTime.ElapsedGameTime.TotalMilliseconds;

            Accel = new Vector2(Accel.X, 0.00098f);

            if (m_Status == IDStatus.MOVE)
            {
                if (Direction == IDDir.LEFT)
                {
                    m_Velocity = new Vector2(-0.03f, m_Velocity.Y);
                }

                if (Direction == IDDir.RIGHT)
                {
                    m_Velocity = new Vector2(0.03f, m_Velocity.Y);
                }
            }

            if (Status == IDStatus.FIRE)
            {
                
                
                Velocity = Vector2.Zero;
                //Direction = tempDirection;
                if (CoolDown(ref CoolDownBullet, 800, _GameTime))
                {
                    //BossBullet b = new BossBullet(new Vector2(this.Position.X, GlobalValue.MARIO_POSITION.Y), this.Direction);
                    //List_Of_Bullet.Add(b);
                    BossBullet b = new BossBullet(new Vector2(this.Position.X, this.Position.Y), this.Direction);
                    GlobalValue.List_Of_Bullet.Add(b);
                }
                if (CoolDown(ref CoolDownFire, 1000, _GameTime))
                {
                    Status = IDStatus.MOVE;
                }
            }

            if (Boss_Heath_Point <= 0)
            {
                Status = IDStatus.DIE;
            }

            if (CoolDown(ref CoolDownMove, 3000, _GameTime) && CanFire)
            {
                Status = IDStatus.FIRE;
            }

            //for (int i = 0; i < List_Of_Bullet.Count; i++)
            //{
            //    List_Of_Bullet[i].UpdateMovement(_GameTime, _Input);
            //}

            base.UpdateMovement(_GameTime, _Input);
            base.Update(_GameTime, _Input); 
        }

        public override void UpdateCollision(CAnimationObject _Object)
        {
            if (_Object.IDObject == IDObject.FIRE_MARIO || _Object.IDObject == IDObject.SMALL_MARIO || _Object.IDObject == IDObject.SUPER_MARIO)
            {
                if (Math.Abs(Position.X - _Object.Position.X) < 368)
                {
                    CanFire = true;
                    if (Position.X > _Object.Position.X && Status == IDStatus.FIRE)
                    {
                        Direction = IDDir.LEFT;
                    }
                    if (Position.X < _Object.Position.X && Status == IDStatus.FIRE)
                    {
                        Direction = IDDir.RIGHT;
                    }
                }
            }

            //for (int i = 0; i < List_Of_Bullet.Count; i++)
            //{
            //    List_Of_Bullet[i].UpdateCollision(_Object);
            //}

            if (CheckCollision(_Object) != DirectCollision.NONE)
            {
                switch (_Object.IDObject)
                {
                    case IDObject.MISC_BASE_BRICK:
                    case IDObject.MISC_IRON_BRICK:
                    case IDObject.MISC_QUESTION_BRICK:
                    case IDObject.MISC_STOCK_PIPE:
                    case IDObject.MISC_HARD_BRICK:
                        if (CheckCollision(_Object) == DirectCollision.TOP)
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
                    case IDObject.FIRE_MARIO:
                    case IDObject.SMALL_MARIO:
                    case IDObject.SUPER_MARIO:
                        if (CheckCollision(_Object) == DirectCollision.BOTTOM && _Object.Status != IDStatus.DIE)
                        {
                            Boss_Heath_Point -= 200;
                            _Object.Velocity = new Vector2(_Object.Velocity.X, -0.35f);
                        }
                        break;
                    case IDObject.BULLET:
                        if (CheckCollision(_Object) != DirectCollision.NONE)
                        {
                            Boss_Heath_Point -= 200;
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
            for (int i = 0; i < GlobalValue.List_Of_Bullet.Count; i++)
            {
                GlobalValue.List_Of_Bullet[i].Draw(_SpriteBatch);
            }
            base.Draw(_SpriteBatch);
        }
    }
}
