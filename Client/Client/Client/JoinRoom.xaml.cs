﻿using System;
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
using System.Windows.Data;

using System.IO;

namespace Client
{
    /// <summary>
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Page
    {
        private readonly Frame _main;
        private readonly string _username;
        private NetworkStream sock;
        private Thread roomUpdaterThread;
        public JoinRoom(Frame main, string username, NetworkStream socket)
        {
            InitializeComponent();
            _main = main;
            _username = username;
            usernameBlock.Text = username;
            sock = socket;
            roomUpdaterThread = new Thread(new ThreadStart(updateRooms));
            roomUpdaterThread.Start();
        }
        private void updateRooms()
        {
            //this function accesses roomsGrid and adds buttons of rooms by the number of rooms
            while(true)
            {
                try
                {
                    //server should write rooms data into RoomsData.txt
                    StreamReader rd = new StreamReader("C:\\Users\\משתמש\\Documents\\cpp\\repos\\trivia\\Client\\Client\\RoomsData.txt");
                    string line;
                    while ((line = rd.ReadLine()) != null)
                    {
                        Button btn = new Button();
                        btn.Name = "join_room_button";
                        btn.Content = line;
                        btn.VerticalAlignment = VerticalAlignment.Center;
                        btn.HorizontalAlignment = HorizontalAlignment.Center;
                        this.roomsPanel.Children.Add(btn);
                    }
                    rd.Close();
                    if(this.roomsPanel.Children.Count == 0)
                    {
                        this.noRoomsBlock.Visibility = Visibility.Visible;
                    }
                    else
                    {
                        this.noRoomsBlock.Visibility = Visibility.Hidden;
                    }
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
        private void join_room_button(object sender, RoutedEventArgs e)
        {
            int defaultId = 0;
            roomUpdaterThread.Suspend();
            string json = "{'id': " + defaultId.ToString() + "}";

            byte[] msgToServer = new byte[1024];
            byte CodeByte = BitConverter.GetBytes((int)Codes.JoinRoom)[0];
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

            if (status == 1)
            {
                _main.Content = new Room(_main, _username, sock);
            }
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
            _main.Content = new MainMenu(_main, _username, sock);
        }
    }
}
