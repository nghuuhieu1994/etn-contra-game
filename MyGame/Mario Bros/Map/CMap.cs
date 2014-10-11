using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using Microsoft.Xna.Framework;

namespace Mario_Bros.Map
{
    
    public static class GetPosMario
    {
        public static Vector2 _PosMario;
        public static Vector2 _GetPosMario()
        {
            return _PosMario;
        }
        public static void PosMario(XmlNode _root)
        {
            XmlNodeList list = _root.SelectNodes("GameObject");
            foreach (XmlNode l in list)
            {
                if (int.Parse(l.Attributes["Type"].Value) == 1)
                {
                    GetPosMario._PosMario = new Vector2(int.Parse(l.Attributes["X"].Value), int.Parse(l.Attributes["Y"].Value));
                }
            }
        }
    }
    public class CGameObject
    {
        private int m_ID;
        public int ID
        {
            get { return m_ID; }
        }
        private int m_Type;
        public int Type
        {
            get { return m_Type; }
        }
        private int m_X;
        public int X
        {
            get { return m_X; }
        }
        private int m_Y;
        public int Y
        {
            get { return m_Y; }
        }
        public CGameObject(int _ID, int _Type, int _X, int _Y)
        {
            m_ID = _ID;
            m_Type = _Type;
            m_X = _X;
            m_Y = _Y;
        }
    }

    public class CNode
    {
        private int m_ID;
        public int ID
        {
            get { return m_ID; }
        }
        private int m_X;
        public int X
        {
            get { return m_X; }
        }
        private int m_Y;
        public int Y
        {
            get { return m_Y; }
        }
        private int m_Width;
        public int Width
        {
            get { return m_Width; }
        }
        private int m_Height;
        public int Height
        {
            get { return m_Height; }
        }
        private List<CGameObject> m_ListObject;
        public List<CGameObject> ListObject
        {
            get { return m_ListObject; }
        }

        
        public CNode(int _ID, int _X, int _Y, int _Width, int _Height)
        {
            m_ID = _ID;
            m_X = _X;
            m_Y = _Y;
            m_Width = _Width;
            m_Height = _Height;
            m_ListObject = null;
        }

        public CNode(int _ID, int _X, int _Y, int _Width, int _Height, List<CGameObject> _ListObject)
        {
            m_ID = _ID;
            m_X = _X;
            m_Y = _Y;
            m_Width = _Width;
            m_Height = _Height;
            m_ListObject = _ListObject;
        }
    }

    public class CGameObjects
    {
        private List<CGameObject> m_ListObjects = new List<CGameObject>();
        public List<CGameObject> ListObjects
        {
            get { return m_ListObjects; }
        }

        public CGameObjects(XmlNode _parent)
        {
            XmlNodeList nodeList;
            nodeList = _parent.SelectNodes("GameObjects");


            foreach (XmlNode Item in nodeList)
            {
                XmlNodeList nodeListChild;
                nodeListChild = Item.SelectNodes("GameObject");
                GetPosMario.PosMario(Item);
                foreach (XmlNode ItemChild in nodeListChild)
                {
                    if(ItemChild.Attributes["Type"].Value != "1")
                    m_ListObjects.Add(new CGameObject(Convert.ToInt32(ItemChild.Attributes["ID"].Value), Convert.ToInt32(ItemChild.Attributes["Type"].Value), Convert.ToInt32(ItemChild.Attributes["X"].Value), Convert.ToInt32(ItemChild.Attributes["Y"].Value)));
                }
            }
        }
    }

    public class CNodes
    {
        private List<CNode> m_ListNodes = new List<CNode>();

        public List<CNode> ListNodes
        {
            get { return m_ListNodes; }
        }

        public CNodes(XmlNode _parent)
        {
            XmlNodeList nodeList;
            nodeList = _parent.SelectNodes("Node");

            foreach (XmlNode Item in nodeList)
            {
                CGameObjects gameObjects = new CGameObjects(Item);

                m_ListNodes.Add(new CNode(Convert.ToInt32(Item.Attributes["ID"].Value), Convert.ToInt32(Item.Attributes["X"].Value), Convert.ToInt32(Item.Attributes["Y"].Value), Convert.ToInt32(Item.Attributes["Width"].Value), Convert.ToInt32(Item.Attributes["Height"].Value), gameObjects.ListObjects));
            }
        }
    }

    public class CMap
    {
        private Dictionary<int, CNode> m_Map = new Dictionary<int, CNode>();
        //private 
        public int m_WidthMap;
        public int m_HeightMap;
        public Dictionary<int, CNode> Map
        {
            get { return m_Map; }
        }
        private Dictionary<int, CGameObject> m_ListObjects = new Dictionary<int, CGameObject>();
        public Dictionary<int, CGameObject> ListObjects
        {
            get { return m_ListObjects; }
        }
        private string m_Path;
        public String Path
        {
            get { return m_Path; }
            set { m_Path = value; }
        }

        private CNodes m_Nodes;

        public CMap(string _Path)
        {
            m_Path = _Path;
            XmlDocument doc = new XmlDocument();
            doc.Load(m_Path);

            XmlNode root = doc.DocumentElement;
            m_WidthMap = int.Parse(root.SelectSingleNode("Width").FirstChild.Value);
           m_HeightMap = int.Parse(root.SelectSingleNode("Height").FirstChild.Value);
            XmlNodeList nodeList = root.SelectNodes("Nodes");

            foreach (XmlNode Item in nodeList)
            {
                m_Nodes = new CNodes(Item);
            }


            for (int i = 0; i < m_Nodes.ListNodes.Count; ++i)
            {

                m_Map.Add(m_Nodes.ListNodes[i].ID, m_Nodes.ListNodes[i]);
                for (int j = 0; j < m_Nodes.ListNodes[i].ListObject.Count; ++j)
                {
                    int k = 0;
                    foreach (KeyValuePair<int, CGameObject> pair in m_ListObjects)
                    {
                        if (m_Nodes.ListNodes[i].ListObject[j].ID == pair.Key)
                            break;
                        ++k;
                    }

                    if (k == m_ListObjects.Count)
                        m_ListObjects.Add(m_Nodes.ListNodes[i].ListObject[j].ID, m_Nodes.ListNodes[i].ListObject[j]);
                }
            }

        }
    }
}
