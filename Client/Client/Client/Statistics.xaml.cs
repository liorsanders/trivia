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
using System.Net.Sockets;
using System.Net;

namespace Client
{
    /// <summary>
    /// Interaction logic for Statistics.xaml
    /// </summary>
    public partial class Statistics : Page
    {
        private readonly Frame _main;
        private readonly string _username;
        private NetworkStream sock;

        public Statistics(Frame main, string username, NetworkStream socket)
        {
            InitializeComponent();
            _main = main;
            _username = username;
            sock = socket;
            BT_Personal_Statistics.Content = username + "'s statistics";
        }

        private void BT_Personal_Statistics_Click(object sender, RoutedEventArgs e)
        {
            _main.Content = new PersonalStatistics(_main, _username, sock);
        }
        private void BT_High_Scores_Click(object sender, RoutedEventArgs e)
        {
            _main.Content = new HighScores(_main, _username, sock);
        }
    }
}
