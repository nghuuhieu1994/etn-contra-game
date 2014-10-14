using Mario_Bros.Framework;
using Mario_Bros.Framework.Quadtree;
using Mario_Bros.Object.Item;
using Microsoft.Xna.Framework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Mario_Bros.Object.Miscellaneous
{
    public class QuestionBrick_1 : CAnimationObject
    {
        CAnimationObject m_Item;
        IDObject IDMario;
        public CAnimationObject Item
        {
            get { return m_Item; }
            set { m_Item = value; }
        }

        public QuestionBrick_1(Vector2 _Position, IDObject _IDItem)
            : base(_Position)
        {
            m_IDObject = IDObject.MISC_QUESTION_BRICK;
            m_Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_QUESTION_BRICK));
            m_Status = IDStatus.ALIVE;
            Sprite.Depth = GlobalValue.MISC_SPRITE_DEPTH;
            switch (_IDItem)
            {
                case IDObject.ITEM_COIN_ACTIVATED:
                    m_Item = new ItemCoin(_Position, _IDItem);
                    break;
                case IDObject.ITEM_GROW_UP:
                    m_Item = new ItemGrowUp(_Position);
                    //m_Item = new CAnimationObject(_Position);
                    break;
                case IDObject.ITEM_1UP_MUSHROOM:
                    m_Item = new Item1UpMushroom(_Position);
                    //m_Item = new GreenMushroom(_Position);
                    break;
                case IDObject.ITEM_STARMAN:
                    m_Item = new ItemStarman(_Position);
                    break;
                default:
                    break;
            }
        }

        public override void UpdateAnimation(GameTime _GameTime, CInput _Input)
        {
            if (m_Status == IDStatus.ALIVE)
            {
                //m_Sprite.UpdateAnimation(_GameTime);
                base.UpdateAnimation(_GameTime, _Input);
            }
            else
            {
                Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_IRON_BRICK));
                Sprite.Depth = 0.9f;
                //Sprite.Animation.SetLocalAnimation();
                //m_Sprite.Animation.CurFrame = 0;
            }
        }

        public override void UpdateMovement(GameTime _GameTime, CInput _Input)
        {
            if (m_Status == IDStatus.DEACTIVATE)
            {
                //if (m_GreenMushroom.Status == IDStatus.UNACTIVATE)
                {
                    switch (Item.IDObject)
                    {
                        case IDObject.ITEM_COIN_ACTIVATED:
                            SoundManager.PlaySound(ESound.SFX_COIN);
                            break;
                        case IDObject.ITEM_GROW_UP:
                            SoundManager.PlaySound(ESound.SFX_ITEM_APPEAR);
                            if (GlobalValue.ID_MARIO == IDObject.SMALL_MARIO)
                            {
                                Item.IDObject = IDObject.ITEM_SUPER_MUSHROOM;
                                Item.Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.ITEM_SUPER_MUSHROOM));
                            }
                            if (GlobalValue.ID_MARIO == IDObject.SUPER_MARIO || GlobalValue.ID_MARIO == IDObject.FIRE_MARIO)
                            {
                                Item.IDObject = IDObject.ITEM_FIRE_FLOWER;
                                Item.Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.ITEM_FIRE_FLOWER));
                            }
                            break;
                        case IDObject.ITEM_1UP_MUSHROOM:
                            SoundManager.PlaySound(ESound.SFX_ITEM_APPEAR);
                            break;
                        case IDObject.ITEM_STARMAN:
                            SoundManager.PlaySound(ESound.SFX_ITEM_APPEAR);
                            break;
                        default:
                            break;
                    }
                    m_Item.Status = IDStatus.ACTIVATE;
                }
                m_Status = IDStatus.UNACTIVATE;
            }
            if (m_Item != null)
            {
                //m_RedMushroom.Update(_GameTime, _Input);
                //m_GreenMushroom.UpdateMovement(_GameTime, _Input);
                if (m_Item.Status == IDStatus.DIE)
                {
                    //m_GreenMushroom = null;
                }
            }
            //base.UpdateMovement(_GameTime, _Input);
        }

        public override void Draw(Microsoft.Xna.Framework.Graphics.SpriteBatch _SpriteBatch)
        {
            //Sprite.Draw(_SpriteBatch);
            //if (m_GreenMushroom != null)
            //{
            //    m_GreenMushroom.Draw(_SpriteBatch);
            //}
            base.Draw(_SpriteBatch);
        }
    }
}
