#include "TicTacToeGame.h"

#include <iostream>
#include <set>
#include <stdexcept>

#include "BoardDimensionException.h"
#include "DuplicatePlayerSymbolException.h"
#include "PlayerCountException.h"

Player TicTacToeGame::GetWinner() const
{
	return winner_;
}

void TicTacToeGame::SetWinner(const Player& winner)
{
	winner_ = winner;
}

ListOfPlayers TicTacToeGame::GetPlayers1() const
{
	return players_;
}

void TicTacToeGame::SetPlayers1(const ListOfPlayers& players)
{
	players_ = players;
}

std::vector<Move> TicTacToeGame::GetMoves() const
{
	return moves_;
}

void TicTacToeGame::SetMoves(const std::vector<Move>& moves)
{
	moves_ = moves;
}

int TicTacToeGame::GetNextPlayerIndex() const
{
	return next_player_index_;
}

void TicTacToeGame::SetNextPlayerIndex(const int next_player_index)
{
	next_player_index_ = next_player_index;
}

GameStatus TicTacToeGame::GetGameStatus() const
{
	return game_status_;
}

void TicTacToeGame::SetGameStatus(const GameStatus game_status)
{
	game_status_ = game_status;
}

TicTacToeGame::TicTacToeGame(const size_t dimension, ListOfPlayers players) :
	board_(dimension), players_(std::move(players))
{

}

 size_t TicTacToeGame::GameBuilder::GetDimension() const
{
	return dimension_;
}

 TicTacToeGame::GameBuilder TicTacToeGame::GameBuilder::SetDimension(const size_t dimension)
{
	dimension_ = dimension;
	return *this;
}

 ListOfPlayers TicTacToeGame::GameBuilder::GetPlayers() const
{
	return players_;
}

 TicTacToeGame::GameBuilder TicTacToeGame::GameBuilder::SetPlayers(const ListOfPlayers& players)
{
	players_ = players;
	return *this;
}

bool TicTacToeGame::GameBuilder::HasDuplicatePlayerSymbols() const
{
	std::set<char> symbols;

	for (const auto& player : players_)
	{
		char symbol = player->GetSymbol();
		if (symbol != '\0') // Ignore uninitialized players
		{
			if (symbols.find(symbol) != symbols.end())
			{
				return true; // Duplicate symbol found
			}
			symbols.insert(symbol);  // Add symbol to the set
		}
	}

	return false; // No duplicates
}

TicTacToeGame::GameBuilder TicTacToeGame::GetBuilder()
{
	static GameBuilder gameBuilder;
	return gameBuilder;
}

bool TicTacToeGame::GameBuilder::IsValid() const
{
	if (players_.size() != dimension_ - 1)
		throw PlayerCountException("Number of players should be " +
			std::to_string(dimension_ - 1));
	if (dimension_ < 3)
		throw BoardDimensionException("Size of the board cannot be less than 3");
	if (HasDuplicatePlayerSymbols())
		throw DuplicatePlayerSymbolException("2 or more players has same symbol");

	return true;
}

std::shared_ptr<TicTacToeGame> TicTacToeGame::GameBuilder::Build() const
{
	try
	{
		if (IsValid())
		{
			auto game = std::make_shared<TicTacToeGame>(dimension_, players_);
			game->game_status_ = GameStatus::IN_PROGRESS;
			game->next_player_index_ = 0;
			return game;
		}
	}
	catch (BoardDimensionException& e)
	{
		std::cout << e.what();
		return nullptr;
	}
	catch (PlayerCountException& e)
	{
		std::cout << e.what();
		return nullptr;
	}
	catch (DuplicatePlayerSymbolException& e)
	{
		std::cout << e.what();
		return nullptr;
	}
	return nullptr;
}