using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;
using Mario_Bros.Framework;

namespace Mario_Bros.Framework
{
    public enum ESong
    {
        SONG_THEMSONG_OW,
        SONG_INTRO,
    }
    public enum ESound
    {
        #region Sound Effect
        SFX_1_UP,
        SFX_BREAKBLOCK,
        SFX_BUMP,
        SFX_COIN,
        SFX_FIREBALL,
        SFX_FIREWORK,
        SFX_FLAGPOLE,
        SFX_GAMEOVER,
        SFX_JUMP_SMALL,
        SFX_JUMP_BIG,
        SFX_KICK,
        SFX_MARIO_DIE,
        SFX_PAUSE,
        SFX_PIPE,
        SFX_POWER_UP,
        SFX_ITEM_APPEAR,
        SFX_STAGE_CLEAR,
        SFX_STOMP,
        SFX_VINE,
        SFX_WARNING,
        SFX_WORLD_CLEAR,
        SFX_MARIO_HURT,
        #endregion
    }
    public static class SoundManager
    {
        // Enable the song is repeat
        public static bool IsRepeating = true;

        // var Member Song
        #region Sounds
        private static SoundEffect sfx_1_up;
        private static SoundEffect sfx_breakblock;
        private static SoundEffect sfx_bump;
        private static SoundEffect sfx_coin;
        private static SoundEffect sfx_fireball;
        private static SoundEffect sfx_firework;
        private static SoundEffect sfx_flagpole;
        private static SoundEffect sfx_gameover;
        private static SoundEffect sfx_jump_small;
        private static SoundEffect sfx_jump_big;
        private static SoundEffect sfx_kick;
        private static SoundEffect sfx_mario_die;
        private static SoundEffect sfx_mario_hurt;
        private static SoundEffect sfx_pause;
        private static SoundEffect sfx_pipe;
        private static SoundEffect sfx_power_up;
        private static SoundEffect sfx_item_appear;
        private static SoundEffect sfx_stage_clear;
        private static SoundEffect sfx_stomp;
        private static SoundEffect sfx_vine;
        private static SoundEffect sfx_warning;
        private static SoundEffect sfx_world_clear;
        #endregion
        #region Song
        private static Song m_ThemeSong;
        private static Song m_IntroSong;
        #endregion

