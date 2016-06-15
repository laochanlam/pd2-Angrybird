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



#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <pig.h>
#include <block.h>

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
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    float final_x,final_y;
    float x_start,y_start;
    float x_end,y_end;
    Bird *birdA;
    Bird *birdB;
    Bird *birdC;
    Bird *birdD;
    int birdCounting;
    bool kick;
};

#endif // MAINWINDOW_H
