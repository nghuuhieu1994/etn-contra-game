//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using Mario_Bros.Framework;
//using Microsoft.Xna.Framework;
//using Microsoft.Xna.Framework.Graphics;
//using Microsoft.Xna.Framework.Input;
//using Microsoft.Xna.Framework.Media;
//using Mario_Bros.Object.Miscellaneous;


//namespace Mario_Bros.Object
//{
//    //public enum IDDir
//    //{ 
//    //    LEFT,
//    //    RIGHT,
//    //}

//    public class Mario : CAnimationObject
//    {
//        private bool m_IsDisableRight = false;
//        private bool m_IsDisableLeft = false;
//        private bool m_IsDisableUp = false;
//        private bool m_IsDisableDown = false;
//        private bool m_IsLockKeyboard = false;
//        private float m_TimeTeleport = 0;
//        private bool m_IsPlaySoundGate = false;

//        private CAnimationObject Gate;

//        private bool m_IsTeleport = false;

//        public bool IsTeleport
//        {
//            get { return m_IsTeleport; }
//            set { m_IsTeleport = value; }
//        }

//        private float m_CDWining = 0;
//        private List<CSprite> SmallSprite;
//        private List<CSprite> BigSprite;


//        private CSprite tempSprite;
//        private int m_PlayTime;
//        public int PlayTime
//        {
//            get { return m_PlayTime; }
//            set { m_PlayTime = value; }
//        }

//        private bool m_IsJumping;
//        private bool m_IsAttacking;
//        private bool m_IsDuck;

//        public bool IsDuck
//        {
//            get { return m_IsDuck; }
//            set { m_IsDuck = value; }
//        }

//        private bool m_isWorldFreeze;
//        private bool m_isDeath;
//        public bool IsWorldFreeze
//        {
//            get { return m_isWorldFreeze; }
//            set { m_isWorldFreeze = value; }
//        }


//        private bool m_isMarioFreeze = false;

//        public bool IsMarioFreeze
//        {
//            get { return m_isMarioFreeze; }
//            set { m_isMarioFreeze = value; }
//        }

//        private float CDFreezing = 0;
//        private float CDDownCast = 0;
//        private bool IsDownCast = false;
//        private bool IsUpCast = false;
//        private bool IsInvincible = false;

//        private IDObject m_IDTransform;
//        //Biến đếm thời gian bất tử
//        private float m_CoolDownInvincible;

//        private Random m_Random;

//        //biến để đếm cooldown cho animation biến lớn của mario
//        private float m_CDColor;
//        //biến để đếm cooldown cho animation biến lớn
//        private float m_CoolDownChanging;

//        private Bullet m_Bullet1;
//        private Bullet m_Bullet2;

//        public bool IsJumping
//        {
//            get { return m_IsJumping; }
//            set { m_IsJumping = value; }
//        }

//        public bool IsAttacking
//        {
//            get { return m_IsAttacking; }
//            set { m_IsAttacking = value; }
//        }

//        public Mario(Vector2 _Position)
//            : base(_Position)
//        {
//            Direction = IDDir.RIGHT;
//            m_Status = IDStatus.MARIO_STAND;
//            m_Velocity = Vector2.Zero;
//            m_Accel = Vector2.Zero;
//            m_IDObject = IDObject.SMALL_MARIO;
//            m_IsJumping = false;
//            m_IsDuck = false;
//            m_Random = new Random();
//            m_Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.SMALL_MARIO));
//            SmallSprite = new List<CSprite>();
//            BigSprite = new List<CSprite>();
//            SmallSprite.Add(new CSprite(CResourceManager.GetInstance().GetResource(IDResource.SMALL_MARIO_INVICIBILITY)));
//            SmallSprite.Add(new CSprite(CResourceManager.GetInstance().GetResource(IDResource.SMALL_MARIO_INVICIBILITY2)));
//            SmallSprite.Add(new CSprite(CResourceManager.GetInstance().GetResource(IDResource.SMALL_MARIO_INVICIBILITY3)));
//            BigSprite.Add(new CSprite(CResourceManager.GetInstance().GetResource(IDResource.BIG_MARIO_INVICIBILITY)));
//            BigSprite.Add(new CSprite(CResourceManager.GetInstance().GetResource(IDResource.BIG_MARIO_INVICIBILITY2)));
//            BigSprite.Add(new CSprite(CResourceManager.GetInstance().GetResource(IDResource.BIG_MARIO_INVICIBILITY3)));

//            Sprite.Depth = GlobalValue.MARIO_SPRITE_DEPTH;
//            m_CoolDownChanging = 0;
//            m_CDColor = 0;
//            m_CoolDownInvincible = 0;
//            m_isWorldFreeze = false;
//            m_isDeath = false;
//        }

//        public override void UpdateAnimation(GameTime _GameTime, CInput _Input)
//        {
//            if (Status != IDStatus.MARIO_STOP)
//            {
//                Sprite.Depth = 1.0f;
//            }
//            //Mario nhỏ

