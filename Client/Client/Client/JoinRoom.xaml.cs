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
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Page
    {
        private readonly Frame _main;
        private readonly string _username;
        public JoinRoom(Frame main, string username)
        {
            InitializeComponent();
            _main = main;
            _username = username;
            tbUsername.Text = "hello " + username;
            /*TODO:
            * add room options to StackPannel after getting rooms from the backend
            * if there are no rooms display a message to say that there are no rooms
            */
        }
        private void btnBack_Click(object sender, RoutedEventArgs e)
        {
            _main.Content = new MainMenu(_main, _username);
        }
    }
}
