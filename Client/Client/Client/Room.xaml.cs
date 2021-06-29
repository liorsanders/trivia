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
using System.Threading;
using System.IO;

namespace Client
{
    /// <summary>
    /// Interaction logic for Room.xaml
    /// </summary>
    public partial class Room : Page
    {
        private int roomId;
        private readonly Frame _main;
        private readonly string _username;
        private NetworkStream sock;
        private Thread roomUpdaterThread;

        public Room(Frame main, string username, NetworkStream socket)
        {
            InitializeComponent();

            this.TB_Admin.Text = "Admin: " + username;
            sock = socket;
            _username = username;
            _main = main;
            roomUpdaterThread = new Thread(new ThreadStart(updateRoom));
            roomUpdaterThread.Start();
            if(roomId == null)
            {
                roomId = 0; // assign default value
            }
        }
        private void updateRoom()
        {
            while(true)
            {
                try
                {
                    string json = "{'id': " + roomId + "}";

                    byte[] msgToServer = new byte[1024];
                    byte CodeByte = BitConverter.GetBytes((int)Codes.GetPlayers)[0];
                    var len = intToBytes(json.Length);
                    msgToServer[0] = CodeByte;
                    for (int i = 0; i < 4; i++)
                    {
                        msgToServer[i + 1] = len[i];
                    }
                    for (int i = 0; i < json.Length; i++)
                    {
                        msgToServer[i + 5] = (byte)(json[i]);
                    }
                    sock.Write(msgToServer, 0, msgToServer.Length);
                    sock.Flush();

                    var msgFromServer = new byte[4096];
                    int byteRead = sock.Read(msgFromServer, 0, msgFromServer.Length);
                    sock.Flush();

                    string response = System.Text.Encoding.UTF8.GetString(msgFromServer);
                    int status = int.Parse(response.Substring(15, 3));

                }
                catch { }

                Thread.Sleep(3000);
            }
        }
        private List<byte> intToBytes(int length)
        {
            List<byte> bytes = new List<byte>();

            bytes.Add((byte)(length >> 24));
            bytes.Add((byte)(length >> 16));
            bytes.Add((byte)(length >> 8));
            bytes.Add((byte)length);

            return bytes;
        }
        private void BT_Back_Click(object sender, RoutedEventArgs e)
        {
            roomUpdaterThread.Suspend();
            _main.Content = new MainMenu(_main, _username, sock);
        }

        
    }
}