//            //Mario chạy
//            if (m_Status == IDStatus.MARIO_RUN)
//            {
//                IsTeleport = false;
//                m_Sprite.Animation.FrameStart = 0;
//                m_Sprite.Animation.FrameEnd = 3;
//                m_Sprite.Animation.TimeAnimation = 80.0f;
//            }
//            //Mario núp lùm
//            if (m_Status == IDStatus.MARIO_DOWN)
//            {
//                //Nếu là mario nhỏ thì frame là 0, còn Mario to trở lên thì frame là 6
//                if (IDObject == IDObject.SMALL_MARIO)
//                {
//                    Sprite.Animation.CurFrame = 0;
//                }
//                else
//                {
//                    Sprite.Animation.CurFrame = 6;
//                }
//                //Chỉnh lại sprite depth để có thể núp sau cây cột
//                //Sprite.Depth = 0.1f;
//            }

//            if (Status == IDStatus.MARIO_JUMP)
//            {
//                Sprite.Animation.CurFrame = 5;
//                IsTeleport = false;
//            }

//            //Mario đứng yên tại chỗ
//            if (Status == IDStatus.MARIO_STAND)
//            {
//                Sprite.Animation.CurFrame = 0;
//            }

//            //Mario lên bàn thờ
//            if (m_Status == IDStatus.DIE)
//            {
//                Sprite.Animation.CurFrame = 6;
//            }

//            //Mario bắn đạn
//            if (m_Status == IDStatus.MARIO_ATTACK)
//            {
//                m_Sprite.Animation.CurFrame = 5;
//            }

//            if (Status == IDStatus.MARIO_STRIPPED)
//            {
//                if (Position.Y < 174)
//                {
//                    Sprite.Animation.CurFrame = 7;
//                }
//                else
//                {
//                    Sprite.Animation.CurFrame = 8;
//                }
//            }

//            if (Status == IDStatus.MARIO_WIN)
//            {
//                Sprite.Animation.CurFrame = 8;
//                m_CDWining += (float)_GameTime.ElapsedGameTime.TotalMilliseconds;

//                if (m_CDWining > 500)
//                {
//                    CResourceManager.GetInstance().GetSoundEffect(IDResource.SFX_STAGE_CLEAR).Play();
//                    Status = IDStatus.MARIO_AUTO_RUN;
//                    m_CDWining = 0;
//                }
//            }
//            if (Status == IDStatus.MARIO_AUTO_RUN)
//            {
//                Velocity = new Vector2(0.05f, Velocity.Y);
//                Direction = IDDir.RIGHT;
//                m_Sprite.Animation.FrameStart = 0;
//                m_Sprite.Animation.FrameEnd = 3;
//                m_Sprite.Animation.TimeAnimation = 80.0f;
//            }

//            if (Status == IDStatus.MARIO_DOWN || Status == IDStatus.TELEPORT)
//            {
//                if (IDObject == IDObject.SMALL_MARIO)
//                {
//                    Sprite.Animation.CurFrame = 0;
//                }
//                else
//                {
//                    Sprite.Animation.CurFrame = 6;
//                }
//            }

//            if (Status == IDStatus.TELEPORT)
//            {
//                Sprite.Depth = 0.05f;
//            }

//            //Mario bất tử
//            if (m_Status == IDStatus.MARIO_UPCAST)
//            {
//                IsUpCast = true;
//            }

//            if (Status == IDStatus.MARIO_INVINCIBLE)
//            {
//                IsInvincible = true;
//            }

//            if (Status == IDStatus.MARIO_DOWNCAST)
//            {
//                IsDownCast = true;
//            }
//            ManageFreezeTime(_GameTime);
//            DownCast(_GameTime);
//            UpCast(_GameTime);
//            Invincible(_GameTime);

//            #region.Xác định hướng di chuyển
//            if (Direction == IDDir.RIGHT)
//                m_Sprite.Effect = SpriteEffects.None;
//            if (Direction == IDDir.LEFT)
//                m_Sprite.Effect = SpriteEffects.FlipHorizontally;
//            #endregion


//            //Console.WriteLine(m_ListOfBullet.Count.ToString());

//            base.UpdateAnimation(_GameTime, _Input);
//        }

//        private void Invincible(GameTime _GameTime)
//        {
//            if (IsInvincible)
//            {
//                m_CoolDownInvincible += (float)_GameTime.ElapsedGameTime.TotalMilliseconds;
//                m_CDColor += (float)_GameTime.ElapsedGameTime.TotalMilliseconds;
//                if (m_CDColor > 400)
//                {
//                    if (IDObject == IDObject.FIRE_MARIO || IDObject == IDObject.SUPER_MARIO)
//                    {
//                        Sprite = BigSprite[(int)m_CoolDownInvincible % 3];
//                    }
//                    if (IDObject == IDObject.SMALL_MARIO)
//                    {
//                        Sprite = SmallSprite[(int)m_CoolDownInvincible % 3];
//                    }
//                    m_CDColor = 0;
//                }
//                if (m_CoolDownInvincible > 8000)
//                {
//                    //Status = IDStatus.MARIO_STAND;
//                    m_CoolDownInvincible = 0;
//                    Sprite = tempSprite;
//                    m_CDColor = 0;
//                    IsInvincible = false;
//                }
//            }
//        }

//        private void UpCast(GameTime _GameTime)
//        {
//            if (IsUpCast)
//            {
//                m_CoolDownInvincible += (float)_GameTime.ElapsedGameTime.TotalMilliseconds;
//                Sprite = BigSprite[(int)m_CoolDownInvincible % 3];
//                if (m_CoolDownInvincible > 1500)
//                {
//                    //Status = IDStatus.MARIO_STAND;
//                    m_CoolDownInvincible = 0;
//                    Sprite = tempSprite;
//                    IsUpCast = false;
//                    m_IsLockKeyboard = false;
//                    m_isMarioFreeze = false;
//                }
//            }
//        }

