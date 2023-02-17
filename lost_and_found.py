
"""
File:    lost_and_found.py
Author:  Ebun Oyemade
Date:    11/16/2021
Section: 12
E-mail:  eoyemad1@umbc.edu
Description:
  Plays game where you need to get to the exit by finding ways around wall, secrets, and keys to open doors

"""

import json


USE = 'e'
EMPTY = ''
FLOOR = '_'
EXIT = 'x'
DOOR = 'd'
SECRET = 's'
WALL = '*'
ITEMS = 'i'
STARTING_LOCATION = 'start'
PLAYER = '\u1330'
QUIT = 'q'
UP = 'w'
LEFT = 'a'
ITEM = 'items'
SYMBOL = 'symbol'
REQUIRES = 'requires'
REVEALED_DOOR = 'D'

def load_map(map_file_name):
    """
        When a map file name is passed the file will load the grid and return it.
        Should you modify this function? No you shouldn't.

    :param map_file_name: a string representing the file name.
    :return: a 2D list which contains the current map.
    """
    with open(map_file_name) as map_file:
        the_map = json.loads(map_file.read())

    return the_map

def display_map(the_map, location):
    # this function checks each item under symbol dictionary in the game map and prints the appropriate character
    pos_x,pos_y = location
    for i in range(len(the_map)):
        print(i ,end = "   ")
        for j in range (len(the_map[i])):
            if the_map[i][j][SYMBOL] != SECRET:
                if i == pos_x and j == pos_y:
                    print(PLAYER, end = EMPTY)
            
                elif len( the_map[i][j][ITEM]) > 0 :
                    print(ITEMS, end = EMPTY)
                    
                else:
                    print(the_map[i][j][SYMBOL], end = EMPTY)
     
            else:
                print(WALL, end = EMPTY)
                
        print(EMPTY)

    return

def set_start(the_map):
    # looks if " start: 'true'" is in the game map and prints player at that point or [0][0] if "start: 'true'" is not in the map 
    location = [0,0]
    for i in range(len(the_map)):
        for j in range(len(the_map[i])):
            if STARTING_LOCATION in the_map[i][j]:
                location[0] = i
                location[1] = j
    pos_x,pos_y = location
    display_map(the_map, location)
    return location

def make_move(the_map, location, command, inventory):
    # checks to see what key was pressed and does the appropriate command
    pos_x,pos_y = location

    # checks to see if the command takes the player off the map
    if command == UP and pos_x > 0:
        if the_map[pos_x - 1][pos_y][SYMBOL] == FLOOR or the_map[pos_x - 1][pos_y][SYMBOL] == EXIT:
            pos_x -= 1
            location[0] = pos_x
            inventory = add_items(pos_x, pos_y, the_map, inventory)
            
        if the_map[pos_x][pos_y][SYMBOL] == EXIT:
            # returns QUIT to exit the while loop in play game 
            command = QUIT
            return location,command,inventory
        
    elif command == SECRET and pos_x + 1 < len(the_map):
        if the_map[pos_x + 1][pos_y][SYMBOL] == FLOOR or the_map[pos_x + 1][pos_y][SYMBOL] == EXIT:
            pos_x += 1
            location[0] = pos_x
            inventory = add_items(pos_x, pos_y, the_map, inventory)
            
        if the_map[pos_x][pos_y][SYMBOL] == EXIT:
            
            command = QUIT
            return location,command,inventory
        
    elif command == LEFT and pos_y - 1 >= 0:
        if the_map[pos_x][pos_y - 1][SYMBOL] == FLOOR or the_map[pos_x][pos_y - 1][SYMBOL] == EXIT:
            pos_y -= 1
            location[1] = pos_y
            inventory = add_items(pos_x, pos_y, the_map, inventory)
            
        if the_map[pos_x][pos_y][SYMBOL] == EXIT:
            command = QUIT
            return location,command,inventory
    elif command == DOOR and pos_y + 1 < len(the_map[pos_x]):
        if the_map[pos_x][pos_y + 1][SYMBOL] == FLOOR or the_map[pos_x][pos_y + 1][SYMBOL] == EXIT:
            pos_y += 1
            location[1] = pos_y
            inventory = add_items(pos_x, pos_y, the_map, inventory)
        if the_map[pos_x][pos_y][SYMBOL] == EXIT: 
            command = QUIT
            return location,command,inventory
    elif command == USE:
        search(the_map, pos_x, pos_y, inventory)
        
    display_map(the_map,location)
    print("Your inventory is:", " ".join(inventory))
    return location,command,inventory


def search(the_map, pos_x, pos_y, inventory):
    # this function controls the functionality of e
    # checks each space around the player doors and secrets 
    for i in range(-1,2):
        for j in range(-1,2):
            if pos_x + i < len(the_map) and pos_y + j < len(the_map[0]):
                # next code checks the required items for the door and sees if they are the players inventory
                if REQUIRES in the_map[pos_x + i][pos_y + j]:
                    for x in the_map[pos_x + i][pos_y + j][REQUIRES]:
            
                        if x in inventory:
                            if the_map[pos_x + i][pos_y + j][SYMBOL].lower() == DOOR:
                                the_map[pos_x + i][pos_y + j][SYMBOL] = FLOOR
                        else:
                            print("You still require:", x)
                else:
                    if the_map[pos_x + i][pos_y + j][SYMBOL].lower() == DOOR:
                        the_map[pos_x + i][pos_y + j][SYMBOL] = FLOOR
                        
                if the_map[pos_x + i][pos_y + j][SYMBOL] == SECRET:
                    the_map[pos_x + i][pos_y + j][SYMBOL] = REVEALED_DOOR
                    print("You found a secret!")
    return

def add_items(pos_x, pos_y, the_map, inventory):
    # checks current location for item and if there is an item the item to inventory and removes from the game map 
    
    if len(the_map[pos_x][pos_y][ITEM]) > 0:    
        for x in the_map[pos_x][pos_y][ITEM]:
            inventory.append(x)
            the_map[pos_x][pos_y][ITEM].remove(x)
            
    return inventory
                     
        

def play_game(the_map):
    inventory = []
    location = set_start(the_map)
    pos_x,pos_y = location
    inventory = add_items(pos_x,pos_y, the_map, inventory)
    
    print("Your inventory is", " ".join(inventory))
    move_command = input("Enter Move (wasd) (e to activate doors or secrets, q to exit the game):")
    location,move_command,inventory = make_move(the_map,location, move_command, inventory)

    # loops game until move_command = 'q'
    while move_command != QUIT:
         move_command = input("Enter Move (wasd) (e to activate doors or secrets, q to exit the game):")
         location,move_command,inventory = make_move(the_map,location, move_command,inventory)
         pos_x,pos_y = location
         
    # if statements determines the result of the game based on the players final location  
    if the_map[pos_x][pos_y][SYMBOL] != EXIT:
        print("You died!")
    else: 
        print("You won!")

        
    
if __name__ == '__main__':
    #checks for maps
    map_file_name = input('What map do you want to load? ')
    the_game_map = load_map(map_file_name)
    
    if the_game_map:
        play_game(the_game_map)
        # call your function now with the_game_map as a parameter.
    
    
