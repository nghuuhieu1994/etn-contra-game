using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Mario_Bros.Framework;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Mario_Bros.Object
{
    public class BaseBrick :  CAnimationObject
    {

        public BaseBrick(Vector2 _Position)
            : base(_Position)
        {
            //gọi copy constructor của sprite
            Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_BASE_BRICK));
            //gán ID của object
            IDObject = IDObject.MISC_BASE_BRICK;
            //gán độ sâu của sprite
            Sprite.Depth = GlobalValue.MISC_SPRITE_DEPTH;
        }
    }
}
