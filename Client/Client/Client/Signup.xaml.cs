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
    /// Interaction logic for Signup.xaml
    /// </summary>
    public partial class Signup : Page
    {
        public Signup()
        {
            InitializeComponent();
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
        private void TB_Email_TextChanged(object sender, TextChangedEventArgs e)
        {


        }

        private void TB_Email_LostFocus(object sender, RoutedEventArgs e)
        {

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

        private void Bt_Signup_MouseEnter(object sender, MouseEventArgs e)
        {
            Button bt = sender as Button;

            Color color = (Color)ColorConverter.ConvertFromString("#6711f2");

            bt.Foreground = new SolidColorBrush(color);
        }

        private void Bt_Signup_MouseLeave(object sender, MouseEventArgs e)
        {

            Button bt = sender as Button;

            Color color = (Color)ColorConverter.ConvertFromString("#8f50f6");

            bt.Foreground = new SolidColorBrush(color);
        }

        private void Bt_Signup_Click(object sender, RoutedEventArgs e)
        {
            Button bt = sender as Button;

            Color color = (Color)ColorConverter.ConvertFromString("#33067a");

            bt.Foreground = new SolidColorBrush(color);
        }

        private void Bt_Signup_LostMouseCapture(object sender, MouseEventArgs e)
        {
            Button bt = sender as Button;

            Color color = (Color)ColorConverter.ConvertFromString("#6711f2");

            bt.Foreground = new SolidColorBrush(color);
        }




    }
}
