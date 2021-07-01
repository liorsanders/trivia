using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    public class RoomStateResponse
    {
        public uint status;
        public bool hasGameBegun;
        public List<string> players;
        public uint questionCount;
        public uint answerTimeout;
    }
}
