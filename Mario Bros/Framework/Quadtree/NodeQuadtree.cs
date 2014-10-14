using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Mario_Bros.Framework.Quadtree
{
    public class NodeQuadtree
    {
        Rectangle m_Rectangle;
        List<NodeQuadtree> m_ListNode;
        List<CAnimationObject> m_ListObject;

        public NodeQuadtree(Vector2 _Position, int _Width, int _Height)
        {
            m_Rectangle = new Rectangle((int)_Position.X,(int)_Position.Y,_Width,_Height);
            m_ListNode = new List<NodeQuadtree>(4);
            m_ListObject = new List<CAnimationObject>();
        }

        public bool AddObject(CAnimationObject _Object)
        {
            if (m_Rectangle.Contains(_Object.Rectangle))
            {
                m_ListObject.Add(_Object);
                //return true;
                if (m_ListObject.Count > 1)
                {
                    if (m_ListNode.Count < 4)
                    {
                        m_ListNode.Add(new NodeQuadtree(new Vector2(m_Rectangle.X, m_Rectangle.Y), m_Rectangle.Width / 2, m_Rectangle.Height / 2));
                        m_ListNode.Add(new NodeQuadtree(new Vector2(m_Rectangle.X + m_Rectangle.Width / 2, m_Rectangle.Y), m_Rectangle.Width / 2, m_Rectangle.Height / 2));
                        m_ListNode.Add(new NodeQuadtree(new Vector2(m_Rectangle.X, m_Rectangle.Y + m_Rectangle.Height / 2), m_Rectangle.Width / 2, m_Rectangle.Height / 2));
                        m_ListNode.Add(new NodeQuadtree(new Vector2(m_Rectangle.X + m_Rectangle.Width / 2, m_Rectangle.Y + m_Rectangle.Height / 2), m_Rectangle.Width / 2, m_Rectangle.Height / 2)); 
                    }
                    for (int i = 0; i < 4; ++i)
                    {
                        if (m_ListNode[i].AddObject(_Object))
                        {
                            m_ListObject.Remove(_Object);
                            return true;
                        }
                    }
                }
                return true;
            }
            return false;
        }

        public void RemoveObject(CAnimationObject _Object)
        {
            m_ListObject.Remove(_Object);
            if(m_ListNode.Count == 4)
            for (int i = 0; i < 4; ++i)
            {
                m_ListNode[i].RemoveObject(_Object);
            }
        }

        public List<CAnimationObject> GetObject(Rectangle Area)
        {
            List<CAnimationObject> result = new List<CAnimationObject>();
            for (int i = 0; i < m_ListObject.Count; ++i)
            {
                if (Area.Intersects(m_ListObject[i].Rectangle))
                {
                    result.Add(m_ListObject[i]);
                }
            }
            if (m_ListNode.Count == 4)
            {
                List<CAnimationObject> temp = new List<CAnimationObject>();
                for (int i = 0; i < 4; ++i)
                {
                    temp = m_ListNode[i].GetObject(Area);
                    for (int j = 0; j < temp.Count; ++j)
                    {
                        result.Add(temp[j]);
                    }
                }
            }
            return result;
        }
    }
}
