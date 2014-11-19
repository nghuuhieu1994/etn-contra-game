using MapEditor.Framwork;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapEditor.Algorithm
{
    public enum PositionOfNode
    {
        TopLeft = 1,
        TopRight = 2,
        BottomLeft = 3,
        BottomRight = 4,
    }

    public class CNode
    {
        public static int MAX_SIZE_OF_COLLISION = 4;
        private CNode m_tl, m_tr, m_bl, m_br;

        public CNode Br
        {
            get { return m_br; }
            set { m_br = value; }
        }

        public CNode Bl
        {
            get { return m_bl; }
            set { m_bl = value; }
        }

        public CNode Tr
        {
            get { return m_tr; }
            set { m_tr = value; }
        }

        public CNode Tl
        {
            get { return m_tl; }
            set { m_tl = value; }
        }
        private int m_id;
        private RECTANGLE m_bound;
        private List<OBJECT> m_listObject;
        private static int MAX_WIDTH_SIZE_OF_NODE = 512;
        private static int MAX_HEIGHT_SIZE_OF_NODE = 448;

        #region.Properties
        public int ID
        {
            get { return this.m_id; }
            set { this.m_id = value; }
        }

        public RECTANGLE Bound
        {
            get { return this.m_bound; }
            set { this.m_bound = value; }
        }

        public List<OBJECT> ListObject
        {
            get { return this.m_listObject; }
            set { this.m_listObject = value; }
        }
        #endregion

        public int getParent()
        {
            return this.m_id / 10;
        }

        public List<OBJECT> getListObject()
        {
            return this.m_listObject;
        }

        public CNode(int parentID, PositionOfNode positionOfNode, RECTANGLE parentBound)
        {
            // if node is root
            this.m_id = parentID * 10 + (int)positionOfNode;

            this.m_tl = null;
            this.m_tr = null;
            this.m_bl = null;
            this.m_br = null;

            this.m_listObject = new List<OBJECT>();

            if (parentID == 0)
            {
                this.m_bound = parentBound;
            }
            else
            {
                if (positionOfNode == PositionOfNode.TopLeft)
                {
                    this.m_bound = new RECTANGLE(parentBound.cX, parentBound.cY, parentBound.width / 2, parentBound.height / 2);
                }
                else if (positionOfNode == PositionOfNode.TopRight)
                {
                    this.m_bound = new RECTANGLE(parentBound.cX + parentBound.width / 2, parentBound.cY, parentBound.width / 2, parentBound.height / 2);
                }
                else if (positionOfNode == PositionOfNode.BottomLeft)
                {
                    this.m_bound = new RECTANGLE(parentBound.cX, parentBound.cY - parentBound.height / 2, parentBound.width / 2, parentBound.height / 2);
                }
                else if (positionOfNode == PositionOfNode.BottomRight)
                {
                    this.m_bound = new RECTANGLE(parentBound.cX + parentBound.width / 2, parentBound.cY - parentBound.height / 2, parentBound.width / 2, parentBound.height / 2);
                }
            }
        }

        public void InsertObject(CNode node, OBJECT obj)
        {
            RECTANGLE rect = RECTANGLE.Intersec(node.m_bound, obj.Bound);

            if (rect.cX == 0 && rect.cY == 0 && rect.width == 0 && rect.height == 0)
            {
                return ;
            }

            if(rect.width < MAX_SIZE_OF_COLLISION && rect.height < MAX_SIZE_OF_COLLISION)
            {
                return;
            }

            if (node.m_bound.width >= 2*MAX_WIDTH_SIZE_OF_NODE)
            {
                if (node.m_tl == null)
                {
                    node.m_tl = new CNode(node.m_id, PositionOfNode.TopLeft, node.m_bound);
                    node.m_tr = new CNode(node.m_id, PositionOfNode.TopRight, node.m_bound);
                    node.m_bl = new CNode(node.m_id, PositionOfNode.BottomLeft, node.m_bound);
                    node.m_br = new CNode(node.m_id, PositionOfNode.BottomRight, node.m_bound);
                }

                node.InsertObject(node.m_tl, obj);
                node.InsertObject(node.m_tr, obj);
                node.InsertObject(node.m_bl, obj);
                node.InsertObject(node.m_br, obj);
            }
            else
            {
                node.m_listObject.Add(obj);
            }

            return;
        }

        public bool IsParent()
        {
            if (this.m_tl != null)
                return true;

            return false;
        }
    }
}
