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

        public Signup(Frame main, NetworkStream socket)
        {
            InitializeComponent();
            _main = main;
            sock = socket;
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
        
        

        private void Bt_Login_Click(object sender, RoutedEventArgs e)
        {
            Button bt = sender as Button;

            Color color = (Color)ColorConverter.ConvertFromString("#33067a");

            bt.Foreground = new SolidColorBrush(color);

            _main.Content = new Login(_main, sock);

        }

        private void Bt_Login_LostMouseCapture(object sender, MouseEventArgs e)
        {
            Button bt = sender as Button;

            Color color = (Color)ColorConverter.ConvertFromString("#6711f2");

            bt.Foreground = new SolidColorBrush(color);
        }

        private void BT_Signup_Click(object sender, RoutedEventArgs e)
        {
            Communicator communicator = new Communicator(sock);
            SignupAccount account = new SignupAccount();
            account.Mail = TB_Email.Text;
            account.Username = TB_Username.Text;
            account.Password = TB_Password.Text;

            string json = JsonConvert.SerializeObject(account, Formatting.Indented);

            List<byte> msgToServer = new List<byte>();
            byte CodeByte = BitConverter.GetBytes((int)Codes.Signup)[0];
            var len = intToBytes(json.Length);
            msgToServer.Add(CodeByte);
            for (int i = 0; i < 4; i++)
            {
                msgToServer.Add(len[i]);
            }
            for (int i = 0; i < json.Length; i++)
            {
                msgToServer.Add((byte)(json[i]));
            }

            communicator.sendMessage(msgToServer);
            var msgFromServer = communicator.getMessage();

            string response = System.Text.Encoding.UTF8.GetString(msgFromServer);
            int status = int.Parse(response.Substring(15, 3));

            if (status == 1)
            {
                _main.Content = new MainMenu(_main, TB_Username.Text, sock);
            }
            else
            {
                MessageBox.Show("invalid signup!");
            }
        }
    }
}
