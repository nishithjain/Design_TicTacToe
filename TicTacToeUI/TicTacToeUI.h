#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TicTacToeUI.h"

class TicTacToeUI : public QMainWindow
{
    Q_OBJECT

public:
    TicTacToeUI(QWidget *parent = nullptr);
    ~TicTacToeUI();

private:
    Ui::TicTacToeUIClass ui;

private slots:
    void onCellClicked();  // Slot for handling button clicks
};
