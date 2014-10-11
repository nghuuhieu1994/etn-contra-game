using Mario_Bros.Framework;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Mario_Bros.Object.Miscellaneous
{
    public class Flag : CAnimationObject
    {
        public Flag(Vector2 _Position)
            : base(_Position)
        {
            IDObject = IDObject.MISC_FLAG;
            Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_FLAG));
            Sprite.Depth = GlobalValue.MISC_SPRITE_DEPTH;
        }
        public override void UpdateCollision(CAnimationObject _Object)
        {
            if (CheckCollision(_Object) != DirectCollision.NONE)
            {
                if (_Object.IDObject == IDObject.MISC_HARD_BRICK)
                {
                    Velocity = Vector2.Zero;
                    Accel = Vector2.Zero;
                }
            }
            base.UpdateCollision(_Object);
        }
    }
}
