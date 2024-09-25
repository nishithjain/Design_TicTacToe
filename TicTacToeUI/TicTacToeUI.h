#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TicTacToeUI.h"

class TicTacToeUI final : public QMainWindow
{
    Q_OBJECT

public:
    TicTacToeUI(QWidget *parent = nullptr);
    ~TicTacToeUI() = default;

private:
    Ui::TicTacToeUIClass ui_;

private slots:
    void OnCell00Clicked();
    void OnCell01Clicked();
    void OnCell02Clicked();
    void OnCell10Clicked();
    void OnCell11Clicked();
    void OnCell12Clicked();
    void OnCell20Clicked();
    void OnCell21Clicked();
    void OnCell22Clicked();
    void OnP1NameChanged(const QString& text);
    void OnPlayerRadioToggled(bool checked);
    void SetGameState(bool is_active) const;
    void OnPlayButtonClicked();
    void OnUndoButtonClicked();
    void OnResetButtonClicked();
};
