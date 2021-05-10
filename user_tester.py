import socket 
import pickle
import constants

# return (server_ip, server_port)
def get_config_info(f_name):
    with open(f_name, 'r') as config_file:
        lines = config_file.read().split('\n')
        return lines[0][lines[0].index('=')+1:], int(lines[1][lines[1].index('=')+1:])
        

def recieve_msg(sock):
    ans = sock.recv(constants.MAX_RECV)
    print(f'recieved from server: {pickle.loads(ans)}') # desirializing and printing data from server

def sign_up(sock):
    data = {'username': constants.USERNAME, 'password': constants.PASSWORD, 'mail': constants.USER_MAIL}
    print(f'sending: {data} to server')
    data = bytearray(pickle.dumps(data)) # serialize dict before sending
    data[0:0] = constants.SIGN_UP_CODE # insert message code
    sock.sendall(data)
    
def log_in(sock):
    data = {'username': constants.USERNAME, 'password': constants.PASSWORD}
    print(f'sending: {data} to server')
    data = bytearray(pickle.dumps(data))
    data[0:0] = constants.LOGIN_CODE # insert message code
    sock.sendall(data)
    

def main():
    try:
        # Create a TCP/IP socket
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            sock.connect(get_config_info(constants.CONFIG_FILE_NAME))
            print('connected to server..')
            sign_up(sock)
            recieve_msg(sock)
            log_in(sock)
            recieve_msg(sock)            
            
    except Exception as e:
        print(f'error: {e}')

if __name__ == '__main__':
    main()