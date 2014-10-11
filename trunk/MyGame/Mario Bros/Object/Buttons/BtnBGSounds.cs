using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Mario_Bros.Framework;
using Microsoft.Xna.Framework;

namespace Mario_Bros.Object.Buttons
{
    class BtnBGSounds : Buttons
    {
        public BtnBGSounds(IDResource _ID, Vector2 _pos)
            : base(_ID, _pos)
        { }
        public override void Update()
        {
            if (IsFocus)
                ID = IDResource.BGOUND_Btn_Act;
            else
                ID = IDResource.BGSOUND_Btn;
            Sprite = CResourceManager.GetInstance().GetResource(ID);
            base.Update();
        }
        public override void Draw(Microsoft.Xna.Framework.Graphics.SpriteBatch SB)
        {
            base.Draw(SB);
        }
    }
}
