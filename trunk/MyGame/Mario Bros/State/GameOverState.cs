using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Mario_Bros.Framework.GameState;
using Mario_Bros.Framework;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;

namespace Mario_Bros.State
{
    class GameOverState : GameState
    {
        float CoolDown = 0;
        public GameOverState(IDGameState _ID)
            : base(_ID)
        {
        }

        public override void InitState(ContentManager CM)
        {
            SoundManager.PlaySound(ESound.SFX_GAMEOVER);
            base.InitState(CM);
        }
        public override void HandleInput(GameTime gameTime, CInput _Input)
        {
            CoolDown += (float)gameTime.ElapsedGameTime.TotalMilliseconds;
            if (CoolDown > 5000)
            {
                
                StateManager.getInst().ExitScreen();
                StateManager.getInst().AddScreen(new MenuState(IDGameState.MENU));
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
            CResourceManager.GetInstance().GetResource(IDResource.GAME_OVER).Draw(SB);
            SB.End();
            base.Draw(SB);
        }
    }
}
