using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Media;
using Microsoft.Xna.Framework.Graphics;

namespace Mario_Bros.Framework
{
    public enum IDResource
    {
        #region Font
        FONT,
        LETTER_A,
        LETTER_B,
        LETTER_C,
        LETTER_D,
        LETTER_E,
        LETTER_F,
        LETTER_G,
        LETTER_H,
        LETTER_I,
        LETTER_J,
        LETTER_K,
        LETTER_L,
        LETTER_M,
        LETTER_N,
        LETTER_O,
        LETTER_P,
        LETTER_Q,
        LETTER_R,
        LETTER_S,
        LETTER_T,
        LETTER_U,
        LETTER_V,
        LETTER_W,
        LETTER_X,
        LETTER_Y,
        LETTER_Z,
        LETTER_0,
        LETTER_1,
        LETTER_2,
        LETTER_3,
        LETTER_4,
        LETTER_5,
        LETTER_6,
        LETTER_7,
        LETTER_8,
        LETTER_9,
        LETTER_MULTI,
        LETTER_DASH,
        LETTER_EXCLAMATION,
        LETTER_COPY_RIGHT,
        #endregion

        #region IDObject
        SMALL_MARIO,
        SUPER_MARIO,
        FIRE_MARIO,
        SMALL_MARIO_INVICIBILITY,
        SMALL_MARIO_INVICIBILITY2,
        SMALL_MARIO_INVICIBILITY3,
        BIG_MARIO_INVICIBILITY,
        BIG_MARIO_INVICIBILITY2,
        BIG_MARIO_INVICIBILITY3,
        BULLET,
        MISC_BASE_BRICK,
        MISC_QUESTION_BRICK,
        MISC_IRON_BRICK,
        MISC_SOFT_BRICK,
        MISC_PIECE_1,
        MISC_PIECE_2,
        MISC_STOCK_PIPE,
        MISC_GATE_PIPE,
        MISC_UP_PIPE,
        MISC_SMALL_GRASS,
        MISC_MEDIUM_GRASS,
        MISC_BIG_GRASS,
        MISC_BIG_MOUNTAIN,
        MISC_MEDIUM_MOUNTAIN,
        MISC_HARD_BRICK,
        MISC_GOAL_POLE,
        MISC_FLAG,
        MISC_CASTLE,
        MISC_STAR_FLAG_CASTLE,
        MISC_FIREWORK,
        ITEM_COIN_ACTIVATED,
        ITEM_COIN_NORMAL,
        ITEM_FIRE_FLOWER,
        ITEM_SUPER_MUSHROOM,
        ITEM_1UP_MUSHROOM,
        ITEM_STARMAN,
        ENEMY_GOOMBA_OW,
        ENEMY_KOOPA_OW,
        ENEMY_HIDE_KOOPA_OW,
        MISC_SMALL_CLOUND,
        MISC_MEDIUM_CLOUND,
        MISC_BIG_CLOUND,
        ENEMY_BOSS_BULLET,
        ENEMY_BOSS,
        #endregion



        #region Code Danh
        INTRO_1,
        INTRO_2,
        BLACK,

        GAME_OVER,
        MENU,
        LOAD,
        ABOUT_Btn,
        ABOUT_Btn_Act,
        EXIT_Btn,
        EXIT_Btn_Act,
        NEWGAME_Btn,
        NEWGAME_Btn_Act,
        OPTION_Btn,
        OPTION_Btn_Act,
        ICON,
        ICON_COIN,

        OPTION,
        SOUND_Btn,
        SOUND_Btn_Act,
        BGSOUND_Btn,
        BGOUND_Btn_Act,
        RETURN_Btn,
        RETURN_Btn_Act,

        ABOUTBG, 
        #endregion
    }

    public class CResourceManager
    {
        #region Font
        private SpriteFont Font;
        private CSprite Letter_A;
        private CSprite Letter_B;
        private CSprite Letter_C;
        private CSprite Letter_D;
        private CSprite Letter_E;
        private CSprite Letter_F;
        private CSprite Letter_G;
        private CSprite Letter_H;
        private CSprite Letter_I;
        private CSprite Letter_J;
        private CSprite Letter_K;
        private CSprite Letter_L;
        private CSprite Letter_M;
        private CSprite Letter_N;
        private CSprite Letter_O;
        private CSprite Letter_P;
        private CSprite Letter_Q;
        private CSprite Letter_R;
        private CSprite Letter_S;
        private CSprite Letter_T;
        private CSprite Letter_U;
        private CSprite Letter_V;
        private CSprite Letter_W;
        private CSprite Letter_X;
        private CSprite Letter_Y;
        private CSprite Letter_Z;
        private CSprite Letter_0;
        private CSprite Letter_1;
        private CSprite Letter_2;
        private CSprite Letter_3;
        private CSprite Letter_4;
        private CSprite Letter_5;
        private CSprite Letter_6;
        private CSprite Letter_7;
        private CSprite Letter_8;
        private CSprite Letter_9;
        private CSprite Letter_Multi;
        private CSprite Letter_Copy_Right;
        private CSprite Letter_Dash;
        private CSprite Letter_Exclamation;
        #endregion

