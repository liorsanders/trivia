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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Threading;

namespace Client
{
    /// <summary>
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Page
    {
        private readonly Frame _main;
        private readonly string _username;
        private Thread roomUpdaterThread;
        public JoinRoom(Frame main, string username)
        {
            InitializeComponent();
            _main = main;
            _username = username;
            usernameBlock.Text = username;
            roomUpdaterThread = new Thread(new ThreadStart(updateRooms));
            roomUpdaterThread.Start();
        }
        private void updateRooms()
        {
            //this function accesses roomsGrid and adds buttons of rooms by the number of rooms

            Thread.Sleep(3);
        }
        private void BT_Exit_Click(object sender, RoutedEventArgs e)
        {
            if (Application.Current.MainWindow is MainWindow main)
            {
                roomUpdaterThread.Suspend();
                main.Close();
            }
        }

        private void BT_Menu_Click(object sender, RoutedEventArgs e)
        {
            roomUpdaterThread.Suspend();
            _main.Content = new MainMenu(_main, _username);
        }
    }
}
