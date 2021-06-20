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

namespace Client
{
    /// <summary>
    /// Interaction logic for PersonalStatistics.xaml
    /// </summary>
    public partial class PersonalStatistics : Page
    {
        private readonly Frame _main;
        private readonly string _username;
        public PersonalStatistics(Frame main, string username)
        {
            InitializeComponent();
            _main = main;
            _username = username;
            usernameBlock.Text = username;
            initializeStats();
        }
        private void initializeStats()
        {
            //get stats from backend, for now use default values
            //use colors for red: bad score, green: good score, blue: medium score
            string defaultAnsweringTime = "00:00";
            int defaultGamesPlayed = 0;
            int defaultRightQuestions = 0;
            int defaultWrongQuestions = 0;

            Personal_averageAnsweringTime.Text = defaultAnsweringTime;
            Personal_averageAnsweringTime.Foreground = new SolidColorBrush(Colors.Red);

            Personal_gamesPlayed.Text = defaultGamesPlayed.ToString();

            Personal_rightQuestions.Text = defaultRightQuestions.ToString();
            Personal_rightQuestions.Foreground = new SolidColorBrush(Colors.Red);

            Personal_wrongQuestions.Text = defaultWrongQuestions.ToString();
            Personal_wrongQuestions.Foreground = new SolidColorBrush(Colors.Green);
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
            _main.Content = new MainMenu(_main, _username);
        }
    }
}
