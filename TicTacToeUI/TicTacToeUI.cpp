#include "TicTacToeUI.h"
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QFrame>

TicTacToeUI::TicTacToeUI(QWidget *parent) : QMainWindow(parent)
{
	ui_.setupUi(this);

	ui_.frame->setFrameStyle(QFrame::StyledPanel);
	ui_.frame->setFrameShadow(QFrame::Raised);
	ui_.frame->setStyleSheet("QFrame { background-color: rgb(135, 206, 235); }");

	connect(ui_.cell00, &QPushButton::clicked, this, &TicTacToeUI::OnCell00Clicked);
	connect(ui_.cell01, &QPushButton::clicked, this, &TicTacToeUI::OnCell01Clicked);
	connect(ui_.cell02, &QPushButton::clicked, this, &TicTacToeUI::OnCell02Clicked);
	connect(ui_.cell10, &QPushButton::clicked, this, &TicTacToeUI::OnCell10Clicked);
	connect(ui_.cell11, &QPushButton::clicked, this, &TicTacToeUI::OnCell11Clicked);
	connect(ui_.cell12, &QPushButton::clicked, this, &TicTacToeUI::OnCell12Clicked);
	connect(ui_.cell20, &QPushButton::clicked, this, &TicTacToeUI::OnCell20Clicked);
	connect(ui_.cell21, &QPushButton::clicked, this, &TicTacToeUI::OnCell21Clicked);
	connect(ui_.cell22, &QPushButton::clicked, this, &TicTacToeUI::OnCell22Clicked);

	connect(ui_.p1NameLineEdit, &QLineEdit::textChanged, this, &TicTacToeUI::OnP1NameChanged);
	connect(ui_.playerRadioBtn, &QRadioButton::toggled, this, &TicTacToeUI::OnPlayerRadioToggled);
	connect(ui_.playButton, &QPushButton::clicked, this, &TicTacToeUI::OnPlayButtonClicked);
	connect(ui_.undoButton, &QPushButton::clicked, this, &TicTacToeUI::OnUndoButtonClicked);
	connect(ui_.gameResetButton, &QPushButton::clicked, this, &TicTacToeUI::OnResetButtonClicked);
}

void TicTacToeUI::OnP1NameChanged(const QString& text)
{
	const bool isNotEmpty = !text.isEmpty();

	ui_.p1SymbolCombo->setEnabled(isNotEmpty);
	ui_.botRadioBtn->setEnabled(isNotEmpty);
	ui_.playerRadioBtn->setEnabled(isNotEmpty);
	ui_.playButton->setEnabled(isNotEmpty);
}

void TicTacToeUI::OnPlayerRadioToggled(bool checked)
{
	// Enable the second player elements if playerRadioBtn is checked
	ui_.p2NameLabel->setEnabled(checked);
	ui_.p2NameLineEdit->setEnabled(checked);
	ui_.p2SymbolLabel->setEnabled(checked);
	ui_.p2SymbolCombo->setEnabled(checked);
}

void TicTacToeUI::SetGameState(const bool is_active) const
{
	// Enable or disable all the game cells
	ui_.cell00->setEnabled(is_active);
	ui_.cell01->setEnabled(is_active);
	ui_.cell02->setEnabled(is_active);
	ui_.cell10->setEnabled(is_active);
	ui_.cell11->setEnabled(is_active);
	ui_.cell12->setEnabled(is_active);
	ui_.cell20->setEnabled(is_active);
	ui_.cell21->setEnabled(is_active);
	ui_.cell22->setEnabled(is_active);

	// Enable/Disable game buttons based on state
	ui_.undoButton->setEnabled(is_active);
	ui_.gameResetButton->setEnabled(is_active);
	ui_.playButton->setEnabled(!is_active);  // Play button is disabled when the game is active
}


void TicTacToeUI::OnPlayButtonClicked()
{
	SetGameState(true);
}

void TicTacToeUI::OnUndoButtonClicked() {}

void TicTacToeUI::OnResetButtonClicked()
{
	SetGameState(false);
	ui_.p1NameLineEdit->clear();
	ui_.p1SymbolCombo->setEnabled(false);
	ui_.botRadioBtn->setChecked(true);
	ui_.botRadioBtn->setEnabled(false);
	ui_.playerRadioBtn->setChecked(false);
	ui_.playerRadioBtn->setEnabled(false);
	ui_.p2NameLineEdit->clear();
	ui_.p2NameLineEdit->setEnabled(false);
	ui_.p2SymbolCombo->setEnabled(false);
}

void TicTacToeUI::OnCell00Clicked() {}
void TicTacToeUI::OnCell01Clicked() {}
void TicTacToeUI::OnCell02Clicked() {}
void TicTacToeUI::OnCell10Clicked() {}
void TicTacToeUI::OnCell11Clicked() {}
void TicTacToeUI::OnCell12Clicked() {}
void TicTacToeUI::OnCell20Clicked() {}
void TicTacToeUI::OnCell21Clicked() {}
void TicTacToeUI::OnCell22Clicked() {}


