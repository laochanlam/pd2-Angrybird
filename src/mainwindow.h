#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream> 
#include <QWidget>
#include <QLabel>
#include <QPushButton>


#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <pig.h>
#include <block.h>
#include <stick.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);


signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void on_Reset_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    QMouseEvent *mouse_event;
    bool flag;
    float final_x,final_y;
    float x_start,y_start;
    float x_end,y_end;
    Bird *birdA;
    Bird *birdB;
    Bird *birdC;
    Bird *birdD;
    QPushButton *Reset;
    QPushButton *Quit;
    Pig *pig;
    Block *left;
    Block *right;
    Block *shelf;
    Stick *stick1;
    Stick *stick2;
    Stick *stick3;
    bool notboom;
    bool ScoreStart;
    int score;
    QLabel *label_Score;
    QString Score;
    QPalette colour;
    int birdCounting;
    bool kick;
};

#endif // MAINWINDOW_H
