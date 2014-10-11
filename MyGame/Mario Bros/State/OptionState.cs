using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Mario_Bros.Framework.GameState;
using Mario_Bros.Object.Buttons;
using Mario_Bros.Framework;
using Microsoft.Xna.Framework;

namespace Mario_Bros.State
{
    class OptionState : GameState
    {
        private List<Buttons> m_ListButtons;
        public List<Buttons> ListButtons
        {
            get { return m_ListButtons; }
            set { m_ListButtons = value; }
        }
        public OptionState(IDGameState _ID)
            : base(_ID)
        {
            m_ListButtons = new List<Buttons>();
            CResourceManager.GetInstance().GetResource(IDResource.ICON).Position = new Vector2(110, 120);
        }

        public override void InitState(Microsoft.Xna.Framework.Content.ContentManager CM)
        {
            ListButtons.Add(new BtnEffSounds(Framework.IDResource.SOUND_Btn_Act,new Microsoft.Xna.Framework.Vector2(130,120)));
            ListButtons.Add(new BtnBGSounds(Framework.IDResource.BGSOUND_Btn, new Microsoft.Xna.Framework.Vector2(130, 150)));
            ListButtons.Add(new BtnReturnMenu(Framework.IDResource.RETURN_Btn, new Microsoft.Xna.Framework.Vector2(130, 180)));
            base.InitState(CM);
        }
        public override void HandleInput(Microsoft.Xna.Framework.GameTime gameTime, Framework.CInput _Input)
        {
            #region Move icon
            if (CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.Y >= 120 &&
                CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.Y <= 180)
            {
                if (_Input.KeyPressed(Microsoft.Xna.Framework.Input.Keys.Down))
                {
                    SoundManager.PlaySound(ESound.SFX_COIN);
                    if (CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.Y == 180)
                        CResourceManager.GetInstance().GetResource(IDResource.ICON).Position = new Vector2(110, 120);
                    else
                    {
                        CResourceManager.GetInstance().GetResource(IDResource.ICON).Position =
                            new Vector2(CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.X,
                                        CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.Y + 30);
                    }
                }
                if (_Input.KeyPressed(Microsoft.Xna.Framework.Input.Keys.Up))
                {
                    SoundManager.PlaySound(ESound.SFX_COIN);
                    if (CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.Y == 120)
                        CResourceManager.GetInstance().GetResource(IDResource.ICON).Position = new Vector2(110, 180);
                    else
                    {
                        CResourceManager.GetInstance().GetResource(IDResource.ICON).Position =
                            new Vector2(CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.X,
                                        CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.Y - 30);
                    }
                }
            }
            #endregion

            #region BtnStatuts
            if (_Input.KeyPressed(Microsoft.Xna.Framework.Input.Keys.Enter) ||
                _Input.KeyPressed(Microsoft.Xna.Framework.Input.Keys.Space))
            {
                if (CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.Y == 120)
                {
                    GlobalSetting.IsSoundEffect = !GlobalSetting.IsSoundEffect;
                }
                if (CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.Y == 150)
                {
                    GlobalSetting.IsSoundBG = !GlobalSetting.IsSoundBG;
                    SoundManager.MuteSong();
                }
                if (CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.Y == 180)
                {
                    StateManager.getInst().ExitScreen();
                    StateManager.getInst().AddScreen(new MenuState(IDGameState.MENU));
                }
            }

            if (CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.Y == 180)
            {
                ListButtons[2].Focus = true;
            }
            else
                ListButtons[2].Focus = false;

            if (GlobalSetting.IsSoundEffect)
                ListButtons[0].Focus = true;
            else
                ListButtons[0].Focus = false;
            if (GlobalSetting.IsSoundBG)
                ListButtons[1].Focus = true;
            else
                ListButtons[1].Focus = false;
            #endregion

            base.HandleInput(gameTime, _Input);
        }
        public override void Update(Microsoft.Xna.Framework.GameTime gameTime)
        {
            for (int i = 0; i < ListButtons.Count; i++)
                ListButtons[i].Update();
            base.Update(gameTime);
        }
        public override void Draw(Microsoft.Xna.Framework.Graphics.SpriteBatch SB)
        {
            SB.Begin();
            CResourceManager.GetInstance().GetResource(IDResource.OPTION).Draw(SB);
            for (int i = 0; i < ListButtons.Count; i++)
                ListButtons[i].Draw(SB);
            CResourceManager.GetInstance().GetResource(IDResource.ICON).Draw(SB);
            SB.End();
            base.Draw(SB);
        }
    }
}
