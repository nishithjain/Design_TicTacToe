#include "TicTacToeUI.h"
#include <QWidget>
#include <QPushButton>
#include <QFrame>

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
				cell->setText("");  // Clear the cell text when disabling
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

void TicTacToeUI::OnCell00Clicked() { OnCellClicked(0, 0); }
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

void TicTacToeUI::OnPlayButtonClicked()
{
	CaptureState();
	SetGameState(true);

	ui_.p1NameLineEdit->setEnabled(false);
	ui_.p1SymbolCombo->setEnabled(false);
	ui_.botRadioBtn->setEnabled(false);
	ui_.playerRadioBtn->setEnabled(false);
	ui_.p2NameLineEdit->setEnabled(false);
	ui_.p2SymbolCombo->setEnabled(false);

	auto [p1_name, p1_symbol] = GetPlayer1NameAndSymbol();
	auto [p2_name, p2_symbol] = GetPlayer2NameAndSymbol();

	const auto text = p1_name + ": " + p1_symbol + "\t" + p2_name + ": " + p2_symbol;

	ui_.InformationLineEdit->setText(text);
}