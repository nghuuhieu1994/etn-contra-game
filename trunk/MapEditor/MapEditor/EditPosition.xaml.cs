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
    /// Interaction logic for EditPosition.xaml
    /// </summary>
    public partial class EditPosition : Window
    {
        public static int finalLocationX;
        public static int finalLocationY;
        public EditPosition(int X, int Y)
        {
            InitializeComponent();
            textboxX.Text = X.ToString();
            textboxY.Text = Y.ToString();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            finalLocationX = int.Parse(textboxX.Text);
            finalLocationY = int.Parse(textboxY.Text);
            this.Close();
        }
    }
}
