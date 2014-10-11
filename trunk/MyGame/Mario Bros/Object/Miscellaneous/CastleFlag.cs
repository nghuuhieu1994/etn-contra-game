using Mario_Bros.Framework;
using Microsoft.Xna.Framework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Mario_Bros.Object.Miscellaneous
{
    class CastleFlag : CAnimationObject
    {
        Vector2 oldPosition;
        public CastleFlag(Vector2 _Position, IDObject _IDObject)
            : base(_Position)
        {
            oldPosition = _Position;
            IDObject = IDObject.MISC_STAR_FLAG_CASTLE;
            if (_IDObject == IDObject.MISC_STAR_FLAG_CASTLE)
            {
                Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_STAR_FLAG_CASTLE));
            }
            Sprite.Depth = 0.05f;
        }

        public override void UpdateMovement(GameTime _GameTime, CInput _Input)
        {
            if (Math.Abs(Position.Y - oldPosition.Y) < 16)
            {
                Velocity = new Vector2(0, -0.1f);
            }
            else
            {
                Velocity = Vector2.Zero;
            }
            base.UpdateMovement(_GameTime, _Input);
            base.Update(_GameTime, _Input);
        }

        
    }
}
