//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using Microsoft.Xna.Framework;
//using Microsoft.Xna.Framework.Graphics;

//namespace Mario_Bros.Framework
//{
//    public enum IDObject
//    {
//        NONE,
//        SMALL_MARIO,
//        SUPER_MARIO,

//        ENEMY_GOOMBA_OW,
//        ENEMY_KOOPA_OW,

//        MISC_BASE_BRICK,
//        MISC_QUESTION_BRICK,
//        MISC_IRON_BRICK,
//        MISC_SOFT_BRICK,
//        MISC_PIECE,
//        MISC_STOCK_PIPE,
//        MISC_GATE_PIPE,
//        MISC_UP_PIPE,
//        MISC_SMALL_GRASS,
//        MISC_MEDIUM_GRASS,
//        MISC_BIG_GRASS,
//        MISC_BIG_MOUNTAIN,
//        MISC_MEDIUM_MOUNTAIN,
//        MISC_HARD_BRICK,
//        MISC_CASTLE,

//        ITEM_COIN_ACTIVATED, // coin nằmg trong gạch
//        ITEM_COIN_NORMAL, // coin nằm ở ngoài
//        ITEM_FIRE_FLOWER,
//        ITEM_SUPER_MUSHROOM,
//        ITEM_1UP_MUSHROOM,
//        ITEM_STARMAN,

//        BRICK_COIN,
//        BRICK_FLOWER,
//        BRICK_1UPMUSHROOM,
//        BRICK_SUPPERMUSHROOM,
//        BRICK_STAR,
//        BRICK_QUESTION_ITEM,

//        FIRE_MARIO,
//        MISC_STAR_FLAG_CASTLE,
//        BULLET,
//        MISC_FLAG,
//        MISC_GOAL_POLE,
//        ITEM_GROW_UP,

//    }

//    /// <summary>
//    /// Có các trạng thái chung và riêng của các đối tượng trong game.
//    /// </summary>
//    public enum IDStatus
//    {
//        #region.Thuộc tính chung cho các đối tượng, để dễ dàng cho việc giải phóng đối tượng
//        ALIVE,
//        DIE,
//        BEFORE_DIE,ACTIVATE,RUN,UNACTIVATE,MOVE,DEACTIVATE,FIRE,THROW_AXE,SHOOTED,
//        #endregion

//        #region Pipe
//        NORMAL_GATE_PIPE,
//        GATE_PIPE_UP,
//        GATE_PIPE_DOWN,
//        TELEPORT,
//        #endregion

//        #region.Mario
//        MARIO_ATTACK,
//        MARIO_DOWN,
//        MARIO_UP,
//        MARIO_DOWNCAST,
//        MARIO_UPCAST,
//        MARIO_RUN,
//        MARIO_INVINCIBLE,
//        MARIO_STAND,
//        MARIO_JUMP,
//        MARIO_STRIPPED,
//        MARIO_WIN,
//        MARIO_AUTO_RUN,
//        MARIO_STOP,
//        #endregion

//        #region.Turtle
//        SPIN,HIDE,
//        #endregion
//    }

//    public class CObject
//    {
//        protected IDObject m_IDObject;
//        protected CSprite m_Sprite;
//        protected Vector2 m_Position; 
//        protected Vector2 m_StartPosition; 
//        protected IDStatus m_Status;
//        private int m_Index;

//        public int Index
//        {
//            get { return m_Index; }
//            set { m_Index = value; }
//        }
//        protected bool m_IsAlive;
//        protected bool m_IsVisible;
//        protected bool m_IsColliable; // có khả năng va chạm

//        #region. Get & Set Propertiese

//        public IDObject IDObject
//        {
//            get { return m_IDObject; }
//            set { m_IDObject = value; }
//        }

//        public Rectangle Rectangle
//        {
//            get { return new Rectangle((int)m_Position.X, (int)m_Position.Y, m_Sprite.FrameWidht, m_Sprite.FrameHeight); }
//        }

//        public CSprite Sprite
//        {
//            get { return m_Sprite; }
//            set { m_Sprite = value; }
//        }

//        public Vector2 Position
//        {
//            get { return m_Position; }
//            set { m_Position = value; }
//        }

//        public Vector2 StartPosition
//        {
//            get { return m_StartPosition; }
//            set { m_StartPosition = value; }
//        }

//        public IDStatus Status
//        {
//            get { return m_Status; }
//            set { m_Status = value; }
//        }

//        public bool IsAlive
//        {
//            get { return m_IsAlive; }
//            set { m_IsVisible = value; }
//        }

//        public bool IsVisible
//        {
//            get { return m_IsVisible; }
//            set { m_IsVisible = value; }
//        }

//        public bool IsColliable
//        {
//            get { return m_IsColliable; }
//            set { m_IsColliable = value; }
//        }

//        #endregion

//        public CObject(Vector2 _Position)
//        {
//            m_Position = _Position;
//            m_StartPosition = m_Position;
//            m_Sprite = null;
//            //m_Status = IDStatus.ALIVE;
//            m_IsAlive = true;
//            m_IsVisible = false;
//            m_IsColliable = false;
//            m_Index = ++GlobalValue.OBJECT_INDEX;
//        }

//        public CObject(IDObject _IDObject, Vector2 _Position)
//        {
//            m_IDObject = _IDObject;
//            m_Position = _Position;
//            m_StartPosition = m_Position;
//            m_Sprite = null;
//            //m_Status = IDStatus.ALIVE;
//            m_IsAlive = true;
//            m_IsVisible = false;
//            m_IsColliable = true;
//        }

//        virtual public void Init()
//        { 

//        }

//        virtual public void SetItem(CAnimationObject _Item)
//        {

//        }

//        virtual public void UpdateAnimation(GameTime _GameTime, CInput _Input)
//        {
//            _Input.Update();
//            m_Sprite.UpdateAnimation(_GameTime);
//        }

//        virtual public void UpdateMovement(GameTime _GameTime, CInput _Input)
//        {
//            //_Input.Update();
//        }

//        virtual public void UpdateCollision(CAnimationObject _Object)
//        { 
            
//        }

//        virtual public void Draw(SpriteBatch _SpriteBatch)
//        {
//            m_Sprite.Position = m_Position;
//            m_Sprite.Draw(_SpriteBatch);
//        }
//    }
//}
