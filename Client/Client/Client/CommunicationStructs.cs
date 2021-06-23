using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Client
{
    struct LoginRequest
    {
        string username;
        string password;
    }

    struct SignupRequest
    {
        string username;
        string password;
        string email;
    }

    
    struct GetPlayersInRoomRequest
    {
        uint roomId;
        
    }
    
    
    struct JoinRoomRequest
    {
        uint roomId;
    }

    
    struct CreateRoomRequest
    {
        string roomName;
        uint maxUsers;
        uint questionCount;
        uint answerTimeout;
    }
}
