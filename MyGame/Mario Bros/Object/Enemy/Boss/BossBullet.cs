using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Mario_Bros.Framework;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Mario_Bros.Object.Enemy.Boss
{
    public class BossBullet : CAnimationObject
    {
        public BossBullet(Vector2 _Position, IDDir _Direction)
            : base(_Position)
        {
            Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.ENEMY_BOSS_BULLET));
            Sprite.Depth = GlobalValue.ENEMY_SPRITE_DEPTH;
            Direction = _Direction;
            IDObject = IDObject.ENEMY_BOSS_BULLET;
        }

        public override void UpdateAnimation(GameTime _GameTime, CInput _Input)
        {
            if (Direction == IDDir.LEFT)
            {
                Sprite.Effect = SpriteEffects.FlipHorizontally;
            }

            if (Direction == IDDir.RIGHT)
            {
                Sprite.Effect = SpriteEffects.None;
            }
            base.UpdateAnimation(_GameTime, _Input);
        }

        public override void UpdateMovement(GameTime _GameTime, CInput _Input)
        {
            if (Direction == IDDir.LEFT)
            {
                m_Velocity = new Vector2(-0.3f, m_Velocity.Y);
            }

            if (Direction == IDDir.RIGHT)
            {
                m_Velocity = new Vector2(0.3f, m_Velocity.Y);
            }
            base.UpdateMovement(_GameTime, _Input);
            base.Update(_GameTime, _Input);
        }

        public override void UpdateCollision(CAnimationObject _Object)
        {
            if (CheckCollision(_Object) != DirectCollision.NONE)
            {
                switch (_Object.IDObject)
                {
                    case IDObject.FIRE_MARIO:
                    case IDObject.SMALL_MARIO:
                    case IDObject.SUPER_MARIO:
                        Status = IDStatus.DIE;
                        break;
                    default:
                        break;
                }
            }
            base.UpdateCollision(_Object);
        }
        public override void Draw(SpriteBatch _SpriteBatch)
        {
            base.Draw(_SpriteBatch);
        }
    }
}
