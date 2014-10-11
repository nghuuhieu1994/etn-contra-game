using Mario_Bros.Framework;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Mario_Bros.Object.Item
{
    public class ItemFireFlower : CAnimationObject
    {
        private Vector2 oldPosition;

        public ItemFireFlower(Vector2 _Position)
            : base(_Position)
        {
            m_IDObject = IDObject.ITEM_FIRE_FLOWER;
            m_Sprite = CResourceManager.GetInstance().GetResource(IDResource.ITEM_FIRE_FLOWER);
            m_Status = IDStatus.UNACTIVATE;
            m_Sprite.Depth = GlobalValue.ITEM_SPRITE_DEPTH;
            oldPosition = _Position;
        }

        public override void UpdateMovement(GameTime _GameTime, CInput _Input)
        {
            if (m_Status == IDStatus.ACTIVATE)
            {
                m_Velocity = new Vector2(0, -0.05f);
            }

            if (oldPosition.Y - m_Position.Y > Sprite.FrameHeight - 1 && m_Status == IDStatus.ACTIVATE && Status != IDStatus.UNACTIVATE)//dung animation chay len
            {
                m_Status = IDStatus.ALIVE;
                m_Velocity = Vector2.Zero;
            }
            base.Update(_GameTime, _Input);
        }

        public override void UpdateCollision(CAnimationObject _Object)
        {
            base.UpdateCollision(_Object);
        }

        public override void Draw(SpriteBatch _SpriteBatch)
        {
            if (m_Status != IDStatus.UNACTIVATE)
            {
                base.Draw(_SpriteBatch);
            }
        }
    }
}
