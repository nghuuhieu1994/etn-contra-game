using MapEditor.Algorithm;
using MapEditor.Framwork;
using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using TileMap;

namespace MapEditor
{
    public partial class MainWindow : Window
    {
        #region.Variable drag 

        bool isDragged = false;
        System.Windows.Point startPosition;
        System.Windows.Point endPosition;
        System.Windows.Point finalPosition = new System.Windows.Point();
        Rectangle rect;

        #endregion

        #region.Variable for create object

        Image selectedItemFromListbox = null;
        Image tempSelectedItem;
        Image newSelectedItem;
        System.Windows.Point positionTempOfSelectedFromListbox;
        System.Windows.Point positionFinalOfSelectedFromListBox;
        bool isAdded;

        #endregion

        public MainWindow()
        {
            InitializeComponent();
            ListBoxCreater.getInstance().InitializeListBox(this.lbEnemyObject);
        }

        public bool CreateGridline()
        {
            if (Support.GRIDLINE == true)
            {
                GridLine.getInstance().CreateGridline();
                
                foreach(Point point in GridLine.getInstance().mListElements.Keys)
                {
                    Canvas.SetLeft(GridLine.getInstance().mListElements[point], point.cX);
                    Canvas.SetTop(GridLine.getInstance().mListElements[point], point.cY);
                    Canvas.SetZIndex(GridLine.getInstance().mListElements[point], 1);
                    WorkspaceWorking.Children.Add(GridLine.getInstance().mListElements[point]);
                }

                return true;
            }

            return false;
        }

        public bool DestroyGridline()
        {
            if (Support.GRIDLINE == true)
            {
                for (int i = 0; i < WorkspaceWorking.Children.Count; ++i)
                {
                    if (WorkspaceWorking.Children[i] is Rectangle)
                    {
                        Rectangle tempRect = (Rectangle)(WorkspaceWorking.Children[i]);
                        if (tempRect.Tag == Support.gridLine)
                        {
                            WorkspaceWorking.Children.Remove(WorkspaceWorking.Children[i]);
                            --i;
                        }
                    }
                }

                GridLine.getInstance().DestroyGridline();
                Support.GRIDLINE = false;
                return true;
            }

            return false;
        }

        public bool ConvertFromTileToObject()
        {
            if (Support.map != null)
            {
                if (Support.listObject == null)
                {
                    Support.listObject = new List<OBJECT>();
                }
                else if(Support.listObject.Count != 0)
                {
                    Support.listObject.Clear();
                }


                for (int i = 0; i < (int)(Support.map.BitMap.PixelHeight)/ Support.HEIGHT_OF_TILE; ++i)
                {
                    for (int j = 0; j < (int)(Support.map.BitMap.PixelWidth)/ Support.WIDTH_OF_TILE; ++j)
                    {
                        if (Support.listObject != null)
                        {
                            ++Support.Count;
                            OBJECT tempObject = new OBJECT((int)ObjectType.TILE_MAP, Support.map.ArrMap[i, j], Support.Count, new VECTOR2D(j * Support.WIDTH_OF_TILE, i * Support.HEIGHT_OF_TILE), new RECTANGLE(j * Support.WIDTH_OF_TILE, i * Support.HEIGHT_OF_TILE, Support.WIDTH_OF_TILE, Support.HEIGHT_OF_TILE));
                            VECTOR2D tempPosition = Support.ConvertCoordination(tempObject);
                            Support.listObject.Add(new OBJECT((int)ObjectType.TILE_MAP, Support.map.ArrMap[i, j], Support.Count, tempPosition, new RECTANGLE(tempPosition.cX, tempPosition.cY, Support.WIDTH_OF_TILE, Support.HEIGHT_OF_TILE)));
                        }
                    }
                }

                for (int i = 0; i < Support.map.ListLedPosition.Count; ++i)
                {
                    ++Support.Count;
                    OBJECT tempObject = new OBJECT((int)ObjectType.LED_OBJECT, 0, Support.Count, new VECTOR2D(Support.map.ListLedPosition[i].cX, Support.map.ListLedPosition[i].cY), new RECTANGLE(Support.map.ListLedPosition[i].cX, Support.map.ListLedPosition[i].cY, 2, 2));
                    VECTOR2D position = Support.ConvertCoordination(tempObject);
                    Support.listObject.Add(new OBJECT((int)ObjectType.LED_OBJECT, 0, Support.Count, new VECTOR2D(position.cX, position.cY), new RECTANGLE(position.cX, position.cY, 2, 2)));
                }

                return true;
            }

            return false;
        }

