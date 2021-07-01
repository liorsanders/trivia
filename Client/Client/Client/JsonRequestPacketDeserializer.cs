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
    public static class JsonResponsetPacketDeserializer
    {
        public static List<byte> intToBytes(int length)
        {
            List<byte> bytes = new List<byte>();

            bytes.Add((byte)(length >> 24));
            bytes.Add((byte)(length >> 16));
            bytes.Add((byte)(length >> 8));
            bytes.Add((byte)length);

            return bytes;
        }
        public static bool checkForError(ResponseDetails details)
        {
            if (details.code == (byte)Codes.Error)
            {
                var jsonFromServer = JsonConvert.DeserializeObject<ErrorMessage>(details.json);
                MessageBox.Show("error: " + jsonFromServer.message);
                return true;
            }
            return false;
        }
    }
}
