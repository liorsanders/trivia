using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Client
{
    class ConfigDetails
    {
        public string ip;
        public int port;
        public void importDetailsFromConfig(string configPath)
        {
            //string content;
            //using (FileStream fs = File.Open(configPath, FileMode.Open))
            //{
            //    byte[] bytesRead = new byte[fs.Length];
            //    fs.Read(bytesRead, 0, Convert.ToInt32(fs.Length));
            //    content = System.Text.Encoding.UTF8.GetString(bytesRead);
            //}
            //var lines = content.Split(new[] { '\r', '\n' });
            //var findEquals = lines[0].IndexOf('=') + 1;
            //this.ip = lines[0].Substring(findEquals, lines[0].Length - findEquals);
            //findEquals = lines[1].IndexOf('=') + 1;
            //this.port = int.Parse(lines[1].Substring(findEquals, lines[1].Length - findEquals));
            this.ip = "127.0.0.1";
            this.port = 8820;
        }
    }
}
