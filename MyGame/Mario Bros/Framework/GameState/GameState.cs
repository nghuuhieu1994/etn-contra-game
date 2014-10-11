using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Mario_Bros.Framework.GameState
{
    public enum IDGameState
    {
        INTRO,
        MENU,
        OPTION,
        ABOUT,
        MAINGAME,
        QUIT,
        WIN,
        LOSE,
        PAUSE,
        GAMEOVER,
        LOAD,
        TIME_UP,
    }

    class GameState
    {
        protected IDGameState m_ID;

        public GameState(IDGameState _ID)
        {
            m_ID = _ID;
        }

        virtual public void InitState(ContentManager CM)
        { }

        virtual public void Update(GameTime gameTime) { }
        virtual public void HandleInput(GameTime gameTime, CInput _Input) { }
        virtual public void Release() { }
        virtual public void Draw(SpriteBatch SB)
        { }
        virtual public void ExitState() 
        {
            StateManager.getInst().ExitScreen();
        }
    }
}
