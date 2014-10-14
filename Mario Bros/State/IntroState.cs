using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Mario_Bros.Framework.GameState;
using Mario_Bros.Framework;
using Microsoft.Xna.Framework.Media;

namespace Mario_Bros.State
{
    class IntroState : GameState
    {
        float k = 0;
        float j = 0;
        float fade = 0.0087f;
        bool m_IsDrawLogo = false;
        bool m_IsDrawGroup = false;

        public IntroState(IDGameState _ID)
            : base(_ID)
        {
        }

        public override void InitState(Microsoft.Xna.Framework.Content.ContentManager CM)
        {
            SoundManager.PlaySong(ESong.SONG_THEMSONG_OW);
            //CResourceManager.GetInstance().GetSoundEffect(IDResource.SFX_INTRO).Play();
            base.InitState(CM);
        }
        public override void HandleInput(Microsoft.Xna.Framework.GameTime gameTime, Framework.CInput _Input)
        {
            if (_Input.KeyPressed(Microsoft.Xna.Framework.Input.Keys.Space) || j < 0)
            {
                //CResourceManager.GetInstance().GetSoundEffect(IDResource.SFX_INTRO).Dispose();
                MediaPlayer.Stop();
                StateManager.getInst().ExitScreen();
                StateManager.getInst().AddScreen(new MenuState(IDGameState.MENU));
            }
            base.HandleInput(gameTime, _Input);
        }
        public override void Update(Microsoft.Xna.Framework.GameTime gameTime)
        {
            CResourceManager.GetInstance().GetResource(IDResource.INTRO_1).Alpha = k;
            CResourceManager.GetInstance().GetResource(IDResource.INTRO_2).Alpha = j;
            //if (k > 1)
            //    j = 0.002f;

            //if (j == 0)
            //    k += 0.003f;
            //else
            //{
            //    k -= 0.003f;
            //}

            //if (k <= 0)
            //{
            //    j += 0.003f;
            //}
            //if (j > 1)
            //{
            //    j -= 0.003f;
            //}
            if (!m_IsDrawLogo)
            {
                k += fade;
                if (k > 1)
                {
                    fade *= -1;
                }
                if (k < 0)
                {
                    fade *= -1;
                    m_IsDrawLogo = true;
                }
            }
            if (m_IsDrawLogo && m_IsDrawGroup == false)
            {
                j += fade;
                if (j > 1)
                {
                    fade *= -1;
                }
                if (j < 0)
                {
                    
                    m_IsDrawGroup = true;
                }
            }


            base.Update(gameTime);
        }
        public override void Draw(Microsoft.Xna.Framework.Graphics.SpriteBatch SB)
        {
            SB.Begin();
            CResourceManager.GetInstance().GetResource(IDResource.BLACK).Draw(SB);
            CResourceManager.GetInstance().GetResource(IDResource.INTRO_1).Draw(SB);
            CResourceManager.GetInstance().GetResource(IDResource.INTRO_2).Draw(SB);
            SB.End();
            base.Draw(SB);
        }
    }
}
