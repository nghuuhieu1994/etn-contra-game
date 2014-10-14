using Mario_Bros.Framework;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Mario_Bros.Object.Miscellaneous
{
    public class StockPipe : CAnimationObject
    {
        public StockPipe(Vector2 _Position)
            : base(_Position)
        {
            IDObject = IDObject.MISC_STOCK_PIPE;
            Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_STOCK_PIPE));
            Sprite.Depth = GlobalValue.MISC_SPRITE_DEPTH;
        }
    }
}