        public bool AddImageOfObjectToCanvas()
        {
            if (Support.listObject != null)
            {
                RemoveAllTileInCanvas();
                for (int i = 0; i < Support.listObject.Count; ++i)
                {
                    if (Support.listObject[i].Type == 0)
                    {
                        // optimize
                        Canvas.SetLeft(Support.listObject[i].image, Support.listObject[i].Position.cX - Support.listObject[i].Bound.width / 2);
                        Canvas.SetTop(Support.listObject[i].image, Support.HEIGHT_MAP - Support.listObject[i].Position.cY - Support.listObject[i].Bound.width / 2);
                        WorkspaceWorking.Children.Add(Support.listObject[i].image);
                    }
                }

                return true;
            }

            return false;
        }

        public void SaveMap()
        {
            if (Support.listObject != null && Support.IsExportXml == false)
            {
                for (int i = 0; i < WorkspaceWorking.Children.Count; ++i)
                {
                    if (WorkspaceWorking.Children[i] is Image)
                    {
                        Image tempRect = (Image)WorkspaceWorking.Children[i];
                        if ((int)tempRect.Tag != (int)ObjectType.TILE_MAP)
                        {
                            ++Support.Count;
                            OBJECT temp = new OBJECT((int)ObjectType.NORMAL_OBJECT, (int)tempRect.Tag, Support.Count, new VECTOR2D((float)Canvas.GetLeft(WorkspaceWorking.Children[i]), (float)Canvas.GetTop(WorkspaceWorking.Children[i])), new RECTANGLE((float)Canvas.GetLeft(WorkspaceWorking.Children[i]), (float)Canvas.GetTop(WorkspaceWorking.Children[i]), (int)tempRect.Width, (int)tempRect.Height));
                            VECTOR2D tempPosition = Support.ConvertCoordination(temp);
                            Support.listObject.Add(new OBJECT((int)ObjectType.NORMAL_OBJECT, (int)tempRect.Tag, Support.Count, tempPosition, new RECTANGLE(tempPosition.cX, tempPosition.cY, (int)tempRect.Width, (int)tempRect.Height)));
                        }
                    }
                }

                if (Support.quadTree == null)
                {
                    Support.quadTree = new CNode(0, PositionOfNode.TopLeft, new RECTANGLE(0, 6550, 6550, 6550));
                    for (int i = 0; i < Support.listObject.Count; ++i)
                    {
                        Support.quadTree.InsertObject(Support.quadTree, Support.listObject[i]);
                    }
                }
                ExportXml.getInstance().MWriter.WriteStartDocument();
                ExportXml.getInstance().writeQuadtreeToXml(Support.quadTree, ExportXml.getInstance().MWriter);
                ExportXml.getInstance().MWriter.WriteEndDocument();
                ExportXml.getInstance().MWriter.Close();

                Support.IsExportXml = true;
                MessageBox.Show("Map đã được tạo thành công, dùng file map.xml để load game nhé ^^", "Thông báo");
            }
            else
            {
                MessageBox.Show("Có map đâu mà đòi lưu ! - Muốn lưu hãy tạo map mới ^^", "Thông báo");
            }
        }

        public bool RemoveAllTileInCanvas()
        {
            if (WorkspaceWorking.Children.Count != 0)
            {
                for (int i = 0; i < WorkspaceWorking.Children.Count; ++i)
                {
                    if (WorkspaceWorking.Children[i] is Image)
                    {
                        Image temp = new Image();
                        temp = (Image)(WorkspaceWorking.Children[i]);
                        if ((int)temp.Tag == 0)
                        {
                            WorkspaceWorking.Children.Remove(WorkspaceWorking.Children[i]);
                            --i;
                        }
                    }
                }

                return true;
            }
            return false;
        }

        /* Event Handler */
        public void click_to_enable_gridline(object sender, RoutedEventArgs e)
        {
            if (Support.GRIDLINE == false)
            {
                Support.GRIDLINE = true;
                CreateGridline();
            }
            else
            {
                DestroyGridline();
            }
        }

        public void click_to_export_xml_file(object sender, RoutedEventArgs e)
        {
            SaveMap();
        }

