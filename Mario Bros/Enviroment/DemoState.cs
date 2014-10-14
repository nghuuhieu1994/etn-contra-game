using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;
using Mario_Bros.Framework;
using Mario_Bros.Object;
using Mario_Bros.Framework.Quadtree;
using Mario_Bros.Framework.GameState;
using Mario_Bros.State;

namespace Mario_Bros.Enviroment
{
    public class DemoState : Microsoft.Xna.Framework.Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        
        // CInput
        CInput m_Input;

        bool m_IsPause = false;

        float _fps, _eLapsedTime;

        public DemoState()
        {
            graphics = new GraphicsDeviceManager(this);

            Content.RootDirectory = "Content";
            graphics.PreferredBackBufferHeight = 224;
            graphics.PreferredBackBufferWidth = 368;
            graphics.ApplyChanges();
        }

        protected override void Initialize()
        {
            CResourceManager.GetInstance().Init(Content);
            SoundManager.LoadContent(Content);
            _fps = _eLapsedTime = 0;
            m_Input = new CInput();
            StateManager.getInst().Content = Content;
            StateManager.getInst().AddScreen(new IntroState(IDGameState.INTRO));
            StateManager.getInst().m_Game = this;
            
            base.Initialize();
        }

        protected override void LoadContent()
        {
            
            spriteBatch = new SpriteBatch(GraphicsDevice);
            base.LoadContent();
            
        }

        protected override void UnloadContent()
        {
            base.UnloadContent();
        }

        protected override void Update(GameTime gameTime)
        {
            if (GlobalSetting.IsExit)
                this.Exit();
            m_Input.Update();
            if (m_Input.KeyDown(Keys.Pause))
            {
                m_IsPause = !m_IsPause;
            }
            if (!m_IsPause)
            {
                StateManager.getInst().HandleInput(gameTime, m_Input);
                StateManager.getInst().Update(gameTime); 
            }
            base.Update(gameTime);
        }

        protected override void Draw(GameTime gameTime)
        {
            #region FPS
            _fps++;
            _eLapsedTime += (float)gameTime.ElapsedGameTime.TotalMilliseconds;
            if (_eLapsedTime > 1000.0f)
            {
                this.Window.Title = "Mario FPS: " + (_fps / _eLapsedTime) * 1000;
                _fps = 0;
                _eLapsedTime = 0;
            }
            #endregion

            //StateManager.getInst().spriteBatch = spriteBatch;
            GraphicsDevice.Clear(Color.CornflowerBlue);
            
            StateManager.getInst().Draw(spriteBatch);
            
            base.Draw(gameTime);
        }
    }

    static class Program
    {
        static void Main(string[] args)
        {
            using (DemoState game = new DemoState())
            {
                game.Run();
            }
        }
    }
}