        #region CSprite
        private CSprite Sprite_Small_Mario;
        private CSprite Sprite_Super_Mario;
        private CSprite Sprite_Fire_Mario;
        private CSprite Sprite_Base_Brick;
        private CSprite Sprite_Question_Brick;
        private CSprite Sprite_Iron_Brick;
        private CSprite Sprite_Soft_Brick;
        private CSprite Sprite_Piece_1;
        private CSprite Sprite_Piece_2;
        private CSprite Sprite_Normal_Coin;
        private CSprite Sprite_Activated_Coin;
        private CSprite Sprite_Fire_Flower;
        private CSprite Sprite_Super_Mushroom;
        private CSprite Sprite_1_Up_Mushroom;
        private CSprite Sprite_Starman;
        private CSprite Sprite_GoomBa_OW;
        private CSprite Sprite_Koopa_OW;
        private CSprite Sprite_Hide_Koopa_OW;
        private CSprite Sprite_Stock_Pipe;
        private CSprite Sprite_Gate_Pipe;
        private CSprite Sprite_Up_Pipe;
        private CSprite Sprite_Small_Grass;
        private CSprite Sprite_Medium_Grass;
        private CSprite Sprite_Big_Grass;
        private CSprite Sprite_Big_Mountain;
        private CSprite Sprite_Medium_Mountain;
        private CSprite Sprite_Hard_Brick;
        private CSprite Sprite_Bullet;
        private CSprite Sprite_Flag;
        private CSprite Sprite_Goal_Pole;
        private CSprite Sprite_Castle;
        private CSprite Sprite_Big_Invi;
        private CSprite Sprite_Big_Invi2;
        private CSprite Sprite_Big_Invi3;
        private CSprite Sprite_Small_Invi;
        private CSprite Sprite_Small_Invi2;
        private CSprite Sprite_Small_Invi3;
        private CSprite Sprite_Star_Flag_Castle;
        private CSprite Sprite_Firework;
        private CSprite Sprite_Small_Clound;
        private CSprite Sprite_Medium_Clound;
        private CSprite Sprite_Big_Clound;
        private CSprite Sprite_Boss;
        private CSprite Sprite_Boss_Bullet;
        #endregion


        #region Intro CSprite
        private CSprite m_Intro1;
        private CSprite m_Intro2;
        private CSprite m_Black;
        #endregion
        #region Menu CSprite
        private CSprite m_BGMenu;
        private CSprite Btn_About;
        private CSprite Btn_About_Act;
        private CSprite Btn_Exit;
        private CSprite Btn_Exit_Act;
        private CSprite Btn_NewGame;
        private CSprite Btn_NewGame_Act;
        private CSprite Btn_Option;
        private CSprite Btn_Option_Act;
        private CSprite Icon;
        private CSprite Icon_Coin;
        #endregion
        #region Option CSprite
        private CSprite m_BGOption;
        private CSprite Btn_Sound;
        private CSprite Btn_Sound_Act;
        private CSprite Btn_BGSound;
        private CSprite Btn_BGSound_Act;
        private CSprite Btn_Return;
        private CSprite Btn_Return_Act;

        private CSprite m_BGAbout;
        #endregion


        #region Game Over
        private CSprite BG_GameOver;
        #endregion

        #region Load Game
        private CSprite BG_LoadGame;
        #endregion
        private static CResourceManager m_ResourceManager;

