#include "GameBoard.h"


GameBoard::GameBoard(const size_t dimension) : dimension_(dimension)
{
	// Resize the board to dimension x dimension
	board_.resize(dimension_);

	for (size_t row = 0; row < dimension_; ++row)
	{
		board_[row].resize(dimension_);

		for (size_t col = 0; col < dimension_; ++col)
		{
			// Initialize each cell with the correct row, col, and an empty player
			board_[row][col] = Cell(CellState::EMPTY, row, col,
				               Player("", '\0', PlayerType::HUMAN));
		}
	}
}

std::vector<std::vector<Cell>> GameBoard::GetBoard() const
{
	return board_;
}

void GameBoard::SetBoard(const std::vector<std::vector<Cell>>& board)
{
	board_ = board;
}

size_t GameBoard::GetDimension() const
{
	return dimension_;
}

void GameBoard::SetDimension(const size_t dimension)
{
	dimension_ = dimension;
}
