using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    public class ResponseDetails
    {
        public int len;
        public int code;
        public string json;
        public void getDetails(byte[] buffer)
        {
            string response = System.Text.Encoding.UTF8.GetString(buffer, 5, buffer.Length - 5);
            this.json = response.Substring(0, response.IndexOf('}') + 1);
            this.len = (buffer[1] << 24) | (buffer[2] << 16) | (buffer[3] << 8) | buffer[4];
            this.code = buffer[0];
        }
    }
}