        private CResourceManager()
        {

            #region CSprite
            Sprite_Small_Mario = new CSprite(IDResource.SMALL_MARIO, 9, 16, 16, 9);
            Sprite_Super_Mario = new CSprite(IDResource.SUPER_MARIO, 9, 16, 32, 9);
            Sprite_Fire_Mario = new CSprite(IDResource.FIRE_MARIO, 9, 16, 32, 9);
            Sprite_Big_Invi = new CSprite(IDResource.BIG_MARIO_INVICIBILITY, 9, 16, 32, 9);
            Sprite_Big_Invi2 = new CSprite(IDResource.BIG_MARIO_INVICIBILITY2, 9, 16, 32, 9);
            Sprite_Big_Invi3 = new CSprite(IDResource.BIG_MARIO_INVICIBILITY3, 9, 16, 32, 9);
            Sprite_Small_Invi = new CSprite(IDResource.SMALL_MARIO_INVICIBILITY, 9, 16, 16, 9);
            Sprite_Small_Invi2 = new CSprite(IDResource.SMALL_MARIO_INVICIBILITY2, 9, 16, 16, 9);
            Sprite_Small_Invi3 = new CSprite(IDResource.SMALL_MARIO_INVICIBILITY3, 9, 16, 16, 9);
            Sprite_Base_Brick = new CSprite(IDResource.MISC_BASE_BRICK, 1, 16, 16, 7);
            Sprite_Question_Brick = new CSprite(IDResource.MISC_QUESTION_BRICK, 4, 16, 16, 4);
            Sprite_Iron_Brick = new CSprite(IDResource.MISC_IRON_BRICK, 1, 16, 16, 1);
            Sprite_Activated_Coin = new CSprite(IDResource.ITEM_COIN_ACTIVATED, 4, 16, 16, 4);
            Sprite_Normal_Coin = new CSprite(IDResource.ITEM_COIN_NORMAL, 4, 16, 16, 4);
            Sprite_Fire_Flower = new CSprite(IDResource.ITEM_FIRE_FLOWER, 4, 16, 16, 4);
            Sprite_Super_Mushroom = new CSprite(IDResource.ITEM_SUPER_MUSHROOM, 4, 16, 16, 4);
            Sprite_1_Up_Mushroom = new CSprite(IDResource.ITEM_1UP_MUSHROOM, 4, 16, 16, 4);
            Sprite_Starman = new CSprite(IDResource.ITEM_STARMAN, 4, 16, 16, 4);
            Sprite_GoomBa_OW = new CSprite(IDResource.ENEMY_GOOMBA_OW, 3, 16, 16, 3);
            Sprite_Koopa_OW = new CSprite(IDResource.ENEMY_KOOPA_OW, 6, 16, 24, 6);
            Sprite_Piece_1 = new CSprite(IDResource.MISC_PIECE_1, 1, 16, 16, 1);
            Sprite_Piece_2 = new CSprite(IDResource.MISC_PIECE_2, 1, 16, 16, 1);
            Sprite_Soft_Brick = new CSprite(IDResource.MISC_SOFT_BRICK, 1, 16, 16, 1);
            Sprite_Stock_Pipe = new CSprite(IDResource.MISC_STOCK_PIPE, 1, 32, 16, 1);
            Sprite_Gate_Pipe = new CSprite(IDResource.MISC_GATE_PIPE, 1, 32, 16, 1);
            Sprite_Up_Pipe = new CSprite(IDResource.MISC_UP_PIPE, 1, 62, 32, 1);
            Sprite_Big_Grass = new CSprite(IDResource.MISC_BIG_GRASS, 1, 64, 16, 1);
            Sprite_Medium_Grass = new CSprite(IDResource.MISC_MEDIUM_GRASS, 1, 48, 16, 1);
            Sprite_Small_Grass = new CSprite(IDResource.MISC_SMALL_GRASS, 1, 32, 16, 1);
            Sprite_Medium_Mountain = new CSprite(IDResource.MISC_MEDIUM_MOUNTAIN, 1, 48, 24, 1);
            Sprite_Big_Mountain = new CSprite(IDResource.MISC_BIG_MOUNTAIN, 1, 80, 35, 1);
            Sprite_Hard_Brick = new CSprite(IDResource.MISC_HARD_BRICK, 1, 16, 16, 1);
            Sprite_Hide_Koopa_OW = new CSprite(IDResource.ENEMY_HIDE_KOOPA_OW, 2, 16, 16, 2);
            Sprite_Bullet = new CSprite(IDResource.BULLET, 4, 8, 8, 2);
            Sprite_Goal_Pole = new CSprite(IDResource.MISC_GOAL_POLE, 1, 8, 136, 1);
            Sprite_Flag = new CSprite(IDResource.MISC_FLAG, 1, 16, 16, 1);
            Sprite_Castle = new CSprite(IDResource.MISC_CASTLE, 1, 80, 80, 1);
            Sprite_Star_Flag_Castle = new CSprite(IDResource.MISC_STAR_FLAG_CASTLE, 1, 16, 32, 1);
            Sprite_Firework = new CSprite(IDResource.MISC_FIREWORK, 3, 16, 16, 1);

            BG_GameOver = new CSprite(IDResource.GAME_OVER, 1, 368, 224, 1);
            BG_LoadGame = new CSprite(IDResource.LOAD, 1, 368, 224, 1);
            Sprite_Small_Clound = new CSprite(IDResource.MISC_SMALL_CLOUND, 1, 32, 24, 1);
            Sprite_Medium_Clound = new CSprite(IDResource.MISC_MEDIUM_CLOUND, 1, 48, 24, 1);
            Sprite_Big_Clound = new CSprite(IDResource.MISC_BIG_CLOUND, 1, 64, 24, 1);
            Sprite_Boss = new CSprite(IDResource.ENEMY_BOSS, 4, 32, 32, 4);
            Sprite_Boss_Bullet = new CSprite(IDResource.ENEMY_BOSS_BULLET, 2, 24, 8, 1);
            #endregion

            #region Letter
            Letter_A = new CSprite(IDResource.LETTER_A, 1, 8, 8, 1);
            Letter_B = new CSprite(IDResource.LETTER_B, 1, 8, 8, 1);
            Letter_C = new CSprite(IDResource.LETTER_C, 1, 8, 8, 1);
            Letter_D = new CSprite(IDResource.LETTER_D, 1, 8, 8, 1);
            Letter_E = new CSprite(IDResource.LETTER_E, 1, 8, 8, 1);
            Letter_F = new CSprite(IDResource.LETTER_F, 1, 8, 8, 1);
            Letter_G = new CSprite(IDResource.LETTER_G, 1, 8, 8, 1);
            Letter_H = new CSprite(IDResource.LETTER_H, 1, 8, 8, 1);
            Letter_I = new CSprite(IDResource.LETTER_I, 1, 8, 8, 1);
            Letter_J = new CSprite(IDResource.LETTER_J, 1, 8, 8, 1);
            Letter_K = new CSprite(IDResource.LETTER_K, 1, 8, 8, 1);
            Letter_L = new CSprite(IDResource.LETTER_L, 1, 8, 8, 1);
            Letter_M = new CSprite(IDResource.LETTER_M, 1, 8, 8, 1);
            Letter_N = new CSprite(IDResource.LETTER_N, 1, 8, 8, 1);
            Letter_O = new CSprite(IDResource.LETTER_O, 1, 8, 8, 1);
            Letter_P = new CSprite(IDResource.LETTER_P, 1, 8, 8, 1);
            Letter_Q = new CSprite(IDResource.LETTER_Q, 1, 8, 8, 1);
            Letter_R = new CSprite(IDResource.LETTER_R, 1, 8, 8, 1);
            Letter_S = new CSprite(IDResource.LETTER_S, 1, 8, 8, 1);
            Letter_T = new CSprite(IDResource.LETTER_T, 1, 8, 8, 1);
            Letter_U = new CSprite(IDResource.LETTER_U, 1, 8, 8, 1);
            Letter_V = new CSprite(IDResource.LETTER_V, 1, 8, 8, 1);
            Letter_W = new CSprite(IDResource.LETTER_W, 1, 8, 8, 1);
            Letter_X = new CSprite(IDResource.LETTER_X, 1, 8, 8, 1);
            Letter_Y = new CSprite(IDResource.LETTER_Y, 1, 8, 8, 1);
            Letter_Z = new CSprite(IDResource.LETTER_Z, 1, 8, 8, 1);
            Letter_0 = new CSprite(IDResource.LETTER_0, 1, 8, 8, 1);
            Letter_1 = new CSprite(IDResource.LETTER_1, 1, 8, 8, 1);
            Letter_2 = new CSprite(IDResource.LETTER_2, 1, 8, 8, 1);
            Letter_3 = new CSprite(IDResource.LETTER_3, 1, 8, 8, 1);
            Letter_4 = new CSprite(IDResource.LETTER_4, 1, 8, 8, 1);
            Letter_5 = new CSprite(IDResource.LETTER_5, 1, 8, 8, 1);
            Letter_6 = new CSprite(IDResource.LETTER_6, 1, 8, 8, 1);
            Letter_7 = new CSprite(IDResource.LETTER_7, 1, 8, 8, 1);
            Letter_8 = new CSprite(IDResource.LETTER_8, 1, 8, 8, 1);
            Letter_9 = new CSprite(IDResource.LETTER_9, 1, 8, 8, 1);
            Letter_Multi = new CSprite(IDResource.LETTER_MULTI, 1, 8, 8, 1);
            Letter_Dash = new CSprite(IDResource.LETTER_DASH, 1, 8, 8, 1);
            Letter_Copy_Right = new CSprite(IDResource.LETTER_COPY_RIGHT, 1, 8, 8, 1);
            Letter_Exclamation = new CSprite(IDResource.LETTER_EXCLAMATION, 1, 8, 8, 1);
            #endregion

            #region Intro
            m_Intro1 = new CSprite(IDResource.INTRO_1, 1, 368, 224, 1);
            m_Intro2 = new CSprite(IDResource.INTRO_2, 1, 368, 224, 1);
            m_Black = new CSprite(IDResource.BLACK, 1, 368, 224, 1);
            #endregion
            #region Menu
            m_BGMenu = new CSprite(IDResource.MENU, 1, 368, 224, 1);
            Btn_About = new CSprite(IDResource.ABOUT_Btn, 1, 64, 8, 1);
            Btn_About_Act = new CSprite(IDResource.ABOUT_Btn_Act, 1, 64, 8, 1);
            Btn_Exit = new CSprite(IDResource.EXIT_Btn, 1, 64, 8, 1);
            Btn_Exit_Act = new CSprite(IDResource.EXIT_Btn_Act, 1, 64, 8, 1);
            Btn_NewGame = new CSprite(IDResource.NEWGAME_Btn, 1, 64, 8, 1);
            Btn_NewGame_Act = new CSprite(IDResource.NEWGAME_Btn_Act, 1, 64, 8, 1);
            Btn_Option = new CSprite(IDResource.OPTION_Btn, 1, 64, 8, 1);
            Btn_Option_Act = new CSprite(IDResource.OPTION_Btn_Act, 1, 64, 8, 1);
            Icon = new CSprite(IDResource.ICON, 1, 8, 8, 1);
            Icon_Coin = new CSprite(IDResource.ICON_COIN, 3, 8, 8, 3);
            #endregion
            #region Option
            m_BGOption = new CSprite(IDResource.OPTION, 1, 368, 224, 1);
            Btn_Sound = new CSprite(IDResource.SOUND_Btn, 1, 90, 20, 1);
            Btn_Sound_Act = new CSprite(IDResource.SOUND_Btn_Act, 1, 90, 20, 1);
            Btn_Return = new CSprite(IDResource.RETURN_Btn, 1, 390, 120, 1);
            Btn_Return_Act = new CSprite(IDResource.RETURN_Btn_Act, 1, 90, 20, 1);
            Btn_BGSound = new CSprite(IDResource.BGSOUND_Btn, 1, 90, 20, 1);
            Btn_BGSound_Act = new CSprite(IDResource.BGOUND_Btn_Act, 1, 90, 20, 1);
            m_BGAbout = new CSprite(IDResource.ABOUTBG, 1, 368, 224, 1);
            #endregion
        }

