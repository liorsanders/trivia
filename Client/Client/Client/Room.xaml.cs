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
            showRoomState();
        }

        private void showRoomState()
        {
            List<byte> msgToServer = new List<byte>();
            msgToServer.Add((byte)Codes.GetRoomState);
            Communicator Communicator = new Communicator(sock);
            roomUpdaterThread.Suspend();
            Communicator.sendMessage(msgToServer);
            var msgFromServer = Communicator.getMessage();
            roomUpdaterThread.Resume();
            ResponseDetails details = new ResponseDetails();
            details.getDetails(msgFromServer);
            if (!JsonResponsetPacketDeserializer.checkForError(details))
            {
                try
                {
                    var roomState = JsonConvert.DeserializeObject<RoomStateResponse>(details.json);
                    string textToShow = "ROOM STATE:" + Environment.NewLine;
                    textToShow = textToShow + "has game begun: " + roomState.ToString();
                    textToShow = textToShow + Environment.NewLine + "question count: " + roomState.questionCount.ToString();
                    textToShow = textToShow + Environment.NewLine + "answer timeout: " + roomState.answerTimeout.ToString();
                    textToShow = textToShow + Environment.NewLine + "status: " + roomState.status.ToString();
                    textToShow = textToShow + Environment.NewLine + "players:" + Environment.NewLine;
                    for (int i = 0; i < roomState.players.Count; i++)
                    {
                        textToShow = textToShow + roomState.players[i] + Environment.NewLine;
                    }
                }
                catch { }
            }
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
                    ResponseDetails details = new ResponseDetails();
                    communicator.sendMessage(msgToServer);
                    var msgFromServer = communicator.getMessage();
                    details.getDetails(msgFromServer);
                    var players = JsonConvert.DeserializeObject<PlayersInRoom>(details.json);

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

        private void BT_Start_Game_Click(object sender, RoutedEventArgs e)
        {

        }

        private void BT_Close_Room_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
