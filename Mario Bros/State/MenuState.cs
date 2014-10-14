using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Mario_Bros.Framework.GameState;
using Microsoft.Xna.Framework;
using Mario_Bros.Framework;
using Mario_Bros.Object.Buttons;
using Microsoft.Xna.Framework.Media;

namespace Mario_Bros.State
{
    class MenuState : GameState
    {
        private List<Buttons> m_ListButtons;
        public List<Buttons> ListButtons
        {
            get { return m_ListButtons; }
            set { m_ListButtons = value; }
        }
        public MenuState(IDGameState _ID)
            : base(_ID)
        {
            m_ListButtons = new List<Buttons>();
            CResourceManager.GetInstance().GetResource(IDResource.ICON).Position = new Vector2(85, 125);
            SoundManager.PlaySong(ESong.SONG_THEMSONG_OW);
            MediaPlayer.IsRepeating = true;
        }

        void Reset()
        {
          GlobalValue.MARIO_LIFE = 3;
          GlobalValue.MARIO_COIN = 0;
          GlobalValue.MARIO_PLAYED_TIME = 210;
          GlobalValue.MARIO_SCORE = 100;
          GlobalValue.GET_FLAG = false;
          GlobalValue.WORLD_FREEZE_TIME = 1500;
          GlobalValue.IS_WORLD_FREEZE = false;
          GlobalValue.IS_LOCK_KEYBOARD = false;
          GlobalValue.TRANSFORM_TIME = 1500;
          GlobalValue.INVINCIBLE_TIME = 8000;
          GlobalValue.TELEPORT_TIME = 1000;
          GlobalValue.IS_GO_DOWN = false;
          GlobalValue.IS_GO_UP = false;
          GlobalValue.OBJECT_INDEX = 0;
          GlobalValue.List_Of_Bullet = new List<CAnimationObject>();
          GlobalValue.KillBoss = false;
          GlobalValue.MARIO_IDOBJECT = IDObject.SMALL_MARIO;
          GlobalSetting.m_IDLevel = 0;
        }

