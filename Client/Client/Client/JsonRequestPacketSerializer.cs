using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
enum Codes
{
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
	LeaveRoom = 49
};
namespace Client
{
    static class JsonRequestPacketSerializer
    {
        static void serializeLoginRequest(string username, string password)
        {
			
        }
    }
}
