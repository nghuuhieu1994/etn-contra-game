using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Mario_Bros.Framework;
using Microsoft.Xna.Framework;

namespace Mario_Bros.Object.Buttons
{
    class BtnEffSounds : Buttons
    {
        public BtnEffSounds(IDResource _ID, Vector2 _pos)
            : base(_ID, _pos)
        { }
        public override void Update()
        {
            if (IsFocus)
            {
                ID = IDResource.SOUND_Btn_Act;
            }
            else
                ID = IDResource.SOUND_Btn;
            Sprite = CResourceManager.GetInstance().GetResource(ID);
            base.Update();
        }
        public override void Draw(Microsoft.Xna.Framework.Graphics.SpriteBatch SB)
        {
            base.Draw(SB);
        }
    }
}
