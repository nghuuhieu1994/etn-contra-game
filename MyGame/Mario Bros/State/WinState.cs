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
    class WinState : GameState
    {
        private CSprite Icon;
        private float CoolDown = 0;
        private string World_Name;
        public WinState(IDGameState _ID)
            : base(_ID)
        {
        }
        public override void InitState(ContentManager CM)
        {
            MediaPlayer.Stop();
            Icon = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.ICON_COIN));
            Icon.Position = new Vector2(145, 10);
            base.InitState(CM);
        }

        public override void HandleInput(GameTime gameTime, CInput _Input)
        {
            CoolDown += (float)gameTime.ElapsedGameTime.TotalMilliseconds;
            if (CoolDown > 2000)
            {
                CoolDown = 0;
                StateManager.getInst().ExitScreen();
                StateManager.getInst().AddScreen(new MenuState(IDGameState.MENU));
            }
            GlobalValue.IS_LOCK_KEYBOARD = false;
            base.HandleInput(gameTime, _Input);
        }
        public override void Update(GameTime gameTime)
        {
            //Icon.UpdateAnimation(gameTime);
            base.Update(gameTime);
        }
        public override void Draw(SpriteBatch SB)
        {
            World_Name = GlobalSetting.m_IDLevel.ToString() + "-1";
            SB.Begin();
            CResourceManager.GetInstance().GetResource(IDResource.BLACK).Draw(SB);
            StateManager.StringDrawer("MARIO", new Vector2(0, 0), SB, Color.White);
            StateManager.StringDrawer(GlobalValue.MARIO_SCORE.ToString().PadLeft(6, '0'), new Vector2(0, 8), SB, Color.White);
            StateManager.StringDrawer("WORLD", new Vector2(200, 0), SB, Color.White);
            //StateManager.StringDrawer(World_Name, new Vector2(205, 8), SB, Color.White);
            StateManager.StringDrawer("TIME", new Vector2(336, 0), SB, Color.White);
            StateManager.StringDrawer(" * ", new Vector2(150, 10), SB, Color.White);
            //StateManager.StringDrawer(((int)(MathHelper.Clamp(GlobalValue.TIME_LEFT, 0, 400))).ToString(), new Vector2(340, 8), SB, Color.White);
            StateManager.StringDrawer("YOU WIN!", new Vector2(150, 100), SB, Color.White);
            StateManager.StringDrawer(GlobalValue.MARIO_COIN.ToString().PadLeft(2, '0'), new Vector2(162, 9), SB, Color.White);
            Icon.Draw(SB);
            SB.End();
            base.Draw(SB);
        }
    }
}