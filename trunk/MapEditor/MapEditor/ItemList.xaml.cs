using System;
using System.Collections.Generic;
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
using System.Windows.Shapes;

namespace MapEditor
{
    /// <summary>
    /// Interaction logic for ItemList.xaml
    /// </summary>
    public partial class ItemList : Window
    {
        private Canvas workspace;
        private System.Windows.Point positionOfItem;

        public ItemList(Canvas _workspace, System.Windows.Point _position)
        {
            InitializeComponent();
            workspace = _workspace;
            positionOfItem = _position;
        }

        private void RadioButton_Checked_1(object sender, RoutedEventArgs e)
        {

        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            if (rbBarrier.IsChecked == true)
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

                        Canvas.SetLeft(image, (double)positionOfItem.X);
                        Canvas.SetTop(image, (double)positionOfItem.Y);
                        workspace.Children.Add(image);
                    }
                }
            }
            else if (rbFlameGun.IsChecked == true)
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

                        Canvas.SetLeft(image, (double)positionOfItem.X);
                        Canvas.SetTop(image, (double)positionOfItem.Y);
                        workspace.Children.Add(image);
                    }
                }
            }
            else if (rbLaserGun.IsChecked == true)
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

                        Canvas.SetLeft(image, (double)positionOfItem.X);
                        Canvas.SetTop(image, (double)positionOfItem.Y);
                        workspace.Children.Add(image);
                    }
                }
            }
            else if (rbMachineGun.IsChecked == true)
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

                        Canvas.SetLeft(image, (double)positionOfItem.X);
                        Canvas.SetTop(image, (double)positionOfItem.Y);
                        workspace.Children.Add(image);
                    }
                }
            }
            else if (rbRapidFire.IsChecked == true)
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

                        Canvas.SetLeft(image, (double)positionOfItem.X);
                        Canvas.SetTop(image, (double)positionOfItem.Y);
                        workspace.Children.Add(image);
                    }
                }
            }
            else if (rbSpeadGun.IsChecked == true)
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

                        Canvas.SetLeft(image, (double)positionOfItem.X);
                        Canvas.SetTop(image, (double)positionOfItem.Y);
                        workspace.Children.Add(image);
                    }
                }
            }
            this.Close();
        }
    }
}
