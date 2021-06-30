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
    /// Interaction logic for PersonalStatistics.xaml
    /// </summary>
    public partial class PersonalStatistics : Page
    {
        private readonly Frame _main;
        private readonly string _username;
        private NetworkStream sock;
        public PersonalStatistics(Frame main, string username, NetworkStream socket)
        {
            InitializeComponent();
            _main = main;
            _username = username;
            sock = socket;
            usernameBlock.Text = username;
            initializePersonalStats();
        }
        private void initializePersonalStats()
        {
            //get stats from backend, for now use default values
            //use colors for red: bad score, green: good score, blue: medium score
            //string defaultAnsweringTime = "00:00";
            //int defaultGamesPlayed = 0;
            //int defaultRightQuestions = 0;
            //int defaultWrongQuestions = 0;

            //Personal_averageAnsweringTime.Text = defaultAnsweringTime;
            //Personal_averageAnsweringTime.Foreground = new SolidColorBrush(Colors.Red);

            //Personal_gamesPlayed.Text = defaultGamesPlayed.ToString();

            //Personal_rightQuestions.Text = defaultRightQuestions.ToString();
            //Personal_rightQuestions.Foreground = new SolidColorBrush(Colors.Red);

            //Personal_wrongQuestions.Text = defaultWrongQuestions.ToString();
            //Personal_wrongQuestions.Foreground = new SolidColorBrush(Colors.Green);
            Communicator communicator = new Communicator(sock);

            GetPersonalStatistics personalStatistics = new GetPersonalStatistics();
            personalStatistics.username = _username;

            string json = JsonConvert.SerializeObject(personalStatistics, Formatting.Indented);

            List<byte> msgToServer = JsonRequestPacketSerializer.serializeJson(json, (int)(Codes.PersonalStatistics));
            communicator.sendMessage(msgToServer);
            var msgFromServer = communicator.getMessage();

            string response = System.Text.Encoding.UTF8.GetString(msgFromServer);
            int status = int.Parse(response.Substring(15, 3));

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
