#include "TicTacToeUI.h"
#include <QWidget>
#include <QPushButton>
#include <QFrame>
#include <QMessageBox>
#include <QGroupBox>
#include <Player.h>

#include "Bot.h"
#include "TicTacToeGame.h"
#include "../TicTacToe/headers/controller/GameController.h"


QPushButton* TicTacToeUI::GetCell(const int row, const int col) const
{
	QPushButton* cells[3][3] =
	{
		{ui_.cell00, ui_.cell01, ui_.cell02},
		{ui_.cell10, ui_.cell11, ui_.cell12},
		{ui_.cell20, ui_.cell21, ui_.cell22}
	};
	return cells[row][col];
}

TicTacToeUI::TicTacToeUI(QWidget* parent) : QMainWindow(parent)
{
	ui_.setupUi(this);
	OnP1SymbolChanged();

	ui_.frame->setFrameStyle(QFrame::StyledPanel);
	ui_.frame->setFrameShadow(QFrame::Raised);
	ui_.frame->setStyleSheet("QFrame { background-color: rgb(135, 206, 235); }");

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			connect(GetCell(i, j), &QPushButton::clicked, this,
				[this, i, j]() { OnCellClicked(i, j); });
		}
	}

	// Connect other UI elements
	connect(ui_.p1NameLineEdit, &QLineEdit::textChanged, this, &TicTacToeUI::OnP1NameChanged);
	connect(ui_.playerRadioBtn, &QRadioButton::toggled, this, &TicTacToeUI::OnPlayerRadioToggled);
	connect(ui_.playButton, &QPushButton::clicked, this, &TicTacToeUI::OnPlayButtonClicked);
	connect(ui_.undoButton, &QPushButton::clicked, this, &TicTacToeUI::OnUndoButtonClicked);
	connect(ui_.gameResetButton, &QPushButton::clicked, this, &TicTacToeUI::OnResetButtonClicked);
	connect(ui_.p1SymbolCombo, &QComboBox::currentTextChanged, this, &TicTacToeUI::OnP1SymbolChanged);
	connect(ui_.p2SymbolCombo, &QComboBox::currentTextChanged, this, &TicTacToeUI::OnP2SymbolChanged);

	// Initialize the UI to the starting state
	ResetUi();
}

void TicTacToeUI::OnP1SymbolChanged()
{
	const QString p1_symbol = ui_.p1SymbolCombo->currentText();

	// Re-add the previously selected symbol for Player 1 in Player 2's combo box
	if (!prev_p1_symbol_.isEmpty())
	{
		ui_.p2SymbolCombo->addItem(prev_p1_symbol_);
	}

	// Remove the newly selected symbol from Player 2's combo box
	if (const int index_to_remove = ui_.p2SymbolCombo->findText(p1_symbol); index_to_remove != -1)
	{
		ui_.p2SymbolCombo->removeItem(index_to_remove);
	}

	// Update the stored previous symbol
	prev_p1_symbol_ = p1_symbol;
}

void TicTacToeUI::OnP2SymbolChanged()
{
	const QString p2_symbol = ui_.p2SymbolCombo->currentText();

	// Re-add the previously selected symbol for Player 2 in Player 1's combo box
	if (!prev_p2_symbol_.isEmpty())
	{
		ui_.p1SymbolCombo->addItem(prev_p2_symbol_);
	}

	// Remove the newly selected symbol from Player 1's combo box
	if (const int index_to_remove = ui_.p1SymbolCombo->findText(p2_symbol); index_to_remove != -1)
	{
		ui_.p1SymbolCombo->removeItem(index_to_remove);
	}

	// Update the stored previous symbol
	prev_p2_symbol_ = p2_symbol;
}

void TicTacToeUI::OnP1NameChanged(const QString& text)
{
	const bool is_not_empty = !text.isEmpty();

	ui_.p1SymbolCombo->setEnabled(is_not_empty);
	ui_.botRadioBtn->setEnabled(is_not_empty);
	ui_.botRadioBtn->setChecked(is_not_empty);
	ui_.playerRadioBtn->setEnabled(is_not_empty);
	ui_.playButton->setEnabled(is_not_empty);
}

void TicTacToeUI::OnPlayerRadioToggled(const bool checked)
{
	// Enable the second player elements if playerRadioBtn is checked
	ui_.p2NameLabel->setEnabled(checked);
	ui_.p2NameLineEdit->setEnabled(checked);
	ui_.p2SymbolLabel->setEnabled(checked);
	ui_.p2SymbolCombo->setEnabled(checked);
}

