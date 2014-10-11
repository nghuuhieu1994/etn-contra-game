using Mario_Bros.Framework;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Mario_Bros.Object.Miscellaneous
{
    public class MediumGrass : CAnimationObject
    {
        public MediumGrass(Vector2 _Position)
            : base(_Position)
        {
            IDObject = IDObject.MISC_MEDIUM_GRASS;
            Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_MEDIUM_GRASS));
            Sprite.Depth = GlobalValue.GRASS_SPRITE_DEPTH;
        }
    }
}
