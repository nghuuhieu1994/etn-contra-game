using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Xml;

namespace MapEditor.Framwork
{
    public class ImportXml
    {
        private static ImportXml mInstance;
        private List<int> mReadList;

        public ImportXml()
        {
            this.mReadList = new List<int>();
        }

        public static ImportXml getInstance()
        {
            if (ImportXml.mInstance == null)
            {
                ImportXml.mInstance = new ImportXml();
            }

            return ImportXml.mInstance;
        }

        public bool isExisted(int index)
        {
            for (int i = 0; i < this.mReadList.Count; ++i)
            {
                if (index == this.mReadList[i])
                    return true;
            }

            return false;
        }

        public void loadCanvas(String pathFileName, Canvas workSpace)
        {
            XmlDocument xmlDocument = new XmlDocument();
            xmlDocument.Load(pathFileName);

            XmlNode rootNode;
            rootNode = xmlDocument.DocumentElement;

            Support.WIDHT_MAP = int.Parse(rootNode.Attributes["Width"].Value);
            Support.HEIGHT_MAP = int.Parse(rootNode.Attributes["Height"].Value);
            Support.MAPNAME = rootNode.Attributes["Name"].Value;

            XmlNodeList nodeList;
            nodeList = xmlDocument.GetElementsByTagName("Object");

            foreach (XmlNode item in nodeList)
            {
                if (this.isExisted(Convert.ToInt32(item.Attributes["Index"].Value)) == false)
                {
                    VECTOR2D tempPosition = new VECTOR2D(float.Parse(item.Attributes["X"].Value), float.Parse(item.Attributes["Y"].Value));
                    int width = Convert.ToInt32(item.Attributes["Width"].Value);
                    int height = Convert.ToInt32(item.Attributes["Height"].Value);

                    tempPosition = Support.ConvertCoordinationOfCanvas(tempPosition, width, height);

                    if (Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.VIRTUAL_OBJECT)
                    {
                        if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.TILE_BASE)
                        {
                            Rectangle shape = new Rectangle();
                            shape.Tag = (int)ObjectID.TILE_BASE;
                            shape.Width = width;
                            shape.Height = height;
                            shape.Stroke = new SolidColorBrush(Colors.Red);
                            shape.StrokeThickness = 3;

                            Canvas.SetLeft(shape, tempPosition.cX);
                            Canvas.SetTop(shape, tempPosition.cY);
                            Canvas.SetZIndex(shape, 2);
                            workSpace.Children.Add(shape);
                            this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                        }
                        else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.VIRTUAL_OBJECT_WATER)
                        {
                            Rectangle shape = new Rectangle();
                            shape.Tag = (int)ObjectID.VIRTUAL_OBJECT_WATER;
                            shape.Width = width;
                            shape.Height = height;
                            shape.Stroke = new SolidColorBrush(Colors.Blue);
                            shape.StrokeThickness = 3;

                            Canvas.SetLeft(shape, tempPosition.cX);
                            Canvas.SetTop(shape, tempPosition.cY);
                            Canvas.SetZIndex(shape, 2);
                            workSpace.Children.Add(shape);
                            this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                        }
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.RAMBO
                        && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Rambo.png", UriKind.Relative)), ObjectID.RAMBO, 52, 70);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.SNIPER_STANDING
                         && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Sniper.png", UriKind.Relative)), ObjectID.SNIPER_STANDING, 48, 64);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.ENEMY_RUN
                             && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Enemy_run.png", UriKind.Relative)), ObjectID.ENEMY_RUN, 36, 66);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.WEAPON_CAPSULE
                            && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Gif_bullet_moving.png", UriKind.Relative)), ObjectID.WEAPON_CAPSULE, 48, 30);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 3);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.WEAPON_SENSOR
                            && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Gif_bullet_static.png", UriKind.Relative)), ObjectID.WEAPON_SENSOR, 64, 64);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.SNIPER_HIDING
                          && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Sniper_hiding_up.png", UriKind.Relative)), ObjectID.SNIPER_HIDING, 48, 34);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.GUN_ROTATING
                         && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Gun_rotation.png", UriKind.Relative)), ObjectID.GUN_ROTATING, 64, 64);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.BIG_GUN_ROTATING
                        && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Big_gun_rotation.png", UriKind.Relative)), ObjectID.BIG_GUN_ROTATING, 64, 64);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.BRIDGE
                       && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Bridge.png", UriKind.Relative)), ObjectID.BRIDGE, 256, 62);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.BIG_BOSS_1
                      && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\boss_1.png", UriKind.Relative)), ObjectID.BIG_BOSS_1, 226, 368);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.BOOM
                      && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Boom.png", UriKind.Relative)), ObjectID.BOOM, 8, 28);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.STONE
                      && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Rock_falling.png", UriKind.Relative)), ObjectID.STONE, 27, 27);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.MAGIC_ROCK
                      && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Rock_flying.png", UriKind.Relative)), ObjectID.MAGIC_ROCK, 32, 31);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.SNIPPER_WATER_HIDING
                      && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Snipper_water_hiding.png", UriKind.Relative)), ObjectID.SNIPPER_WATER_HIDING, 34, 62);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.TANK
                      && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Tank.png", UriKind.Relative)), ObjectID.TANK, 200, 128);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.BIG_CAPSULE_BOSS
                      && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Big_capsule_boss.png", UriKind.Relative)), ObjectID.BIG_CAPSULE_BOSS, 120, 128);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.FIRE_BRIDGE
                      && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Bridge_2.png", UriKind.Relative)), ObjectID.FIRE_BRIDGE, 256, 32);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.ENEMY_RUN_SHOOTING
                        && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Enemy_run_shooting.png", UriKind.Relative)), ObjectID.ENEMY_RUN_SHOOTING, 49, 64);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.OBJECT_BARRIER
                            && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        for (int i = 0; i < Support.ListItem.Count; ++i)
                        {
                            if ((int)Support.ListItem[i].Tag == (int)ObjectID.OBJECT_BARRIER)
                            {
                                Image image = new Image();
                                image.Source = Support.ListItem[i].Source;
                                image.Tag = Support.ListItem[i].Tag;
                                image.Width = Support.ListItem[i].Width;
                                image.Height = Support.ListItem[i].Height;

                                Canvas.SetLeft(image, (double)tempPosition.cX);
                                Canvas.SetTop(image, (double)tempPosition.cY);
                                Canvas.SetZIndex(image, 2);
                                workSpace.Children.Add(image);
                            }
                        }
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.OBJECT_FLAME_GUN
                         && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        for (int i = 0; i < Support.ListItem.Count; ++i)
                        {
                            if ((int)Support.ListItem[i].Tag == (int)ObjectID.OBJECT_FLAME_GUN)
                            {
                                Image image = new Image();
                                image.Source = Support.ListItem[i].Source;
                                image.Tag = Support.ListItem[i].Tag;
                                image.Width = Support.ListItem[i].Width;
                                image.Height = Support.ListItem[i].Height;

                                Canvas.SetLeft(image, (double)tempPosition.cX);
                                Canvas.SetTop(image, (double)tempPosition.cY);
                                Canvas.SetZIndex(image, 2);
                                workSpace.Children.Add(image);
                            }
                        }
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.OBJECT_LASER_GUN
                         && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        for (int i = 0; i < Support.ListItem.Count; ++i)
                        {
                            if ((int)Support.ListItem[i].Tag == (int)ObjectID.OBJECT_LASER_GUN)
                            {
                                Image image = new Image();
                                image.Source = Support.ListItem[i].Source;
                                image.Tag = Support.ListItem[i].Tag;
                                image.Width = Support.ListItem[i].Width;
                                image.Height = Support.ListItem[i].Height;

                                Canvas.SetLeft(image, (double)tempPosition.cX);
                                Canvas.SetTop(image, (double)tempPosition.cY);
                                Canvas.SetZIndex(image, 2);
                                workSpace.Children.Add(image);
                            }
                        }
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if(Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.OBJECT_MACHINE_GUN
                         && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        for (int i = 0; i < Support.ListItem.Count; ++i)
                        {
                            if ((int)Support.ListItem[i].Tag == (int)ObjectID.OBJECT_MACHINE_GUN)
                            {
                                Image image = new Image();
                                image.Source = Support.ListItem[i].Source;
                                image.Tag = Support.ListItem[i].Tag;
                                image.Width = Support.ListItem[i].Width;
                                image.Height = Support.ListItem[i].Height;

                                Canvas.SetLeft(image, (double)tempPosition.cX);
                                Canvas.SetTop(image, (double)tempPosition.cY);
                                Canvas.SetZIndex(image, 2);
                                workSpace.Children.Add(image);
                            }
                        }
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if(Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.OBJECT_RAPID_GUN
                         && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        for (int i = 0; i < Support.ListItem.Count; ++i)
                        {
                            if ((int)Support.ListItem[i].Tag == (int)ObjectID.OBJECT_RAPID_GUN)
                            {
                                Image image = new Image();
                                image.Source = Support.ListItem[i].Source;
                                image.Tag = Support.ListItem[i].Tag;
                                image.Width = Support.ListItem[i].Width;
                                image.Height = Support.ListItem[i].Height;

                                Canvas.SetLeft(image, (double)tempPosition.cX);
                                Canvas.SetTop(image, (double)tempPosition.cY);
                                Canvas.SetZIndex(image, 2);
                                workSpace.Children.Add(image);
                            }
                        }
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.OBJECT_SPREAD_GUN
                          && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        for (int i = 0; i < Support.ListItem.Count; ++i)
                        {
                            if ((int)Support.ListItem[i].Tag == (int)ObjectID.OBJECT_SPREAD_GUN)
                            {
                                Image image = new Image();
                                image.Source = Support.ListItem[i].Source;
                                image.Tag = Support.ListItem[i].Tag;
                                image.Width = Support.ListItem[i].Width;
                                image.Height = Support.ListItem[i].Height;

                                Canvas.SetLeft(image, (double)tempPosition.cX);
                                Canvas.SetTop(image, (double)tempPosition.cY);
                                Canvas.SetZIndex(image, 2);
                                workSpace.Children.Add(image);
                            }
                        }
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                }
            }
        }
    }
}
