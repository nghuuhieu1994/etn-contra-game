using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Mario_Bros.Framework;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Mario_Bros.Object.Buttons
{
    //public enum IDButttons
    //{
    //    NEWGAME,
    //    OPTION,
    //    ABOUT,
    //    EXIT,
    //    SOUND,
    //    BGSOUND,
    //}
    public class Buttons
    {
        protected CSprite m_Sprite;
        protected bool IsFocus;
        protected IDResource m_ID;
        protected Vector2 Position;
        #region
        public CSprite Sprite
        {
            get { return m_Sprite; }
            set { m_Sprite = value; }
        }
        public bool Focus
        {
            get { return IsFocus; }
            set { IsFocus = value; }
        }
        public IDResource ID
        {
            get { return m_ID; }
            set { m_ID = value; }
        }
        #endregion

        public Buttons(IDResource _ID, Vector2 _pos)
        {
            IsFocus = false;
            ID = _ID;
            Sprite = CResourceManager.GetInstance().GetResource(ID);
           Position = _pos;
        }

        virtual public void Update()
        {
            Sprite.Position = Position;
        }

        virtual public void Draw(SpriteBatch SB)
        {
            Sprite.Draw(SB);
        }

    }
}