        public static CResourceManager GetInstance()
        {
            if (m_ResourceManager == null)
                m_ResourceManager = new CResourceManager();
            return m_ResourceManager;

        }

        public void Init(ContentManager _ContentManager)
        {
            Font = _ContentManager.Load<SpriteFont>("Font/font");
            #region Font
            Letter_A.Init(_ContentManager, "Image/Game State Image/Font/Letter/A", 0, 0, 0.0f);
            Letter_B.Init(_ContentManager, "Image/Game State Image/Font/Letter/B", 0, 0, 0.0f);
            Letter_C.Init(_ContentManager, "Image/Game State Image/Font/Letter/C", 0, 0, 0.0f);
            Letter_D.Init(_ContentManager, "Image/Game State Image/Font/Letter/D", 0, 0, 0.0f);
            Letter_E.Init(_ContentManager, "Image/Game State Image/Font/Letter/E", 0, 0, 0.0f);
            Letter_F.Init(_ContentManager, "Image/Game State Image/Font/Letter/F", 0, 0, 0.0f);
            Letter_G.Init(_ContentManager, "Image/Game State Image/Font/Letter/G", 0, 0, 0.0f);
            Letter_H.Init(_ContentManager, "Image/Game State Image/Font/Letter/H", 0, 0, 0.0f);
            Letter_I.Init(_ContentManager, "Image/Game State Image/Font/Letter/I", 0, 0, 0.0f);
            Letter_J.Init(_ContentManager, "Image/Game State Image/Font/Letter/J", 0, 0, 0.0f);
            Letter_K.Init(_ContentManager, "Image/Game State Image/Font/Letter/K", 0, 0, 0.0f);
            Letter_L.Init(_ContentManager, "Image/Game State Image/Font/Letter/L", 0, 0, 0.0f);
            Letter_M.Init(_ContentManager, "Image/Game State Image/Font/Letter/M", 0, 0, 0.0f);
            Letter_N.Init(_ContentManager, "Image/Game State Image/Font/Letter/N", 0, 0, 0.0f);
            Letter_O.Init(_ContentManager, "Image/Game State Image/Font/Letter/O", 0, 0, 0.0f);
            Letter_P.Init(_ContentManager, "Image/Game State Image/Font/Letter/P", 0, 0, 0.0f);
            Letter_Q.Init(_ContentManager, "Image/Game State Image/Font/Letter/Q", 0, 0, 0.0f);
            Letter_R.Init(_ContentManager, "Image/Game State Image/Font/Letter/R", 0, 0, 0.0f);
            Letter_S.Init(_ContentManager, "Image/Game State Image/Font/Letter/S", 0, 0, 0.0f);
            Letter_T.Init(_ContentManager, "Image/Game State Image/Font/Letter/T", 0, 0, 0.0f);
            Letter_U.Init(_ContentManager, "Image/Game State Image/Font/Letter/U", 0, 0, 0.0f);
            Letter_V.Init(_ContentManager, "Image/Game State Image/Font/Letter/V", 0, 0, 0.0f);
            Letter_W.Init(_ContentManager, "Image/Game State Image/Font/Letter/W", 0, 0, 0.0f);
            Letter_X.Init(_ContentManager, "Image/Game State Image/Font/Letter/X", 0, 0, 0.0f);
            Letter_Y.Init(_ContentManager, "Image/Game State Image/Font/Letter/Y", 0, 0, 0.0f);
            Letter_Z.Init(_ContentManager, "Image/Game State Image/Font/Letter/Z", 0, 0, 0.0f);
            Letter_0.Init(_ContentManager, "Image/Game State Image/Font/Letter/0", 0, 0, 0.0f);
            Letter_1.Init(_ContentManager, "Image/Game State Image/Font/Letter/1", 0, 0, 0.0f);
            Letter_2.Init(_ContentManager, "Image/Game State Image/Font/Letter/2", 0, 0, 0.0f);
            Letter_3.Init(_ContentManager, "Image/Game State Image/Font/Letter/3", 0, 0, 0.0f);
            Letter_4.Init(_ContentManager, "Image/Game State Image/Font/Letter/4", 0, 0, 0.0f);
            Letter_5.Init(_ContentManager, "Image/Game State Image/Font/Letter/5", 0, 0, 0.0f);
            Letter_6.Init(_ContentManager, "Image/Game State Image/Font/Letter/6", 0, 0, 0.0f);
            Letter_7.Init(_ContentManager, "Image/Game State Image/Font/Letter/7", 0, 0, 0.0f);
            Letter_8.Init(_ContentManager, "Image/Game State Image/Font/Letter/8", 0, 0, 0.0f);
            Letter_9.Init(_ContentManager, "Image/Game State Image/Font/Letter/9", 0, 0, 0.0f);
            Letter_Exclamation.Init(_ContentManager, "Image/Game State Image/Font/Punctuation/Exclamation", 0, 0, 0.0f);
            Letter_Dash.Init(_ContentManager, "Image/Game State Image/Font/Punctuation/Dash", 0, 0, 0.0f);
            Letter_Copy_Right.Init(_ContentManager, "Image/Game State Image/Font/Punctuation/CopyRight", 0, 0, 0.0f);
            Letter_Multi.Init(_ContentManager, "Image/Game State Image/Font/Punctuation/Multi", 0, 0, 0.0f);
            #endregion Font

            #region Sprite
            Sprite_Small_Clound.Init(_ContentManager, "Image/Game Image/Miscellaneous/SmallClound-32-24", 0, 0, 0.0f);
            Sprite_Medium_Clound.Init(_ContentManager, "Image/Game Image/Miscellaneous/MediumClound-48-24", 0, 0, 0.0f);
            Sprite_Big_Clound.Init(_ContentManager, "Image/Game Image/Miscellaneous/BigClound-64-24", 0, 0, 0.0f);
            Sprite_Castle.Init(_ContentManager, "Image/Game Image/Miscellaneous/Castle-80-80", 0, 0, 0.0f);
            Sprite_Iron_Brick.Init(_ContentManager, "Image/Game Image/Miscellaneous/BrickIron-16-16", 0, 0, 0.0f);
            Sprite_Question_Brick.Init(_ContentManager, "Image/Game Image/Miscellaneous/BrickQuestion-64-16", 0, 3, 250.0f);
            Sprite_Base_Brick.Init(_ContentManager, "Image/Game Image/Miscellaneous/BaseBrick-16-16", 0, 0, 0.0f);
            Sprite_Piece_1.Init(_ContentManager, "Image/Game Image/Miscellaneous/MiscPiece-1-16-16", 0, 0, 0.0f);
            Sprite_Piece_2.Init(_ContentManager, "Image/Game Image/Miscellaneous/MiscPiece-2-16-16", 0, 0, 0.0f);
            Sprite_Soft_Brick.Init(_ContentManager, "Image/Game Image/Miscellaneous/BrickSoft-16-16", 0, 0, 0.0f);
            Sprite_Gate_Pipe.Init(_ContentManager, "Image/Game Image/Miscellaneous/PipeGate-32-16", 0, 0, 0.0f);
            Sprite_Stock_Pipe.Init(_ContentManager, "Image/Game Image/Miscellaneous/PipeStock-32-16", 0, 0, 0.0f);
            Sprite_Up_Pipe.Init(_ContentManager, "Image/Game Image/Miscellaneous/PipeUp-62-32", 0, 0, 0.0f);
            Sprite_Small_Grass.Init(_ContentManager, "Image/Game Image/Miscellaneous/SmallGrass-32-16", 0, 0, 0.0f);
            Sprite_Medium_Grass.Init(_ContentManager, "Image/Game Image/Miscellaneous/MediumGrass-48-16", 0, 0, 0.0f);
            Sprite_Big_Grass.Init(_ContentManager, "Image/Game Image/Miscellaneous/BigGrass-64-16", 0, 0, 0.0f);
            Sprite_Big_Mountain.Init(_ContentManager, "Image/Game Image/Miscellaneous/BigMountain-80-35", 0, 0, 0.0f);
            Sprite_Medium_Mountain.Init(_ContentManager, "Image/Game Image/Miscellaneous/MediumMountain-48-24", 0, 0, 0.0f);
            Sprite_Hard_Brick.Init(_ContentManager, "Image/Game Image/Miscellaneous/HardBrick-16-16", 0, 0, 0.0f);
            Sprite_Small_Mario.Init(_ContentManager, "Image/Game Image/Mario/MarioSmall-144-16", 0, 0, 0.0f);
            Sprite_Super_Mario.Init(_ContentManager, "Image/Game Image/Mario/MarioSuper-144-32", 0, 0, 0.0f);
            Sprite_Fire_Mario.Init(_ContentManager, "Image/Game Image/Mario/MarioFire-144-32", 0, 0, 0.0f);
            Sprite_Small_Invi.Init(_ContentManager, "Image/Game Image/Mario/SmallMarioInvincibility-144-16", 0, 0, 0.0f);
            Sprite_Small_Invi2.Init(_ContentManager, "Image/Game Image/Mario/SmallMarioInvincibility2-144-16", 0, 0, 0.0f);
            Sprite_Small_Invi3.Init(_ContentManager, "Image/Game Image/Mario/SmallMarioInvincibility3-144-16", 0, 0, 0.0f);
            Sprite_Big_Invi.Init(_ContentManager, "Image/Game Image/Mario/BigMarioInvincibility-144-32", 0, 0, 0.0f);
            Sprite_Big_Invi2.Init(_ContentManager, "Image/Game Image/Mario/BigMarioInvincibility2-144-32", 0, 0, 0.0f);
            Sprite_Big_Invi3.Init(_ContentManager, "Image/Game Image/Mario/BigMarioInvincibility3-144-32", 0, 0, 0.0f);
            Sprite_Normal_Coin.Init(_ContentManager, "Image/Game Image/Item/ItemNormalCoin-64-16", 0, 3, 200.0f);
            Sprite_Activated_Coin.Init(_ContentManager, "Image/Game Image/Item/ItemActivatedCoin-64-16", 0, 3, 50.0f);
            Sprite_Fire_Flower.Init(_ContentManager, "Image/Game Image/Item/ItemFireFlower-64-16", 0, 3, 50.0f);
            Sprite_Super_Mushroom.Init(_ContentManager, "Image/Game Image/Item/ItemSuperMushroom-16-16", 0, 0, 0.0f);
            Sprite_1_Up_Mushroom.Init(_ContentManager, "Image/Game Image/Item/Item1UpMushroom-16-16", 0, 0, 0.0f);
            Sprite_Starman.Init(_ContentManager, "Image/Game Image/Item/ItemStarman-64-16", 0, 3, 50.0f);
            Sprite_GoomBa_OW.Init(_ContentManager, "Image/Game Image/Enemy/GoomBa-48-16-OW", 0, 2, 200.0f);
            Sprite_Koopa_OW.Init(_ContentManager, "Image/Game Image/Enemy/Koopa-96-24-OW", 0, 1, 200.0f);
            Sprite_Hide_Koopa_OW.Init(_ContentManager, "Image/Game Image/Enemy/HideKoopa-32-16-OW", 0, 0, 0.0f);
            Sprite_Bullet.Init(_ContentManager, "Image/Game Image/Mario/BulletMario-16-16", 0, 3, 80.0f);
            Sprite_Flag.Init(_ContentManager, "Image/Game Image/Miscellaneous/Flag-16-16", 0, 0, 0.0f);
            Sprite_Goal_Pole.Init(_ContentManager, "Image/Game Image/Miscellaneous/GoalPole-16-136", 0, 0, 0.0f);
            Sprite_Star_Flag_Castle.Init(_ContentManager, "Image/Game Image/Miscellaneous/CastleStarFlag-16-16", 0, 0, 0.0f);
            Sprite_Firework.Init(_ContentManager, "Image/Game Image/Miscellaneous/Firework-16-48", 0, 2, 100.0f);
            Sprite_Boss.Init(_ContentManager, "Image/Game Image/Enemy/BossGreen-128-32", 0, 3, 100.0f);
            Sprite_Boss_Bullet.Init(_ContentManager, "Image/Game Image/Enemy/BossBullet-24-16", 0, 1, 20.0f);
            BG_GameOver.Init(_ContentManager, "Image/Game State Image/GameOver/GameOver", 0, 0, 0.0f);
            BG_LoadGame.Init(_ContentManager, "Image/Game State Image/Load/LoadGame", 0, 0, 0.0f); 
            #endregion
            
            // Danh's code
            #region CSprite Intro,Menu,Option
            m_Intro1.Init(_ContentManager, @"Image\Game State Image\Intro\Intro_Gameuit", 0, 0, 100);
            m_Intro2.Init(_ContentManager, @"Image\Game State Image\Intro\intro_SV", 0, 0, 100);
            m_Black.Init(_ContentManager, @"Image\Game State Image\Intro\BG", 0, 0, 100);
            m_BGMenu.Init(_ContentManager, @"Image\Game State Image\Menu\BGMenu", 0, 0, 100);
            Btn_About.Init(_ContentManager, @"Image\Game State Image\Menu\btn_About", 0, 0, 100);
            Btn_About_Act.Init(_ContentManager, @"Image\Game State Image\Menu\btn_About_Act", 0, 0, 100);
            Btn_Exit.Init(_ContentManager, @"Image\Game State Image\Menu\btn_Exit", 0, 0, 100);
            Btn_Exit_Act.Init(_ContentManager, @"Image\Game State Image\Menu\btn_Exit_Act", 0, 0, 100);
            Btn_NewGame.Init(_ContentManager, @"Image\Game State Image\Menu\btn_newGame", 0, 0, 100);
            Btn_NewGame_Act.Init(_ContentManager, @"Image\Game State Image\Menu\btn_newGame_Act", 0, 0, 100);
            Btn_Option.Init(_ContentManager, @"Image\Game State Image\Menu\btn_Option", 0, 0, 100);
            Btn_Option_Act.Init(_ContentManager, @"Image\Game State Image\Menu\btn_Option_Act", 0, 0, 100);
            Icon.Init(_ContentManager, @"Image\Game State Image\Menu\Icon", 0, 0, 0.0f);
            Icon_Coin.Init(_ContentManager, "Image/Game State Image/Load/IconCoin-24-8", 0, 2, 150.0f);

            m_BGOption.Init(_ContentManager, @"Image\Game State Image\Option\BG_option", 0, 0, 100);
            Btn_BGSound.Init(_ContentManager, @"Image\Game State Image\Option\BG_Sounds", 0, 0, 100);
            Btn_BGSound_Act.Init(_ContentManager, @"Image\Game State Image\Option\BG_Sounds_Act", 0, 0, 100);
            Btn_Return.Init(_ContentManager, @"Image\Game State Image\Option\ReturnMenu", 0, 0, 100);
            Btn_Return_Act.Init(_ContentManager, @"Image\Game State Image\Option\ReturnMenu_Act", 0, 0, 100);
            Btn_Sound.Init(_ContentManager, @"Image\Game State Image\Option\Eff_Sounds", 0, 0, 100);
            Btn_Sound_Act.Init(_ContentManager, @"Image\Game State Image\Option\Eff_Sounds_Act", 0, 0, 100);
            m_BGAbout.Init(_ContentManager, @"Image\Game State Image\About\BGAbout", 0, 0, 100);
            #endregion
        }

