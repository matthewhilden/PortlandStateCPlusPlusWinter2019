#pragma once

#include "board.h"
#include "game.h"

#include <QtGui>
#include <QtCore>
#include <QTimer>
#include <QLabel>
#include <QString>

#include <QMainWindow>

#include <string>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:

        int _dropSpeed;         // Speed control falling pieces
        game _game;

        QTimer * _timer;
        QTimer * _pauseTimer;

        QLabel * _pauseLabel;
        QLabel * _scoreLabel;
        QLabel * _nextPieceLabel;
        QLabel * _levelLabel;
        QLabel * _linesLabel;
        QLabel * _hiscoreLabel;
        QLabel * _controlsLabel;

        QLabel * _scoreValue;
        QLabel * _levelValue;
        QLabel * _linesValue;
        QLabel * _hiscoreValue;

        int _elapsedTime;

        Ui::MainWindow *ui;

    public:

        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    public slots:

        void drop_piece();
        void finish_timer();

    protected:

        void paintEvent(QPaintEvent * e);
        void keyPressEvent(QKeyEvent * e);

        void increase_speed();
        void pause_timer();
        void unpause_timer();


};
