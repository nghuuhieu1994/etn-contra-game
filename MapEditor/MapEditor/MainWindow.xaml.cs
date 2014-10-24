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
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        /*
        private BitmapImage carBitmap = new BitmapImage(new Uri(Support.stringPathFile + "universe.jpg", UriKind.Absolute));
        private Image image = new Image();
        private Rectangle rect = new Rectangle();

        private BitmapImage rsTileMap = new BitmapImage(new Uri(Support.stringPathFile + "test_tile_map.jpg", UriKind.Absolute));
        private CMap map;
        */

        /* Properties for drag mouse */
        bool isDragged = false;
        System.Windows.Point startPosition;
        System.Windows.Point endPosition;
        System.Windows.Point finalPosition = new System.Windows.Point();
        Rectangle rect;

        public MainWindow()
        {
            InitializeComponent();

            #region.Comment
            /*
            image.Source = carBitmap;
            image.Width = carBitmap.Width;
            image.Height = carBitmap.Height;
            image.Clip = new RectangleGeometry(new Rect(0, 0, 100, 100));
            Canvas.SetLeft(image, 10);
            Canvas.SetRight(image, 10);
            */

            /*
            rect.Stroke = new SolidColorBrush(Colors.Yellow);
            rect.Width = Support.WIDTH_OF_TILE;
            rect.Height = Support.HEIGHT_OF_TILE;
            Canvas.SetLeft(rect, 0);
            Canvas.SetTop(rect, 64);
            WorkspaceWorking.Children.Add(rect);
            WorkspaceWorking.Children.Add(image);
            */

            /*
            WorkspaceWorking.Background = Brushes.Black;

            Support.GRIDLINE = true;
            GridLine.getInstance().CreateGridline();

            foreach(Point point in GridLine.getInstance().mListElements.Keys)
            {
                Canvas.SetLeft(GridLine.getInstance().mListElements[point], point.cX);
                Canvas.SetTop(GridLine.getInstance().mListElements[point], point.cY);
                WorkspaceWorking.Children.Add(GridLine.getInstance().mListElements[point]);
            }
            */

            /*
            map = new CMap(rsTileMap);
            map.CreateTileMap();
            BitmapSource bmpSource;
            JpegBitmapEncoder bmpCreate = new JpegBitmapEncoder();

            byte[] arrPixel = new byte[((map.TileMap.Count * Support.WIDTH_OF_TILE * map.BitMap.Format.BitsPerPixel) / 8) * Support.HEIGHT_OF_TILE];

            int offsetX = 0;
            int offsetY = 0;

           for (int i = 0; i < map.TileMap.Count; ++i)
           {
                offsetX = map.TileMap[i].ID;
                map.TileMap[i].ExportBitMap(offsetX, offsetY, arrPixel, (map.TileMap.Count * Support.WIDTH_OF_TILE * map.BitMap.Format.BitsPerPixel / 8));
           }

            FileStream stream = new FileStream("tile_map.bmp", FileMode.Create);
            bmpSource = BitmapSource.Create(map.TileMap.Count * Support.WIDTH_OF_TILE, Support.HEIGHT_OF_TILE, 96, 96, map.BitMap.Format, null, arrPixel, ((map.TileMap.Count * Support.WIDTH_OF_TILE * map.BitMap.Format.BitsPerPixel) / 8));
            bmpCreate.Frames.Add(BitmapFrame.Create(bmpSource));
            bmpCreate.Save(stream);
          
            
            */
            #endregion
        }

        #region.Gridline [DONE]
        // Create a gridline [ set true in default ]
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

        // Destroy gridline when GRIDLINE = false
        public bool DestroyGridline()
        {
            if (Support.GRIDLINE == true)
            {
                for (int i = 0; i < WorkspaceWorking.Children.Count; ++i)
                {
                    if (WorkspaceWorking.Children[i] is Rectangle)
                    {
                        WorkspaceWorking.Children.Remove(WorkspaceWorking.Children[i]);
                        --i;
                    }
                }

                GridLine.getInstance().DestroyGridline();
                Support.GRIDLINE = false;
                return true;
            }

            return false;
        }

        // click to enable gridline
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
        #endregion

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
                    Support.WIDHT_MAP = (int)(Support.map.BitMap.Width  + 0.9);
                    Support.HEIGHT_MAP = (int)(Support.map.BitMap.Height + 0.9);
                    DestroyGridline();
                    Support.GRIDLINE = true;
                    CreateGridline();
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
                JpegBitmapEncoder bmpCreate = new JpegBitmapEncoder();

                byte[] arrPixel = new byte[((Support.map.TileMap.Count * Support.WIDTH_OF_TILE * Support.map.BitMap.Format.BitsPerPixel) / 8) * Support.HEIGHT_OF_TILE];

                int offsetX = 0;
                int offsetY = 0;

                for (int i = 0; i < Support.map.TileMap.Count; ++i)
                {
                    offsetX = Support.map.TileMap[i].ID;
                    Support.map.TileMap[i].ExportBitMap(offsetX, offsetY, arrPixel, (Support.map.TileMap.Count * Support.WIDTH_OF_TILE * Support.map.BitMap.Format.BitsPerPixel / 8));
                }

                FileStream stream = new FileStream(@"..\..\Resource\tilemap\tile_map.bmp", FileMode.Create);
                bmpSource = BitmapSource.Create(Support.map.TileMap.Count * Support.WIDTH_OF_TILE, Support.HEIGHT_OF_TILE, 96, 96, Support.map.BitMap.Format, null, arrPixel, ((Support.map.TileMap.Count * Support.WIDTH_OF_TILE * Support.map.BitMap.Format.BitsPerPixel) / 8));
                bmpCreate.Frames.Add(BitmapFrame.Create(bmpSource));
                bmpCreate.Save(stream);
                stream.Close();

                ConvertFromTileToObject();
                AddImageOfObjectToCanvas();
            }

        }

        public bool ConvertFromTileToObject()
        {
            if (Support.map != null)
            {
             //   BitmapImage bmpTileMap = new BitmapImage(new Uri(Support.stringPathFile + "tilemap/tile_map.bmp", UriKind.Absolute));

                if (Support.listObject == null)
                {
                    Support.listObject = new List<OBJECT>();
                }
                else if(Support.listObject.Count != 0)
                {
                    Support.listObject.Clear();
                }

                for (int i = 0; i < (int)(Support.map.BitMap.Height + 0.9)/ Support.HEIGHT_OF_TILE; ++i)
                {
                    for (int j = 0; j < (int)(Support.map.BitMap.Width + 0.9)/ Support.WIDTH_OF_TILE; ++j)
                    {
                        if (Support.listObject != null)
                        {
                           Support.listObject.Add(new OBJECT(0, Support.map.ArrMap[i, j], new VECTOR2D(j * Support.WIDTH_OF_TILE, i * Support.HEIGHT_OF_TILE), new RECTANGLE(j * Support.WIDTH_OF_TILE, i * Support.HEIGHT_OF_TILE, Support.WIDTH_OF_TILE, Support.HEIGHT_OF_TILE)));
                        }
                    }
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
                        Canvas.SetLeft(Support.listObject[i].image, Support.listObject[i].Position.cX);
                        Canvas.SetTop(Support.listObject[i].image, Support.listObject[i].Position.cY);
                        WorkspaceWorking.Children.Add(Support.listObject[i].image);
                    }
                }

                return true;
            }

            return false;
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

        // Drawing rectangle
        public void click_to_export_xml_file(object sender, RoutedEventArgs e)
        {
            if (Support.listObject != null  && Support.IsExportXml == false)
            {
                ExportXml.getInstance().writeXmlFile(Support.listObject);
                Support.IsExportXml = true;
                MessageBox.Show("Export XML FILE SUCCESSFUL");
            }
            else
            {
                MessageBox.Show("Can not export XML FILE");
            }
        }

        public void down_to_define_start_position(object sender, MouseEventArgs m)
        {
            if (isDragged == false)
            {
                isDragged = true;
                startPosition = m.GetPosition(WorkspaceWorking);
            }

            startPosition.X = ((int)m.GetPosition(WorkspaceWorking).X / (int)Support.WIDHT_OF_VIRTUALOBJECT) * Support.WIDHT_OF_VIRTUALOBJECT;
            startPosition.Y = ((int)m.GetPosition(WorkspaceWorking).Y / Support.HEIGHT_OF_VIRTUALOBJECT) * Support.HEIGHT_OF_VIRTUALOBJECT;
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
                rect.Width = (double)Math.Abs(endPosition.X - startPosition.X);
                rect.Height = (double)Math.Abs(endPosition.Y - startPosition.Y);
                rect.Stroke = new SolidColorBrush(Colors.Red);
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

                        OBJECT obj = new OBJECT(1, 0, new VECTOR2D((float)finalPosition.X, (float)finalPosition.Y), new RECTANGLE((float)finalPosition.X, (float)finalPosition.Y, (int)rect.Width, (int)rect.Height));
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
                    rect = null;
                    startPosition = endPosition;
                }
            }

            // Update coordination for tb
            if (this.tbX != null && this.tbY != null)
            {
                this.tbX.Text = m.GetPosition(WorkspaceWorking).X.ToString();
                this.tbY.Text = m.GetPosition(WorkspaceWorking).Y.ToString();
            }
        }


    }
}
