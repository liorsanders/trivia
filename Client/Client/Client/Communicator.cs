using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;

namespace Client
{
    class Communicator
    {
        private NetworkStream _socket;
        public Communicator(NetworkStream socket)
        {
            _socket = socket;
        }
        public void sendMessage(List<byte> data)
        {
            byte[] buffer = data.ToArray();
            _socket.Write(buffer, 0, buffer.Length);
            _socket.Flush();
        }

        public byte[] getMessage()
        {
            byte[] buffer = new byte[4096];
            int bytesRead = _socket.Read(buffer, 0, 4096);
            _socket.Flush();
            return buffer;
        }
    }
}