        public SpriteFont GetFont(IDResource _ID)
        {
            switch (_ID)
            {
                case IDResource.FONT:
                    return Font;
                default:
                    return null;
            }
        }

        public CSprite GetSpriteFromChar(char _Char)
        {
            switch (_Char)
            {
                case '-':
                    return Letter_Dash;
                case '@':
                    return Letter_Copy_Right;
                case '*':
                    return Letter_Multi;
                case '!':
                    return Letter_Exclamation;
                case 'a':
                case 'A':
                    return Letter_A;
                case 'b':
                case 'B':
                    return Letter_B;
                case 'c':
                case 'C':
                    return Letter_C;
                case 'd':
                case 'D':
                    return Letter_D;
                case 'e':
                case 'E':
                    return Letter_E;
                case 'f':
                case 'F':
                    return Letter_F;
                case 'g':
                case 'G':
                    return Letter_G;
                case 'h':
                case 'H':
                    return Letter_H;
                case 'i':
                case 'I':
                    return Letter_I;
                case 'j':
                case 'J':
                    return Letter_J;
                case 'k':
                case 'K':
                    return Letter_K;
                case 'l':
                case 'L':
                    return Letter_L;
                case 'm':
                case 'M':
                    return Letter_M;
                case 'o':
                case 'O':
                    return Letter_O;
                case 'n':
                case 'N':
                    return Letter_N;
                case 'p':
                case 'P':
                    return Letter_P;
                case 'q':
                case 'Q':
                    return Letter_Q;
                case 'r':
                case 'R':
                    return Letter_R;
                case 's':
                case 'S':
                    return Letter_S;
                case 't':
                case 'T':
                    return Letter_T;
                case 'u':
                case 'U':
                    return Letter_U;
                case 'v':
                case 'V':
                    return Letter_V;
                case 'w':
                case 'W':
                    return Letter_W;
                case 'x':
                case 'X':
                    return Letter_X;
                case 'y':
                case 'Y':
                    return Letter_Y;
                case 'z':
                case 'Z':
                    return Letter_Z;
                case '0':
                    return Letter_0;
                case '1':
                    return Letter_1;
                case '2':
                    return Letter_2;
                case '3':
                    return Letter_3;
                case '4':
                    return Letter_4;
                case '5':
                    return Letter_5;
                case '6':
                    return Letter_6;
                case '7':
                    return Letter_7;
                case '8':
                    return Letter_8;
                case '9':
                    return Letter_9;
                default:
                    return null;
            }
        }

