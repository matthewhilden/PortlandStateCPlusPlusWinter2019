#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "board.h"

const int BOARD_WIDTH_PIXELS = 300;
const int BOARD_HEIGHT_PIXELS = 600;
const int cellWidth = BOARD_WIDTH_PIXELS / BOARD_WIDTH;
const int cellHeight = BOARD_HEIGHT_PIXELS / BOARD_HEIGHT;

const int BOARD_HEIGHT_OFFSET = 100;
const int BOARD_WIDTH_OFFSET = 225;
const int NEXT_PIECE_HEIGHT_OFFSET = 205;
const int NEXT_PIECE_WIDTH_OFFSET = 530;

const int DEFAULT_DROP_SPEED = 1000;
const double SPEED_LEVEL_MULTIPLIER = 0.8;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _dropSpeed = DEFAULT_DROP_SPEED;
    _timer = new QTimer(this);
    _pauseTimer = new QTimer(this);

    connect(_timer, SIGNAL(timeout()), this, SLOT(drop_piece()));
    connect(_pauseTimer, SIGNAL(timeout()), this, SLOT(finish_timer()));

    _timer->start(_dropSpeed);

    _pauseLabel = new QLabel(this);
    _pauseLabel->setGeometry(QRect(BOARD_WIDTH_OFFSET + BOARD_WIDTH_PIXELS / 2 - 35,
                                   BOARD_HEIGHT_OFFSET + BOARD_HEIGHT_PIXELS / 2, 100, 20));
    QFont labelFont;
    labelFont.setPointSize(15);
    _pauseLabel->setFont(labelFont);
    _pauseLabel->setText("PAUSED");
    _pauseLabel->setVisible(false);

    _scoreLabel = new QLabel(this);
    _scoreLabel->setGeometry(QRect(NEXT_PIECE_WIDTH_OFFSET + 3, BOARD_HEIGHT_OFFSET, 100, 20));
    _scoreLabel->setFont(labelFont);
    _scoreLabel->setText("SCORE");

    _nextPieceLabel = new QLabel(this);
    _nextPieceLabel->setGeometry(QRect(NEXT_PIECE_WIDTH_OFFSET + 3, 205, 150, 20));
    _nextPieceLabel->setFont(labelFont);
    _nextPieceLabel->setText("NEXT PIECE");

    _levelLabel = new QLabel(this);
    _levelLabel->setGeometry(QRect(NEXT_PIECE_WIDTH_OFFSET + 3, BOARD_HEIGHT_OFFSET + 25, 100, 20));
    _levelLabel->setFont(labelFont);
    _levelLabel->setText("LEVEL");

    _linesLabel = new QLabel(this);
    _linesLabel->setGeometry(QRect(NEXT_PIECE_WIDTH_OFFSET + 3, BOARD_HEIGHT_OFFSET + 50, 100, 20));
    _linesLabel->setFont(labelFont);
    _linesLabel->setText("LINES");

    _hiscoreLabel = new QLabel(this);
    _hiscoreLabel->setGeometry(QRect(NEXT_PIECE_WIDTH_OFFSET + 3, BOARD_HEIGHT_OFFSET + 75, 100, 20));
    _hiscoreLabel->setFont(labelFont);
    _hiscoreLabel->setText("HISCORE");

    _controlsLabel = new QLabel(this);
    _controlsLabel->setGeometry(QRect(NEXT_PIECE_WIDTH_OFFSET + 3, NEXT_PIECE_HEIGHT_OFFSET + 130, 200, 290));
    _controlsLabel->setFont(labelFont);
    _controlsLabel->setText("CONTROLS\n\nMOVE\t-arrows\nROTATE\t-r\nPAUSE\t-space\nNEW\t-space");

    QString qscore = QString::fromStdString(std::to_string(_game.get_score()));
    _scoreValue = new QLabel(this);
    _scoreValue->setGeometry(QRect(NEXT_PIECE_WIDTH_OFFSET + 103, BOARD_HEIGHT_OFFSET, 100, 20));
    _scoreValue->setFont(labelFont);
    _scoreValue->setText(qscore);

    QString qlevel = QString::fromStdString(std::to_string(_game.get_level()));
    _levelValue = new QLabel(this);
    _levelValue->setGeometry(QRect(NEXT_PIECE_WIDTH_OFFSET + 103, BOARD_HEIGHT_OFFSET + 25, 100, 20));
    _levelValue->setFont(labelFont);
    _levelValue->setText(qlevel);

    QString qlines = QString::fromStdString(std::to_string(_game.get_lines()));
    _linesValue = new QLabel(this);
    _linesValue->setGeometry(QRect(NEXT_PIECE_WIDTH_OFFSET + 103, BOARD_HEIGHT_OFFSET + 50, 100, 20));
    _linesValue->setFont(labelFont);
    _linesValue->setText(qlines);

    QString qhiscore = QString::fromStdString(std::to_string(_game.get_hiscore()));
    _hiscoreValue = new QLabel(this);
    _hiscoreValue->setGeometry(QRect(NEXT_PIECE_WIDTH_OFFSET + 103, BOARD_HEIGHT_OFFSET + 75, 100, 20));
    _hiscoreValue->setFont(labelFont);
    _hiscoreValue->setText(qhiscore);
}

