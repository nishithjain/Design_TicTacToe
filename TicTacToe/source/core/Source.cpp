#include <vector>
#include <string>

#include "Bot.h"
#include "Player.h"
#include "TicTacToeGame.h"
using namespace std;

int main()
{
	constexpr int dimension = 3;

	ListOfPlayers players;
	players.push_back(make_shared<Player>("Nishith", '0', PlayerType::HUMAN));
	players.push_back(make_shared<Bot>("Bot", 'X', BotDifficultyLevel::EASY));

	auto game = TicTacToeGame::GetBuilder()
		.SetDimension(dimension)
		.SetPlayers(players)
		.Build();

	while(game->GetGameStatus() == GameStatus::IN_PROGRESS)
	{
		
	}

	if(game->GetGameStatus() == GameStatus::DRAW)
	{
		
	}
	else if(game->GetGameStatus() == GameStatus::ENDED)
	{
		// game->GetWinner();
	}

	return 0;
}