        public void down_to_define_start_position(object sender, MouseEventArgs m)
        {
            if (true)
            {
                #region.For drag to create virtual object
                if (isDragged == false)
                {
                    isDragged = true;
                    startPosition = m.GetPosition(WorkspaceWorking);
                }

                startPosition.X = ((int)m.GetPosition(WorkspaceWorking).X / (int)Support.WIDHT_OF_VIRTUALOBJECT) * Support.WIDHT_OF_VIRTUALOBJECT;
                startPosition.Y = ((int)m.GetPosition(WorkspaceWorking).Y / Support.HEIGHT_OF_VIRTUALOBJECT) * Support.HEIGHT_OF_VIRTUALOBJECT;

                #endregion
            }
        }

        public void move_to_update_position(object sender, MouseEventArgs m)
        {
            if (isDragged == true && m.LeftButton == MouseButtonState.Pressed)
            {
                if (rect != null)
                {
                    WorkspaceWorking.Children.Remove(rect);
                }

                endPosition = m.GetPosition(WorkspaceWorking);

                #region Scroll SrollViewer of Canvas
                if (endPosition.X > 800 + ScrollCanvas.HorizontalOffset)
                {
                    ScrollCanvas.ScrollToHorizontalOffset(ScrollCanvas.HorizontalOffset + 1);
                    ScrollCanvas.UpdateLayout();
                } 
                #endregion

                endPosition.X = ((int)endPosition.X / Support.WIDHT_OF_VIRTUALOBJECT) * Support.WIDHT_OF_VIRTUALOBJECT;
                endPosition.Y = ((int)endPosition.Y / Support.HEIGHT_OF_VIRTUALOBJECT) * Support.HEIGHT_OF_VIRTUALOBJECT;
                
                if ((int)endPosition.X % Support.WIDHT_OF_VIRTUALOBJECT > 0 || (endPosition.X - startPosition.X) / Support.WIDHT_OF_VIRTUALOBJECT < 1)
                {
                    endPosition.X += Support.WIDHT_OF_VIRTUALOBJECT;
                }

                if ((int)endPosition.Y % Support.HEIGHT_OF_VIRTUALOBJECT > 0 || (endPosition.Y - startPosition.Y) / Support.HEIGHT_OF_VIRTUALOBJECT < 1)
                {
                    endPosition.Y += Support.HEIGHT_OF_VIRTUALOBJECT;
                }


                rect = new Rectangle();
                rect.Tag = Support.virtualObject;
                rect.Width = (double)Math.Abs(endPosition.X - startPosition.X);
                rect.Height = (double)Math.Abs(endPosition.Y - startPosition.Y);
                if (Support.IsVirtualWater == true)
                {
                    rect.Stroke = new SolidColorBrush(Colors.Blue);
                }
                else
                {
                    rect.Stroke = new SolidColorBrush(Colors.Red);
                }
                rect.StrokeThickness = 3;

                if (endPosition.X > startPosition.X)
                {
                    Canvas.SetLeft(rect, startPosition.X);
                    finalPosition.X = startPosition.X;
                }
                else
                {
                    Canvas.SetLeft(rect, endPosition.X);
                    finalPosition.X = endPosition.X;
                }

                if (startPosition.Y < endPosition.Y)
                {
                    Canvas.SetTop(rect, startPosition.Y);
                    finalPosition.Y = startPosition.Y;
                }
                else
                {
                    Canvas.SetTop(rect, endPosition.Y);
                    finalPosition.Y = endPosition.Y;
                }
                Canvas.SetZIndex(rect, 2);
                WorkspaceWorking.Children.Add(rect);
            }
            else
            {
                if (isDragged == true && m.LeftButton == MouseButtonState.Released)
                {
                    isDragged = false;
                    if (rect != null)
                    {
                        ++Support.Count;
                        if (Support.IsVirtualWater == false)
                        {
                            OBJECT temp = new OBJECT((int)ObjectType.VIRTUAL_OBJECT, 0, Support.Count, new VECTOR2D((float)finalPosition.X, (float)finalPosition.Y), new RECTANGLE((float)finalPosition.X, (float)finalPosition.Y, (int)rect.Width, (int)rect.Height));
                            VECTOR2D tempPosition = Support.ConvertCoordination(temp);


                            OBJECT obj = new OBJECT((int)ObjectType.VIRTUAL_OBJECT, 0, Support.Count, new VECTOR2D((float)tempPosition.cX, (float)tempPosition.cY), new RECTANGLE((float)tempPosition.cX, (float)tempPosition.cY, (int)rect.Width, (int)rect.Height));

                            if (Support.listObject == null)
                            {
                                Support.listObject = new List<OBJECT>();
                            }
                            if (obj.Bound.width != 0 && obj.Bound.height != 0)
                            {
                                Support.listObject.Add(obj);
                            }

                            obj = null;

                        }
                        else
                        {
                            OBJECT temp = new OBJECT((int)ObjectType.VIRTUAL_OBJECT, 0, Support.Count, new VECTOR2D((float)finalPosition.X, (float)finalPosition.Y), new RECTANGLE((float)finalPosition.X, (float)finalPosition.Y, (int)rect.Width, (int)rect.Height));
                            VECTOR2D tempPosition = Support.ConvertCoordination(temp);

                            EditPosition form = new EditPosition((int)tempPosition.cX, (int)tempPosition.cY);
                            form.ShowDialog();
                            tempPosition = new VECTOR2D(EditPosition.finalLocationX, EditPosition.finalLocationY);

                            OBJECT obj = new OBJECT((int)ObjectType.VIRTUAL_OBJECT, (int)ObjectID.VIRTUAL_OBJECT_WATER, Support.Count, new VECTOR2D((float)tempPosition.cX, (float)tempPosition.cY), new RECTANGLE((float)tempPosition.cX, (float)tempPosition.cY, (int)rect.Width, (int)rect.Height));

                            if (Support.listObject == null)
                            {
                                Support.listObject = new List<OBJECT>();
                            }
                            if (obj.Bound.width != 0 && obj.Bound.height != 0)
                            {
                                Support.listObject.Add(obj);
                            }

                            obj = null;

                        }
                    }
                    rect = null;
                    startPosition = endPosition;
                }
            }

            // Update coordination for tb
            if (this.tbX != null && this.tbY != null)
            {
                this.tbX.Text = m.GetPosition(WorkspaceWorking).X.ToString();
                this.tbY.Text = (Support.HEIGHT_MAP - m.GetPosition(WorkspaceWorking).Y).ToString();
            }

            if (Support.IsEraser == false)
            {
                #region.For to create enemyobject

                if (selectedItemFromListbox != null && m.LeftButton != MouseButtonState.Pressed)
                {
                    isAdded = false;
                    WorkspaceWorking.Children.Remove(tempSelectedItem);

                    Image cursorImage = new Image();
                    cursorImage.Tag = selectedItemFromListbox.Tag;
                    cursorImage.Source = selectedItemFromListbox.Source;
                    cursorImage.Width = selectedItemFromListbox.Width;
                    cursorImage.Height = selectedItemFromListbox.Height;
                    cursorImage.Opacity = 0.8f;

                    positionTempOfSelectedFromListbox = m.GetPosition(WorkspaceWorking);

                    tempSelectedItem = cursorImage;

                    if (Support.IsAlign == true)
                    {
                        #region.Collision between rambo & virtualobject
                        for (int i = 0; i < WorkspaceWorking.Children.Count; ++i)
                        {
                            RECTANGLE cursor = new RECTANGLE((float)positionTempOfSelectedFromListbox.X, (float)positionTempOfSelectedFromListbox.Y, (int)cursorImage.Width, (int)cursorImage.Height);

                            if (WorkspaceWorking.Children[i] is Rectangle)
                            {
                                Rectangle convertingObject = (Rectangle)(WorkspaceWorking.Children[i]);
                                if (convertingObject.Tag == Support.virtualObject && ((int)cursorImage.Tag == (int)ObjectID.RAMBO ||
                                                                (int)cursorImage.Tag == (int)ObjectID.SNIPER_STANDING))
                                {
                                    RECTANGLE tempRect = new RECTANGLE((float)Canvas.GetLeft(WorkspaceWorking.Children[i]), (float)Canvas.GetTop(WorkspaceWorking.Children[i]), (int)convertingObject.Width, (int)convertingObject.Height);
                                    RECTANGLE collisionRect = RECTANGLE.IntersectCanvas(tempRect, cursor);
                                    if (collisionRect.width != 0 && collisionRect.height != 0)
                                    {
                                        positionTempOfSelectedFromListbox.Y = tempRect.cY - cursorImage.Height;
                                    }
                                }
                                else if (convertingObject.Tag == Support.gridLine && ((int)cursorImage.Tag == (int)ObjectID.GUN_ROTATING ||
                                                                     (int)cursorImage.Tag == (int)ObjectID.BIG_GUN_ROTATING))
                                {
                                    RECTANGLE tempRect = new RECTANGLE((float)Canvas.GetLeft(WorkspaceWorking.Children[i]), (float)Canvas.GetTop(WorkspaceWorking.Children[i]), (int)convertingObject.Width, (int)convertingObject.Height);
                                    RECTANGLE collisionRect = RECTANGLE.IntersectCanvas(tempRect, cursor);
                                    if (collisionRect.width != 0 && collisionRect.height != 0)
                                    {
                                        positionTempOfSelectedFromListbox.X = tempRect.cX;
                                        positionTempOfSelectedFromListbox.Y = tempRect.cY;
                                    }
                                }
                            }
                        }
                    }
                    Canvas.SetLeft(cursorImage, (double)(positionTempOfSelectedFromListbox.X));
                    Canvas.SetTop(cursorImage, (double)(positionTempOfSelectedFromListbox.Y));
                    WorkspaceWorking.Children.Add(cursorImage);
                        #endregion
                }
                
                if (m.LeftButton == MouseButtonState.Pressed && selectedItemFromListbox != null && isAdded == false)
                {
                    WorkspaceWorking.Children.Remove(tempSelectedItem);
                    Image finalSelectedItem = new Image();
                    finalSelectedItem.Tag = selectedItemFromListbox.Tag;
                    finalSelectedItem.Source = selectedItemFromListbox.Source;
                    finalSelectedItem.Width = selectedItemFromListbox.Width;
                    finalSelectedItem.Height = selectedItemFromListbox.Height;

                    Canvas.SetLeft(finalSelectedItem, (double)(positionTempOfSelectedFromListbox.X));
                    Canvas.SetTop(finalSelectedItem, (double)(positionTempOfSelectedFromListbox.Y));
                    WorkspaceWorking.Children.Add(finalSelectedItem);
                    isAdded = true;
                }
            }
            else
            {
                for (int i = 0; i < WorkspaceWorking.Children.Count; ++i)
                {
                    if (WorkspaceWorking.Children[i] is Image)
                    {
                        Image tempSelected = (Image)(WorkspaceWorking.Children[i]);
                        if ((int)tempSelected.Tag != (int)ObjectType.TILE_MAP)
                        {
                            RECTANGLE rect = new RECTANGLE((float)Canvas.GetLeft(WorkspaceWorking.Children[i]), (float)Canvas.GetTop(WorkspaceWorking.Children[i]), (int)tempSelected.Width, (int)tempSelected.Height);
                            System.Windows.Point tempPoint = new System.Windows.Point(m.GetPosition(WorkspaceWorking).X, m.GetPosition(WorkspaceWorking).Y);
                            if (rect.IsContain(tempPoint) == true)
                            {
                                WorkspaceWorking.Children.Remove(WorkspaceWorking.Children[i]);
                            }
                        }
                    }
                    else if (WorkspaceWorking.Children[i] is Rectangle)
                    {
                        Rectangle tempRect = (Rectangle)(WorkspaceWorking.Children[i]);
                        if (tempRect.Tag == Support.virtualObject)
                        {
                            RECTANGLE rect = new RECTANGLE((float)Canvas.GetLeft(WorkspaceWorking.Children[i]), (float)Canvas.GetTop(WorkspaceWorking.Children[i]), (int)tempRect.Width, (int)tempRect.Height);
                            System.Windows.Point tempPoint = new System.Windows.Point(m.GetPosition(WorkspaceWorking).X, m.GetPosition(WorkspaceWorking).Y);
                            if (rect.IsContain(tempPoint) == true)
                            {
                                WorkspaceWorking.Children.Remove(WorkspaceWorking.Children[i]);
                            }
                        }
                    }
                }
            }
            #endregion
        }

