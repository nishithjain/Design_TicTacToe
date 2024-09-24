	#pragma once
#include <memory>
#include <vector>

#include "GameBoard.h"
#include "GameStatus.h"
#include "Move.h"
#include "Player.h"

using ListOfPlayers = std::vector<std::shared_ptr<Player>>;
class TicTacToeGame
{
	GameBoard board_;
	ListOfPlayers players_;
	std::vector<Move> moves_;
	int next_player_index_ = 0;
	GameStatus game_status_ = GameStatus::ENDED;
	Player winner_;

public:
	Player GetWinner() const;
	void SetWinner(const Player& winner);
	ListOfPlayers GetPlayers1() const;
	void SetPlayers1(const ListOfPlayers& players);
	std::vector<Move> GetMoves() const;
	void SetMoves(const std::vector<Move>& moves);
	int GetNextPlayerIndex() const;
	void SetNextPlayerIndex(int next_player_index);
	GameStatus GetGameStatus() const;
	void SetGameStatus(GameStatus game_status);

	explicit TicTacToeGame(size_t dimension, ListOfPlayers players);

	class GameBuilder
	{
		// GameBoard board_; To build the game, we just need the dimension.
		size_t dimension_ = 3;
		ListOfPlayers players_;
		// std::vector<Move> moves_; Initially no moves will be there.
		// int next_player_index_; We start with 0th index
		// GameStatus game_status_; This is also not required. 
		// Player winner_;

	public:
		size_t GetDimension() const;
		GameBuilder SetDimension(size_t dimension);
		ListOfPlayers GetPlayers() const;
		GameBuilder SetPlayers(const ListOfPlayers& players);
		std::shared_ptr<TicTacToeGame> Build() const;
		bool IsValid() const;
		bool HasDuplicatePlayerSymbols() const;
	};

	static GameBuilder GetBuilder();
};

	