//        private void DownCast(GameTime _GameTime)
//        {
//            if (IsDownCast)
//            {
//                CDDownCast += (float)_GameTime.ElapsedGameTime.TotalMilliseconds;
//                if (CDDownCast < 1500)
//                {
//                    if (Sprite.Alpha == 1f)
//                    {
//                        Sprite.Alpha = 0.1f;
//                        return;
//                    }
//                    if (Sprite.Alpha == 0.1f)
//                    {
//                        Sprite.Alpha = 1f;
//                        return;
//                    }
//                }
//                else
//                {
//                    //Status = IDStatus.MARIO_STAND;
//                    CDDownCast = 0;
//                    IsDownCast = false;
//                    Sprite.Alpha = 1.0f;
//                }
//            }
//        }

//        /// <summary>
//        /// Phân tích tín hiệu input để xử lý status cho Mario
//        /// </summary>
//        /// <param name="_Input"></param>
//        /// <returns></returns>
//        private void AnalysisInput(CInput _Input)
//        {
//            if (_Input.KeyDown(Keys.Right) && Status != IDStatus.MARIO_JUMP && !m_IsDisableRight)
//            {
//                Direction = IDDir.RIGHT;
//                Accel = new Vector2(0.01f, Accel.Y);
//                Status = IDStatus.MARIO_RUN;
//            }

//            if (_Input.KeyDown(Keys.Left) && Status != IDStatus.MARIO_JUMP && !m_IsDisableLeft)
//            {
//                Direction = IDDir.LEFT;
//                Accel = new Vector2(-0.01f, Accel.Y);
//                Status = IDStatus.MARIO_RUN;
//            }

//            if (_Input.KeyPressed(Keys.Up) && Status != IDStatus.MARIO_JUMP && !m_IsDisableUp)
//            {
//                Status = IDStatus.MARIO_JUMP;
//                Velocity = new Vector2(Velocity.X, -0.35f);
//            }

//            if (_Input.KeyDown(Keys.Down) && Status != IDStatus.MARIO_JUMP && !m_IsDisableDown)
//            {
//                //Velocity = Vector2.Zero;
//                Accel = new Vector2(0, Accel.Y);
//                //Status = IDStatus.MARIO_RUN;
//                Status = IDStatus.MARIO_DOWN;
//            }

//            Damping(_Input);

//        }

//        private void ManageFreezeTime(GameTime _GameTime)
//        {
//            if (IsWorldFreeze)
//            {
//                CDFreezing += (float)_GameTime.ElapsedGameTime.TotalMilliseconds;
//                if (CDFreezing > 1500)
//                {
//                    IsWorldFreeze = false;
//                    CDFreezing = 0;
//                }
//            }
//        }

//        /// <summary>
//        /// Giới hạn tốc độ của Mario
//        /// </summary>
//        /// <returns></returns>
//        private void LimitSpeed()
//        {
//            if (Velocity.X > 0.1f)
//            {
//                Velocity = new Vector2(0.1f, Velocity.Y);
//            }
//            if (Velocity.X < -0.1f)
//            {
//                Velocity = new Vector2(-0.1f, Velocity.Y);
//            }
//            if (Velocity.Y > 0.25f)
//            {
//                Velocity = new Vector2(Velocity.X, 0.25f);
//            }
//        }

//        /// <summary>
//        /// Hãm vận tốc của Mario khi công còn nhận input
//        /// </summary>
//        /// <param name="_Input"></param>
//        /// <returns></returns>
//        private void Damping(CInput _Input)
//        {
//            if (!_Input.KeyDown(Keys.Left) && !_Input.KeyDown(Keys.Right))
//            {
//                Accel = new Vector2(0, Accel.Y);
//                //m_Velocity = new Vector2(m_Velocity.X - m_Velocity.X * 0.1f, m_Velocity.Y);
//                m_Velocity = new Vector2(m_Velocity.X - 0.2f * m_Velocity.X, m_Velocity.Y);
//                if (Math.Abs(m_Velocity.X) <= 0.001f)
//                {
//                    m_Velocity = new Vector2(0.0f, m_Velocity.Y);
//                    if (!_Input.KeyDown(Keys.Up) && !_Input.KeyPressed(Keys.Z) && !_Input.KeyDown(Keys.Down) && Status != IDStatus.TELEPORT)
//                    {
//                        Status = IDStatus.MARIO_STAND;
//                    }
//                    //Console.WriteLine("damping stand");
//                }
//            }
//        }

//        private void ManageTeleport(GameTime _GameTime)
//        {
//            if (Status == IDStatus.TELEPORT)
//            {
//                m_TimeTeleport += (float)_GameTime.ElapsedGameTime.TotalMilliseconds;
//                if (m_TimeTeleport > 3000)
//                {
//                    Gate.Status = IDStatus.TELEPORT;
//                    //Gate = null;
//                    m_TimeTeleport = 0;
//                }
//            }
//        }

//        private void ManageBullet()
//        {
//            if (m_Bullet1 != null)
//            {
//                if (Math.Abs(m_Bullet1.Position.X - Position.X) > GlobalValue.SCREEN_WIDTH || m_Bullet1.Status == IDStatus.DIE)
//                {
//                    m_Bullet1 = null;
//                }
//            }
//            if (m_Bullet2 != null)
//            {
//                if (Math.Abs(m_Bullet2.Position.X - Position.X) > GlobalValue.SCREEN_WIDTH || m_Bullet2.Status == IDStatus.DIE)
//                {
//                    m_Bullet2 = null;
//                }
//            }
//        }

