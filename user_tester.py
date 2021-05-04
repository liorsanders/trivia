import socket 
import pickle

CONFIG_FILE_NAME = 'config.txt'
MSG_WITH_SERVER = 'Hello'
MAX_RECV = 1024
USERNAME = 'user1'
PASSWORD = '1234'

LOGIN_CODE = '\x01'.encode()
SIGN_UP_CODE = '\x02'.encode()

# return (server_ip, server_port)
def get_config_info(f_name):
    with open(f_name, 'r') as config_file:
        lines = config_file.read().split('\n')
        return lines[0][lines[0].index('=')+1:], int(lines[1][lines[1].index('=')+1:])
        

def recieve_msg(sock):
    ans = sock.recv(MAX_RECV)
    print(f'recieved from server: {pickle.loads(ans)}') # desirializing and printing data from server

def main():
    try:
        # Create a TCP/IP socket
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            sock.connect(get_config_info(CONFIG_FILE_NAME))
            print('connected to server..')
            login = {'username': USERNAME, 'password': PASSWORD}
            sign_up = {'username': USERNAME, 'password': PASSWORD, 'mail': 'user1@gmail.com'}
            print(f'sending: {sign_up} to server')
            data = bytearray(pickle.dumps(sign_up)) # serialize dict before sending
            data[0:0] = SIGN_UP_CODE # insert message code
            sock.sendall(data)
            recieve_msg(sock)
            print(f'sending: {login} to server')
            data = bytearray(pickle.dumps(login))
            data[0:0] = LOGIN_CODE # insert message code
            sock.sendall(data)
            recieve_msg(sock)
            
    except Exception as e:
        print(f'error: {e}')

if __name__ == '__main__':
    main()