void TicTacToeUI::SetGameState(const bool is_active) const
{
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			QPushButton* cell = GetCell(row, col);
			cell->setEnabled(is_active);
			if (!is_active)
			{
				cell->setIcon(QIcon());
			}
		}
	}

	// Enable/Disable game buttons based on state
	ui_.undoButton->setEnabled(is_active);
	ui_.gameResetButton->setEnabled(is_active);
	ui_.playButton->setEnabled(!is_active);  // Play button is disabled when the game is active
}

void TicTacToeUI::OnUndoButtonClicked() {}

void TicTacToeUI::OnResetButtonClicked()
{
	RestoreState();
	ResetUi();
}

void TicTacToeUI::ResetUi()
{
	SetGameState(false);  // Disable all the cells at the start
	ui_.InformationLineEdit->clear();
}

void TicTacToeUI::OnCellClicked(int row, int col)
{
	// Handle cell click based on row and col

	QPushButton* clicked_button = GetCell(row, col);
	if (clicked_button == nullptr)
		return;

	auto [player_name, symbol] = GetCurrentPlayerInfo();

	// Set the icon based on the player's symbol
	if (symbol == "#")
	{
		const QIcon icon(":/TicTacToeUI/Resources/hash.png");
		clicked_button->setIcon(icon);
	}
	else if (symbol == "@")
	{
		const QIcon icon(":/TicTacToeUI/Resources/at.png");
		clicked_button->setIcon(icon);
	}
	else if (symbol == "O")
	{
		const QIcon icon(":/TicTacToeUI/Resources/o.png");
		clicked_button->setIcon(icon);
	}
	else if (symbol == "X")
	{
		const QIcon icon(":/TicTacToeUI/Resources/x.png");
		clicked_button->setIcon(icon);
	}

	const int width = clicked_button->width() - 20;
	const int height = clicked_button->height() - 20;

	const QSize new_icon_size(width, height);

	clicked_button->setIconSize(new_icon_size);
	// Disable the button
	clicked_button->setEnabled(false);

	// Switch to the next player
	SwitchPlayer();
	const auto text = "Your turn [" + FormatPlayerInfo(player_info_.current_player_info) + "]";
	InformationLine(text);
}

void TicTacToeUI::CaptureState()
{
	current_state_.p1_name = ui_.p1NameLineEdit->text();
	current_state_.p1_line_enabled = ui_.p1NameLineEdit->isEnabled();
	current_state_.p1_symbol = ui_.p1SymbolCombo->currentText();
	current_state_.p1_symbol_enabled = ui_.p1SymbolCombo->isEnabled();

	current_state_.bot_selected = ui_.botRadioBtn->isChecked();
	current_state_.bot_enabled = ui_.botRadioBtn->isEnabled();
	current_state_.player_selected = ui_.playerRadioBtn->isChecked();
	current_state_.player_enabled = ui_.playerRadioBtn->isEnabled();

	current_state_.p2_name = ui_.p2NameLineEdit->text();
	current_state_.p2_line_enabled = ui_.p2NameLineEdit->isEnabled();
	current_state_.p2_symbol = ui_.p2SymbolCombo->currentText();
	current_state_.p2_symbol_enabled = ui_.p2SymbolCombo->isEnabled();
}

void TicTacToeUI::RestoreState()
{
	ui_.p1NameLineEdit->setText(current_state_.p1_name);
	ui_.p1NameLineEdit->setEnabled(current_state_.p1_line_enabled);
	ui_.p1SymbolCombo->setCurrentText(current_state_.p1_symbol);
	ui_.p1SymbolCombo->setEnabled(current_state_.p1_symbol_enabled);

	ui_.botRadioBtn->setChecked(current_state_.bot_selected);
	ui_.botRadioBtn->setEnabled(current_state_.bot_enabled);
	ui_.playerRadioBtn->setChecked(current_state_.player_selected);
	ui_.playerRadioBtn->setEnabled(current_state_.player_enabled);

	ui_.p2NameLineEdit->setText(current_state_.p2_name);
	ui_.p2NameLineEdit->setEnabled(current_state_.p2_line_enabled);
	ui_.p2SymbolCombo->setCurrentText(current_state_.p2_symbol);
	ui_.p2SymbolCombo->setEnabled(current_state_.p2_symbol_enabled);
}

void TicTacToeUI::SwitchPlayer()
{
	if (player_info_.current_player_info == player_info_.player1_info)
	{
		player_info_.current_player_info = player_info_.player2_info;
	}
	else
	{
		player_info_.current_player_info = player_info_.player1_info;
	}
}

std::tuple<QString, QString> TicTacToeUI::GetCurrentPlayerInfo() const
{
	return player_info_.current_player_info;
}

