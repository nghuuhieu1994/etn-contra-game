using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

namespace Mario_Bros.Framework.GameState
{
    class StateManager
    {
        public Game m_Game;
        private List<GameState> m_listState;
        public List<GameState> getListState()
        {
            if (m_listState == null)
                m_listState = new List<GameState>();

            return m_listState;
        }

        private ContentManager m_Content;
        public ContentManager Content
        {
            get { return m_Content; }
            set { m_Content = value; }
        }

        //private SpriteBatch m_SpriteBatch;
        //public SpriteBatch spriteBatch
        //{
        //    get { return spriteBatch; }
        //    set { spriteBatch = value; }
        //}

        protected StateManager(){}

        private static StateManager m_instance;
        public static StateManager getInst()
        {
            if (m_instance == null)
                m_instance = new StateManager();

            return m_instance;
        }

        public void Init()
        {
            if (getListState().Count != 0)
            {
                getListState()[getListState().Count - 1].InitState(Content);
            }
        }
        public void Update(GameTime gameTime)
        {
            if (getListState().Count != 0)
            {
                getListState()[getListState().Count - 1].Update(gameTime);
            }
        }
        public void HandleInput(GameTime gameTime, CInput Input)
        {
            if (getListState().Count != 0)
            {
                getListState()[getListState().Count - 1].HandleInput(gameTime, Input);
            }
        }
        public void Draw(SpriteBatch SB)
        {
            if (getListState().Count != 0)
            {
                getListState()[getListState().Count - 1].Draw(SB);
            }
        }

        public void AddScreen(GameState State)
        {
            if (getListState().Count != 0)
            {
                getListState()[getListState().Count - 1].Release();
            }
            getListState().Add(State);
            getListState()[getListState().Count - 1].InitState(Content);
        }

        public void RemoveScreen(GameState State)
        {
            if (getListState().Count != 0)
            {
                getListState().Remove(State);
            }
        }

        public void ClearAllScreen()
        {
            while (getListState().Count != 0)
                ExitScreen();
        }

        public void ExitScreen()
        {
            getListState().RemoveAt(getListState().Count - 1);
        }

        public static void StringDrawer(string _String, Vector2 _StartPosition, SpriteBatch _SpriteBatch, Color _Color)
        {
            Vector2 positionOfChar = _StartPosition;
            CSprite temp;
            for (int i = 0; i < _String.Count<char>(); i++)
            {
                if (_String[i] != ' ')
                {
                    temp = new CSprite(CResourceManager.GetInstance().GetSpriteFromChar(_String[i]));
                    temp.Position = positionOfChar;
                    temp.Color = _Color;
                    temp.Depth = 1.0f;
                    temp.Draw(_SpriteBatch); 
                }
                if (_String[i] == ' ')
                {
                    positionOfChar = new Vector2(positionOfChar.X + 4, positionOfChar.Y);
                }
                else
                {
                    positionOfChar = new Vector2(positionOfChar.X + 8, positionOfChar.Y);
                }
            }
        }
    }
}