//        private void UpdateBullet(GameTime _GameTime, CInput _Input)
//        {
//            if (m_Bullet1 != null)
//            {
//                m_Bullet1.UpdateAnimation(_GameTime, _Input);
//                m_Bullet1.UpdateMovement(_GameTime, _Input);
//            }
//            if (m_Bullet2 != null)
//            {
//                m_Bullet2.UpdateAnimation(_GameTime, _Input);
//                m_Bullet2.UpdateMovement(_GameTime, _Input);
//            }
//        }

//        private void UpdateCollisionBullet(CAnimationObject _Object)
//        {
//            if (m_Bullet1 != null)
//            {
//                m_Bullet1.UpdateCollision(_Object);
//            }
//            if (m_Bullet2 != null)
//            {
//                m_Bullet2.UpdateCollision(_Object);
//            }
//        }

//        private void CheckDead()
//        {
//            if (m_Status == IDStatus.DIE && m_isDeath == false)
//            {
//                CResourceManager.GetInstance().GetSoundEffect(IDResource.SFX_MARIO_DIE).Play();
//                m_Velocity.X = 0;
//                m_Accel.X = 0;
//                if (!m_isDeath)
//                {
//                    m_Velocity.Y = -0.35f;
//                    m_isDeath = true;
//                }
//            }
//        }

//        private void AddBullet()
//        {
//            if (m_Bullet1 == null)
//            {
//                m_Bullet1 = new Bullet(this.Position, this.Direction);
//                CResourceManager.GetInstance().GetSoundEffect(IDResource.SFX_FIREBALL).Play();
//                return;
//            }
//            if (m_Bullet2 == null)
//            {
//                m_Bullet2 = new Bullet(this.Position, this.Direction);
//                CResourceManager.GetInstance().GetSoundEffect(IDResource.SFX_FIREBALL).Play();
//                return;
//            }
//        }

//        public override void UpdateMovement(GameTime _GameTime, CInput _Input)
//        {

//            // Gia tốc trọng trường
//            //Console.WriteLine(Status.ToString());
//            if (Status != IDStatus.TELEPORT)
//            {
//                Accel = new Vector2(m_Accel.X, 0.00098f);
//            }

//            if (Status != IDStatus.MARIO_JUMP && Status != IDStatus.DIE && !m_IsLockKeyboard)
//            {
//                AnalysisInput(_Input);
//            }

//            if (_Input.KeyPressed(Keys.Z) && IDObject == IDObject.FIRE_MARIO)
//            {
//                AddBullet();
//                if (Sprite.Animation.CurFrame != 5)
//                {
//                    Sprite.Animation.CurFrame = 5;
//                    Sprite.Animation.SetLocalAnimation();
//                }
//                Status = IDStatus.MARIO_ATTACK;
//            }

//            ManageTeleport(_GameTime);
//            UpdateBullet(_GameTime, _Input);
//            ManageBullet();
//            LimitSpeed();
//            CheckDead();

//            base.Update(_GameTime, _Input);
//        }

