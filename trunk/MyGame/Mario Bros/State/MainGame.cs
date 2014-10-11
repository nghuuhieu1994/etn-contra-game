using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Mario_Bros.Framework.GameState;
using Mario_Bros.Framework;
using Mario_Bros.Object;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Media;
using Mario_Bros.Framework.Quadtree;
using Mario_Bros.Map;
using Microsoft.Xna.Framework.Input;

namespace Mario_Bros.State
{
    class MainGame : GameState
    {
        // let's code ur maingame here
        // code them am thanh vao nha :v
        //bool m_isPlayDeathSound = false;
        //float TimeLeft = 0;
        float m_StopTime1 = 0;
        float delayFlag = 0;
        float delayStage = 0;
        Mario Mario;
        CCamera2D cam;
        List<CAnimationObject> list;
        QuadTree quadTree = null;
        CInput m_input;
        CSprite Icon;
        float PlayedTime = 0;
        bool IsWarning = false;
        string World_Name;
        string m_Map;
        CMap map;
        // test choi
        SpriteFont _font;
        public MainGame(IDGameState _ID)
            : base(_ID)
        { }
        public override void InitState(ContentManager CM)
        {
            GlobalValue.OBJECT_INDEX = 0;
            list = new List<CAnimationObject>();
            GlobalValue.KillBoss = false;
            m_Map = "map" + GlobalSetting.m_IDLevel.ToString() + ".xml";
            World_Name = GlobalSetting.m_IDLevel.ToString() + "-1";
            map = new CMap(m_Map);
            Build.BuildQNodeMap(map, Build.BuildObjectInMap(map));
            Mario = new Mario(GetPosMario._GetPosMario());
            MediaPlayer.IsRepeating = true;
            MediaPlayer.Stop();
            SoundManager.PlaySong(ESong.SONG_THEMSONG_OW);
            quadTree = Build.BuildQuadTree(Build.BuildQNodeMap(map, Build.BuildObjectInMap(map)));
            cam = new CCamera2D(StateManager.getInst().m_Game);
            m_input = new CInput();
            Icon = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.ICON_COIN));
            Icon.Position = new Vector2(145, 10);
            _font = CM.Load<SpriteFont>(@"Font/font");
            base.InitState(CM);
            
        }
        public override void HandleInput(GameTime gameTime, CInput _Input)
        {
            if (Mario.Status != IDStatus.MARIO_STOP)
            {
                PlayedTime += (float)gameTime.ElapsedGameTime.TotalMilliseconds;
                GlobalValue.TIME_LEFT = (int)(210 - PlayedTime / 1000);
            }

            if (PlayedTime > 180000 && !IsWarning)
            {
                SoundManager.PlaySound(ESound.SFX_WARNING);
                IsWarning = true;
            }
            
            if (PlayedTime > 210000)
            {
                --GlobalValue.MARIO_LIFE;
                StateManager.getInst().ExitScreen();
                StateManager.getInst().AddScreen(new TimeUp(IDGameState.TIME_UP));
            }

            Icon.UpdateAnimation(gameTime);
            Mario.UpdateAnimation(gameTime, m_input); 
            if (!Mario.IsMarioFreeze)
            {
                Mario.UpdateMovement(gameTime, m_input);
                if (Mario.Position.X < 0)
                {
                    Mario.Position = new Vector2(0, Mario.Position.Y);
                }
                if (Mario.Position.X + Mario.GetBound().Width >= map.m_WidthMap)
                {
                    Mario.Position = new Vector2(map.m_WidthMap - Mario.GetBound().Width, Mario.Position.Y);
                }
            }
            if(_Input.KeyDown(Keys.Back))
            {
                StateManager.getInst().ExitScreen();
                StateManager.getInst().AddScreen(new MenuState(IDGameState.MENU)); 
            }
            cam.Update(Mario, map.m_WidthMap, map.m_HeightMap);
            quadTree.InsertListObjectView(cam.Rectangle, quadTree.RootNode);
            if (GlobalValue.KillBoss)
            {
                for (int i = 0; i < list.Count; ++i)
                {
                    if (list[i].IDObject == IDObject.ENEMY_BOSS)
                    {
                        list[i].Status = IDStatus.DIE;
                    }
                }
            }
            for (int i = 0; i < GlobalValue.List_Of_Bullet.Count; i++)
            {
                GlobalValue.List_Of_Bullet[i].UpdateAnimation(gameTime, _Input);
                GlobalValue.List_Of_Bullet[i].UpdateMovement(gameTime, _Input);
                Mario.UpdateCollision(GlobalValue.List_Of_Bullet[i]);
                GlobalValue.List_Of_Bullet[i].UpdateCollision(Mario);
                if (GlobalValue.List_Of_Bullet[i].Status == IDStatus.DIE)
                {
                    GlobalValue.List_Of_Bullet.Remove(GlobalValue.List_Of_Bullet[i]);
                }
            }
            list = quadTree.ListObjectsInView;
            for (int i = 0; i < list.Count; ++i)
            {
                if (list[i].Status == IDStatus.DIE)
                {
                    //m_QuadTree.Tree.RemoveObject(list[i]);
                    //list[i] = null;
                    quadTree.RemoveObject(list[i], quadTree.RootNode);
                    list.Remove(list[i]);
                }
                else
                {
                    Mario.UpdateCollision(list[i]);
                    list[i].UpdateCollision(Mario);
                    for (int j = 0; j < list.Count; ++j)
                    {
                        list[j].UpdateCollision(list[i]);
                    }
                    if (!Mario.IsWorldFreeze)
                    {
                        list[i].UpdateAnimation(gameTime, m_input);
                        list[i].UpdateMovement(gameTime, m_input);
                    }
                }
            }
			
			if (Mario.Position.Y > GlobalValue.SCREEN_HEIGHT)
            {
                Mario.Status = IDStatus.DIE;
            }

            if (Mario.Status == IDStatus.DIE)
            {
                MediaPlayer.Stop();
                GlobalValue.MARIO_IDOBJECT = IDObject.SMALL_MARIO;
                m_StopTime1 += (float)gameTime.ElapsedGameTime.Milliseconds;

                for (int i = 0; i < GlobalValue.List_Of_Bullet.Count; i++)
                {
                    GlobalValue.List_Of_Bullet.Remove(GlobalValue.List_Of_Bullet[i]);
                }

                if (m_StopTime1 >= 2000.0f)
                {
                    --GlobalValue.MARIO_LIFE;
                    if (GlobalValue.MARIO_LIFE > 0)
                    {
                        StateManager.getInst().ExitScreen();
                        StateManager.getInst().AddScreen(new LoadGame(IDGameState.LOAD)); 
                    }
                    else
                    {
                        StateManager.getInst().ExitScreen();
                        StateManager.getInst().AddScreen(new GameOverState(IDGameState.GAMEOVER));
                    }
                }
            }
            
            if (Mario.Status == IDStatus.MARIO_STOP)
            {
                delayFlag += (float)gameTime.ElapsedGameTime.TotalMilliseconds;
                if (GlobalValue.TIME_LEFT > 0 && delayFlag > 50)
                {
                    GlobalValue.MARIO_SCORE += 200;
                    GlobalValue.TIME_LEFT -= 2;
                    delayFlag = 0;
                    SoundManager.PlaySound(ESound.SFX_COIN);
                }
            }

            if (GlobalValue.TIME_LEFT <= 0)
            {
                GlobalValue.GET_FLAG = true;
            }

            if (GlobalValue.GET_FLAG)
            {
                delayStage += (float)gameTime.ElapsedGameTime.TotalMilliseconds;
                if (delayStage > 3000)
                {
                    delayStage = 0;
                    GlobalValue.GET_FLAG = false;
                    GlobalSetting.m_IDLevel++;
                    GlobalValue.MARIO_IDOBJECT = Mario.IDObject;
                    if (GlobalSetting.m_IDLevel < 3)
                    {
                        StateManager.getInst().ExitScreen();
                        StateManager.getInst().AddScreen(new LoadGame(IDGameState.LOAD));
                    }
                    else
                    {
                        StateManager.getInst().ExitScreen();
                        StateManager.getInst().AddScreen(new WinState(IDGameState.WIN));
                    }
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
            SB.Begin(SpriteSortMode.FrontToBack, BlendState.AlphaBlend, null, null, null, null, cam.get_matrix_transform());
            for (int i = 0; i < list.Count; ++i)
            {
                list[i].Draw(SB);
            }
            Mario.Draw(SB);
            SB.End();
            SB.Begin();
            Icon.Draw(SB);
            //for (int i = 0; i < GlobalValue.List_Of_Bullet.Count; i++)
            //{
            //    GlobalValue.List_Of_Bullet[i].Draw(SB);
            //}
            StateManager.StringDrawer("MARIO", new Vector2(0, 0), SB, Color.White);
            StateManager.StringDrawer(GlobalValue.MARIO_SCORE.ToString().PadLeft(6, '0'), new Vector2(0, 8), SB, Color.White);
            StateManager.StringDrawer("WORLD", new Vector2(200, 0), SB, Color.White);
            StateManager.StringDrawer(World_Name, new Vector2(205, 8), SB, Color.White);
            StateManager.StringDrawer("TIME", new Vector2(336, 0), SB, Color.White);
            StateManager.StringDrawer(((int)(MathHelper.Clamp(GlobalValue.TIME_LEFT, 0, 400))).ToString(), new Vector2(340, 8), SB, Color.White);
            StateManager.StringDrawer(" * ", new Vector2(150, 10), SB, Color.White);
            StateManager.StringDrawer(GlobalValue.MARIO_COIN.ToString().PadLeft(2, '0'), new Vector2(162, 9), SB, Color.White);
            SB.End();
            base.Draw(SB);
        }
    }
}
