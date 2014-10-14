using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Mario_Bros.Framework;

namespace Mario_Bros.Map
{
    public class QuadTree
    {
        private QNode m_RootNode;
        public QNode RootNode
        {
            get { return m_RootNode; }
        }
        private List<CAnimationObject> m_ListObjectsInView = new List<CAnimationObject>();
        public List<CAnimationObject> ListObjectsInView
        {
            get { return m_ListObjectsInView; }
        }
        private Rectangle m_RectWorld;

        public QuadTree()
        {
            m_RootNode = null;
        }

        public QuadTree(QNode _root)
        {
            m_RootNode = _root;
        }

        public void InsertListObjectView(Rectangle viewport, QNode node)
        {
            int i = 0;
            int j = 0;

            if (m_RootNode == node)
            {
                if (m_ListObjectsInView.Count > 0)
                    m_ListObjectsInView.Clear();
            }

            if (node.GetChildNode(1) == null) // NẾU TRỞ THÀNH NODE LÁ
            {
                if (node.Bound.Intersects(viewport)) // VA CHẠM VỚI NODE
                {
                    for (i = 0; i < node.GetListObjects().Count; ++i)
                    {
                        for (j = 0; j < m_RootNode.GetListObjects().Count; ++j)
                        {
                            if (node.GetListObjects()[i] == m_RootNode.GetListObjects()[j])
                                break;
                        }

                        if (j == m_RootNode.GetListObjects().Count)
                        {
                            m_ListObjectsInView.Add(node.GetListObjects()[i]);
                        }
                    }
                }
            }
            else
            {
                if (node.GetChildNode(1).Bound.Intersects(viewport))
                {
                    InsertListObjectView(viewport, node.GetChildNode(1));
                }
                if (node.GetChildNode(2).Bound.Intersects(viewport))
                {
                    InsertListObjectView(viewport, node.GetChildNode(2));
                }
                if (node.GetChildNode(3).Bound.Intersects(viewport))
                {
                    InsertListObjectView(viewport, node.GetChildNode(3));
                }
                if (node.GetChildNode(4).Bound.Intersects(viewport))
                {
                    InsertListObjectView(viewport, node.GetChildNode(4));
                }
            }
        }

        public List<CAnimationObject> GetListObjectInView()
        {
            return m_ListObjectsInView;
        }

        public void RemoveObject(CAnimationObject _object, QNode _node)
        {
            if (_node.GetChildNode(1) == null)
            {
                _node.RemoveObject(_object);
            }
            else
            {
                RemoveObject(_object, _node.GetChildNode(1));
                RemoveObject(_object, _node.GetChildNode(2));
                RemoveObject(_object, _node.GetChildNode(3));
                RemoveObject(_object, _node.GetChildNode(4));
            }
        }
    }
}
