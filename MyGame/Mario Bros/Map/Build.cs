using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Mario_Bros.Framework;
using Microsoft.Xna.Framework;
using Mario_Bros.Object;
using Mario_Bros.Object.Enemy;
using Mario_Bros.Object.Miscellaneous;
using Mario_Bros.Object.Item;
using Mario_Bros.Object.Enemy.Boss;

namespace Mario_Bros.Map
{
    public class Build
    {
        public static CAnimationObject MakeObject(IDObject _type, Vector2 _pos)
        {
            CAnimationObject _object = null;
            switch (_type)
            {
                //case IDObject.SMALL_MARIO:
                //    _object = new Mario(_pos);
                //    break;
                case IDObject.ENEMY_GOOMBA_OW:
                    _object = new Goomba(_pos, IDDir.LEFT);
                    break;
                case IDObject.ENEMY_KOOPA_OW:
                    _object = new Koopa(_pos);
                    break;
                case IDObject.MISC_BASE_BRICK:
                    _object = new BaseBrick(_pos);
                    break;
                case IDObject.MISC_BIG_GRASS:
                    _object = new BigGrass(_pos);
                    break;
                case IDObject.MISC_BIG_MOUNTAIN:
                    _object = new BigMountain(_pos);
                    break;
                case IDObject.MISC_CASTLE:
                    _object = new Castle(_pos);
                    break;
                case IDObject.ENEMY_BOSS:
                    _object = new Boss(_pos);
                    break;
                //case IDObject.MISC_GATE_PIPE:
                    //_object = new GatePipe(_pos, IDStatus.GATE_PIPE_DOWN);
                    //break;
                case IDObject.MISC_HARD_BRICK:
                    _object = new HardBrick(_pos);
                    break;
                case IDObject.MISC_IRON_BRICK:
                    _object = new HardBrick(_pos);
                    break;
                case IDObject.MISC_STOCK_PIPE:
                    _object = new StockPipe(_pos);
                    break;
                case IDObject.MISC_MEDIUM_GRASS:
                    _object = new MediumGrass(_pos);
                    break;
                case IDObject.MISC_MEDIUM_MOUNTAIN:
                    _object = new MediumMountain(_pos);
                    break;
                case IDObject.MISC_PIECE:
                    _object = new Piece(_pos);
                    break;
                case IDObject.MISC_QUESTION_BRICK:
                    _object = new QuestionBrick(_pos, IDObject.ITEM_COIN_ACTIVATED);
                    break;
                case IDObject.MISC_SMALL_GRASS:
                    _object = new SmallGrass(_pos);
                    break;
                case IDObject.MISC_SOFT_BRICK:
                    _object = new SoftBrick(_pos);
                    break;
                case IDObject.MISC_GOAL_POLE:
                    _object = new GoalPole(_pos);
                    break;
                case IDObject.MISC_GATE_PIPE:
                    _object = new GatePipe(_pos);
                    break;
                case IDObject.MISC_FLAG:
                    _object = new Flag(_pos);
                    break;
                //case IDObject.BRICK_COIN:
                //    _object = new QuestionBrick(_pos, IDObject.ITEM_COIN_ACTIVATED);
                //    break;
                case IDObject.ITEM_STARMAN:
                    _object = new ItemStarman(_pos);
                    break;
                //case IDObject.MISC_UP_PIPE:
                //    _object = new UpPipe(_pos);
                //    break;
                case IDObject.ITEM_1UP_MUSHROOM:
                    _object = new Item1UpMushroom(_pos);
                    break;
                case IDObject.MISC_SMALL_CLOUND:
                    _object = new SmallClound(_pos);
                    break;
                case IDObject.MISC_MEDIUM_CLOUND:
                    _object = new MediumClound(_pos);
                    break;
                case IDObject.MISC_BIG_CLOUND:
                    _object = new BigClound(_pos);
                    break;
                case IDObject.ITEM_COIN_ACTIVATED:
                    _object = new ItemCoin(_pos, IDObject.ITEM_COIN_ACTIVATED);
                    break;
                case IDObject.ITEM_COIN_NORMAL:
                    _object = new ItemCoin(_pos, IDObject.ITEM_COIN_NORMAL);
                    break;
                case IDObject.ITEM_FIRE_FLOWER:
                    _object = new ItemFireFlower(_pos);
                    break;
                case IDObject.ITEM_SUPER_MUSHROOM:
                    _object = new ItemSuperMushroom(_pos);
                    break;
                case IDObject.ITEM_GROW_UP:
                    _object = new ItemGrowUp(_pos);
                    break;
                //case IDObject.BRICK_COIN:
                //    _object = new QuestionBrick(_pos, IDObject.ITEM_COIN_ACTIVATED);
                //    break;
                //case IDObject.BRICK_FLOWER:
                //    _object = new QuestionBrick(_pos, IDObject.ITEM_FIRE_FLOWER);
                //    break;
                //case IDObject.BRICK_SUPPERMUSHROOM:
                //    _object = new QuestionBrick(_pos, IDObject.ITEM_SUPER_MUSHROOM);
                //    break;
                //case IDObject.BRICK_1UPMUSHROOM:
                //    _object = new QuestionBrick(_pos, IDObject.BRICK_1UPMUSHROOM);
                //    break;
                //case IDObject.BRICK_STAR:
                //    _object = new QuestionBrick(_pos, IDObject.ITEM_STARMAN);
                //    break;
                default:
                    break;
            }

            return _object;
        }

