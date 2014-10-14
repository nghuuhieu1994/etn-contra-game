using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Mario_Bros.Object;
using Microsoft.Xna.Framework.Graphics;
using Mario_Bros.Object.Miscellaneous;
using Mario_Bros.Object.Enemy;

namespace Mario_Bros.Framework.Quadtree
{
    public class Quadtree
    {
        NodeQuadtree m_Tree;

        List<BaseBrick> BaseList;
        QuestionBrick m_QuestionBrick;
        QuestionBrick m_QuestionBrick2;
        public NodeQuadtree Tree
        {
            get { return m_Tree; }
            set { m_Tree = value; }
        }

        public Quadtree()
        {
            m_Tree = new NodeQuadtree(Vector2.Zero, 3000, 1500);
            BaseList = new List<BaseBrick>();
        }

        public void Init()
        {
            m_QuestionBrick = new QuestionBrick(new Vector2(100, 155), IDObject.ITEM_STARMAN);
            m_QuestionBrick2 = new QuestionBrick(new Vector2(84, 155), IDObject.ITEM_FIRE_FLOWER);
            for (int i = 0; i < 100; i++)
            {
                BaseList.Add(new BaseBrick(new Vector2(i * CResourceManager.GetInstance().GetResource(IDResource.MISC_BASE_BRICK).FrameWidht, 224-16)));
            }

            for (int i = 0; i < BaseList.Count; i++)
            {
                m_Tree.AddObject(BaseList[i]);
            }
            m_Tree.AddObject(new Goomba(new Vector2(300, 200), IDDir.RIGHT));
            m_Tree.AddObject(new SoftBrick(new Vector2(116, 155)));
            m_Tree.AddObject(new Koopa(new Vector2(50, 174)));
            m_Tree.AddObject(m_QuestionBrick);
            m_Tree.AddObject(m_QuestionBrick.Item);
            m_Tree.AddObject(m_QuestionBrick2);
            m_Tree.AddObject(m_QuestionBrick2.Item);
            m_Tree.AddObject(new StockPipe(new Vector2(200, 224 - 32)));
            m_Tree.AddObject(new GatePipe(new Vector2(200, 224 - 48), IDStatus.GATE_PIPE_DOWN, new Vector2(650, 0)));
            m_Tree.AddObject(new ItemCoin(new Vector2(200, 100), IDObject.ITEM_COIN_NORMAL));
            m_Tree.AddObject(new BigMountain(new Vector2(300, 173)));
            int a = 2;
            while (a <= 9)
            {
                for (int i = 0; i < a; i++)
                {
                    m_Tree.AddObject(new HardBrick(new Vector2(700 - 16 * i, GlobalValue.SCREEN_HEIGHT - 16 * (11 - a))));
                }
                ++a;
            }
            m_Tree.AddObject(new GoalPole(new Vector2(815, GlobalValue.SCREEN_HEIGHT - 16 * 2 - 136)));
            m_Tree.AddObject(new HardBrick(new Vector2(815 - 4, GlobalValue.SCREEN_HEIGHT - 16 * 2)));

            m_Tree.AddObject(new Castle(new Vector2(950, GlobalValue.SCREEN_HEIGHT - 16 - 80)));
        }
    }
}
