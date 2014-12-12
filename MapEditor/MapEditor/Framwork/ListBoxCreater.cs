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

        public static Image getImageForListBox(BitmapImage bmpImage, ObjectID id, int width, int height)
        {
            Image image = new Image();
            image.Tag = (int)id;
            image.Source = bmpImage;
            image.Width = width;
            image.Height = height;

            return image;
        }

        public void InitializeListBox(ListBox lbEnemyObject, ListBox lbLandObject, ListBox lbBoss1Object, ListBox lbBoss2Object = null, ListBox lbBoss3Object = null)
        {
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Rambo.png", UriKind.Relative)), ObjectID.RAMBO, 52, 70));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Sniper.png", UriKind.Relative)), ObjectID.SNIPER_STANDING, 48, 64));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Enemy_run.png", UriKind.Relative)), ObjectID.ENEMY_RUN, 36, 66));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Gif_bullet_moving.png", UriKind.Relative)), ObjectID.WEAPON_CAPSULE, 48, 30));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Gif_bullet_static.png", UriKind.Relative)), ObjectID.WEAPON_SENSOR, 64, 64));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Sniper_hiding_up.png", UriKind.Relative)), ObjectID.SNIPER_HIDING, 48, 34));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Gun_rotation.png", UriKind.Relative)), ObjectID.GUN_ROTATING, 64, 64));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Big_gun_rotation.png", UriKind.Relative)), ObjectID.BIG_GUN_ROTATING, 64, 64));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Enemy_big_gun.png", UriKind.Relative)), ObjectID.ENEMY_BIG_GUN_SHOOTING, 64, 64));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Snipper_water_hiding.png", UriKind.Relative)), ObjectID.SNIPPER_WATER_HIDING, 34, 62));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Tank.png", UriKind.Relative)), ObjectID.TANK, 200, 128));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Rock_falling.png", UriKind.Relative)), ObjectID.STONE, 27, 27));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Rock_flying.png", UriKind.Relative)), ObjectID.MAGIC_ROCK, 32, 31));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Boom.png", UriKind.Relative)), ObjectID.BOOM, 8, 28));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Enemy_run_shooting.png", UriKind.Relative)), ObjectID.ENEMY_RUN_SHOOTING, 49, 64));

            lbLandObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Bridge.png", UriKind.Relative)), ObjectID.BRIDGE, 256, 62));
            lbLandObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Bridge_2.png", UriKind.Relative)), ObjectID.FIRE_BRIDGE, 256, 32));

            lbBoss1Object.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\boss_1.png", UriKind.Relative)), ObjectID.BIG_BOSS_1, 226, 368));
            lbBoss1Object.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Big_capsule_boss.png", UriKind.Relative)), ObjectID.BIG_CAPSULE_BOSS, 120, 128));

            Support.ListItem.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\item\Barrier.png", UriKind.Relative)), ObjectID.OBJECT_BARRIER, 48, 30));
            Support.ListItem.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\item\FlameGun.png", UriKind.Relative)), ObjectID.OBJECT_FLAME_GUN, 48, 30));
            Support.ListItem.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\item\LaserGun.png", UriKind.Relative)), ObjectID.OBJECT_LASER_GUN, 48, 30));
            Support.ListItem.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\item\MachineGun.png", UriKind.Relative)), ObjectID.OBJECT_MACHINE_GUN, 48, 30));
            Support.ListItem.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\item\RapidFire.png", UriKind.Relative)), ObjectID.OBJECT_RAPID_GUN, 48, 30));
            Support.ListItem.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\item\SpreadGun.png", UriKind.Relative)), ObjectID.OBJECT_SPREAD_GUN, 48, 30));
        }
    }
}
