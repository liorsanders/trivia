using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    public class HighScoresResult
    {
        //assume the order is ascending and usernames[i]
        // and scores[i] are same person
        public List<string> usernames;
        public List<double> scores;
    }
}
