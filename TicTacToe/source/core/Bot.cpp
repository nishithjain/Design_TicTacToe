#include "Bot.h"

Bot::Bot(const std::string& name, const char symbol,
	const BotDifficultyLevel bot_difficulty_level)
	: Player(name, symbol, PlayerType::BOT),
	bot_difficulty_level_(bot_difficulty_level)
{
	
}

BotDifficultyLevel Bot::GetBotDifficultyLevel() const
{
	return bot_difficulty_level_;
}

void Bot::SetBotDifficultyLevel(const BotDifficultyLevel bot_difficulty_level)
{
	bot_difficulty_level_ = bot_difficulty_level;
}