        public CSprite GetResource(IDResource _ID)
        {
            switch(_ID)
            {
                #region Sprite
                case IDResource.ENEMY_BOSS:
                    return Sprite_Boss;
                case IDResource.ENEMY_BOSS_BULLET:
                    return Sprite_Boss_Bullet;
                case IDResource.MISC_BIG_CLOUND:
                    return Sprite_Big_Clound;
                case IDResource.MISC_MEDIUM_CLOUND:
                    return Sprite_Medium_Clound;
                case IDResource.MISC_SMALL_CLOUND:
                    return Sprite_Small_Clound;
                case IDResource.MISC_FIREWORK:
                    return Sprite_Firework;
                case IDResource.MISC_STAR_FLAG_CASTLE:
                    return Sprite_Star_Flag_Castle;
                case IDResource.BIG_MARIO_INVICIBILITY:
                    return Sprite_Big_Invi;
                case IDResource.BIG_MARIO_INVICIBILITY2:
                    return Sprite_Big_Invi2;
                case IDResource.BIG_MARIO_INVICIBILITY3:
                    return Sprite_Big_Invi3;
                case IDResource.SMALL_MARIO_INVICIBILITY:
                    return Sprite_Small_Invi;
                case IDResource.SMALL_MARIO_INVICIBILITY2:
                    return Sprite_Small_Invi2;
                case IDResource.SMALL_MARIO_INVICIBILITY3:
                    return Sprite_Small_Invi3;
                case IDResource.MISC_CASTLE:
                    return Sprite_Castle;
                case IDResource.MISC_FLAG:
                    return Sprite_Flag;
                case IDResource.MISC_GOAL_POLE:
                    return Sprite_Goal_Pole;
                case IDResource.ICON_COIN:
                    return Icon_Coin;
                case IDResource.LOAD:
                    return BG_LoadGame;
                case IDResource.BULLET:
                    return Sprite_Bullet;
                case IDResource.ENEMY_HIDE_KOOPA_OW:
                    return Sprite_Hide_Koopa_OW;
                case IDResource.MISC_HARD_BRICK:
                    return Sprite_Hard_Brick;
                case IDResource.MISC_BIG_MOUNTAIN:
                    return Sprite_Big_Mountain;
                case IDResource.MISC_MEDIUM_MOUNTAIN:
                    return Sprite_Medium_Mountain;
                case IDResource.MISC_BIG_GRASS:
                    return Sprite_Big_Grass;
                case IDResource.MISC_MEDIUM_GRASS:
                    return Sprite_Medium_Grass;
                case IDResource.MISC_SMALL_GRASS:
                    return Sprite_Small_Grass;
                case IDResource.MISC_UP_PIPE:
                    return Sprite_Up_Pipe;
                case IDResource.MISC_STOCK_PIPE:
                    return Sprite_Stock_Pipe;
                case IDResource.MISC_GATE_PIPE:
                    return Sprite_Gate_Pipe;
                case IDResource.MISC_SOFT_BRICK:
                    return Sprite_Soft_Brick;
                case IDResource.MISC_PIECE_1:
                    return Sprite_Piece_1;
                case IDResource.MISC_PIECE_2:
                    return Sprite_Piece_2;
                case IDResource.GAME_OVER:
                    return BG_GameOver;
                case IDResource.ENEMY_GOOMBA_OW:
                    return Sprite_GoomBa_OW;
                case IDResource.ENEMY_KOOPA_OW:
                    return Sprite_Koopa_OW;
                case IDResource.ITEM_1UP_MUSHROOM:
                    return Sprite_1_Up_Mushroom;
                case IDResource.ITEM_FIRE_FLOWER:
                    return Sprite_Fire_Flower;
                case IDResource.ITEM_SUPER_MUSHROOM:
                    return Sprite_Super_Mushroom;
                case IDResource.ITEM_STARMAN:
                    return Sprite_Starman;
                case IDResource.ITEM_COIN_NORMAL:
                    return Sprite_Normal_Coin;
                case IDResource.ITEM_COIN_ACTIVATED:
                    return Sprite_Activated_Coin;
                case IDResource.MISC_IRON_BRICK:
                    return Sprite_Iron_Brick;
                case IDResource.MISC_QUESTION_BRICK:
                    return Sprite_Question_Brick;
                case IDResource.MISC_BASE_BRICK:
                    return Sprite_Base_Brick;
                case IDResource.SMALL_MARIO:
                    return Sprite_Small_Mario;
                case IDResource.SUPER_MARIO:
                    return Sprite_Super_Mario;
                case IDResource.FIRE_MARIO:
                    return Sprite_Fire_Mario;
                #endregion
                #region State
                case IDResource.INTRO_1:
                    return m_Intro1;
                case IDResource.INTRO_2:
                    return m_Intro2;
                case IDResource.BLACK:
                    return m_Black;
                case IDResource.MENU:
                    return m_BGMenu;
                case IDResource.ABOUT_Btn:
                    return Btn_About;
                case IDResource.ABOUT_Btn_Act:
                    return Btn_About_Act;
                case IDResource.EXIT_Btn:
                    return Btn_Exit;
                case IDResource.EXIT_Btn_Act:
                    return Btn_Exit_Act;
                case IDResource.NEWGAME_Btn:
                    return Btn_NewGame;
                case IDResource.NEWGAME_Btn_Act:
                    return Btn_NewGame_Act;
                case IDResource.OPTION_Btn:
                    return Btn_Option;
                case IDResource.OPTION_Btn_Act:
                    return Btn_Option_Act;
                case IDResource.ICON:
                    return Icon;
                case IDResource.OPTION:
                    return m_BGOption;
                case IDResource.SOUND_Btn:
                    return Btn_Sound;
                case IDResource.SOUND_Btn_Act:
                    return Btn_Sound_Act;
                case IDResource.BGSOUND_Btn:
                    return Btn_BGSound;
                case IDResource.BGOUND_Btn_Act:
                    return Btn_BGSound_Act;
                case IDResource.RETURN_Btn:
                    return Btn_Return;
                case IDResource.RETURN_Btn_Act:
                    return Btn_Return_Act;
                case IDResource.ABOUTBG:
                    return m_BGAbout;
                default:
                    return null;
                #endregion
            }
        }

