using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
enum Codes
{
	PersonalStatistics = 80,
	Signup = 73,
	Login = 25,
	Error = 8,
	Logout = 98,
	CreateRoom = 88,
	JoinRoom = 44, 
	GetRoom = 15,
	GetPlayers = 64,
	Statistics = 30,
	CloseRoom = 67,
	Start = 4,
	GetRoomState = 16,
	LeaveRoom = 49,
    HighScores = 35,
    GetRooms = 71
};
namespace Client
{
    public static class JsonRequestPacketSerializer
    {
        public static List<byte> serializeJson(string json, int code)
        {
            List<byte> msgToServer = new List<byte>();
            byte CodeByte = BitConverter.GetBytes(code)[0];
            var len = JsonResponsetPacketDeserializer.intToBytes(json.Length);
            msgToServer[0] = CodeByte;
            for (int i = 0; i < 4; i++)
            {
                msgToServer[i + 1] = len[i];
            }
            for (int i = 0; i < json.Length; i++)
            {
                msgToServer[i + 5] = (byte)(json[i]);
            }
            return msgToServer;
        }
    }
}
