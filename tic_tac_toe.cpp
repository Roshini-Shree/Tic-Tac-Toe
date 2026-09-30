#include <iostream>
#include <limits>

using namespace std;

const int SIZE = 3;

// Clears bad input from the buffer so the program doesn't get stuck
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Fills the 3x3 board with placeholder numbers 1-9 so players
// know which number corresponds to which cell
void initializeBoard(char board[SIZE][SIZE]) {
    char cellNumber = '1';
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            board[row][col] = cellNumber++;
        }
    }
}

// Prints the board in a readable ASCII grid
void displayBoard(char board[SIZE][SIZE]) {
    cout << "\n";
    for (int row = 0; row < SIZE; row++) {
        cout << " ";
        for (int col = 0; col < SIZE; col++) {
            cout << board[row][col];
            if (col < SIZE - 1) cout << " | ";
        }
        cout << "\n";
        if (row < SIZE - 1) cout << "---+---+---\n";
    }
    cout << "\n";
}

// Converts a 1-9 cell choice into row/col coordinates
bool getCoordinates(int choice, int& row, int& col) {
    if (choice < 1 || choice > 9) return false;
    choice--; // shift to 0-based index
    row = choice / SIZE;
    col = choice % SIZE;
    return true;
}

// Checks all rows, columns, and both diagonals for a win
bool checkWin(char board[SIZE][SIZE], char player) {
    // Rows and columns
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true; // row win
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true; // column win
    }
    // Diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;

    return false;
}

// Board is full when no cell still holds its original number (1-9)
bool isBoardFull(char board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            char c = board[row][col];
            if (c >= '1' && c <= '9') return false; // empty cell found
        }
    }
    return true;
}

int main() {
    char board[SIZE][SIZE];
    char currentPlayer = 'X';
    bool gameWon = false;
    bool boardFull = false;

    cout << "===== Tic-Tac-Toe (2 Player) =====\n";
    cout << "Players take turns entering a number 1-9 matching the board position.\n";

    initializeBoard(board);
    displayBoard(board);

    while (!gameWon && !boardFull) {
        int choice, row, col;

        cout << "Player " << currentPlayer << ", enter your move (1-9): ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input! Please enter a number.\n";
            clearInputBuffer();
            continue;
        }

        if (!getCoordinates(choice, row, col)) {
            cout << "Invalid move! Choose a number between 1 and 9.\n";
            continue;
        }

        // Cell already taken if it no longer holds a digit 1-9
        char cell = board[row][col];
        if (cell == 'X' || cell == 'O') {
            cout << "That cell is already taken! Choose another.\n";
            continue;
        }

        board[row][col] = currentPlayer;
        displayBoard(board);

        if (checkWin(board, currentPlayer)) {
            cout << "Player " << currentPlayer << " wins! Congratulations!\n";
            gameWon = true;
        } else if (isBoardFull(board)) {
            cout << "It's a draw! The board is full.\n";
            boardFull = true;
        } else {
            // Switch turns
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }

    cout << "Game over. Thanks for playing!\n";
    return 0;
}
