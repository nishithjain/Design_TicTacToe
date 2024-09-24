#pragma once
#include "BotDifficultyLevel.h"
#include "Player.h"

class Bot final : public Player
{
	BotDifficultyLevel bot_difficulty_level_ = BotDifficultyLevel::EASY;

public:
	Bot(const std::string& name, char symbol,
		BotDifficultyLevel bot_difficulty_level);

	BotDifficultyLevel GetBotDifficultyLevel() const;
	void SetBotDifficultyLevel(BotDifficultyLevel bot_difficulty_level);
};

