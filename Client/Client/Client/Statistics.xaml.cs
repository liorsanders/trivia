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
    /// Interaction logic for Statistics.xaml
    /// </summary>
    public partial class Statistics : Page
    {
        private readonly Frame _main;
        private readonly string _username;
        public Statistics(Frame main, string username)
        {
            InitializeComponent();
            _main = main;
            _username = username;
            BT_Personal_Statistics.Content = username + "'s statistics";
        }

        private void BT_Personal_Statistics_Click(object sender, RoutedEventArgs e)
        {
            _main.Content = new PersonalStatistics(_main, _username);
        }
        private void BT_High_Scores_Click(object sender, RoutedEventArgs e)
        {
            _main.Content = new HighScores(_main, _username);
        }
    }
}
