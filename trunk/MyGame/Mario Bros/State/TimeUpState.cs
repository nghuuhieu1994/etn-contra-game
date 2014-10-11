using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Mario_Bros.Framework.GameState;
using Mario_Bros.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Media;

namespace Mario_Bros.State
{
    class TimeUp : GameState
    {
        private float CoolDown = 0;
        public TimeUp(IDGameState _ID)
            : base(_ID)
        {
        }
        public override void InitState(ContentManager CM)
        {
            MediaPlayer.Stop();
            base.InitState(CM);
        }

        public override void HandleInput(GameTime gameTime, CInput _Input)
        {
            CoolDown += (float)gameTime.ElapsedGameTime.TotalMilliseconds;
            if (CoolDown > 5000)
            {
                if (GlobalValue.MARIO_LIFE > 0)
                {
                    StateManager.getInst().ExitScreen();
                    StateManager.getInst().AddScreen(new LoadGame(IDGameState.LOAD));
                }
                else
                {
                    StateManager.getInst().ExitScreen();
                    StateManager.getInst().AddScreen(new MainGame(IDGameState.MENU));
                }
            }
            base.HandleInput(gameTime, _Input);
        }
        public override void Update(GameTime gameTime)
        {
            base.Update(gameTime);
        }
        public override void Draw(SpriteBatch SB)
        {
            SB.Begin();
            CResourceManager.GetInstance().GetResource(IDResource.BLACK).Draw(SB);
            StateManager.StringDrawer("Time Up", new Vector2(158, 108), SB, Color.White);
            //StateManager.StringDrawer(GlobalValue.MARIO_LIFE.ToString(), new Vector2(192, 108), SB);
            SB.End();
            base.Draw(SB);
        }
    }
}