MainWindow::~MainWindow()
{
    delete ui;

    delete _pauseLabel;         // Free up pointers
    delete _scoreLabel;
    delete _nextPieceLabel;
    delete _levelLabel;
    delete _linesLabel;
    delete _hiscoreLabel;
    delete _controlsLabel;
    delete _scoreValue;
    delete _levelValue;
    delete _linesValue;
    delete _hiscoreValue;
}

void MainWindow::paintEvent(QPaintEvent * e)
{
    QPainter painter(this);

    // Fill Board Space

    QPen blackPen(Qt::black);

    QRect gameBoardRectangle(BOARD_WIDTH_OFFSET, BOARD_HEIGHT_OFFSET, BOARD_WIDTH_PIXELS, BOARD_HEIGHT_PIXELS);

    QRect scoreRectangle(NEXT_PIECE_WIDTH_OFFSET, BOARD_HEIGHT_OFFSET, 200, 100);

    QRect nextPieceRectangle(NEXT_PIECE_WIDTH_OFFSET, NEXT_PIECE_HEIGHT_OFFSET, 200, 200);

    QRect controlsRectangle(NEXT_PIECE_WIDTH_OFFSET, NEXT_PIECE_HEIGHT_OFFSET + 205, 200, 290);

    // Draw Board

    blackPen.setWidth(1);
    painter.setPen(blackPen);

    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            int value = _game.get_board_position(x, y);

            if (value != EMPTY_SPACE)
            {
                QRect cell(BOARD_WIDTH_OFFSET + x * cellWidth, BOARD_HEIGHT_OFFSET + y * cellHeight, cellWidth, cellHeight);

                switch(value)
                {
                    case 0: painter.fillRect(cell, QBrush("#00FFFF"));
                            break;
                    case 1: painter.fillRect(cell, QBrush("#0000FF"));
                            break;
                    case 2: painter.fillRect(cell, QBrush("#FFA500"));
                            break;
                    case 3: painter.fillRect(cell, QBrush("#FFFF00"));
                            break;
                    case 4: painter.fillRect(cell, QBrush("#00FF00"));
                            break;
                    case 5: painter.fillRect(cell, QBrush("#800080"));
                            break;
                    case 6: painter.fillRect(cell, QBrush("#FF0000"));
                            break;
                }

                painter.drawRect(cell);
            }
        }

        // Draw next piece

        if (!_game.game_over())
        {
            int value = _game.get_next_piece()->get_type();

            std::pair<int, int> one = _game.get_next_piece()->get_one();
            QRect cellOne(NEXT_PIECE_WIDTH_OFFSET + one.first * cellWidth - 1 * cellWidth, NEXT_PIECE_HEIGHT_OFFSET + one.second * cellWidth + 2 * cellWidth, cellWidth, cellHeight);

            std::pair<int, int> two = _game.get_next_piece()->get_two();
            QRect cellTwo(NEXT_PIECE_WIDTH_OFFSET + two.first * cellWidth - 1 * cellWidth, NEXT_PIECE_HEIGHT_OFFSET + two.second * cellWidth + 2 * cellWidth, cellWidth, cellHeight);

            std::pair<int, int> three = _game.get_next_piece()->get_three();
            QRect cellThree(NEXT_PIECE_WIDTH_OFFSET + three.first * cellWidth - 1 * cellWidth, NEXT_PIECE_HEIGHT_OFFSET + three.second * cellWidth + 2 * cellWidth, cellWidth, cellHeight);

            std::pair<int, int> four = _game.get_next_piece()->get_four();
            QRect cellFour(NEXT_PIECE_WIDTH_OFFSET + four.first * cellWidth - 1 * cellWidth, NEXT_PIECE_HEIGHT_OFFSET + four.second * cellWidth + 2 * cellWidth, cellWidth, cellHeight);

            switch(value)
            {
                case 0: painter.fillRect(cellOne, QBrush("#00FFFF"));
                        painter.fillRect(cellTwo, QBrush("#00FFFF"));
                        painter.fillRect(cellThree, QBrush("#00FFFF"));
                        painter.fillRect(cellFour, QBrush("#00FFFF"));
                        break;
                case 1: painter.fillRect(cellOne, QBrush("#0000FF"));
                        painter.fillRect(cellTwo, QBrush("#0000FF"));
                        painter.fillRect(cellThree, QBrush("#0000FF"));
                        painter.fillRect(cellFour, QBrush("#0000FF"));
                        break;
                case 2: painter.fillRect(cellOne, QBrush("#FFA500"));
                        painter.fillRect(cellTwo, QBrush("#FFA500"));
                        painter.fillRect(cellThree, QBrush("#FFA500"));
                        painter.fillRect(cellFour, QBrush("#FFA500"));
                        break;
                case 3: painter.fillRect(cellOne, QBrush("#FFFF00"));
                        painter.fillRect(cellTwo, QBrush("#FFFF00"));
                        painter.fillRect(cellThree, QBrush("#FFFF00"));
                        painter.fillRect(cellFour, QBrush("#FFFF00"));
                        break;
                case 4: painter.fillRect(cellOne, QBrush("#00FF00"));
                        painter.fillRect(cellTwo, QBrush("#00FF00"));
                        painter.fillRect(cellThree, QBrush("#00FF00"));
                        painter.fillRect(cellFour, QBrush("#00FF00"));
                        break;
                case 5: painter.fillRect(cellOne, QBrush("#800080"));
                        painter.fillRect(cellTwo, QBrush("#800080"));
                        painter.fillRect(cellThree, QBrush("#800080"));
                        painter.fillRect(cellFour, QBrush("#800080"));
                        break;
                case 6: painter.fillRect(cellOne, QBrush("#FF0000"));
                        painter.fillRect(cellTwo, QBrush("#FF0000"));
                        painter.fillRect(cellThree, QBrush("#FF0000"));
                        painter.fillRect(cellFour, QBrush("#FF0000"));
                        break;
            }

            painter.drawRect(cellOne);
            painter.drawRect(cellTwo);
            painter.drawRect(cellThree);
            painter.drawRect(cellFour);
        }
    }

    // Draw Borders

    QPen cyanPen(Qt::black);
    cyanPen.setWidth(2);
    painter.setPen(cyanPen);

    painter.drawRect(gameBoardRectangle);
    painter.drawRect(scoreRectangle);
    painter.drawRect(nextPieceRectangle);
    painter.drawRect(controlsRectangle);

    // Update Labels

    QString qscore = QString::fromStdString(std::to_string(_game.get_score()));
    _scoreValue->setText(qscore);

    QString qlevel = QString::fromStdString(std::to_string(_game.get_level()));
    _levelValue->setText(qlevel);

    QString qlines = QString::fromStdString(std::to_string(_game.get_lines()));
    _linesValue->setText(qlines);
}