//        public override void UpdateCollision(CAnimationObject _Object)
//        {
//            UpdateCollisionBullet(_Object);
//            if (CheckCollision(_Object) != DirectCollision.NONE && m_Status != IDStatus.DIE)
//            {
//                switch (_Object.IDObject)
//                {
//                    #region Goomba
//                    case IDObject.ENEMY_GOOMBA_OW:
//                        if ((CheckCollision(_Object) == DirectCollision.TOP || CheckCollision(_Object) == DirectCollision.RIGHT || CheckCollision(_Object) == DirectCollision.LEFT || CheckCollision(_Object) == DirectCollision.BOTTOM) && IsInvincible && _Object.Status != IDStatus.SHOOTED)
//                        {
//                            _Object.Status = IDStatus.SHOOTED;
//                            _Object.Velocity = new Vector2(0, -0.2f);
//                        }
//                        if (CheckCollision(_Object) == DirectCollision.TOP && _Object.Status == IDStatus.ALIVE && !IsWorldFreeze)
//                        {
//                            CResourceManager.GetInstance().GetSoundEffect(IDResource.SFX_STOMP).Play();
//                            _Object.Status = IDStatus.BEFORE_DIE;
//                            m_Velocity.Y = -m_Velocity.Y;
//                            break;
//                        }
//                        if ((CheckCollision(_Object) == DirectCollision.RIGHT || CheckCollision(_Object) == DirectCollision.LEFT) && _Object.Status == IDStatus.ALIVE && !IsWorldFreeze)
//                        {
//                            if (m_IDObject == IDObject.FIRE_MARIO)
//                            {
//                                CResourceManager.GetInstance().GetSoundEffect(IDResource.SFX_MARIO_HURT).Play();
//                                Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.SUPER_MARIO));
//                                IDObject = IDObject.SUPER_MARIO;
//                                Status = IDStatus.MARIO_DOWNCAST;
//                                IsWorldFreeze = true;
//                                break;
//                            }
//                            if (m_IDObject == IDObject.SUPER_MARIO)
//                            {
//                                CResourceManager.GetInstance().GetSoundEffect(IDResource.SFX_MARIO_HURT).Play();
//                                Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.SMALL_MARIO));
//                                IsWorldFreeze = true;
//                                Status = IDStatus.MARIO_DOWNCAST;
//                                IDObject = IDObject.SMALL_MARIO;
//                                break;
//                            }
//                            if (m_IDObject == IDObject.SMALL_MARIO)
//                            {
//                                m_Status = IDStatus.DIE;
//                                break;
//                            }
//                            if (Direction == IDDir.RIGHT)
//                            {
//                                Position = new Vector2(Position.X - 5f, Position.Y);
//                            }
//                            if (Direction == IDDir.LEFT)
//                            {
//                                Position = new Vector2(Position.X + 5f, Position.Y);
//                            }
//                            Velocity = Vector2.Zero;
//                        }
//                        break;
//                    #endregion
//                    #region Soft Brick
//                    case IDObject.MISC_SOFT_BRICK:
//                        if (CheckCollision(_Object) == DirectCollision.TOP && _Object.Status != IDStatus.ACTIVATE && _Object.Status != IDStatus.DIE)
//                        {
//                            if (Status == IDStatus.MARIO_JUMP)
//                            {
//                                Status = IDStatus.MARIO_STAND;
//                            }
//                            m_IsJumping = false;
//                            m_Velocity = new Vector2(m_Velocity.X, 0.0f);
//                            m_Position.Y = _Object.Position.Y - Sprite.FrameHeight;
//                            break;
//                        }
//                        else if (CheckCollision(_Object) == DirectCollision.BOTTOM && _Object.Status != IDStatus.ACTIVATE && _Object.Status != IDStatus.DIE)
//                        {
//                            m_Velocity = new Vector2(m_Velocity.X, 0.01f);
//                            if (_Object.Status != IDStatus.MOVE)
//                            {
//                                _Object.Velocity = new Vector2(0, -0.04f);
//                            }
//                            m_Position.Y = _Object.Position.Y + _Object.Sprite.FrameHeight + 2f;
//                            if (this.IDObject == Framework.IDObject.SMALL_MARIO)
//                            {
//                                _Object.Status = IDStatus.MOVE;
//                                break;
//                            }
//                            if (this.IDObject == Framework.IDObject.FIRE_MARIO || this.IDObject == Framework.IDObject.SUPER_MARIO)
//                            {
//                                CResourceManager.GetInstance().GetSoundEffect(IDResource.SFX_BREAKBLOCK).Play();
//                                _Object.Velocity = new Vector2(0, m_Velocity.Y - 1);
//                                _Object.Status = IDStatus.BEFORE_DIE;
//                                break;
//                            }
//                        }
//                        else if (CheckCollision(_Object) == DirectCollision.LEFT)
//                        {
//                            m_Velocity = new Vector2(0.0f, m_Velocity.Y);
//                            Position = new Vector2(_Object.Position.X - Sprite.FrameWidht - 1, Position.Y);
//                            break;
//                        }
//                        else if (CheckCollision(_Object) == DirectCollision.RIGHT)
//                        {
//                            m_Velocity = new Vector2(0.0f, m_Velocity.Y);
//                            Position = new Vector2(_Object.Position.X + _Object.Sprite.FrameWidht + 1, Position.Y);
//                            break;
//                        }
//                        break;
//                    case IDObject.ITEM_COIN_NORMAL:
//                        if ((CheckCollision(_Object) == DirectCollision.TOP || CheckCollision(_Object) == DirectCollision.RIGHT || CheckCollision(_Object) == DirectCollision.LEFT) && _Object.Status == IDStatus.ALIVE)
//                        {
//                            CResourceManager.GetInstance().GetSoundEffect(IDResource.SFX_COIN).Play();
//                            _Object.Status = IDStatus.DIE;
//                            GlobalValue.MARIO_SCORE += 100;
//                            GlobalValue.MARIO_COIN += 100;
//                        }
//                        break;
//                    #endregion
//                    #region Fire Flower
//                    case IDObject.ITEM_FIRE_FLOWER:
//                        if ((CheckCollision(_Object) == DirectCollision.TOP || CheckCollision(_Object) == DirectCollision.RIGHT || CheckCollision(_Object) == DirectCollision.LEFT) && _Object.Status == IDStatus.ALIVE)
//                        {
//                            CResourceManager.GetInstance().GetSoundEffect(IDResource.SFX_POWER_UP).Play();
//                            _Object.Status = IDStatus.DIE;
//                            if (m_IDObject == IDObject.SMALL_MARIO || m_IDObject == IDObject.SUPER_MARIO)
//                            {
//                                IDObject = IDObject.FIRE_MARIO;
//                                m_Status = IDStatus.MARIO_UPCAST;
//                                tempSprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.FIRE_MARIO));
//                                IsWorldFreeze = true;
//                                m_IsLockKeyboard = true;
//                                m_isMarioFreeze = true;
//                            }
//                            GlobalValue.MARIO_SCORE += 1000;
//                            break;
//                        }
//                        break;
//                    #endregion
//                    case IDObject.BRICK_1UPMUSHROOM:
//                        if ((CheckCollision(_Object) == DirectCollision.TOP || CheckCollision(_Object) == DirectCollision.RIGHT || CheckCollision(_Object) == DirectCollision.LEFT) && _Object.Status == IDStatus.ALIVE)
//                        {
//                            CResourceManager.GetInstance().GetSoundEffect(IDResource.ITEM_1UP_MUSHROOM).Play();
//                            _Object.Status = IDStatus.DIE;
//                            GlobalValue.MARIO_LIFE += 1;
//                            break;
//                        }
//                        break;
//                    case IDObject.BRICK_SUPPERMUSHROOM:
//                        if ((CheckCollision(_Object) == DirectCollision.TOP || CheckCollision(_Object) == DirectCollision.RIGHT || CheckCollision(_Object) == DirectCollision.LEFT) && _Object.Status == IDStatus.ALIVE)
//                        {
//                            CResourceManager.GetInstance().GetSoundEffect(IDResource.SFX_POWER_UP).Play();
//                            _Object.Status = IDStatus.DIE;
//                            if (m_IDObject == IDObject.SMALL_MARIO)
//                            {
//                                IDObject = IDObject.SUPER_MARIO;
//                                m_Status = IDStatus.MARIO_UPCAST;
//                                tempSprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.SUPER_MARIO));
//                                IsWorldFreeze = true;
//                                m_IsLockKeyboard = true;
//                                m_isMarioFreeze = true;
//                            }
//                            GlobalValue.MARIO_SCORE += 1000;
//                            break;
//                        }
//                        break;
//                    #region Case Koopa
//                    case IDObject.ENEMY_KOOPA_OW:
//                        if ((CheckCollision(_Object) == DirectCollision.TOP || CheckCollision(_Object) == DirectCollision.RIGHT || CheckCollision(_Object) == DirectCollision.LEFT || CheckCollision(_Object) == DirectCollision.BOTTOM) && IsInvincible && _Object.Status != IDStatus.SHOOTED)
//                        {
//                            _Object.Status = IDStatus.SHOOTED;
//                            _Object.Velocity = new Vector2(0, -0.2f);
//                        }
//                        if (CheckCollision(_Object) == DirectCollision.TOP && _Object.Status == IDStatus.ALIVE)
//                        {
//                            m_Velocity.Y = -0.02f;
//                            _Object.Status = IDStatus.HIDE;
//                            _Object.Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.ENEMY_HIDE_KOOPA_OW));
//                        }
//                        if ((CheckCollision(_Object) == DirectCollision.RIGHT || CheckCollision(_Object) == DirectCollision.LEFT) && _Object.Status == IDStatus.HIDE)
//                        {
//                            if (Direction == IDDir.LEFT && CheckCollision(_Object) == DirectCollision.RIGHT)
//                            {
//                                _Object.Direction = IDDir.LEFT;
//                                _Object.Status = IDStatus.SPIN;
//                                CResourceManager.GetInstance().GetSoundEffect(IDResource.SFX_KICK).Play();
//                                break;
//                            }
//                            if (Direction == IDDir.RIGHT && CheckCollision(_Object) == DirectCollision.LEFT)
//                            {
//                                _Object.Direction = IDDir.RIGHT;
//                                _Object.Status = IDStatus.SPIN;
//                                CResourceManager.GetInstance().GetSoundEffect(IDResource.SFX_KICK).Play();
//                                break;
//                            }
//                            break;
//                        }
//                        if (CheckCollision(_Object) == DirectCollision.TOP && _Object.Status == IDStatus.HIDE)
//                        {
//                            if (Status == IDStatus.MARIO_JUMP)
//                            {
//                                Status = IDStatus.MARIO_STAND;
//                            }
//                            m_Velocity.Y = 0;
//                            //m_IsDisableUp = true;
//                            IsJumping = false;
//                            break;
//                        }
//                        if (CheckCollision(_Object) == DirectCollision.TOP && _Object.Status == IDStatus.SPIN)
//                        {
//                            if (Status == IDStatus.MARIO_JUMP)
//                            {
//                                Status = IDStatus.MARIO_STAND;
//                            }
//                            m_Velocity.Y = 0;
//                            IsJumping = false;
//                            _Object.Status = IDStatus.HIDE;
//                            break;
//                        }
//                        if ((CheckCollision(_Object) == DirectCollision.RIGHT || CheckCollision(_Object) == DirectCollision.LEFT) && _Object.Status == IDStatus.SPIN && !IsWorldFreeze)
//                        {
//                            if (m_IDObject == IDObject.FIRE_MARIO)
//                            {
//                                CResourceManager.GetInstance().GetSoundEffect(IDResource.SFX_MARIO_HURT).Play();
//                                IDObject = IDObject.SUPER_MARIO;
//                                IsWorldFreeze = true;
//                                Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.SUPER_MARIO));
//                                Status = IDStatus.MARIO_DOWNCAST;
//                                break;
//                            }
//                            if (m_IDObject == IDObject.SUPER_MARIO)
//                            {
//                                CResourceManager.GetInstance().GetSoundEffect(IDResource.SFX_MARIO_HURT).Play();
//                                IDObject = IDObject.SMALL_MARIO;
//                                Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.SMALL_MARIO));
//                                IsWorldFreeze = true;
//                                Status = IDStatus.MARIO_DOWNCAST;
//                                break;
//                            }
//                            if (m_IDObject == IDObject.SMALL_MARIO)
//                            {
//                                //m_Velocity.Y = -3.0f;
//                                m_Status = IDStatus.DIE;
//                                break;
//                            }
//                        }
//                        if ((CheckCollision(_Object) == DirectCollision.RIGHT || CheckCollision(_Object) == DirectCollision.LEFT) && _Object.Status == IDStatus.ALIVE && !IsWorldFreeze)
//                        {
//                            if (m_IDObject == IDObject.FIRE_MARIO)
//                            {
//                                CResourceManager.GetInstance().GetSoundEffect(IDResource.SFX_MARIO_HURT).Play();
//                                IDObject = IDObject.SUPER_MARIO;
//                                Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.SUPER_MARIO));
//                                IsWorldFreeze = true;
//                                Status = IDStatus.MARIO_DOWNCAST;
//                                break;
//                            }
//                            if (m_IDObject == IDObject.SUPER_MARIO)
//                            {
//                                CResourceManager.GetInstance().GetSoundEffect(IDResource.SFX_MARIO_HURT).Play();
//                                IDObject = IDObject.SMALL_MARIO;
//                                Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.SMALL_MARIO));
//                                IsWorldFreeze = true;
//                                Status = IDStatus.MARIO_DOWNCAST;
//                                break;
//                            }
//                            if (m_IDObject == IDObject.SMALL_MARIO)
//                            {
//                                m_Status = IDStatus.DIE;
//                                break;
//                            }
//                        }
//                        break;
//                    #endregion
//                    #region Case Base Brick
//                    case IDObject.MISC_BASE_BRICK:
//                    case IDObject.MISC_HARD_BRICK:
//                        if (CheckCollision(_Object) == DirectCollision.TOP)
//                        {
//                            //if (Status != IDStatus.MARIO_RUN && Status != IDStatus.MARIO_STAND && Status != IDStatus.MARIO_ATTACK && Status != IDStatus.MARIO_STRIPPED && Status != IDStatus.MARIO_WIN && Status != IDStatus.MARIO_AUTO_RUN && Status != IDStatus.MARIO_DOWNCAST)
//                            if (Status == IDStatus.MARIO_JUMP)
//                            {
//                                Status = IDStatus.MARIO_STAND;
//                            }
//                            //m_IsDisableUp = false;
//                            m_IsJumping = false;
//                            m_Velocity = new Vector2(m_Velocity.X, 0.0f);
//                            m_Position.Y = _Object.Position.Y - Sprite.FrameHeight;
//                            if (Status == IDStatus.MARIO_STRIPPED)
//                            {
//                                Position = new Vector2(Position.X + 12, Position.Y);

