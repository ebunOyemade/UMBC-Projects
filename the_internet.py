"""
File:    the_internet.py
Author:  ebun oyemade
Date:    12/2/21
Section: 12
E-mail:  eoyemad1@umbc.edu
Description:
  simulates the internet by creating servers and connections between those servers and finding routes between those servers
"""

QUIT = 'quit'
IP_CHECK = 256
CONNECTIONS = 'connections'
IP = 'ip'
CURRENT = 'current'
EMPTY = ''
CREATE_SERVER = 'create-server'
CREATE_CONNECTION = 'create-connection'
SET_SERVER = 'set-server'
PING = 'ping'
TRACEROUTE = ['traceroute', 'tracert']
IP_CONFIG = 'ip-config'
DISPLAY_SERVERS = 'display-servers'
TIME = 'time'
SPACE = ' '
COUNT = 'count'
TWO = 2
THREE = 3
FOUR = 4
DOT = '.'

def run_the_internet(command, servers, current_ip):
    '''
        the function command and then calls the appropriate function
        :param command: a string that determines what function will be called
        :param servers: a dictionary that contains the information of all srevers
        :param current_ip: a dictionary contains which server has been selected
        :return:
    '''
    # splits command up to obtain information to activate necessary function/if statement 
    info = command.split(SPACE)    

    if info[0] == CREATE_SERVER:
        if len(info) == THREE:
            create_server(info[1], info[TWO], servers)

    elif info[0] == CREATE_CONNECTION:
        if len(info) == FOUR:
            create_connection(info[1], info[TWO], info[THREE], servers)

    elif info[0] == SET_SERVER:
        if len(info) == TWO:
            if info[1] in servers:
                current_ip[CURRENT] = info[1]
                print(f'Server {current_ip[CURRENT]} selected')

            else:
                print(f'Server/IP {info[1]} not found')

    elif info[0] == PING:
        if current_ip and len(info) == TWO:
            visited = []
            server = find_server(servers, info[1])

            if server:
                ping(servers, current_ip[CURRENT], current_ip[CURRENT], server, visited)

            else:
                print(f'Server/IP {info[1]} not found')

    elif info[0] in TRACEROUTE:
        if current_ip and len(info) == TWO:
            visited = []
            server = find_server(servers, info[1])

            if server:
                print(f'Tracing route to {server} [{info[1]}]')
                traceroute(servers, current_ip[CURRENT], current_ip[CURRENT], info[1], visited)

            else:
                print(f'Server/IP {info[1]} not found')

    elif info[0] == IP_CONFIG:
        if current_ip:
            name = current_ip[CURRENT]
            print(name, "\t", servers[name][IP])

    elif info[0] == 'display-servers':
        display_server(servers)

    else:
        print(f'{info[0]} is not a valid command')


def create_server(name, address, servers):
    '''
        This function creates servers checks to see if they are valid and stores in servers

        :param name: a string that stores the name of the of the server
        :param address: a string that stores the address of the studio
        :param servers: a dictionary that stores the information for all servers
        :return:
    '''
    is_valid = True
    check = address.split(DOT)
    
    if len(check) == FOUR:
        # Splits address into four to evaluate if each number is under 256
        for i in check:
            i = int(i)

            if i >= IP_CHECK:
                is_valid = False
    else:
        is_valid = False

    if not is_valid:
        print(f'The ip address {address} is not a valid address')
        return
    
    if name in servers:
        print(f'Server {name} already exists')
        return 
    
    for key in servers:
        if address in servers[key][IP]:
            print(f'The ip address {address} already exists')
            return
    
    # creates server as key in servers that stores a dictionary
    servers[name] = {}
    servers[name][IP] = address
    servers[name][CONNECTIONS] = []
    servers[name][TIME] = []
    print(f'Success: A server with name {name} was created at ip {address}')


def create_connection(connect1, connect2, time, servers):
    '''
        This function creates a connection between servers and stores it in servers

        :param connect1: a string that contains the first server
        :param connect2: a string that contains the second server
        :param time: a string that contains time in ms
        :param servers: a dictionary that contains information about the servers
        :return:
    '''
    # checks if there is already a connection between servers and if each server exists
    if connect1 in servers and connect2 in servers:
        if connect2 not in servers[connect1][CONNECTIONS]:
            servers[connect1][CONNECTIONS].append(connect2)
            servers[connect1][TIME].append(time)
            servers[connect2][CONNECTIONS].append(connect1)
            servers[connect2][TIME].append(time)
            print(f'A server with name {connect1} is now connected to {connect2}')

        else:
            print(f'The server {connect1} is already connected to {connect2}')

    else:
        print(f'The server(s) {connect1} and or {connect2} do not exist')