        public void click_to_load_backgroundmap(object sender, RoutedEventArgs e)
        {

            if (Support.map != null)
            {
                Support.map = null;
            }

            OpenFileDialog openFileDialogSourcePicture = new OpenFileDialog();
            openFileDialogSourcePicture.Filter = "PNG (*.png)|*.png| BMP (*.bmp)|*.bmp| All File (*.*)|*.*";
            openFileDialogSourcePicture.FilterIndex = 3;
            openFileDialogSourcePicture.RestoreDirectory = true;

            if (openFileDialogSourcePicture.ShowDialog() == true)
            {
                CTile.CountID = 0;
                if (Support.map == null)
                {
                    Support.map = new CMap(new BitmapImage(new Uri(openFileDialogSourcePicture.FileName, UriKind.Absolute)));
                    Support.WIDHT_MAP = (int)(Support.map.BitMap.PixelWidth);
                    Support.HEIGHT_MAP = (int)(Support.map.BitMap.PixelHeight);
                    
                    if (Support.GRIDLINE == true)
                    {
                        DestroyGridline();
                        Support.GRIDLINE = true;
                        CreateGridline();
                    }

                    if (Support.IsExportXml == true)
                    {
                        Support.IsExportXml = false;
                        ExportXml.getInstance().DestroyWriter();
                    }
                    WorkspaceWorking.Width = Support.WIDHT_MAP;
                    WorkspaceWorking.Height = Support.HEIGHT_MAP;
                    Support.map.CreateTileMap();
                }
            }

            if (Support.map != null)
            {
                BitmapSource bmpSource;
                PngBitmapEncoder bmpCreate = new PngBitmapEncoder();
                
                byte[] arrPixel = new byte[((Support.map.TileMap.Count * Support.WIDTH_OF_TILE * Support.map.BitMap.Format.BitsPerPixel) / 8) * Support.HEIGHT_OF_TILE];

                int offsetX = 0;
                int offsetY = 0;

                for (int i = 0; i < Support.map.TileMap.Count; ++i)
                {
                    offsetX = Support.map.TileMap[i].ID;
                    Support.map.TileMap[i].ExportBitMap(offsetX, offsetY, arrPixel, (Support.map.TileMap.Count * Support.WIDTH_OF_TILE * Support.map.BitMap.Format.BitsPerPixel / 8));
                }

                FileStream stream = new FileStream(@"..\..\Resource\tilemap\tile_map.png", FileMode.Create);
                bmpSource = BitmapSource.Create(Support.map.TileMap.Count * Support.WIDTH_OF_TILE, Support.HEIGHT_OF_TILE, 96, 96, Support.map.BitMap.Format, null, arrPixel, ((Support.map.TileMap.Count * Support.WIDTH_OF_TILE * Support.map.BitMap.Format.BitsPerPixel) / 8));
                bmpCreate.Frames.Add(BitmapFrame.Create(bmpSource));
                bmpCreate.Save(stream);
                stream.Close();

                ConvertFromTileToObject();
                AddImageOfObjectToCanvas();

                Support.IsBackground = true;
            }

        }

