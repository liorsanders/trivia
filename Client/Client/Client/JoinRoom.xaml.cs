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
using Newtonsoft.Json;
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
            Communicator communicator = new Communicator(sock);
            List<byte> msgToServer = new List<byte>();
            msgToServer.Add((byte)Codes.GetRooms);
            
            while (true)
            {
                try
                {
                    communicator.sendMessage(msgToServer);
                    var msgFromServer = communicator.getMessage();
                    string response = System.Text.Encoding.UTF8.GetString(msgFromServer);
                    int status = int.Parse(response.Substring(15, 3));
                    string jsonResponse = msgFromServer.ToString();
                    jsonResponse = jsonResponse.Substring(16, jsonResponse.Length - 16);
                    var rooms = JsonConvert.DeserializeObject<RoomsResult>(jsonResponse);

                    this.roomButtons.Items.Clear();
                    for(int i=0;i<rooms.roomNames.Count;i++)
                    {
                        ListBoxItem room = new ListBoxItem();
                        Button roomButton = new Button();
                        roomButton.FontFamily = new FontFamily("Comic Sans MS");
                        roomButton.FontSize = 30;
                        TextBlock text = new TextBlock();
                        text.Text = rooms.roomNames[i] + "(" + rooms.roomIds[i].ToString() + ")";
                        roomButton.Content = text;
                        room.Content = roomButton;
                        this.roomButtons.Items.Add(room);
                    }

                    if (this.roomButtons.Items.Count == 0)
                    {
                        this.noRoomsBlock.Visibility = Visibility.Visible;
                    }
                    else
                    {
                        this.noRoomsBlock.Visibility = Visibility.Hidden;
                    }
                }
                catch { }
                Thread.Sleep(3000);
            }

        }
        private void join_room_button(object sender, RoutedEventArgs e)
        {
            
            roomUpdaterThread.Suspend();
            string roomInformation = ((Button)sender).Content.ToString();
            int roomId = int.Parse(roomInformation[roomInformation.Length - 2].ToString());
            string roomName = roomInformation.Substring(0, roomInformation.IndexOf('('));
            _main.Content = new Room(_main, _username, sock, roomId, roomName);
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
            _main.Content = new MainMenu(_main, _username, sock);
        }
    }
}
