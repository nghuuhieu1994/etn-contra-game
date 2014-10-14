using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Mario_Bros.Framework;

namespace Mario_Bros.Map
{
    public class QNode
    {
        private QNode m_tl, m_tr, m_bl, m_br;
        private int m_ID;
        public int ID
        {
            get { return m_ID; }
        }
        private List<CAnimationObject> m_ListObjects;
        private Rectangle m_Bound;
        public Rectangle Bound
        {
            get { return m_Bound; }
            set { m_Bound = value; }
        }

        public QNode(int _ID, Rectangle _Bound)
        {
            m_tl = null;
            m_tr = null;
            m_bl = null;
            m_br = null;
            m_ID = _ID;
            m_Bound = _Bound;
        }


        public int GetParentID()
        {
            return (int)m_ID / 8;
        }

        public void InsertObjects(List<CAnimationObject> _ListObjecst)
        {
            m_ListObjects = _ListObjecst;
        }

        public List<CAnimationObject> GetListObjects()
        {
            return m_ListObjects;
        }

        public void AddChildNode(QNode _node)
        {
            int num = _node.ID % 8;

            switch (num)
            {
                case 1:
                    m_tl = _node;
                    break;
                case 2:
                    m_tr = _node;
                    break;
                case 3:
                    m_bl = _node;
                    break;
                case 4:
                    m_br = _node;
                    break;
                default:
                    break;
            }
        }

        public QNode GetChildNode(int _i)
        {
            switch (_i)
            {
                case 1:
                    return m_tl;
                case 2:
                    return m_tr;
                case 3:
                    return m_bl;
                case 4:
                    return m_br;
            }

            return null;
        }

        public void RemoveObject(CAnimationObject _object)
        {
            m_ListObjects.Remove(_object);
        }
    }
}
