using Mario_Bros.Framework;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Mario_Bros.Object.Miscellaneous
{
    public class SmallGrass : CAnimationObject
    {
        public SmallGrass(Vector2 _Position)
            : base(_Position)
        {
            IDObject = IDObject.MISC_SMALL_GRASS;
            Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_SMALL_GRASS));
            Sprite.Depth = GlobalValue.GRASS_SPRITE_DEPTH;
        }
    }
}
