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
    /// Interaction logic for MainMenu.xaml
    /// </summary>
    public partial class MainMenu : Page
    {
        private readonly Frame _main;
        private readonly string _username;

        public MainMenu(Frame main, string username)
        {
            InitializeComponent();

            _main = main;
        }

        private void BT_CreateRoom_Click(object sender, RoutedEventArgs e)
        {
            // move to create room
        }

        private void BT_Statistics_Click(object sender, RoutedEventArgs e)
        {
            // move to statistics
        }

        private void BT_Exit_Click(object sender, RoutedEventArgs e)
        {
            if (Application.Current.MainWindow is MainWindow main)
            {
                main.Close();
            }
        }

        private void BT_JoinRoom_Click(object sender, RoutedEventArgs e)
        {
            // move to join room
        }
    }
}
