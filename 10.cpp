#include <iostream>
#include <vector>
using namespace std;

class NQueens {
public:
    // Function to check if a queen can be placed at the board[i][col]
    bool isSafe(const vector<vector<int>>& board, int row, int col, int N) {
        // Check this column on the upper side
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 1) {
                return false; // Same column
            }
        }

        // Check upper diagonal on left side
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 1) {
                return false; // Upper left diagonal
            }
        }

        // Check upper diagonal on right side
        for (int i = row, j = col; i >= 0 && j < N; i--, j++) {
            if (board[i][j] == 1) {
                return false; // Upper right diagonal
            }
        }

        return true; // No clashes
    }

    // Function to solve the N-Queens problem using backtracking
    bool solveNQueens(vector<vector<int>>& board, int row, int N) {
        // If all queens are placed, return true
        if (row == N) {
            return true;
        }

        // Try placing the queen in all columns one by one
        for (int col = 0; col < N; col++) {
            if (isSafe(board, row, col, N)) {
                // Place the queen
                board[row][col] = 1;

                // Recur to place the rest of the queens
                if (solveNQueens(board, row + 1, N)) {
                    return true;
                }

                // If placing queen in board[row][col] doesn't lead to a solution
                board[row][col] = 0; // Backtrack
            }
        }

        return false; // No place is found for this row
    }

    // Function to print the solution
    void printSolution(const vector<vector<int>>& board, int N) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << (board[i][j] == 1 ? "Q " : ". ");
            }
            cout << endl;
        }
    }

    // Function to initiate the N-Queens problem solution
    void solve(int N) {
        vector<vector<int>> board(N, vector<int>(N, 0)); // Initialize the board

        if (solveNQueens(board, 0, N)) {
            printSolution(board, N); // If solution exists, print the board
        } else {
            cout << "Solution does not exist." << endl;
        }
    }
};

int main() {
    NQueens nq;
    int N, choice;

    while (true) {
        // Menu driven interface
        cout << "\n--- N-Queens Problem Menu ---\n";
        cout << "1. Solve N-Queens\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the value of N (number of queens): ";
                cin >> N;
                nq.solve(N);
                break;

            case 2:
                cout << "Exiting program...\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

