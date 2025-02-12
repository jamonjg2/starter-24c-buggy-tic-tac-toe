#include "functions.hpp"

#include <iostream>

void PrintBoard(const std::vector<std::vector<char>>& board) {
  for (unsigned int i = 0; i < kBoardSize; ++i) {
    for (unsigned int j = 0; j < kBoardSize; ++j) {
      std::cout << board[i][j] << ' ';
    }
    std::cout << '\n';
  }
}

void InitializeBoard(std::vector<std::vector<char>>& board) {
  board.clear();
  for (unsigned int i = 0; i < kBoardSize; ++i) {
    board.push_back(std::vector<char>(kBoardSize, ' '));
  }
}

bool MakeMove(std::vector<std::vector<char>>& board,
              int row,
              int col,
              char player) {
  if (row <= 0 || row > kBoardSize || col <= 0 || col > kBoardSize) { //player input begins at 1 and ends at 3, while vector indexes begin at 0 and end at 2
    std::cerr << "Error: Move out of bounds!\n";
    return false;
  }
  if (board[row-1][col-1] != ' ') { //row should be accessed first not col => watchlist with board variable wasn't getting filled row first column second
    std::cerr << "Error: Cell already occupied!\n";
    return false;
  }
  board[row-1][col-1] = player; //row first then column, and decrease index by 1 to account for user (they input 1-3 not 0-2)
  return true;
}

char CheckWinner(const std::vector<std::vector<char>>& board) {
  for (unsigned int i = 0; i < kBoardSize; ++i) {
    if (board[i][0] == board[i][1] && board[i][1] == board[i][2] &&
        board[i][0] != ' ') {
      return board[i][0]; //returns false info => should be board[i][0] (found through board watchlist after winning 2nd column as X, says 0 won)
    }
  }

  for (unsigned int i = 0; i < kBoardSize; ++i) {
    if (board[0][i] == board[1][i] && board[1][i] == board[2][i] &&
        board[0][i] != ' ') {
      return board[0][i];
    }
  }
  /*
  board watchlist says theres diaganol but doesn't check
  below only checks for one diagonal (left to right) when we also need to check for other diagonal (right to left)
  */
  if (board[0][2] == board[1][1] && board[1][1] == board[2][0] &&
      board[0][2] != ' ') {
    return board[0][2]; //should return board[0][2] not board[0][0] => x's won diagonally but returned that o's won
  }
  if (board[0][0] == board[1][1] && board[1][1] == board[2][2] &&
      board[0][0] != ' ') { //checking for right to left diagonal that was not accounted for originally
        return board[0][0];
      }
  return ' ';
}

bool IsBoardFull(const std::vector<std::vector<char>>& board) {
  for (unsigned int i = 0; i < kBoardSize; ++i) {
    for (unsigned int j = 0; j < kBoardSize; ++j) {
      if (board[i][j] == ' ') {
        return false;
      }
    }
  }
  return true;
}

void SwitchPlayer(char& player) { player = (player == 'X') ? 'O' : 'X'; }