// Drops piece one vertical position
void MainWindow::drop_piece()
{
    if (!_game.game_over())
    {
        if (!_game.move_piece(DOWN))
        {
            int currentLevel = _game.get_level();

            if (_game.lock_piece_and_replace())
            {
                int newLevel = _game.get_level();

                if (currentLevel != newLevel)
                {
                    increase_speed();
                }
            }
        }
        this->repaint();
    }
}

// Increase speed of falling pieces
void MainWindow::increase_speed()
{
    _dropSpeed *= SPEED_LEVEL_MULTIPLIER;
    _timer->start(_dropSpeed);
}

// Pause timer during game pause
void MainWindow::pause_timer()
{
    _elapsedTime = _timer->remainingTime();
    _timer->stop();
}

// Unpause timer
// Switches to secondary timer to finish remaining cylce
void MainWindow::unpause_timer()
{
    _pauseTimer->start(_dropSpeed - _elapsedTime);
    _elapsedTime = 0;
}

// Switches from secondary timer to primary timer
// Drops piece one vertical position
void MainWindow::finish_timer()
{
    _pauseTimer->stop();
    drop_piece();
    _timer->start(_dropSpeed);
}

void MainWindow::keyPressEvent(QKeyEvent * e)
{
    QPainter painter(this);

    if (!_game.game_over())
    {
        if (!_game.paused())
        {
            switch(e->key())
            {
                case Qt::Key_R:     _game.rotate_piece();
                                    break;

                case Qt::Key_Left:  _game.move_piece(LEFT);
                                    break;

                case Qt::Key_Right: _game.move_piece(RIGHT);
                                    break;

                case Qt::Key_Down:  if (!_game.move_piece(DOWN))
                                    {
                                        int currentLevel = _game.get_level();

                                        if (_game.lock_piece_and_replace())
                                        {
                                            int newLevel = _game.get_level();

                                            if (currentLevel != newLevel)
                                            {
                                                increase_speed();
                                            }
                                        }
                                    }
                                    break;
            }
        }

        if (e->key() == Qt::Key_Space)
        {
            if (_game.paused())
            {
                unpause_timer();
                _pauseLabel->setVisible(false);
            }
            else
            {
                pause_timer();
                _pauseLabel->setVisible(true);
            }
            _game.toggle_pause();

        }
        this->repaint();
    }
    else
    {
        if (e->key() == Qt::Key_Space)
        {
            _game.reset_game();

            QString qhiscore = QString::fromStdString(std::to_string(_game.get_hiscore()));
            _hiscoreValue->setText(qhiscore);

            _dropSpeed = DEFAULT_DROP_SPEED;
            _timer->start(_dropSpeed);
        }
        this->repaint();
    }
}
