using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Mario_Bros.Framework;

namespace Mario_Bros.Object.Buttons
{
    class BtnAbout : Buttons
    {
        public BtnAbout(IDResource _ID, Vector2 _pos)
            : base(_ID, _pos)
        { }

        public override void Update()
        {
            if (IsFocus)
            {
                ID = IDResource.ABOUT_Btn_Act;
            }
            else
                ID = IDResource.ABOUT_Btn;
            Sprite = CResourceManager.GetInstance().GetResource(ID);
            base.Update();
        }

        public override void Draw(Microsoft.Xna.Framework.Graphics.SpriteBatch SB)
        {
            base.Draw(SB);
        }
    }
}
