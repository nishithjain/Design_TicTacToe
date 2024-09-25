#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TicTacToeUI.h"
#include <tuple>

class TicTacToeUI final : public QMainWindow
{
    Q_OBJECT

public:
    QPushButton* GetCell(int row, int col) const;
    TicTacToeUI(QWidget *parent = nullptr);
    void OnP1SymbolChanged();
    void OnP2SymbolChanged();
    ~TicTacToeUI() override = default;

private:
    Ui::TicTacToeUIClass ui_;
    QString prev_p1_symbol_;
    QString prev_p2_symbol_;

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
    std::tuple<QString, QString> GetPlayer1NameAndSymbol() const;
    std::tuple<QString, QString> GetPlayer2NameAndSymbol() const;
    void OnP1NameChanged(const QString& text);
    void OnPlayerRadioToggled(bool checked);
    void SetGameState(bool is_active) const;
    void OnPlayButtonClicked();
    void OnUndoButtonClicked();
    void OnResetButtonClicked();
    void ResetUi();
    void OnCellClicked(int row, int col);
};
