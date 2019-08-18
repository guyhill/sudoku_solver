#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int board[] = { 0, 0, 8, 0, 5, 0, 0, 0, 0,
                0, 0, 0, 3, 0, 0, 0, 0, 0,
                0, 0, 2, 0, 0, 0, 7, 0, 5,
          
                0, 2, 0, 6, 0, 9, 0, 3, 0,
                8, 0, 0, 0, 0, 0, 0, 0, 4,
                0, 5, 0, 4, 0, 1, 0, 7, 0,
          
                2, 0, 1, 0, 0, 0, 8, 0, 0,
                0, 0, 0, 0, 0, 3, 0, 0, 0,
                0, 0, 0, 0, 4, 0, 6, 0 ,0 };


// The groups of squares on the board that must contain
// the set 1-9, with each number occurring exactly once
int groups[27][9] = { {0, 1, 2, 3, 4, 5, 6, 7, 8},              // Rows
                    {9, 10, 11, 12, 13, 14, 15, 16, 17},
                    {18, 19, 20, 21, 22, 23, 24, 25, 26},
                    {27, 28, 29, 30, 31, 32, 33, 34, 35},
                    {36, 37, 38, 39, 40, 41, 42, 43, 44},
                    {45, 46, 47, 48, 49, 50, 51, 52, 53},
                    {54, 55, 56, 57, 58, 59, 60, 61, 62},
                    {63, 64, 65, 66, 67, 68, 69, 70, 71},
                    {72, 73, 74, 75, 76, 77, 78, 79, 80},

                    {0, 9, 18, 27, 36, 45, 54, 63, 72},       // Columns
                    {1, 10, 19, 28, 37, 46, 55, 64, 73},
                    {2, 11, 20, 29, 38, 47, 56, 65, 74},
                    {3, 12, 21, 30, 39, 48, 57, 66, 75},
                    {4, 13, 22, 31, 40, 49, 58, 67, 76},
                    {5, 14, 23, 32, 41, 50, 59, 68, 77},
                    {6, 15, 24, 33, 42, 51, 60, 69, 78},
                    {7, 16, 25, 34, 43, 52, 61, 70, 79},
                    {8, 17, 26, 35, 44, 53, 62, 71, 80},

                    {0, 1, 2, 9, 10, 11, 18, 19, 20},         // 3x3 squares
                    {3, 4, 5, 12, 13, 14, 21, 22, 23},
                    {6, 7, 8, 15, 16, 17, 24, 25, 26},
                    {27, 28, 29, 36, 37, 38, 45, 46, 47},
                    {30, 31, 32, 39, 40, 41, 48, 49, 50},
                    {33, 34, 35, 42, 43, 44, 51, 52, 53},
                    {54, 55, 56, 63, 64, 65, 72, 73, 74},
                    {57, 58, 59, 66, 67, 68, 75, 76, 77},
                    {60, 61, 62, 69, 70, 71, 78, 79, 80}};


#define BUFLEN 9 * 27 + 4
char output_buffer[BUFLEN];
int groups_per_pos[81][3];
unsigned int masks[27];


void fill_buffer() {
    char *s = output_buffer;

    memset(output_buffer, ' ', BUFLEN);
    for (int i=0; i<9; i++) {
        s[26] = '\n';
        s += 27;
    }
    s[0] = s[1] = s[2] = '-';
    s[3] = '\0';
}


void print_board(int board[]) {
    char *s = output_buffer;
    for (int i=0; i<81; i++) {
        *s = (char) board[i] + '0';
        s += 3;
    }
    puts(output_buffer);
}


int in(int a[], int len, int n) {

    for (int i=0; i<len; i++) {
        if (a[i] == n) {
            return 1;
        }
    }
    return 0;
}


void init_groups_per_pos(int groups[][9]) {
    for (int pos=0; pos<81; pos++) {
        int k = 0;
        for (int i=0; i<27; i++) {
            if (in(groups[i], 9, pos)) {
                groups_per_pos[pos][k++] = i;
            }
        }
    }
}


void init_masks() {
    for (int i=0; i<27; i++) {
        masks[i] = 0x3ff;
    }
    for (int pos=0; pos<81; pos++) {
        for (int j=0; j<3; j++) {
            int cur_group = groups_per_pos[pos][j];
            masks[cur_group] &= ~(1 << board[pos]);    
        }
    }
}


void backtrack(int board[], int position) {

#ifdef DEBUG
    print_board(board);
    getchar();
#endif

    while(board[position] != 0 && position <= 80) {
        position += 1;
    }

    if (position <= 80) {
        unsigned int valid_numbers;
        int group1, group2, group3;

        group1 = groups_per_pos[position][0];
        group2 = groups_per_pos[position][1];
        group3 = groups_per_pos[position][2];
        valid_numbers = masks[group1] & masks[group2] & masks[group3];
        for (int num = 1; num <= 9; num++) {
            unsigned int mask = 1 << num;
            if (valid_numbers & mask) {
                masks[group1] &= ~mask;
                masks[group2] &= ~mask;
                masks[group3] &= ~mask;
                board[position] = num;
                backtrack(board, position + 1);
                masks[group1] |= mask;
                masks[group2] |= mask;
                masks[group3] |= mask;
            }
        }
        board[position] = 0;
    } else {
        print_board(board);
    }
}


int main(int argc, char **argv) {
    init_groups_per_pos(groups);
    init_masks();
    fill_buffer();

    int n_iter;

    if (argc == 1) n_iter = 1;
    else n_iter = atoi(argv[1]);
    fprintf(stderr, "%i iterations\n", n_iter);

    for (int i=0; i<n_iter; i++) {
        backtrack(board, 0);
    }

    return 0;
}

// Produces the same output as solver.py, but much faster:
// On the same machine, it finishes in 0.14 seconds, or about 70x faster.
// This speedup is in line with speedup gained when porting other Python
// projects to C/C++.
// With non-branching code in get_valid_numbers(), 0.125 seconds
// With optimized print_board(), 0.103 seconds