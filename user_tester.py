import socket 

CONFIG_FILE_NAME = 'config.txt'
MSG_WITH_SERVER = 'Hello'

# return (server_ip, server_port)
def get_config_info(f_name):
    with open(f_name, 'r') as config_file:
        lines = config_file.read().split('\n')
        return lines[0][lines[0].index('=')+1:], int(lines[1][lines[1].index('=')+1:])
        

def main():
    try:
        # Create a TCP/IP socket
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            # Connect the socket to the port where the server is listening
            sock.connect(get_config_info(CONFIG_FILE_NAME))

            print('connected to server..')
            data = sock.recv(len(MSG_WITH_SERVER))
            print(f'msg from mt server: {data.decode()}')
            print(f'sending: {MSG_WITH_SERVER}')
            sock.sendall(MSG_WITH_SERVER.encode())

    except Exception as e:
        print(f'error: {e}')

if __name__ == '__main__':
    main()