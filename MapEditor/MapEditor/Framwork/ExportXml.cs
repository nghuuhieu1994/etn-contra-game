using MapEditor.Algorithm;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Xml;

namespace MapEditor.Framwork
{
    public class ExportXml
    {
        private static ExportXml mInstance;
        private XmlWriter mWriter;

        public XmlWriter MWriter
        {
            get { return mWriter; }
            set { mWriter = value; }
        }
        XmlWriterSettings mWriterXmlSettings;

        private ExportXml()
        {
            mWriterXmlSettings = new XmlWriterSettings();
            mWriterXmlSettings.Indent = true;
            mWriter = XmlWriter.Create("map.xml", mWriterXmlSettings);
        }

        public static ExportXml getInstance()
        {
            if(mInstance == null)
            {
                mInstance = new ExportXml();
            }

            return mInstance;
        }

        public bool writeXmlFile(List<OBJECT> _listObject)
        {
            if (mWriter != null && _listObject != null)
            {
                mWriter.WriteStartElement("Objects");
                for (int i = 0; i < _listObject.Count; ++i)
                {
                    writeElement(_listObject[i]);
                }
                mWriter.WriteEndElement();
                mWriter.Close();
                return true;
            }

            return false;
        }

        public void writeElement(OBJECT _object)
        {
            mWriter.WriteStartElement("Object");
            VECTOR2D temp = new VECTOR2D();
            temp = Support.ConvertCoordination(_object);
            if (_object.ID == 26 && temp.cY == 32 && temp.cX == 32)
            {
                MessageBox.Show("DAY");
            }
            mWriter.WriteAttributeString("Type", Convert.ToString(_object.Type));
            mWriter.WriteAttributeString("Id", Convert.ToString(_object.ID));
            mWriter.WriteAttributeString("X", Convert.ToString(temp.cX));
            mWriter.WriteAttributeString("Y", Convert.ToString(temp.cY));
            if (_object.Type == 1)
            {
                mWriter.WriteAttributeString("Width", Convert.ToString(_object.Bound.width));
                mWriter.WriteAttributeString("Height", Convert.ToString(_object.Bound.height));
            }
            mWriter.Flush();
            mWriter.WriteEndElement();
        }

        public void writeQuadtreeToXml(CNode quadTree, XmlWriter writer)
        {
            if (quadTree != null)
            {
                mWriter.WriteStartElement("Node");
                mWriter.WriteAttributeString("Id", Convert.ToString(quadTree.ID));
                mWriter.WriteAttributeString("X", Convert.ToString(quadTree.Bound.cX));
                mWriter.WriteAttributeString("Y", Convert.ToString(quadTree.Bound.cY));
                mWriter.WriteAttributeString("Width", Convert.ToString(quadTree.Bound.width));
                mWriter.WriteAttributeString("Height", Convert.ToString(quadTree.Bound.height));

                if (quadTree.ListObject.Count == 0)
                {
                    writeQuadtreeToXml(quadTree.Tl, mWriter);
                    writeQuadtreeToXml(quadTree.Tr, mWriter);
                    writeQuadtreeToXml(quadTree.Bl, mWriter);
                    writeQuadtreeToXml(quadTree.Br, mWriter);
                }
                else
                {
                    mWriter.WriteStartElement("Objects"); 
                    for (int i = 0; i < quadTree.ListObject.Count; ++i)
                    {
                        mWriter.WriteStartElement("Object");
                        mWriter.WriteAttributeString("Type", Convert.ToString(quadTree.ListObject[i].Type));
                        mWriter.WriteAttributeString("Id", Convert.ToString(quadTree.ListObject[i].ID));
                        mWriter.WriteAttributeString("X", Convert.ToString(quadTree.ListObject[i].Position.cX));
                        mWriter.WriteAttributeString("Y", Convert.ToString(quadTree.ListObject[i].Position.cY));
                        mWriter.WriteAttributeString("Width", Convert.ToString(quadTree.ListObject[i].Bound.width));
                        mWriter.WriteAttributeString("Height", Convert.ToString(quadTree.ListObject[i].Bound.height));
                        mWriter.WriteEndElement();
                    }
                    mWriter.WriteEndElement();
                }

                mWriter.WriteEndElement();
            }
        }
        public bool DestroyWriter()
        {
            if (mWriter != null)
            {
                mWriter = null;

                return true;
            }
            return false;
        }
    }
}