//                                Direction = IDDir.LEFT;
//                                Status = IDStatus.MARIO_WIN;
//                            }
//                            break;
//                        }
//                        else if (CheckCollision(_Object) == DirectCollision.BOTTOM)
//                        {
//                            m_Velocity = new Vector2(m_Velocity.X, 0.0098f);
//                            m_Position.Y = _Object.Position.Y + _Object.Sprite.FrameHeight + 1;
//                            break;
//                        }
//                        else if (CheckCollision(_Object) == DirectCollision.LEFT)
//                        {
//                            m_Velocity = new Vector2(0.0f, m_Velocity.Y);
//                            Position = new Vector2(Position.X - 0.05f, Position.Y);
//                            break;
//                        }
//                        else if (CheckCollision(_Object) == DirectCollision.RIGHT)
//                        {
//                            m_Velocity = new Vector2(0.0f, m_Velocity.Y);
//                            Position = new Vector2(Position.X + 0.05f, Position.Y);
//                            break;
//                        }
//                        break;
//                    #endregion
//                    #region Goal Pole
//                    case IDObject.MISC_GOAL_POLE:
//                        if ((CheckCollision(_Object) == DirectCollision.BOTTOM || CheckCollision(_Object) == DirectCollision.LEFT || CheckCollision(_Object) == DirectCollision.RIGHT || CheckCollision(_Object) == DirectCollision.TOP) && !m_IsLockKeyboard)
//                        {
//                            if (!m_IsLockKeyboard)
//                            {
//                                Position = new Vector2(_Object.Position.X - 9, Position.Y);
//                                CResourceManager.GetInstance().GetSoundEffect(IDResource.SFX_FLAGPOLE).Play();
//                                MediaPlayer.Stop();
//                            }
//                            Status = IDStatus.MARIO_STRIPPED;
//                            m_IsLockKeyboard = true;
//                            Accel = Vector2.Zero;
//                            Velocity = Vector2.Zero;
//                            _Object.Status = IDStatus.ACTIVATE;
//                        }
//                        break;
//                    #endregion
//                    #region Pipe
//                    case IDObject.MISC_GATE_PIPE:
//                        if (CheckCollision(_Object) == DirectCollision.TOP)
//                        {
//                            if (Status == IDStatus.MARIO_JUMP)
//                            {
//                                Status = IDStatus.MARIO_STAND;
//                            }
//                            if (_Object.Status == IDStatus.GATE_PIPE_DOWN && Position.X > _Object.Position.X + 3 && Position.X < _Object.Position.X + 15)
//                            {
//                                IsTeleport = true;
//                            }
//                            else
//                            {
//                                IsTeleport = false;
//                            }
//                            if (_Object.Status == IDStatus.GATE_PIPE_DOWN && IsTeleport && Status == IDStatus.MARIO_DOWN)
//                            {
//                                Status = IDStatus.TELEPORT;
//                                Velocity = new Vector2(0, 0.01f);
//                                Accel = Vector2.Zero;
//                                Gate = _Object;
//                                if (!m_IsPlaySoundGate)
//                                {
//                                    CResourceManager.GetInstance().GetSoundEffect(IDResource.SFX_PIPE).Play();
//                                    MediaPlayer.Pause();
//                                    m_IsPlaySoundGate = true;
//                                }
//                                break;
//                            }
//                            if (Status != IDStatus.TELEPORT)
//                            {
//                                m_IsJumping = false;
//                                m_Velocity = new Vector2(m_Velocity.X, 0.0f);
//                                m_Position.Y = _Object.Position.Y - Sprite.FrameHeight;
//                            }
//                            break;
//                        }
//                        if (CheckCollision(_Object) == DirectCollision.LEFT)
//                        {
//                            m_Velocity = new Vector2(0.0f, m_Velocity.Y);
//                            Position = new Vector2(Position.X - 0.05f, Position.Y);
//                            break;
//                        }
//                        else if (CheckCollision(_Object) == DirectCollision.RIGHT)
//                        {
//                            m_Velocity = new Vector2(0.0f, m_Velocity.Y);
//                            Position = new Vector2(Position.X + 0.05f, Position.Y);
//                            break;
//                        }
//                        break;
//                    case IDObject.MISC_STOCK_PIPE:
//                        //if (CheckCollision(_Object) == DirectCollision.TOP)
//                        //{
//                        //    if (Status == IDStatus.MARIO_JUMP)
//                        //    {
//                        //        Status = IDStatus.MARIO_STAND;
//                        //    }
//                        //    m_IsJumping = false;
//                        //    m_Velocity = new Vector2(m_Velocity.X, 0.0f);
//                        //    m_Position.Y = _Object.Position.Y - Sprite.FrameHeight;
//                        //    break;
//                        //}
//                        if (CheckCollision(_Object) == DirectCollision.BOTTOM)
//                        {
//                            m_Velocity = new Vector2(m_Velocity.X, 0.0098f);
//                            m_Position.Y = _Object.Position.Y + _Object.Sprite.FrameHeight + 1;
//                            break;
//                        }
//                        else if (CheckCollision(_Object) == DirectCollision.LEFT)
//                        {
//                            m_Velocity = new Vector2(0.0f, m_Velocity.Y);
//                            Position = new Vector2(Position.X - 0.05f, Position.Y);
//                            break;
//                        }
//                        else if (CheckCollision(_Object) == DirectCollision.RIGHT)
//                        {
//                            m_Velocity = new Vector2(0.0f, m_Velocity.Y);
//                            Position = new Vector2(Position.X + 0.05f, Position.Y);
//                            break;
//                        }
//                        break;
//                    #endregion
//                    #region Question Brick
//                    case IDObject.MISC_QUESTION_BRICK:
//                        if (CheckCollision(_Object) == DirectCollision.TOP)
//                        {
//                            if (Status == IDStatus.MARIO_JUMP)
//                            {
//                                Status = IDStatus.MARIO_STAND;
//                            }
//                            m_IsJumping = false;
//                            m_Velocity = new Vector2(m_Velocity.X, 0.0f);
//                            m_Position.Y = _Object.Position.Y - Sprite.FrameHeight;
//                            break;
//                        }
//                        else if (CheckCollision(_Object) == DirectCollision.BOTTOM)
//                        {
//                            m_Velocity = new Vector2(m_Velocity.X, 0.0098f);
//                            m_Position.Y = _Object.Position.Y + _Object.Sprite.FrameHeight + 1;
//                            if (_Object.Status != IDStatus.UNACTIVATE)
//                            {
//                                _Object.Status = IDStatus.DEACTIVATE;
//                            }
//                            break;
//                        }
//                        else if (CheckCollision(_Object) == DirectCollision.LEFT)
//                        {
//                            m_Velocity = new Vector2(0.0f, m_Velocity.Y);
//                            break;
//                        }
//                        else if (CheckCollision(_Object) == DirectCollision.RIGHT)
//                        {
//                            m_Velocity = new Vector2(0.0f, m_Velocity.Y);
//                            break;
//                        }
//                        break;
//                    #endregion
//                    #region Case Starman
//                    case IDObject.ITEM_STARMAN:
//                        if ((CheckCollision(_Object) == DirectCollision.TOP || CheckCollision(_Object) == DirectCollision.RIGHT || CheckCollision(_Object) == DirectCollision.LEFT || CheckCollision(_Object) == DirectCollision.BOTTOM) && _Object.Status != IDStatus.UNACTIVATE)
//                        {
//                            CResourceManager.GetInstance().GetSoundEffect(IDResource.SFX_POWER_UP).Play();
//                            Status = IDStatus.MARIO_INVINCIBLE;
//                            tempSprite = Sprite;
//                            _Object.Status = IDStatus.DIE;

//                            break;
//                        }
//                        break;
//                    #endregion
//                    #region Case Default
//                    default:
//                        break;
//                    #endregion
//                }
//            }
//            base.UpdateCollision(_Object);
//        }

//        private void DrawBullet(SpriteBatch _SpriteBatch)
//        {
//            if (m_Bullet1 != null)
//            {
//                m_Bullet1.Draw(_SpriteBatch);
//            }
//            if (m_Bullet2 != null)
//            {
//                m_Bullet2.Draw(_SpriteBatch);
//            }
//        }

//        public override void Draw(SpriteBatch _SpriteBatch)
//        {
//            DrawBullet(_SpriteBatch);
//            base.Draw(_SpriteBatch);
//        }
//    }
//}