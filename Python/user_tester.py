import socket
import constants


# return (server_ip, server_port)
def get_server_details(file_name):
    config_file = open(file_name, "r")

    server_port = config_file.readline()
    server_port = server_port[server_port.find('='):]

    server_ip = config_file.readline()
    server_ip = server_ip[server_ip.find('='):]

    return server_port, server_ip


def receive_message(sock):
    ans = sock.recv(constants.MAX_RECV)
    # To Do: deserialize message


def sign_up(sock):
    data = {'username': constants.USERNAME, 'password': constants.PASSWORD, 'mail': constants.USER_MAIL}
    print(f'sending: {data} to server')
    data = bytearray(pickle.dumps(data))  # serialize dict before sending
    data[0:0] = constants.SIGN_UP_CODE  # insert message code
    sock.sendall(data)


def log_in(sock):
    data = {'username': constants.USERNAME, 'password': constants.PASSWORD}
    print(f'sending: {data} to server')
    data = bytearray(pickle.dumps(data))
    data[0:0] = constants.LOGIN_CODE  # insert message code
    sock.sendall(data)


def main():
    try:
        # Create a TCP/IP socket
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            sock.connect(get_server_details(constants.CONFIG_FILE_NAME))
            print('connected to server..')
            sign_up(sock)
            receive_message(sock)
            log_in(sock)
            receive_message(sock)

    except Exception as e:
        print(f'error: {e}')


if __name__ == '__main__':
    main()
