using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
    }
}
