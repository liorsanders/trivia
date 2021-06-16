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
    /// Interaction logic for CreateRoom.xaml
    /// </summary>
    public partial class CreateRoom : Page
    {
        private readonly Frame _main;
        private readonly string _username;

        public CreateRoom(Frame main, string username)
        {
            InitializeComponent();

            _main = main;
            _username = username;

            this.username.Text = _username;
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
    }
}
