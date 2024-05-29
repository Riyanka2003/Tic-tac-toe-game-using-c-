#include <iostream>
#include <limits> // For numeric limits
using namespace std;

char board[3][3];
char current_marker;
int current_player;

void drawBoard() {
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}

bool placeMarker(int row, int col) {
    if (board[row][col] != ' ') return false;
    board[row][col] = current_marker;
    return true;
}

int winner() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == current_marker && board[i][1] == current_marker && board[i][2] == current_marker) return current_player;
        if (board[0][i] == current_marker && board[1][i] == current_marker && board[2][i] == current_marker) return current_player;
    }
    // Check diagonals
    if (board[0][0] == current_marker && board[1][1] == current_marker && board[2][2] == current_marker) return current_player;
    if (board[0][2] == current_marker && board[1][1] == current_marker && board[2][0] == current_marker) return current_player;
    
    return 0;
}

void swap_player_and_marker() {
    if (current_marker == 'X') current_marker = 'O';
    else current_marker = 'X';

    if (current_player == 1) current_player = 2;
    else current_player = 1;
}

void game() {
    current_marker = 'X';
    current_player = 1;

    int player_won;
    for (int i = 0; i < 9; i++) {
        drawBoard();
        int row, col;
        cout << "It's player " << current_player << "'s turn. Enter row and column (0-2): ";
        cin >> row >> col;
        
        if (cin.fail() || row < 0 || row > 2 || col < 0 || col > 2) {
            cin.clear(); // clear input buffer to restore cin to a usable state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore last input
            cout << "Invalid input! Please enter numbers between 0 and 2." << endl;
            i--;
            continue;
        }
        if (!placeMarker(row, col)) {
            cout << "Position already occupied! Try again." << endl;
            i--;
            continue;
        }
        player_won = winner();
        if (player_won != 0) {
            drawBoard();
            cout << "Player " << player_won << " wins!" << endl;
            return;
        }
        swap_player_and_marker();
    }
    drawBoard();
    cout << "It's a tie!" << endl;
}

int main() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
    game();
    return 0;
}
