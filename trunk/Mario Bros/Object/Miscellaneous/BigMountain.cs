using Mario_Bros.Framework;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Mario_Bros.Object.Miscellaneous
{
    public class BigMountain : CAnimationObject
    {

        public BigMountain(Vector2 _Position)
            : base(_Position)
        {
            IDObject = IDObject.MISC_BIG_MOUNTAIN;
            Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_BIG_MOUNTAIN));
            Sprite.Depth = GlobalValue.GRASS_SPRITE_DEPTH;
        }
    }
}
