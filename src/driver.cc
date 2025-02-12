#include <iostream>
#include <limits>

#include "functions.hpp"

/*
  Order of two if blocks on lines 32-46 doesn't account for when the board is full but theres a winner, it only says its a tie when board is full even if there is a winner
    watchlist of board[][] variable carries a win for x ([1][2], [2][2], [3][2]) but says that its a tie, when x should be winner
    workaround => checking for winner should come before checking if board is full
*/

int main() {
  std::vector<std::vector<char>> board;
  InitializeBoard(board); //according to watch list in debug, board is always initialized correctly

  char current_player = 'X';
  int row = 0, col = 0;

  PrintBoard(board);

  while (true) {
    std::cout << "Player " << current_player
              << ", enter your move (row and column): ";

    while (!(std::cin >> row >> col)) {
      std::cin.clear();  // Clear the error state.
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                      '\n');  // Ignore invalid input.
      std::cerr << "Invalid input: Please enter integers." << std::endl;
    }

    if (MakeMove(board, row, col, current_player)) { //if player enters out of bounds index (0 or >3), that is checked here in MakeMove()
      //below two swapped to make sure it checks for winner before declaring a tie
      char winner = CheckWinner(board);
      if (winner != ' ') {
        PrintBoard(board);
        std::cout << "Player " << winner << " wins!" << std::endl;
        break;
      }
      if (IsBoardFull(board)) {
        PrintBoard(board);
        std::cout << "It's a tie!" << std::endl;
        break;
      }
      SwitchPlayer(current_player);
    }
  }

  return 0;
}