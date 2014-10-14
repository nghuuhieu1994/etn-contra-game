using Mario_Bros.Framework;
using Mario_Bros.Framework.Quadtree;
using Mario_Bros.Object.Item;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Mario_Bros.Object.Miscellaneous
{
    class Piece : CAnimationObject
        {
            //private float _rotation;
            public Piece(Vector2 _Position)
                : base(_Position)
            {
                m_IDObject = IDObject.MISC_PIECE;
                //m_Sprite = CResourceManager.GetInstance().GetResource(IDResource.MISC_PIECE);
                
                m_Status = IDStatus.ACTIVATE;
            }

            public override void UpdateMovement(GameTime _GameTime, CInput _Input)
            {
                //base.UpdateMovement(_GameTime, _Input);
                base.Update(_GameTime, _Input);
            }
        }
    public class SoftBrick : CAnimationObject
    {
        Vector2 oldPosition;
        List<Piece> m_ListOfPiece;
        float m_StopTime;

        public SoftBrick(Vector2 _Position)
            : base(_Position)
        {
            m_IDObject = IDObject.MISC_SOFT_BRICK;
            m_Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_SOFT_BRICK));
            //m_BrickStatus = BrickStatus.STABLE;
            Sprite.Depth = GlobalValue.MISC_SPRITE_DEPTH;
            m_Status = IDStatus.ALIVE;
            oldPosition = _Position;
            m_StopTime = 0;
            m_ListOfPiece = new List<Piece>();
        }

        public override void UpdateMovement(GameTime _GameTime, CInput _Input)
        {

            if (Status == IDStatus.MOVE)
            {
                m_Accel.Y = 0.0002f;
            }

            if (this.Position.Y > oldPosition.Y)
            {
                m_Position.Y = oldPosition.Y;
                m_Velocity = Vector2.Zero;
                m_Accel = Vector2.Zero;
                if (Status != IDStatus.ALIVE)
                    Status = IDStatus.ALIVE;
            }

            //if (m_Velocity.Y > 1.0f)
            //{
            //    m_Velocity.Y = 0.00001f;
            //}

            //if (m_BrickStatus == BrickStatus.BEFORE_BREAK && m_ListOfPiece != null)
            //{
            //    _rotation += _GameTime.ElapsedGameTime.Milliseconds;
            //    for (int i = 0; i < 4; ++i)
            //    {
            //        m_ListOfPiece[i].UpdateMovement(_GameTime, _Input);
            //    }
            //}

            if (Status == IDStatus.BEFORE_DIE)
            {
                Status = IDStatus.ACTIVATE;
                //m_Position.Y = Position.Y - 10;
                //m_BrickStatus = BrickStatus.BEFORE_BREAK;
                for (int i = 0; i < 4; ++i)
                {
                    m_ListOfPiece.Add(new Piece(new Vector2(Position.X + 8 * (i % 2), Position.Y + 8 * (i / 2) - 20)));
                //}
                //for (int i = 0; i < 4; ++i)
                //{
                    if (i == 0)
                    {
                        m_ListOfPiece[i].Velocity = new Vector2(-0.2f, -0.2f);
                        m_ListOfPiece[i].Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_PIECE_2));
                        m_Sprite.Depth = GlobalValue.MISC_SPRITE_DEPTH;
                    }
                    if (i == 1)
                    {
                        m_ListOfPiece[i].Velocity = new Vector2(0.2f, -0.2f);
                        m_ListOfPiece[i].Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_PIECE_1));
                        m_Sprite.Depth = GlobalValue.MISC_SPRITE_DEPTH;
                    }
                    if (i == 2)
                    {
                        m_ListOfPiece[i].Velocity = new Vector2(-0.2f, 0.2f);
                        m_ListOfPiece[i].Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_PIECE_2));
                        m_Sprite.Depth = GlobalValue.MISC_SPRITE_DEPTH;
                    }
                    if (i == 3)
                    {
                        m_ListOfPiece[i].Velocity = new Vector2(0.2f, 0.2f);
                        m_ListOfPiece[i].Sprite = new CSprite(CResourceManager.GetInstance().GetResource(IDResource.MISC_PIECE_1));
                        m_Sprite.Depth = GlobalValue.MISC_SPRITE_DEPTH;
                    }
                    m_ListOfPiece[i].Accel = new Vector2(0, 0.005f);
                }
            }

            if (Status == IDStatus.ACTIVATE)
            {
                for (int i = 0; i < 4; ++i)
                {
                    m_ListOfPiece[i].UpdateMovement(_GameTime, _Input);
                }
                m_StopTime += (float)_GameTime.ElapsedGameTime.Milliseconds;
                if (m_StopTime >= 2000.0f)
                    m_Status = IDStatus.DIE;
            }

            //base.UpdateMovement(_GameTime, _Input);
            base.Update(_GameTime, _Input);
        }

        public override void Draw(SpriteBatch _SpriteBatch)
        {
            if (Status == IDStatus.ALIVE || Status == IDStatus.MOVE)
            {
                base.Draw(_SpriteBatch);
            }

            if (Status == IDStatus.ACTIVATE)
            {
                for (int i = 0; i < 4; i++)
                {
                    //m_ListOfPiece[i].Sprite.Rotation = 2 * (float)((_rotation) * (Math.PI)) / 180.0f;
                    m_ListOfPiece[i].Sprite.Depth = 1.0f;
                    m_ListOfPiece[i].Draw(_SpriteBatch);
                }
            }
        }
    }
}
