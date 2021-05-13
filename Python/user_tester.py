import socket
import constants
import json


# return (server_ip, server_port)
def get_server_details(file_name):
    config_file = open(file_name, "r")

    server_ip = config_file.readline()
    server_ip = server_ip[server_ip.find('=') + 1:].replace("\n", "")  # extract ip

    server_port = config_file.readline()
    server_port = int(server_port[server_port.find('=') + 1:]) # extract port

    return server_ip, server_port


def deserialize_message(message):
    code = message[constants.CODE_INDEX]

    length = int.from_bytes(
        message[constants.LENGTH_INDEX:constants.MESSAGE_INDEX],
        byteorder="big")

    data = message[constants.MESSAGE_INDEX:].decode()

    return code, length, data


def receive_message(sock):
    answer = sock.recv(constants.MAX_RECV)
    code, length, data = deserialize_message(answer)
    print("message has received!\ncode:", code, ", length:", length, ", data:", data)


def length_to_four_bytes(data):
    data_length = len(data)

    return data_length.to_bytes(constants.INT_BYTES,
                                byteorder='big')  # convert the length from int to four bytes


def sign_up(sock):
    data = {
        "Username": constants.USERNAME,
        "Password": constants.PASSWORD,
        "Mail": constants.USER_MAIL
    }

    json_data = json.dumps(data)
    print("sending:", json_data, ",to server.")

    full_message = constants.SIGN_UP_CODE + \
                   length_to_four_bytes(json_data) + \
                   json_data.encode()

    sock.sendall(full_message)


def log_in(sock):
    data = {
        "Username": constants.USERNAME,
        "Password": constants.PASSWORD,
    }

    json_data = json.dumps(data)
    print("sending:", json_data, ",to server.")

    full_message = constants.LOGIN_CODE + \
                   length_to_four_bytes(json_data) + \
                   json_data.encode()

    sock.sendall(full_message)


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
        print("error:", {e})


if __name__ == '__main__':
    main()
