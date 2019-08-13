# The initial Sudoku board
# TODO: read this from file
board = [ 0, 0, 8, 0, 5, 0, 0, 0, 0,
          0, 0, 0, 3, 0, 0, 0, 0, 0,
          0, 0, 2, 0, 0, 0, 7, 0, 5,
          
          0, 2, 0, 6, 0, 9, 0, 3, 0,
          8, 0, 0, 0, 0, 0, 0, 0, 4,
          0, 5, 0, 4, 0, 1, 0, 7, 0,
          
          2, 0, 1, 0, 0, 0, 8, 0, 0,
          0, 0, 0, 0, 0, 3, 0, 0, 0,
          0, 0, 0, 0, 4, 0, 6, 0 ,0]

# The groups of squares on the board that must contain
# the set 1-9, with each number occurring exactly once
groups = [[0, 1, 2, 3, 4, 5, 6, 7, 8],              # Rows
          [9, 10, 11, 12, 13, 14, 15, 16, 17],
          [18, 19, 20, 21, 22, 23, 24, 25, 26],
          [27, 28, 29, 30, 31, 32, 33, 34, 35],
          [36, 37, 38, 39, 40, 41, 42, 43, 44],
          [45, 46, 47, 48, 49, 50, 51, 52, 53],
          [54, 55, 56, 57, 58, 59, 60, 61, 62],
          [63, 64, 65, 66, 67, 68, 69, 70, 71],
          [72, 73, 74, 75, 76, 77, 78, 79, 80],

          [0, 9, 18, 27, 36, 45, 54, 63, 72],       # Columns
          [1, 10, 19, 28, 37, 46, 55, 64, 73],
          [2, 11, 20, 29, 38, 47, 56, 65, 74],
          [3, 12, 21, 30, 39, 48, 57, 66, 75],
          [4, 13, 22, 31, 40, 49, 58, 67, 76],
          [5, 14, 23, 32, 41, 50, 59, 68, 77],
          [6, 15, 24, 33, 42, 51, 60, 69, 78],
          [7, 16, 25, 34, 43, 52, 61, 70, 79],
          [8, 17, 26, 35, 44, 53, 62, 71, 80],

          [0, 1, 2, 9, 10, 11, 18, 19, 20],         # 3x3 squares
          [3, 4, 5, 12, 13, 14, 21, 22, 23],
          [6, 7, 8, 15, 16, 17, 24, 25, 26],
          [27, 28, 29, 36, 37, 38, 45, 46, 47],
          [30, 31, 32, 39, 40, 41, 48, 49, 50],
          [33, 34, 35, 42, 43, 44, 51, 52, 53],
          [54, 55, 56, 63, 64, 65, 72, 73, 74],
          [57, 58, 59, 66, 67, 68, 75, 76, 77],
          [60, 61, 62, 69, 70, 71, 78, 79, 80]]


# Check if a new number, to be positioned at current_pos
# of board, is valid.
# We check, for all groups to which current_pos belongs,
# if the new number occurs on any board position within the group. 
# If it does, it cannot be placed at current_pos, and False is
# returned. Otherwise True is returned.
# TODO: It is probably faster to check, for each position
#       on the board, to which groups this position belongs.
#       This needs to be done only once, before running the
#       backtracking algorithm proper.
def is_valid_version0(board, current_pos, num):
    for group in groups:
        if current_pos in group:
            for pos in group:
                if board[pos] == num:
                    return False
    return True


# Optimized is_valid()
groups_per_pos = []
def generate_groups_per_pos():
    global groups_per_pos

    for pos in range(81):
        groups_this_pos = []
        for group in groups:
            if pos in group:
                groups_this_pos.append(group)
        groups_per_pos.append(groups_this_pos)


def is_valid_version1(board, current_pos, num):
    for group in groups_per_pos[current_pos]:
        for pos in group:
            if board[pos] == num:
                return False
    return True


# Further optimized is_valid()
# I noted that some positions are checked multiple times in the
# previous version, because rows, columns and 3x3 squares overlap.
# Also, the (known to be empty) current position itself is also
# checked (3 times!) unnecessarily.
# In this version we remove the overlap, as well as the position
# itself.
dependent_positions = [] # For each position on the board, a list of 
                         # "dependent" positions, i.e., positions that
                         # share a group with that position.
def generate_dependent_positions():
    global dependent_positions

    for pos in range(81):
        cur_dependent_positions = []
        for group in groups:
            if pos in group:
                for new_pos in group:
                    if new_pos != pos and new_pos not in cur_dependent_positions:
                        cur_dependent_positions.append(new_pos)
        dependent_positions.append(cur_dependent_positions)


def is_valid(board, current_pos, num):
    for check_pos in dependent_positions[current_pos]:
        if board[check_pos] == num:
            return False
    return True


# Prints the board. Print the numbers in each position
# of the board, with a newline after each group of 9 (i.e., each row).
def print_board(board):
    pos = 0
    for i in range(9):
        for j in range(9):
            print(board[pos], " ", end = "")
            pos += 1
        print()


# The backtracking algorithm
# Tries every number that is valid at the current position,
# then recursively calls itself with this new board.
def backtrack(board, position = 0):
    #print_board(board)
    #input()

    # Skip squares with given numbers
    while position < 80 and board[position] != 0:
        position += 1

    if position <= 80:
        for i in range(1, 10, 1):
            if not is_valid(board, position, i):
                continue
            board[position] = i
            backtrack(board, position + 1)
        board[position] = 0     # Restore original board
    else:
        print_board(board)
        print("---")


if __name__ == "__main__":
    generate_dependent_positions()
    backtrack(board)


# The algorithm generates 2942 solutions to the current puzzle.
#
# Timings were measured on my Asus Zenbook (i5 8265U @ 1.6 GHz, Python 3.7.1, battery power)
# With the naive is_valid(), it takes 1 minute 32 seconds to do so.
# With pre-generated groups for each position, it takes 29 seconds.
# With pre-generated dependent positions, it takes 23.5 seconds.
# No longer copying the board for each iteration: 22 seconds.