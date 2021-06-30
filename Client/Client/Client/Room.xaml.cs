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
using System.IO;
using Newtonsoft.Json;

namespace Client
{
    /// <summary>
    /// Interaction logic for Room.xaml
    /// </summary>
    public partial class Room : Page
    {
        private int roomId;
        private string roomName;
        private readonly Frame _main;
        private readonly string _username;
        private NetworkStream sock;
        private Thread roomUpdaterThread;

        public Room(Frame main, string username, NetworkStream socket, int id, string name)
        {
            InitializeComponent();

            //this.TB_Admin.Text = "Admin: " + username;
            sock = socket;
            _username = username;
            _main = main;
            roomId = id;
            roomName = name;
            roomUpdaterThread = new Thread(new ThreadStart(updateRoom));
            roomUpdaterThread.Start();
        }
        private void updateRoom()
        {
            Communicator communicator = new Communicator(sock);

            PlayersInRoomRequest request = new PlayersInRoomRequest();
            request.roomId = this.roomId;
            string json = JsonConvert.SerializeObject(request, Formatting.Indented);
            List<byte> msgToServer = JsonRequestPacketSerializer.serializeJson(json, (int)(Codes.GetPlayers));

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

                    var players = JsonConvert.DeserializeObject<PlayersInRoom>(jsonResponse);

                    PlayersList.Items.Clear();
                    for(int i=0;i<players.players.Count;i++)
                    {
                        ListBoxItem playerItem = new ListBoxItem();
                        TextBlock block = new TextBlock();
                        block.FontSize = 20;
                        block.FontFamily = new FontFamily("Comic Sans MS");
                        block.Text = players.players[i];
                        playerItem.Content = block;
                        this.PlayersList.Items.Add(playerItem);
                    }
                }
                catch { }

                Thread.Sleep(3000);
            }
        }
        
        private void BT_Back_Click(object sender, RoutedEventArgs e)
        {
            roomUpdaterThread.Suspend();
            _main.Content = new MainMenu(_main, _username, sock);
        }

        
    }
}
