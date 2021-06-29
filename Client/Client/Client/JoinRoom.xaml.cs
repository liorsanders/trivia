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
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Windows.Data;

using System.IO;

namespace Client
{
    /// <summary>
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Page
    {
        private readonly Frame _main;
        private readonly string _username;
        private NetworkStream sock;
        private Thread roomUpdaterThread;
        public JoinRoom(Frame main, string username, NetworkStream socket)
        {
            InitializeComponent();
            _main = main;
            _username = username;
            usernameBlock.Text = username;
            sock = socket;
            roomUpdaterThread = new Thread(new ThreadStart(updateRooms));
            roomUpdaterThread.Start();
        }
        private void updateRooms()
        {
            //this function accesses roomsGrid and adds buttons of rooms by the number of rooms
            while(true)
            {
                try
                {
                    StreamReader rd = new StreamReader("C:\\Users\\משתמש\\Documents\\cpp\\repos\\trivia\\Client\\Client\\RoomData.txt");
                    string line;
                    while ((line = rd.ReadLine()) != null)
                    {
                        Button btn = new Button();
                        btn.Name = "join_room_button";
                        btn.Content = line;
                        roomsPanel.Children.Add(btn);
                    }
                    rd.Close();
                    if(roomsPanel.Children.Count == 0)
                    {
                        noRoomsBlock.Visibility = Visibility.Visible;
                    }
                    else
                    {
                        noRoomsBlock.Visibility = Visibility.Hidden;
                    }
                }
                catch { }
                Thread.Sleep(3000);
            }

        }
        private void join_room_button(object sender, RoutedEventArgs e)
        {
            roomUpdaterThread.Suspend();
            _main.Content = new Room(_main, _username, sock);
        }
        private void BT_Exit_Click(object sender, RoutedEventArgs e)
        {
            if (Application.Current.MainWindow is MainWindow main)
            {
                main.Close();
            }
        }

        private void BT_Menu_Click(object sender, RoutedEventArgs e)
        {
            _main.Content = new MainMenu(_main, _username, sock);
        }
    }
}
