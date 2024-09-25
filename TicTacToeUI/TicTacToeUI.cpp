#include "TicTacToeUI.h"
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QFrame>

TicTacToeUI::TicTacToeUI(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	ui.frame->setFrameStyle(QFrame::StyledPanel);
	ui.frame->setFrameShadow(QFrame::Raised);
	ui.frame->setStyleSheet("QFrame { background-color: rgb(135, 206, 235); }");
}

TicTacToeUI::~TicTacToeUI()
{}

void TicTacToeUI::onCellClicked()
{
}