        public static void LoadContent(ContentManager Content)
        {
            #region Sounds
            sfx_1_up = Content.Load<SoundEffect>("Audio/Game Audio/smb_1-up");
            sfx_breakblock = Content.Load<SoundEffect>("Audio/Game Audio/smb_breakblock");
            sfx_bump = Content.Load<SoundEffect>("Audio/Game Audio/smb_bump");
            sfx_coin = Content.Load<SoundEffect>("Audio/Game Audio/smb_coin");
            sfx_fireball = Content.Load<SoundEffect>("Audio/Game Audio/smb_fireball");
            sfx_firework = Content.Load<SoundEffect>("Audio/Game Audio/smb_fireworks");
            sfx_flagpole = Content.Load<SoundEffect>("Audio/Game Audio/smb_flagpole");
            sfx_gameover = Content.Load<SoundEffect>("Audio/Game Audio/smb_gameover");
            sfx_item_appear = Content.Load<SoundEffect>("Audio/Game Audio/smb_powerup_appears");
            sfx_jump_big = Content.Load<SoundEffect>("Audio/Game Audio/smb_jump-super");
            sfx_jump_small = Content.Load<SoundEffect>("Audio/Game Audio/smb_jump-small");
            sfx_kick = Content.Load<SoundEffect>("Audio/Game Audio/smb_kick");
            sfx_mario_die = Content.Load<SoundEffect>("Audio/Game Audio/smb_mariodie");
            sfx_mario_hurt = Content.Load<SoundEffect>("Audio/Game Audio/smb_mariohurt");
            sfx_pause = Content.Load<SoundEffect>("Audio/Game Audio/smb_pause");
            sfx_pipe = Content.Load<SoundEffect>("Audio/Game Audio/smb_pipe");
            sfx_power_up = Content.Load<SoundEffect>("Audio/Game Audio/smb_powerup");
            sfx_stage_clear = Content.Load<SoundEffect>("Audio/Game Audio/smb_stage_clear");
            sfx_stomp = Content.Load<SoundEffect>("Audio/Game Audio/smb_stomp");
            sfx_vine = Content.Load<SoundEffect>("Audio/Game Audio/smb_vine");
            sfx_warning = Content.Load<SoundEffect>("Audio/Game Audio/smb_warning");
            sfx_world_clear = Content.Load<SoundEffect>("Audio/Game Audio/smb_world_clear");
            m_ThemeSong = Content.Load<Song>("Audio/Song/ThemeSong");
            m_IntroSong = Content.Load<Song>("Audio/Song/Intro");
            #endregion
        }
        public static void PlaySound(ESound ID)
        {
            if (GlobalSetting.IsSoundEffect)
            {
                switch (ID)
                {
                    case ESound.SFX_1_UP:
                        if (sfx_1_up != null)
                            sfx_1_up.Play();
                        break;
                    case ESound.SFX_BREAKBLOCK:
                        if (sfx_breakblock != null)
                            sfx_breakblock.Play();
                        break;
                    case ESound.SFX_BUMP:
                        if (sfx_bump != null)
                            sfx_bump.Play();
                        break;
                    case ESound.SFX_COIN:
                        if (sfx_coin != null)
                            sfx_coin.Play();
                        break;
                    case ESound.SFX_FIREBALL:
                        if (sfx_fireball != null)
                            sfx_fireball.Play();
                        break;
                    case ESound.SFX_FIREWORK:
                        if (sfx_firework != null)
                            sfx_firework.Play();
                        break;
                    case ESound.SFX_FLAGPOLE:
                        if (sfx_flagpole != null)
                            sfx_flagpole.Play();
                        break;
                    case ESound.SFX_GAMEOVER:
                        if (sfx_gameover != null)
                            sfx_gameover.Play();
                        break;
                    case ESound.SFX_ITEM_APPEAR:
                        if (sfx_item_appear != null)
                            sfx_item_appear.Play();
                        break;
                    case ESound.SFX_JUMP_BIG:
                        if (sfx_jump_big != null)
                            sfx_jump_big.Play();
                        break;
                    case ESound.SFX_JUMP_SMALL:
                        if (sfx_jump_small != null)
                            sfx_jump_small.Play();
                        break;
                    case ESound.SFX_KICK:
                        if (sfx_kick != null)
                            sfx_kick.Play();
                        break;
                    case ESound.SFX_MARIO_DIE:
                        if (sfx_mario_die != null)
                            sfx_mario_die.Play();
                        break;
                    case ESound.SFX_MARIO_HURT:
                        if (sfx_mario_hurt != null)
                            sfx_mario_hurt.Play();
                        break;
                    case ESound.SFX_PAUSE:
                        if (sfx_pause != null)
                            sfx_pause.Play();
                        break;
                    case ESound.SFX_PIPE:
                        if (sfx_pipe != null)
                            sfx_pipe.Play();
                        break;
                    case ESound.SFX_POWER_UP:
                        if (sfx_power_up != null)
                            sfx_power_up.Play();
                        break;
                    case ESound.SFX_STAGE_CLEAR:
                        if (sfx_stage_clear != null)
                            sfx_stage_clear.Play();
                        break;
                    case ESound.SFX_STOMP:
                        if (sfx_stomp != null)
                            sfx_stomp.Play();
                        break;
                    case ESound.SFX_VINE:
                        if (sfx_vine != null)
                            sfx_vine.Play();
                        break;
                    case ESound.SFX_WARNING:
                        if (sfx_warning != null)
                            sfx_warning.Play();
                        break;
                    case ESound.SFX_WORLD_CLEAR:
                        if (sfx_world_clear != null)
                            sfx_world_clear.Play();
                        break;
                    default:
                        break;
                }
            }
        }
        public static void PlaySong(ESong ID)
        {
            if (GlobalSetting.IsSoundBG)
            {
                switch (ID)
                {
                    case ESong.SONG_INTRO:
                        if (m_IntroSong != null)
                        {
                            MediaPlayer.Play(m_IntroSong);
                        }
                        break;
                    case ESong.SONG_THEMSONG_OW:
                        if (m_ThemeSong != null)
                        {
                            MediaPlayer.Play(m_ThemeSong);
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        public static void MuteSong()
        {
            MediaPlayer.IsMuted = !MediaPlayer.IsMuted;
        }
        public static void StopSong()
        {
            MediaPlayer.Stop();
        }
    }
}