void TicTacToeUI::InitializePlayers()
{
	player_info_.player1_info = GetPlayer1NameAndSymbol();
	player_info_.player2_info = GetPlayer2NameAndSymbol();
	player_info_.current_player_info = player_info_.player1_info;
}

void TicTacToeUI::OnCell00Clicked()
{
	
}
void TicTacToeUI::OnCell01Clicked() { OnCellClicked(0, 1); }
void TicTacToeUI::OnCell02Clicked() { OnCellClicked(0, 2); }
void TicTacToeUI::OnCell10Clicked() { OnCellClicked(1, 0); }
void TicTacToeUI::OnCell11Clicked() { OnCellClicked(1, 1); }
void TicTacToeUI::OnCell12Clicked() { OnCellClicked(1, 2); }
void TicTacToeUI::OnCell20Clicked() { OnCellClicked(2, 0); }
void TicTacToeUI::OnCell21Clicked() { OnCellClicked(2, 1); }
void TicTacToeUI::OnCell22Clicked() { OnCellClicked(2, 2); }

std::tuple<QString, QString> TicTacToeUI::GetPlayer1NameAndSymbol() const
{
	// Returns the current symbol for Player 1
	return { ui_.p1NameLineEdit->text(), ui_.p1SymbolCombo->currentText() };
}

std::tuple<QString, QString> TicTacToeUI::GetPlayer2NameAndSymbol() const
{
	if (ui_.playerRadioBtn->isChecked())
	{
		// Player 2 selected
		return { ui_.p2NameLineEdit->text(), ui_.p2SymbolCombo->currentText() };
	}
	// Bot is selected, assign bot symbol
	// Get Player 1's symbol
	const QString p1_symbol = ui_.p1SymbolCombo->currentText();

	// Find a symbol for the bot that is different from Player 1's symbol
	QString bot_symbol;
	for (int i = 0; i < ui_.p2SymbolCombo->count(); ++i)
	{
		if (QString symbol = ui_.p2SymbolCombo->itemText(i); symbol != p1_symbol)
		{
			bot_symbol = symbol; // Select the first available symbol that is different
			break; // Break once a valid symbol is found
		}
	}
	// Return Bot's name and selected symbol
	return { "Bot", bot_symbol };
}

void TicTacToeUI::InformationLine(const QString& text) const
{
	ui_.InformationLineEdit->clear();


	ui_.InformationLineEdit->setText(text);
}

void TicTacToeUI::Play()
{
	constexpr int dimension = 3;

	ListOfPlayers players;

	players.push_back(std::make_shared<Player>(std::get<0>(player_info_.player1_info).toStdString(),
		std::get<1>(player_info_.player1_info).toStdString().c_str()[0], PlayerType::HUMAN));

	if (ui_.botRadioBtn->isChecked())
	{
		players.push_back(std::make_shared<Bot>("Bot", std::get<1>(player_info_.player2_info).toStdString().c_str()[0],
			BotDifficultyLevel::EASY));
	}
	else
	{
		players.push_back(std::make_shared<Player>(std::get<0>(player_info_.player2_info).toStdString(),
			std::get<1>(player_info_.player2_info).toStdString().c_str()[0], PlayerType::HUMAN));
	}

	const auto game = GameController::CreateGame(dimension, players);

	//while (GameController::GetGameStatus(game) == GameStatus::IN_PROGRESS)
	//{

	//}
}

QString TicTacToeUI::FormatPlayerInfo(const std::tuple<QString, QString>& player_info)
{
	return std::get<0>(player_info) + ": " + std::get<1>(player_info);
}

void TicTacToeUI::OnPlayButtonClicked()
{
	InitializePlayers();

	if (std::get<0>(player_info_.player2_info).isEmpty())
	{
		QMessageBox::warning(this, "Invalid Input",
			"Please enter a valid name for player 2.");
		return;
	}

	if (std::get<0>(player_info_.player2_info).toLower() == "bot")
	{
		QMessageBox::warning(this, "Invalid Input",
			"Player 2 name cannot be Bot!");
		return;
	}

	CaptureState();
	SetGameState(true);

	ui_.p1NameLineEdit->setEnabled(false);
	ui_.p1SymbolCombo->setEnabled(false);
	ui_.botRadioBtn->setEnabled(false);
	ui_.playerRadioBtn->setEnabled(false);
	ui_.p2NameLineEdit->setEnabled(false);
	ui_.p2SymbolCombo->setEnabled(false);


	const auto text = "Your turn [" + FormatPlayerInfo(player_info_.current_player_info) + "]";
	InformationLine(text);
	Play();
}