def ping(servers, start, current_ip, destination, visited, visit=[], time=0):
    """
        This function determines how long it takes (in ms) to get to one server another if possible
        by recursively testing routes
        
        :param servers: a dictionary that contains information about the servers
        :param start: a string that contains the starting server
        :param current_ip: a string that contains the current server
        :param destination: a string that has the end server
        :param visited: a list that contains the permanent list of visited servers
        :param visit: a list that contains the visited servers for each iteration
        :param time: a integer that contains the total time to reach the server
        :return:
    """
    if destination == current_ip:
        print(f'Reply from {servers[current_ip][IP]} time = {time}')
        return

    elif start in visited:
        # returns when all possibilities are exhausted and destination can not be reached
        print(f'Unable to resolve target system name {destination}')
        return

    else:
        visit.append(current_ip)
        for i in range(len(servers[current_ip][CONNECTIONS])):
            test = servers[current_ip][CONNECTIONS][i]

            if test not in visit and test not in visited:
                time += int(servers[current_ip][TIME][i])
                current_ip = servers[current_ip][CONNECTIONS][i]
                return ping(servers, start, current_ip, destination, visited, visit, time)
        # resets if a route reaches dead end    
        visited.append(current_ip)
        current_ip = start
        visit = []
        return ping(servers, start, current_ip, destination, visited, visit, time * 0)


def traceroute(servers, start, current_ip, destination, visited, visit=[], route={}, time=0, count=0):
    """
        This function finds the route to get to one server another if possible
        
        :param servers: a dictionary that contains information about the servers
        :param start: a string that contains the starting server
        :param current_ip: a string that contains the current server
        :param destination: a string that has the end server
        :param visited: a list that contains the permanent list of visited servers
        :param visit: a list that contains the visited servers for each iteration
        :param route: a dictionary that contains the route between two servers
        :param time: a integer that contains the total time to reach the server
        :param count: a integer that counts each step in the route
        :return:
    """
    if destination == current_ip:
        for key in route:
            print('\t', route[key][COUNT], '\t', route[key][TIME], '\t', servers[key][IP], '\t', key)

        print('\t', count, '\t', time, '\t', servers[current_ip][IP], '\t', current_ip)
        print('Trace complete')
        return

    elif start in visited:
        # returns when all possibilities are exhausted and destination can not be reached
        print(f'Unable to resolve target system name {destination}')

    else:
        # creates new entry in the dictionary 
        visit.append(current_ip)
        route[current_ip] = {}
        route[current_ip][TIME] = time
        route[current_ip][IP] = servers[current_ip][IP]
        route[current_ip][COUNT] = count

        for i in range(len(servers[current_ip][CONNECTIONS])):
            test = servers[current_ip][CONNECTIONS][i]
            if test not in visited and test not in visit:
                time = int(servers[current_ip][TIME][i])
                current_ip = servers[current_ip][CONNECTIONS][i]
                return traceroute(servers, start, current_ip, destination, visited, visit, route, time, count + 1)
            
        #resets if route reaches a dead end
        visited.append(current_ip)
        current_ip = start
        visit = []
        route = {}
        return traceroute(servers, start, current_ip, destination, visited, visit, route, time * 0, count * 0)


def display_server(servers):
    """
    this function displays the servers with information o
    :param servers:
    :return:
    """
    for key in servers:
        # goes through servers and prints all information about each server
        print('\t', key, end='\t')
        print(servers[key][IP])
        connections_list = servers[key][CONNECTIONS]

        for i in range(len(connections_list)):
            print('\t', end='\t')
            name = connections_list[i]
            print(name, '\t', servers[name][IP], '\t', servers[key][TIME][i])


def find_server(servers, selected):
    """
    This function determines if a server exists and if it finds the name of a server based on the ip address
    if the name was not given 
    :param servers: a dictionary that contains all servers 
    :param selected: a string that contains an ip address or name of a server
    :return: a string that is the name of server or an empty string if is not in the server
    """
    in_servers = False

    if selected in servers:
        return selected

    else:
        for key in servers:
            if selected in servers[key][IP]:
                in_servers = True

            if in_servers:
                converted = servers[key]
                return converted
            
        # converted is set to an empty string to evaluate an if statement     
        converted = EMPTY
        return converted


if __name__ == '__main__':
    current_ip = {}
    servers = {}
    command = input(">>> ")

    while command != QUIT:
        # prompts for commands until quit is entered
        run_the_internet(command, servers, current_ip)
        command = input(">>> ")

