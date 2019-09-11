#include <stdint.h>
#include <cstring>
#include <string>
#include <fstream>

#include "vcl/vectorclass.h"

using namespace std;


#define NBOARDS 16

int16_t boards[81 * NBOARDS];
int16_t masks[27 * NBOARDS];


bool read_puzzle(int i, fstream &file) {

    for (int j=0; j<81; j++) {
        if (file.eof()) {
            return false;
        }
        file >> boards[j * 16 + i];
    }
    return true;
}


Vec16sb read_puzzles(string filename) {

    fstream file(filename);
    Vec16sb isBoardValid(true);
    int nvalid = 0;

    for (int i=0; i<16; i++) {
        if (read_puzzle(i, file)) {
            nvalid += 1;
        }
    }
    file.close();

    isBoardValid.cutoff(nvalid);
    return isBoardValid;
}


#define BUFLEN 9 * 27 + 4
char output_buffer[BUFLEN];

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


void print_board(int board_num) {
    char *s = output_buffer;
    char board_char;
    for (int i=0; i<81; i++) {
        *s = (char) boards[i * 16 + board_num] + '0';
        s += 3;
    }
    if (board_num < 10) {
        board_char = board_num + '0';
    } else {
        board_char = board_num + 'A' - 10;
    }
    s[1] = board_char;
    puts(output_buffer);
}


int main() {
    fill_buffer();

    Vec16sb isBoardValid = read_puzzles("puzzles8.txt");
    for (int i=0; i<16; i++) {
        if (isBoardValid[i]) {
            print_board(i);
        }
    }
}