        public static Dictionary<int, CAnimationObject> BuildObjectInMap(CMap _map)
        {
            Dictionary<int, CAnimationObject> listObject = new Dictionary<int, CAnimationObject>();

            foreach (KeyValuePair<int, CGameObject> pair in _map.ListObjects)
            {
                CAnimationObject _object = null;
                Vector2 _pos = new Vector2(pair.Value.X, pair.Value.Y);
                IDObject _type = (IDObject)pair.Value.Type;
                _object = Build.MakeObject(_type, _pos);

                if (_object != null)
                {
                    listObject.Add(pair.Key, _object);
                }
            }

            // gán coin vào break_question
            foreach (KeyValuePair<int, CAnimationObject> pair in listObject)
            {
                if (pair.Value.IDObject == IDObject.MISC_QUESTION_BRICK)
                {
                    foreach (KeyValuePair<int, CAnimationObject> p in listObject)
                    {
                        if (pair.Value.Position == p.Value.Position && (p.Value.IDObject == IDObject.ITEM_COIN_ACTIVATED ||
                            p.Value.IDObject == IDObject.ITEM_FIRE_FLOWER || p.Value.IDObject == IDObject.ITEM_SUPER_MUSHROOM ||
                            p.Value.IDObject == IDObject.ITEM_1UP_MUSHROOM || p.Value.IDObject == IDObject.ITEM_STARMAN || p.Value.IDObject == IDObject.ITEM_GROW_UP))
                        {
                            pair.Value.SetItem(p.Value);
                        }
                    }
                }
            }
            return listObject;
        }

        public static Dictionary<int, QNode> BuildQNodeMap(CMap _map, Dictionary<int, CAnimationObject> _listObject)
        {
            Dictionary<int, QNode> mapNode = new Dictionary<int, QNode>();

            foreach (KeyValuePair<int, CNode> pair in _map.Map)
            {
                QNode node = null;
                List<CAnimationObject> list = new List<CAnimationObject>();
                Rectangle _bound = new Rectangle(pair.Value.X, pair.Value.Y, pair.Value.Width, pair.Value.Height);
                node = new QNode(pair.Key, _bound);
                for (int i = 0; i < pair.Value.ListObject.Count; ++i)
                {
                    foreach (KeyValuePair<int, CAnimationObject> o in _listObject)
                    {
                        if (pair.Value.ListObject[i].ID == o.Key)
                        {
                            list.Add(o.Value);
                        }
                    }
                }
                node.InsertObjects(list);
                mapNode.Add(pair.Key, node);
            }

            return mapNode;
        }

        public static QuadTree BuildQuadTree(Dictionary<int, QNode> mapNode)
        {
            QNode root = null;
            QNode q = null;
            var first = mapNode.First();
            root = first.Value;
            QuadTree quadTree;

            foreach (KeyValuePair<int, QNode> pair in mapNode)
            {
                if (pair.Key != 1)
                {
                    int parentID = pair.Value.GetParentID();
                    foreach (KeyValuePair<int, QNode> pair2 in mapNode)
                    {
                        if (pair2.Key == parentID)
                        {
                            q = pair2.Value;
                            break;
                        }
                    }
                    q.AddChildNode(pair.Value);
                }
            }

            quadTree = new QuadTree(root);
            return quadTree;
        }
    }
}
