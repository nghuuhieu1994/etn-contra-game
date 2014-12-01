using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Media.Imaging;

namespace MapEditor.Framwork
{
    public class ListBoxCreater
    {
        private static ListBoxCreater mListBoxCreater;

        private ListBoxCreater()
        {

        }

        public static ListBoxCreater getInstance()
        {
            if (mListBoxCreater == null)
            {
                mListBoxCreater = new ListBoxCreater();
            }

            return mListBoxCreater;
        }

        public Image getImageForListBox(BitmapImage bmpImage, ObjectID id, int width, int height)
        {
            Image image = new Image();
            image.Tag = (int)id;
            image.Source = bmpImage;
            image.Width = width;
            image.Height = height;

            return image;
        }

        public void InitializeListBox(ListBox lbEnemyObject, ListBox lbLandObject)
        {
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Rambo.png", UriKind.Relative)), ObjectID.RAMBO, 52, 70));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Sniper.png", UriKind.Relative)), ObjectID.SNIPER_STANDING, 48, 64));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Enemy_run.png", UriKind.Relative)), ObjectID.ENEMY_RUN, 36, 66));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Gif_bullet_moving.png", UriKind.Relative)), ObjectID.WEAPON_CAPSULE, 48, 30));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Gif_bullet_static.png", UriKind.Relative)), ObjectID.WEAPON_SENSOR, 64, 64));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Sniper_hiding_up.png", UriKind.Relative)), ObjectID.SNIPER_HIDING, 48, 34));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Gun_rotation.png", UriKind.Relative)), ObjectID.GUN_ROTATING, 64, 64));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Big_gun_rotation.png", UriKind.Relative)), ObjectID.BIG_GUN_ROTATING, 64, 64));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Boss_gun.png", UriKind.Relative)), ObjectID.BOSS_GUN, 48, 62));

            lbLandObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Bridge.png", UriKind.Relative)), ObjectID.BRIDGE, 256, 62));
        }
    }
}
