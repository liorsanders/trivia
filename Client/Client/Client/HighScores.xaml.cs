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
using Newtonsoft.Json;

namespace Client
{
    /// <summary>
    /// Interaction logic for HighScores.xaml
    /// </summary>
    public partial class HighScores : Page
    {
        private readonly Frame _main;
        private readonly string _username;
        private NetworkStream sock;
        public HighScores(Frame main, string username, NetworkStream socket)
        {
            InitializeComponent();
            _main = main;
            _username = username;
            usernameBlock.Text = username;
            sock = socket;
            initializeHighScores();
        }

        private void initializeHighScores()
        {
            Communicator communicator = new Communicator(sock);
            List<byte> msgToServer = new List<byte>();
            msgToServer.Add((byte)(Codes.HighScores));
            communicator.sendMessage(msgToServer);
            var msgFromServer = communicator.getMessage();
            ResponseDetails details = new ResponseDetails();
            details.getDetails(msgFromServer);
            if(!JsonResponsetPacketDeserializer.checkForError(details))
            {
                var scores = JsonConvert.DeserializeObject<HighScoresResult>(details.json);

                for (int i = 0; i < scores.scores.Count; i++)
                {
                    TableCell rank = new TableCell();
                    rank.Blocks.Add(new Paragraph(new Run(i.ToString())));
                    this.highScoresRankRow.Cells.Add(rank);
                    TableCell score = new TableCell();
                    score.Blocks.Add(new Paragraph(new Run(scores.scores[i].ToString())));
                    this.highScoreScoreRow.Cells.Add(score);
                    TableCell name = new TableCell();
                    name.Blocks.Add(new Paragraph(new Run(scores.usernames[i])));
                    this.highScoresNameRow.Cells.Add(name);
                }
            }
            
        }
        private void BT_Exit_Click(object sender, RoutedEventArgs e)
        {
            if (Application.Current.MainWindow is MainWindow main) { 

                this.highScoresNameRow.Cells.Clear();
                this.highScoresRankRow.Cells.Clear();
                this.highScoreScoreRow.Cells.Clear();
                main.Close();
            }
        }

        private void BT_Menu_Click(object sender, RoutedEventArgs e)
        {
            this.highScoresNameRow.Cells.Clear();
            this.highScoresRankRow.Cells.Clear();
            this.highScoreScoreRow.Cells.Clear();
            _main.Content = new MainMenu(_main, _username, sock);
        }
    }
}