        public override void InitState(Microsoft.Xna.Framework.Content.ContentManager CM)
        {
            Reset();
            m_ListButtons.Add(new BtnNewGame(IDResource.NEWGAME_Btn, new Vector2(95, 125)));
            m_ListButtons.Add(new BtnOption(IDResource.OPTION_Btn, new Vector2(95, 150)));
            m_ListButtons.Add(new BtnAbout(IDResource.ABOUT_Btn, new Vector2(205, 125)));
            m_ListButtons.Add(new BtnExit(IDResource.EXIT_Btn, new Vector2(205, 150)));
            base.InitState(CM);
        }
        public override void HandleInput(GameTime gameTime, CInput _Input)
        {
            #region Move icon
            if (CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.Y >= 125 &&
                CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.Y <= 150)
            {
                if (_Input.KeyPressed(Microsoft.Xna.Framework.Input.Keys.Down))
                {
                    SoundManager.PlaySound(ESound.SFX_COIN);
                    if (CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.Y == 150)
                    {
                        if (CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.X == 85)
                            CResourceManager.GetInstance().GetResource(IDResource.ICON).Position = new Vector2(85, 125);
                        else
                        {
                            CResourceManager.GetInstance().GetResource(IDResource.ICON).Position = new Vector2(195, 125);
                        }
                    }
                    else
                    {
                        CResourceManager.GetInstance().GetResource(IDResource.ICON).Position =
                            new Vector2(CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.X,
                                        CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.Y + 25);
                    }
                }

                if(_Input.KeyPressed(Microsoft.Xna.Framework.Input.Keys.Up))
                {
                    SoundManager.PlaySound(ESound.SFX_COIN);
                    if (CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.Y == 125)
                    {
                        if (CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.X == 85)
                            CResourceManager.GetInstance().GetResource(IDResource.ICON).Position = new Vector2(85, 150);
                        else
                        {
                            CResourceManager.GetInstance().GetResource(IDResource.ICON).Position = new Vector2(195, 150);
                        }
                    }
                    else
                    {
                        CResourceManager.GetInstance().GetResource(IDResource.ICON).Position =
                            new Vector2(CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.X,
                                        CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.Y - 25);
                    }
                }

                if (_Input.KeyPressed(Microsoft.Xna.Framework.Input.Keys.Right))
                {
                    SoundManager.PlaySound(ESound.SFX_COIN);
                    if (CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.X == 85)
                    {
                        CResourceManager.GetInstance().GetResource(IDResource.ICON).Position = new Vector2(195, CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.Y);
                    }
                    else
                    {
                        CResourceManager.GetInstance().GetResource(IDResource.ICON).Position = new Vector2(85, CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.Y);
                    }
                }

                if (_Input.KeyPressed(Microsoft.Xna.Framework.Input.Keys.Left))
                {
                    SoundManager.PlaySound(ESound.SFX_COIN);
                    if (CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.X == 85)
                    {
                        CResourceManager.GetInstance().GetResource(IDResource.ICON).Position = new Vector2(195, CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.Y);
                    }
                    else
                    {
                        CResourceManager.GetInstance().GetResource(IDResource.ICON).Position = new Vector2(85, CResourceManager.GetInstance().GetResource(IDResource.ICON).Position.Y);
                    }
                }
            }
            #endregion
            #region Btn stattuts
            Vector2 Temp = CResourceManager.GetInstance().GetResource(IDResource.ICON).Position;

            if (Temp == new Vector2(85, 125))
            {
                ListButtons[0].Focus = true;
            }
            else
                ListButtons[0].Focus = false;

            if (Temp == new Vector2(85, 150))
            {
                ListButtons[1].Focus = true;
            }
            else
            {
                ListButtons[1].Focus = false;
            }

            if (Temp == new Vector2(195, 125))
                ListButtons[2].Focus = true;
            else
                ListButtons[2].Focus = false;

            if (Temp == new Vector2(195, 150))
                ListButtons[3].Focus = true;
            else
                ListButtons[3].Focus = false;
            #endregion

            #region ChangeState
            if (_Input.KeyPressed(Microsoft.Xna.Framework.Input.Keys.Space) ||
                _Input.KeyPressed(Microsoft.Xna.Framework.Input.Keys.Enter))
            {
                if (ListButtons[0].Focus == true)
                {
                    GlobalValue.MARIO_LIFE = 3;
                    GlobalValue.MARIO_SCORE = 0;
                    GlobalValue.MARIO_COIN = 0;
                    StateManager.getInst().ExitScreen();
                    StateManager.getInst().AddScreen(new LoadGame(IDGameState.LOAD));
                }

                if (ListButtons[1].Focus == true)
                {
                    StateManager.getInst().ExitScreen();
                    StateManager.getInst().AddScreen(new OptionState(IDGameState.OPTION));
                }
                if (ListButtons[2].Focus == true)
                {
                    StateManager.getInst().ExitScreen();
                    StateManager.getInst().AddScreen(new AboutState(IDGameState.ABOUT));
                }
                if (ListButtons[3].Focus == true)
                {
                    StateManager.getInst().ClearAllScreen();
                    GlobalSetting.IsExit = !GlobalSetting.IsExit;
                }
            }
            #endregion
            base.HandleInput(gameTime, _Input);
        }
        public override void Update(GameTime gameTime)
        {
            for (int i = 0; i < m_ListButtons.Count; i++)
                m_ListButtons[i].Update();

            base.Update(gameTime);
        }
        public override void Draw(Microsoft.Xna.Framework.Graphics.SpriteBatch SB)
        {
            SB.Begin();
            CResourceManager.GetInstance().GetResource(IDResource.MENU).Draw(SB);
            for (int i = 0; i < ListButtons.Count; i++)
                ListButtons[i].Draw(SB);
            CResourceManager.GetInstance().GetResource(IDResource.ICON).Draw(SB);
            SB.End();
            base.Draw(SB);
        }
    }
}
