using Mario_Bros.Framework;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Media;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Mario_Bros.Object.Miscellaneous
{
    public class GatePipe : CAnimationObject
    {
        Vector2 Portal;
        public GatePipe(Vector2 _Position, IDStatus _Status, Vector2 _Destination)
            : base(_Position)
        {
            IDObject = IDObject.MISC_GATE_PIPE;
            
            Status = IDStatus.GATE_PIPE_DOWN;
            Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_GATE_PIPE));
            Sprite.Depth = GlobalValue.MISC_SPRITE_DEPTH;
            Portal = _Destination;
        }

        public GatePipe(Vector2 _Position) : base(_Position)
        {
            IDObject = IDObject.MISC_GATE_PIPE;
            Status = IDStatus.GATE_PIPE_DOWN;
            Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_GATE_PIPE));
            Sprite.Depth = GlobalValue.MISC_SPRITE_DEPTH;
            Portal = _Position;
        }

        public override void UpdateCollision(CAnimationObject _Object)
        {
            //Console.WriteLine("aaaa");
            if ((_Object.IDObject == IDObject.FIRE_MARIO || _Object.IDObject == IDObject.SMALL_MARIO || _Object.IDObject == IDObject.SUPER_MARIO) && Status == IDStatus.TELEPORT)
            {
                _Object.Position = Portal;
                _Object.Status = IDStatus.MARIO_JUMP;
                _Object.Accel = new Vector2(0, 0.00098f);
                MediaPlayer.Resume();
                Status = IDStatus.NORMAL_GATE_PIPE;
            }
            base.UpdateCollision(_Object);
        }
    }
}