        private void lbEnemyObject_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (Support.IsBackground == true)
            {
                Image temp = (Image)this.lbEnemyObject.SelectedItem;

                selectedItemFromListbox = new Image();
                selectedItemFromListbox.Tag = temp.Tag;
                selectedItemFromListbox.Source = temp.Source;
                selectedItemFromListbox.Width = temp.Width;
                selectedItemFromListbox.Height = temp.Height;
            }
            else
            {
                MessageBox.Show("Vui lòng thêm background cho game, trước khi chọn đối tượng");
            }
        }

        public void click_to_align_background(object sender, RoutedEventArgs e)
        {
            if (Support.IsAlign == true)
            {
                Support.IsAlign = false;
            }
            else
            {
                Support.IsAlign = true;
            }
        }

        public void click_to_back_pointer(object sender, RoutedEventArgs e)
        {
            WorkspaceWorking.Children.Remove(tempSelectedItem);
            selectedItemFromListbox = null;
            Support.IsVirtualWater = false;
        }

        public void click_to_enable_eraser(object sender, RoutedEventArgs e)
        {
            if (Support.IsEraser == false)
            {
                WorkspaceWorking.Children.Remove(tempSelectedItem);
                Support.IsEraser = true;
            }
            else
            {
                Support.IsEraser = false;
            }
        }

        public void click_to_enable_water(object sender, RoutedEventArgs e)
        {
            if (Support.IsVirtualWater == false)
            {
                Support.IsVirtualWater = true;
            }
            else
            {
                Support.IsVirtualWater = false;
            }
        }
        /* End Event Handler */
    }
}
