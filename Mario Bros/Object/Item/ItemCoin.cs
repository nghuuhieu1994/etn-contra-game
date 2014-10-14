using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Mario_Bros.Framework;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Mario_Bros.Object
{
    public class ItemCoin : CAnimationObject
    {
        private Vector2 oldPosition;
        private float m_StopTime;
        public ItemCoin(Vector2 _Position, IDObject _IDObject)
            : base(_Position)
        {
            IDObject = _IDObject;
            switch (_IDObject)
            {
                case IDObject.ITEM_COIN_ACTIVATED:
                    m_Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.ITEM_COIN_ACTIVATED));
                    Sprite.Depth = 0.1f;
                    break;
                case IDObject.ITEM_COIN_NORMAL:
                    Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.ITEM_COIN_NORMAL));
                    break;
                default:
                    break;
            }
            oldPosition = _Position;
        }

        public override void UpdateAnimation(GameTime _GameTime, CInput _Input)
        {
            //if (m_Status == IDStatus.UNACTIVATE)
            //{
            //    Sprite.Animation.CurFrame = 3;
            //}
            base.UpdateAnimation(_GameTime, _Input);
        }

        public override void UpdateMovement(GameTime _GameTime, CInput _Input)
        {
            if (m_Status == IDStatus.ACTIVATE && IDObject == IDObject.ITEM_COIN_ACTIVATED)
            {
                
                Sprite.Animation.FrameStart = 0;
                Sprite.Animation.TimeAnimation = 50.0f;
                if (m_Position.Y > oldPosition.Y - Sprite.FrameHeight - 1)
                {
                    Velocity = new Vector2(0, -.1f);
                }
                else
                {
                    Velocity = Vector2.Zero;
                }
                m_StopTime += (float)_GameTime.ElapsedGameTime.Milliseconds;
                if (m_StopTime >= 400.0f)
                    m_Status = IDStatus.DIE;
                base.Update(_GameTime, _Input);
            }
        }

        public override void Draw(SpriteBatch _SpriteBatch)
        {
            if (Status == IDStatus.ACTIVATE && IDObject == IDObject.ITEM_COIN_ACTIVATED)
            {
                base.Draw(_SpriteBatch);
            }
            if (IDObject == IDObject.ITEM_COIN_NORMAL)
            {
                base.Draw(_SpriteBatch);
            }
        }

        private void MoveTo(Vector2 _Destination)
        {
            Vector2 temp;
            temp = (_Destination - Position);
            temp.Normalize();
            Velocity = temp;
        }
    }
}
