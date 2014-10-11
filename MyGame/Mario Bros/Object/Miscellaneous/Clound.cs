using Mario_Bros.Framework;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Mario_Bros.Object.Miscellaneous
{
    public class SmallClound : CAnimationObject
    {
        public SmallClound(Vector2 _Position)
            : base(_Position)
        {
            IDObject = IDObject.MISC_SMALL_CLOUND;
            Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_SMALL_CLOUND));
            Sprite.Depth = GlobalValue.MISC_SPRITE_DEPTH;
        }
    }

    public class MediumClound : CAnimationObject
    {
        public MediumClound(Vector2 _Position)
            : base(_Position)
        {
            IDObject = IDObject.MISC_MEDIUM_CLOUND;
            Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_MEDIUM_CLOUND));
            Sprite.Depth = GlobalValue.MISC_SPRITE_DEPTH;
        }
    }

    public class BigClound : CAnimationObject
    {
        public BigClound(Vector2 _Position)
            : base(_Position)
        {
            IDObject = IDObject.MISC_BIG_CLOUND;
            Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_BIG_CLOUND));
            Sprite.Depth = GlobalValue.MISC_SPRITE_DEPTH;
        }
    }
}