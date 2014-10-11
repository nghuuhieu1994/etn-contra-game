using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Mario_Bros.Algorithm
{
    public struct Box
    {
        public float x;
        public float y;
        public float w;
        public float h;

        public float vx;
        public float vy;

        // Nhớ nhân vận tốc cho thời gian thực
        public Box(float _x, float _y, float _w, float _h, float _vx, float _vy)
        {
            x = _x;
            y = _y;
            w = _w;
            h = _h;
            vx = _vx;
            vy = _vy;
        }

        public Box(float _x, float _y, float _w, float _h)
        {
            x = _x;
            y = _y;
            w = _w;
            h = _h;
            vx = 0.0f;
            vy = 0.0f;
        }
    }

    public class SweptAABB
    {
        public static Box GetBroadPhaseBox(Box b)
        {
            Box BroadPhaseBox = new Box(0.0f, 0.0f, 0.0f, 0.0f);

            BroadPhaseBox.x = b.vx > 0 ? b.x : b.x + b.vx;
            BroadPhaseBox.y = b.vy > 0 ? b.y : b.y + b.vy;
            BroadPhaseBox.w = b.vx > 0 ? b.w + b.vx : b.w - b.vx;
            BroadPhaseBox.h = b.vy > 0 ? b.h + b.vy : b.h - b.vy;

            return BroadPhaseBox;
        }

        public static bool CheckAABB(Box b1, Box b2, ref float moveX, ref float moveY)
        {
            moveX = 0.0f;
            moveY = 0.0f;

            float l = b2.x - (b1.x + b1.w);
            float r = (b2.x + b2.w) - b1.x;
            float t = b2.y - (b1.y + b1.h);
            float b = (b2.y + b2.h) - b1.y;

            if (l > 0 || r < 0 || t > 0 || b < 0)
                return false;

            // lấy khoảng bị va chạm ngắn nhất, để cộng cho nhanh
            moveX = Math.Abs(l) < r ? l : r;
            moveY = Math.Abs(t) < b ? t : b;

            // lấy chiều có khoảng va chạm ngắn, nhất để cộng cho lẹ
            if (Math.Abs(moveX) < Math.Abs(moveY))
            {
                moveY = 0.0f;
            }
            else
            {
                moveX = 0.0f;
            }

            return true;
        }

        public static float Swept_AABB(Box b1, Box b2, ref float normalx, ref float normaly)
        {
            float xInvEntry, yInvEntry;
            float xInvExit, yInvExit;

            // find the distance between the objects on the near and far sides for both x and y
            if (b1.vx > 0.0f)
            {
                xInvEntry = b2.x - (b1.x + b1.w);
                xInvExit = (b2.x + b2.w) - b1.x;
            }
            else
            {
                xInvEntry = (b2.x + b2.w) - b1.x;
                xInvExit = b2.x - (b1.x + b1.w);
            }

            if (b1.vy > 0.0f)
            {
                yInvEntry = b2.y - (b1.y + b1.h);
                yInvExit = (b2.y + b2.h) - b1.y;
            }
            else
            {
                yInvEntry = (b2.y + b2.h) - b1.y;
                yInvExit = b2.y - (b1.y + b1.h);
            }

            // find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
            float xEntry, yEntry;
            float xExit, yExit;

            if (b1.vx == 0.0f)
            {
                xEntry = -float.PositiveInfinity;
                xExit = float.PositiveInfinity;
            }
            else
            {
                xEntry = xInvEntry / b1.vx;
                xExit = xInvExit / b1.vx;
            }

            if (b1.vy == 0.0f)
            {
                yEntry = -float.PositiveInfinity;
                yExit = float.PositiveInfinity;
            }
            else
            {
                yEntry = yInvEntry / b1.vy;
                yExit = yInvExit / b1.vy;
            }

            // find the earliest/latest times of collision
            float entryTime = Math.Max(xEntry, yEntry);
            float exitTime = Math.Min(xExit, yExit);

            // if there was no collision
            if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
            {
                normalx = 0.0f;
                normaly = 0.0f;
                return 1.0f;
            }
            else // if there was a collision
            {
                // calculate normal of collided surface
                if (xEntry > yEntry && (b1.y + b1.h + 1.0f != b2.y ))
                {
                    if (xInvEntry < 0.0f)
                    {
                        normalx = 1.0f;
                        normaly = 0.0f;
                    }
                    else
                    {
                        normalx = -1.0f;
                        normaly = 0.0f;
                    }
                }
                else
                {
                    if (yInvEntry < 0.0f)
                    {
                        normalx = 0.0f;
                        normaly = 1.0f;
                    }
                    else
                    {
                        normalx = 0.0f;
                        normaly = -1.0f;
                    }
                }

                // return the time of collision
                return entryTime;
            }
        }
    }
}
