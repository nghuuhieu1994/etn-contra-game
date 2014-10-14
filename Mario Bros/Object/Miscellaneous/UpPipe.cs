using Mario_Bros.Framework;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Mario_Bros.Object.Miscellaneous
{
    public class UpPipe : CAnimationObject
    {
        public UpPipe(Vector2 _Position)
            : base(_Position)
        {
            //IDObject = IDObject.MISC_UP_PIPE;
            Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_UP_PIPE));
            Sprite.Depth = GlobalValue.MISC_SPRITE_DEPTH;
        }
    }
}
