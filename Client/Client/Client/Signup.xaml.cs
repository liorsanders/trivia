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
using Newtonsoft.Json;
using System.Net.Sockets;
using System.Net;

namespace Client
{
    /// <summary>
    /// Interaction logic for Signup.xaml
    /// </summary>
    public partial class Signup : Page
    {
        private NetworkStream sock;
        private readonly Frame _main;

        public Signup(Frame main)
        {
            InitializeComponent();
            _main = main;
        }

        private void TB_Email_GotFocus(object sender, RoutedEventArgs e)
        {
            TextBox tb = sender as TextBox;

            if (tb.Text == "email")
            {
                tb.Text = string.Empty;
            }
            else
            {
                tb.GotFocus -= TB_Email_GotFocus;
            }
        }
        private void TB_Email_LostFocus(object sender, RoutedEventArgs e)
        {
            TextBox tb = sender as TextBox;

            if (tb.Text == string.Empty)
            {
                tb.Text = "email";
            }
            else
            {
                tb.LostFocus -= TB_Email_LostFocus;
            }
        }

        private void TB_Email_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;

            if (tb.Text != "email" && tb.Text != "")
            {
                Color color = (Color)ColorConverter.ConvertFromString("#2a2e47");

                tb.Foreground = new SolidColorBrush(color);
            }
        }

        public void TB_Username_GotFocus(object sender, RoutedEventArgs e)
        {
            TextBox tb = sender as TextBox;

            if (tb.Text == "username")
            {
                tb.Text = string.Empty;
            }
            else
            {
                tb.GotFocus -= TB_Username_GotFocus;
            }
        }

        private void TB_Username_LostFocus(object sender, RoutedEventArgs e)
        {
            TextBox tb = sender as TextBox;

            if (tb.Text == string.Empty)
            {
                tb.Text = "username";
            }
            else
            {
                tb.LostFocus -= TB_Username_LostFocus;
            }
        }

        private void TB_Password_GotFocus(object sender, RoutedEventArgs e)
        {
            TextBox tb = sender as TextBox;

            if (tb.Text == "password")
            {
                tb.Text = string.Empty;
            }
            else
            {
                tb.GotFocus -= TB_Username_GotFocus;
            }
        }

        private void TB_Password_LostFocus(object sender, RoutedEventArgs e)
        {
            TextBox tb = sender as TextBox;

            if (tb.Text == string.Empty)
            {
                tb.Text = "password";
            }
            else
            {
                tb.LostFocus -= TB_Username_LostFocus;
            }
        }

        private void TB_Password_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;

            if (tb.Text != "password" && tb.Text != "")
            {
                Color color = (Color)ColorConverter.ConvertFromString("#2a2e47");

                tb.Foreground = new SolidColorBrush(color);

                tb.FontFamily = new FontFamily("Password");
            }
        }

        private void TB_Username_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;

            if (tb.Text != "username" && tb.Text != "")
            {
                Color color = (Color)ColorConverter.ConvertFromString("#2a2e47");

                tb.Foreground = new SolidColorBrush(color);
            }
        }

        private void CB_ShowPassword_Checked(object sender, RoutedEventArgs e)
        {

            TB_Password.FontFamily = new FontFamily("Courier");
        }

        private void CB_ShowPassword_Unchecked(object sender, RoutedEventArgs e)
        {
            if (TB_Password.Text != "password" && TB_Password.Text != "")
            {
                TB_Password.FontFamily = new FontFamily("Password");
            }
        }

        private void Bt_Login_MouseEnter(object sender, MouseEventArgs e)
        {
            Button bt = sender as Button;

            Color color = (Color)ColorConverter.ConvertFromString("#6711f2");

            bt.Foreground = new SolidColorBrush(color);
        }

        private void Bt_Login_MouseLeave(object sender, MouseEventArgs e)
        {

            Button bt = sender as Button;

            Color color = (Color)ColorConverter.ConvertFromString("#8f50f6");

            bt.Foreground = new SolidColorBrush(color);
        }
        private List<byte> intToBytes(int length)
        {
            List<byte> bytes = new List<byte>();

            bytes.Add((byte)(length >> 24));
	        bytes.Add((byte)(length >> 16));
            bytes.Add((byte)(length >> 8));
            bytes.Add((byte)(length >> 8));

	        return bytes;
        }
        
        private void connectToServer()
        {
            ConfigDetails details = new ConfigDetails();
            details.importDetailsFromConfig("config.txt");
            TcpClient client = new TcpClient();
            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse(details.ip), details.port);
            client.Connect(serverEndPoint);
            sock = client.GetStream();
        }

        private void Bt_Login_Click(object sender, RoutedEventArgs e)
        {
            Button bt = sender as Button;

            Color color = (Color)ColorConverter.ConvertFromString("#33067a");

            bt.Foreground = new SolidColorBrush(color);

            Account account = new Account();
            account.username = TB_Username.Text;
            account.password = TB_Password.Text;

            string json = JsonConvert.SerializeObject(account, Formatting.Indented);

            byte[] msgToServer = new byte[1024];
            byte CodeByte = BitConverter.GetBytes((int)Codes.Login)[0];
            var len = intToBytes(json.Length);
            msgToServer[0] = CodeByte;
            for(int i=0;i<4;i++)
            {
                msgToServer[i + 1] = len[i];
            }
            for(int i=0;i<json.Length;i++)
            {
                msgToServer[i + 5] = (byte)(json[0]);
            }
            //next send through the messgae through socket
            _main.Content = new Login(_main);
        }

        private void Bt_Login_LostMouseCapture(object sender, MouseEventArgs e)
        {
            Button bt = sender as Button;

            Color color = (Color)ColorConverter.ConvertFromString("#6711f2");

            bt.Foreground = new SolidColorBrush(color);
        }

        private void BT_Signup_Click(object sender, RoutedEventArgs e)
        {
            _main.Content = new MainMenu(_main, TB_Username.Text);
        }
    }
}
