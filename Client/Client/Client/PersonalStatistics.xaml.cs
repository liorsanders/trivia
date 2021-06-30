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
        private void initializeAverageTime(double time)
        {
            Personal_averageAnsweringTime.Text = time.ToString();
            if (time < 5)
            {
                Personal_averageAnsweringTime.Foreground = new SolidColorBrush(Colors.Green);
            }
            else if (time < 10)
            {
                Personal_averageAnsweringTime.Foreground = new SolidColorBrush(Colors.Blue);
            }
            else
            {
                Personal_averageAnsweringTime.Foreground = new SolidColorBrush(Colors.Red);
            }
        }
        private void initializePersonalStats()
        {
            Communicator communicator = new Communicator(sock);

            GetPersonalStatistics personalStatistics = new GetPersonalStatistics();
            personalStatistics.username = _username;

            string json = JsonConvert.SerializeObject(personalStatistics, Formatting.Indented);

            List<byte> msgToServer = JsonRequestPacketSerializer.serializeJson(json, (int)(Codes.PersonalStatistics));
            communicator.sendMessage(msgToServer);
            var msgFromServer = communicator.getMessage();

            string response = System.Text.Encoding.UTF8.GetString(msgFromServer);
            int status = int.Parse(response.Substring(15, 3));

            string jsonResponse = msgFromServer.ToString();
            jsonResponse = jsonResponse.Substring(16, jsonResponse.Length - 16);

            var statistics = JsonConvert.DeserializeObject<PersonalStatisticsResult>(jsonResponse);
            initializeAverageTime(statistics.averageTime);
            Personal_gamesPlayed.Text = statistics.gamesPlayed.ToString();
            Personal_rightQuestions.Text = statistics.answeredRight.ToString();
            Personal_wrongQuestions.Text = statistics.answeredWrong.ToString();

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
