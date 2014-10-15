using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace MapEditor.Framwork
{
    public class ExportXml
    {
        private static ExportXml mInstance;
        private XmlWriter mWriter;
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
            VECTOR2D temp = new VECTOR2D();
            temp = Support.ConvertCoordination(_object);
            mWriter.WriteStartElement("Object");
            mWriter.WriteAttributeString("Type", Convert.ToString(_object.Type));
            mWriter.WriteAttributeString("Id", Convert.ToString(_object.ID));
            mWriter.WriteAttributeString("X", Convert.ToString(temp.cX));
            mWriter.WriteAttributeString("Y", Convert.ToString(temp.cY));
            mWriter.Flush();
            mWriter.WriteEndElement();
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