        //public SoundEffect GetSoundEffect(IDResource _ID)
        //{
        //    switch (_ID)
        //    {
        //        case IDResource.SFX_MARIO_HURT:
        //            return sfx_mario_hurt;
        //        case IDResource.SFX_1_UP:
        //            return sfx_1_up;
        //        case IDResource.SFX_BREAKBLOCK:
        //            return sfx_breakblock;
        //        case IDResource.SFX_BUMP:
        //            return sfx_bump;
        //        case IDResource.SFX_COIN:
        //            return sfx_coin;
        //        case IDResource.SFX_FIREBALL:
        //            return sfx_fireball;
        //        case IDResource.SFX_FIREWORK:
        //            return sfx_firework;
        //        case IDResource.SFX_FLAGPOLE:
        //            return sfx_flagpole;
        //        case IDResource.SFX_GAMEOVER:
        //            return sfx_gameover;
        //        case IDResource.SFX_JUMP_SMALL:
        //            return sfx_jump_small;
        //        case IDResource.SFX_JUMP_BIG:
        //            return sfx_jump_big;
        //        case IDResource.SFX_KICK:
        //            return sfx_kick;
        //        case IDResource.SFX_MARIO_DIE:
        //            return sfx_mario_die;
        //        case IDResource.SFX_PAUSE:
        //            return sfx_pause;
        //        case IDResource.SFX_PIPE:
        //            return sfx_pipe;
        //        case IDResource.SFX_POWER_UP:
        //            return sfx_power_up;
        //        case IDResource.SFX_ITEM_APPEAR:
        //            return sfx_item_appear;
        //        case IDResource.SFX_STAGE_CLEAR:
        //            return sfx_stage_clear;
        //        case IDResource.SFX_STOMP:
        //            return sfx_stomp;
        //        case IDResource.SFX_VINE:
        //            return sfx_vine;
        //        case IDResource.SFX_WARNING:
        //            return sfx_warning;
        //        case IDResource.SFX_WORLD_CLEAR:
        //            return sfx_world_clear;
        //        default:
        //            return null;
        //    }
        //}

        //public Song GetSong(IDResource _ID)
        //{
        //    switch (_ID)
        //    {
        //        case IDResource.SONG_INTRO:
        //            return m_IntroSong;
        //        case IDResource.SONG_THEMSONG_OW:
        //            return m_ThemeSong;
        //        default:
        //            return null;
        //    }
        //}
    }
}
