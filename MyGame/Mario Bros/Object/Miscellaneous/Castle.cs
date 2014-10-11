using Mario_Bros.Framework;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Mario_Bros.Object.Miscellaneous
{
    public class Castle : CAnimationObject
    {
        CastleFlag m_Flag;
        CSprite m_Firework1;
        CSprite m_Firework2;
        public Castle(Vector2 _Position)
            : base(_Position)
        {
            IDObject = IDObject.MISC_CASTLE;
            Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_CASTLE));
            m_Firework1 = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_FIREWORK));
            m_Firework2 = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_FIREWORK));
            m_Firework1.Position = new Vector2(Position.X - 15, Position.Y - 10);
            m_Firework2.Position = new Vector2(Position.X + 60, Position.Y - 20);
            Sprite.Depth = GlobalValue.MISC_SPRITE_DEPTH;
        }

        public override void UpdateMovement(GameTime _GameTime, CInput _Input)
        {
            if (GlobalValue.GET_FLAG && m_Flag == null)
            {
                m_Flag = new CastleFlag(new Vector2(this.Position.X + 40 - 4, this.Position.Y), IDObject.MISC_STAR_FLAG_CASTLE);
            }
            if (m_Flag != null)
            {
                m_Flag.UpdateMovement(_GameTime, _Input);
                m_Firework1.UpdateAnimation(_GameTime);
                m_Firework2.UpdateAnimation(_GameTime);
            }
            base.UpdateMovement(_GameTime, _Input);
        }

        public override void UpdateCollision(CAnimationObject _Object)
        {
            if (_Object.IDObject == IDObject.FIRE_MARIO || _Object.IDObject == IDObject.SMALL_MARIO || _Object.IDObject == IDObject.SUPER_MARIO)
            {
                if (_Object.Position.X > Position.X + 35)
                {
                    _Object.Status = IDStatus.MARIO_STOP;
                    _Object.Sprite.Depth = 0.05f;
                    _Object.Velocity = Vector2.Zero;
                    _Object.Accel = Vector2.Zero;
                }
            }

            base.UpdateCollision(_Object);
        }

        public override void Draw(SpriteBatch _SpriteBatch)
        {
            if (m_Flag != null)
            {
                m_Flag.Draw(_SpriteBatch);
                m_Firework1.Draw(_SpriteBatch);
                m_Firework2.Draw(_SpriteBatch);
            }
            base.Draw(_SpriteBatch);
        }
    }
}

