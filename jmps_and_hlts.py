"""
File:    jmps_and_hlts.py
Author:  Ebun Oyemade
Date:    10/27/2021
Section: 12
E-mail:  eoyemad1@umbc.edu
Description:
  prints the board and plays the game of 'jmps and hlts' and records the events of each turn
"""

import random

GRID_WIDTH = 8
GRID_HEIGHT = 3
DICE_SIDES = 6
STOP = 'no'

def generate_random_map(length, the_seed=0):
    """
        :param length - the length of the map
        :param the_seed - the seed of the map
        :return: a randomly generated map based on a specific seed, and length.
    """
    if the_seed:
        random.seed(the_seed)
    map_list = []
    for _ in range(length - 2):
        random_points = random.randint(1, 100)
        random_position = random.randint(0, length - 1)
        map_list.append(random.choices(
            ['nop', f'add {random_points}', f'sub {random_points}', f'mul {random_points}', f'jmp {random_position}',
             'hlt'], weights=[5, 2, 2, 2, 3, 1], k=1)[0])

    return ['nop'] + map_list + ['hlt']


def make_grid(table_size):
    """
    :param table_size: this needs to be the length of the map
    :return: returns a display grid that you can then modify with fill_grid_square (it's a 2d-grid of characters)
    """
    floating_square_root = table_size ** (1 / 2)
    int_square_root = int(floating_square_root) + (1 if floating_square_root % 1 else 0)
    table_height = int_square_root
    if int_square_root * (int_square_root - 1) >= table_size:
        table_height -= 1

    the_display_grid = [[' ' if j % GRID_WIDTH else '*' for j in range(GRID_WIDTH * int_square_root + 1)]
                        if i % GRID_HEIGHT else ['*' for j in range(GRID_WIDTH * int_square_root + 1)]
                        for i in range(table_height * GRID_HEIGHT + 1)]

    return the_display_grid


def fill_grid_square(display_grid, size, index, message):
    """
    :param display_grid:  the grid that was made from make_grid
    :param size:  this needs to be the length of the total map, otherwise you may not be able to place things correctly.
    :param index: the index of the position where you want to display the message
    :param message: the message to display in the square at position index, separated by line returns.
    """
    floating_square_root = size ** (1 / 2)
    int_square_root = int(floating_square_root) + (1 if floating_square_root % 1 else 0)
    table_row = index // int_square_root
    table_col = index % int_square_root

    if table_row % 2 == 0:
        column_start = GRID_WIDTH * table_col

    else:
        column_start = GRID_WIDTH * (int_square_root - (table_col + 1))

    for r, message_line in enumerate(message.split('\n')):
        for k, c in enumerate(message_line):
            display_grid[GRID_HEIGHT * table_row + 1 + r][column_start + 1 + k] = c


def roll_dice():
    """
        Call this function once per turn.

        :return: returns the dice roll
    """
    return random.randint(1, DICE_SIDES)


def make_message(game_map, length):
    # makes a list that contains message for all the board spaces
    num_list = []
    message = []
    # makes a numbered list starting at 0 for each board space
    for i in range(0, length):
        add = str(i)
        num_list.append(add)
    # combines map_list commands and list of number the range from 0 - (length-1)
    for i in range(0, length):
        add = num_list[i] + '\n' + game_map[i]
        message.append(add)

    return message


def score_calc(action, score, num):
    # calculates score based on the command of the landed space
    if action == 'add':
        score += num
    elif action == 'sub':
        score -= num
    else:
        score *= num

    return score

def play_game(game_map):
    # plays the games and prints results of each turn
    # the board position, score, command of the space and dice roll
    space = game_map[0]
    space = " ".join(space)
    info = space.split(" ")
    action = space[0]
    location = 0
    score = 0

    while action != 'hlt':
        roll = roll_dice()
        location += roll
        # if statement starts user at the beginning if they go further then length of the board
        if location > len(game_map) - 1:
            location %= (len(game_map))
        # used to obtain command while without numerical value and store it a variable
        # for the if statement
        space = game_map[location]
        space = "".join(space)
        info = space.split(" ")
        action = info[0]

        if action != 'nop' and action != 'jmp' and action != 'hlt':
            print("Pos:", location, "Score:", score, "instruction", space, "Rolled:", roll)
            num = int(info[1])
            score = score_calc(action, score, num)

        elif action == 'jmp':
            # does the jump command
            print("Pos:", location, "Score:", score, "instruction", space, "Rolled:", roll)
            num = int(info[1])
            location = num
            space = game_map[location]
            space = "".join(space)
            info = space.split(" ")
            action = info[0]
            # activates command of the new space
            if action != 'nop' and action != 'jmp' and action != 'hlt':
                num = int(info[1])
                score = score_calc(action, score, num)
                print("Pos:", location, "Score:", score, "instruction", space, "Rolled:", roll)

            else:
                print("Pos:", location, "Score:", score, "instruction", space, "Rolled:", roll)

        else:
            print("Pos:", location, "Score:", score, "instruction", space, "Rolled:", roll)

    print("Final Pos:", location, "Final Score:", score, "Instruction hlt")
def display_board(settings):
    # displays the board with the commands on the spaces
    length = int(settings[0])
    seed = int(settings[1])
    game_map = generate_random_map(length, seed)
    the_grid = make_grid(length)
    message = make_message(game_map, length)
    # adds the board messages to the board
    for i in range(0, len(message)):
        fill_grid_square(the_grid, length, i, message[i])
    #prints the board
    for i in range(len(the_grid)):
        print(''.join(the_grid[i]))

    return game_map
if __name__ == '__main__':
    settings = input("Board Size and Seed: ").split()
    game_map = display_board(settings)
    play_game(game_map)
    repeat = input("continue? ")
    # Keeps looping the game until user says 'no' to continuing
    while repeat.lower() != STOP:
        settings = input("Board Size and Seed: ").split()
        game_map = display_board(settings)
        play_game(game_map)
        repeat = input("continue? ")

    pass


