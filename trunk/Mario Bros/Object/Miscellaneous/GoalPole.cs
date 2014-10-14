using Mario_Bros.Framework;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Mario_Bros.Object.Miscellaneous
{
    public class GoalPole : CAnimationObject
    {
        Flag m_Flag;

        public GoalPole(Vector2 _Position)
            : base(_Position)
        {
            IDObject = IDObject.MISC_GOAL_POLE;
            Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_GOAL_POLE));
            Sprite.Depth = GlobalValue.MISC_SPRITE_DEPTH;
            m_Flag = new Flag(new Vector2(Position.X - 13, Position.Y + 8));
            Status = IDStatus.UNACTIVATE;
        }

        public override void UpdateMovement(GameTime _GameTime, CInput _Input)
        {
            if (Status == IDStatus.ACTIVATE)
            {
                m_Flag.Accel = new Vector2(0, 0.00098f);
                Status = IDStatus.UNACTIVATE;
            }
            m_Flag.Update(_GameTime, _Input);
            base.UpdateMovement(_GameTime, _Input);
        }

        public override void UpdateCollision(CAnimationObject _Object)
        {
            m_Flag.UpdateCollision(_Object);
            base.UpdateCollision(_Object);
        }

        public override void Draw(SpriteBatch _SpriteBatch)
        {
            m_Flag.Draw(_SpriteBatch);
            base.Draw(_SpriteBatch);
        }
    }
}
