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
using Newtonsoft.Json;

namespace Client
{
    /// <summary>
    /// Interaction logic for CreateRoom.xaml
    /// </summary>
    public partial class CreateRoom : Page
    {
        private readonly Frame _main;
        private readonly string _username;
        private NetworkStream sock;

        public CreateRoom(Frame main, string username, NetworkStream socket)
        {
            InitializeComponent();

            _main = main;
            _username = username;
            this.username.Text = _username;
            sock = socket;
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

        public void TB_RoomName_GotFocus(object sender, RoutedEventArgs e)
        {
            TextBox tb = sender as TextBox;

            if (tb.Text == "room name")
            {
                tb.Text = string.Empty;
            }
            else
            {
                tb.GotFocus -= TB_RoomName_GotFocus;
            }
        }

        private void TB_RoomName_LostFocus(object sender, RoutedEventArgs e)
        {
            TextBox tb = sender as TextBox;

            if (tb.Text == string.Empty)
            {
                tb.Text = "room name";
            }
            else
            {
                tb.LostFocus -= TB_RoomName_LostFocus;
            }
        }

        private void TB_RoomName_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;

            if (tb.Text != "room name" && tb.Text != "")
            {
                Color color = (Color)ColorConverter.ConvertFromString("#2a2e47");

                tb.Foreground = new SolidColorBrush(color);
            }
        }

        private void BT_People_Up_Click(object sender, RoutedEventArgs e)
        {
            if (People.Content.ToString() != "10")
            {
                People.Content = Convert.ToInt32(People.Content.ToString()) + 1;
            }
        }

        private void BT_People_Down_Click(object sender, RoutedEventArgs e)
        {
            if (People.Content.ToString() != "0")
            {
                People.Content = Convert.ToInt32(People.Content.ToString()) - 1;
            }
        }

        private void BT_Time_Up_Click(object sender, RoutedEventArgs e)
        {
            if (Time.Content.ToString() != "30")
            {
                Time.Content = Convert.ToInt32(Time.Content.ToString()) + 1;
            }
        }

        private void BT_Time_Down_Click(object sender, RoutedEventArgs e)
        {
            if (Time.Content.ToString() != "0")
            {
                Time.Content = Convert.ToInt32(Time.Content.ToString()) - 1;
            }
        }

        private void BT_CreateRoom_Click(object sender, RoutedEventArgs e)
        {
            Communicator communicator = new Communicator(sock);
            CreateRoomRequest request = new CreateRoomRequest();
            request.amountOfPeople = int.Parse(People.Content.ToString());
            request.roomName = TB_RoomName.Text;
            request.timePerQuestion = int.Parse(Time.Content.ToString());
            string json = JsonConvert.SerializeObject(request, Formatting.Indented);

            List<byte> msgToServer = JsonRequestPacketSerializer.serializeJson(json, (int)(Codes.CreateRoom));
            communicator.sendMessage(msgToServer);
            var msgFromServer = communicator.getMessage();

            string response = System.Text.Encoding.UTF8.GetString(msgFromServer);
            int status = int.Parse(response.Substring(15, 3));
            string jsonResponse = msgFromServer.ToString();
            jsonResponse = jsonResponse.Substring(16, jsonResponse.Length - 16);
            int roomId = JsonConvert.DeserializeObject<CreateRoomResponse>(jsonResponse).id;

            if (status == 1)
            {
                _main.Content = new Room(_main, _username, sock, roomId, request.roomName);
            }
            else
            {
                MessageBox.Show("could not create room :(");
            }
        }
    }
}
