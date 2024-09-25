#include "TicTacToeUI.h"
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QFrame>

TicTacToeUI::TicTacToeUI(QWidget *parent)
    : QMainWindow(parent)
{
    // Call setupUi first to set up the UI designed in Qt Designer
    ui.setupUi(this);

    // Get the central widget set up by setupUi
    QWidget* centralWidget = this->centralWidget();

    // Create a grid layout and set it on the central widget
    QGridLayout* gridLayout = new QGridLayout(centralWidget);

    // Loop to create 9 QPushButton cells and add them to the grid
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            QPushButton* cellButton = new QPushButton("Hello");
            cellButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // Ensure buttons expand
            gridLayout->addWidget(cellButton, i * 2, j * 2);  // Place button in the grid

            // Connect each button to the onCellClicked function
            connect(cellButton, &QPushButton::clicked, this, &TicTacToeUI::onCellClicked);

            // Add vertical line frames
            if (j < 2) {  // Don't add a vertical line after the last column
                QFrame* verticalLine = new QFrame();
                verticalLine->setFrameShape(QFrame::VLine);
                verticalLine->setLineWidth(2);  // Adjust line width
                gridLayout->addWidget(verticalLine, i * 2, j * 2 + 1);  // Place vertical line after the button
            }
        }

        // Add horizontal line frames
        if (i < 2) {  // Don't add a horizontal line after the last row
            QFrame* horizontalLine = new QFrame();
            horizontalLine->setFrameShape(QFrame::HLine);
            horizontalLine->setLineWidth(2);  // Adjust line width
            gridLayout->addWidget(horizontalLine, i * 2 + 1, 0, 1, 5);  // Span the entire row
        }
    }
}

TicTacToeUI::~TicTacToeUI()
{}

void TicTacToeUI::onCellClicked()
{
}
