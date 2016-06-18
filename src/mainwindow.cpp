#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setBackgroundBrush(QPixmap(":/bg.jpg").scaled(960, 540));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{

    scene = new QGraphicsScene(0,0,960,540);
    ui->graphicsView->setScene(scene);
    world = new b2World(b2Vec2(0.0f, -9.8f));
    GameItem::setGlobalSize(QSizeF(32,18),size());
    new Land(16.0f,1.5f,32.0f,3.0f,QPixmap(":/ground.png").scaled(960 ,90),world,scene);



    birdD = new Bird(3.0f, 8.0f, 1.0f,&timer,QPixmap(":/birdA.png").scaled(60, 60),world,scene,10);
    pig = new Pig(25.0f,6.0f, 1.0f,&timer,QPixmap(":/pig.png").scaled(60, 60),world,scene);
    left = new Block(23.0f,6.0f,1.0f,4.0f,&timer,QPixmap(":/redblock.png").scaled(30,120),world,scene);
    right = new Block(27.0f,6.0f,1.0f,4.0f,&timer,QPixmap(":/redblock.png").scaled(30,120),world,scene);
    shelf = new Block(3.0f,6.0f,1.0f,4.0f,&timer,QPixmap(":/redblock.png").scaled(30,120),world,scene);
    stick1 = new Stick(24.8f,10.0f,4.5f,2.95f,&timer,QPixmap(":/stick.png").scaled(130,90),world,scene);
    stick2 = new Stick(24.8f,13.0f,4.5f,2.95f,&timer,QPixmap(":/stick.png").scaled(130,90),world,scene);
    stick3 = new Stick(24.8f,15.0f,4.5f,2.95f,&timer,QPixmap(":/stick.png").scaled(130,90),world,scene);
    birdCounting = 8;


    QPushButton *Reset = new QPushButton(this);
    Reset->setGeometry(30,10,125,50);
    connect(Reset, SIGNAL (released()), this, SLOT (on_Reset_clicked()));
    Reset->setObjectName("Reset");
    Reset->show();
    Reset->setStyleSheet("#Reset{border-image:url(:/newb.png)}");




    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}


bool MainWindow::eventFilter(QObject *, QEvent *event)
{



    QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);


    if(event->type() == QEvent::MouseButtonPress)
    {

        if (birdCounting == 7)
                birdD->skillA();
        if (birdCounting == 5)
                birdC->skillB();
        if (birdCounting == 3)
                birdB->skillC(&timer,world,scene);
        if (birdCounting == 1)
                birdA->skillD(&timer,world,scene);




            x_start = mouse_event->x();
            y_start = mouse_event->y();

        /* TODO : add your code here */
        //std::cout << x_start << y_start << std::endl ;
    }
    if(event->type() == QEvent::MouseMove)
    {
        /* TODO : add your code here */
        //std::cout << "Move !" << std::endl ;

    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        /* TODO : add your code here */
        //std::cout << "Release !" << std::endl ;

        x_end = mouse_event->x();
        y_end = mouse_event->y();



        final_x = abs(x_start)-abs(x_end);
        final_y =abs(y_start)-abs(y_end);

        if (birdCounting == 2 && kick == true)
        {

            if (final_x >= 100)
                final_x = 100;
            if (final_y >= 100)
                final_y = 100;
            if (final_x <= -100)
                final_x = -100;
            if (final_y <= -100)
                final_y = -100;

            if (final_x/4 -1 >= 0 || final_y/4 -1 >= 0)
            {
                birdA->setLinearVelocity(b2Vec2(final_x/4,final_y/4));
                birdCounting--;
                kick = false;
            }

        }
        if (birdCounting == 4 && kick == true)
        {
            if (final_x >= 100)
                final_x = 100;
            if (final_y >= 100)
                final_y = 100;
            if (final_x <= -100)
                final_x = -100;
            if (final_y <= -100)
                final_y = -100;

            if (final_x/4 -1 >= 0 || final_y/4 -1 >= 0)
            {
                birdB->setLinearVelocity(b2Vec2(final_x/4,final_y/4));
                birdCounting--;
                kick = false;
            }
        }
        if (birdCounting == 6 && kick == true)
        {
            if (final_x >= 100)
                final_x = 100;
            if (final_y >= 100)
                final_y = 100;
            if (final_x <= -100)
                final_x = -100;
            if (final_y <= -100)
                final_y = -100;

            if (final_x/4 -1 >= 0 || final_y/4 -1 >= 0)
            {
                birdC->setLinearVelocity(b2Vec2(final_x/4,final_y/4));
                birdCounting--;
                kick = false;
            }
        }
        if (birdCounting == 8 && kick == true)
        {
            if (final_x >= 100)
                final_x = 100;
            if (final_y >= 100)
                final_y = 100;
            if (final_x <= -100)
                final_x = -100;
            if (final_y <= -100)
                final_y = -100;

            if (final_x/4 -1 >= 0 || final_y/4 -1 >= 0)
            {
                birdD->setLinearVelocity(b2Vec2(final_x/4,final_y/4));
                birdCounting--;
                flag = true;
                kick = false;
            }
        }

        //std::cout << 'x=' <<final_x <<std::endl<<'y='<< final_y << std::endl ;
        //std::cout << x_end << x_end << std::endl ;
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::on_Reset_clicked()
{

    delete birdD;
    delete pig;
    delete left;
    delete right;
    delete shelf;
    delete stick1;
    delete stick2;
    delete stick3;


    birdD = new Bird(3.0f, 8.0f, 1.0f,&timer,QPixmap(":/birdA.png").scaled(60, 60),world,scene,10);
    if (birdCounting <= 7)
    {
        delete birdC;
        if (birdCounting <= 5)
        {
            delete birdB;
            birdB->deletethem();
            if (birdCounting <= 3)
            {
                delete birdA;
                birdA->deletethem();
            }
        }
    }


    pig = new Pig(25.0f,6.0f, 1.0f,&timer,QPixmap(":/pig.png").scaled(60, 60),world,scene);
    left = new Block(23.0f,6.0f,1.0f,4.0f,&timer,QPixmap(":/redblock.png").scaled(30,120),world,scene);
    right = new Block(27.0f,6.0f,1.0f,4.0f,&timer,QPixmap(":/redblock.png").scaled(30,120),world,scene);
    shelf = new Block(3.0f,6.0f,1.0f,4.0f,&timer,QPixmap(":/redblock.png").scaled(30,120),world,scene);
    stick1 = new Stick(24.8f,10.0f,4.5f,2.95f,&timer,QPixmap(":/stick.png").scaled(130,90),world,scene);
    stick2 = new Stick(24.8f,13.0f,4.5f,2.95f,&timer,QPixmap(":/stick.png").scaled(130,90),world,scene);
    stick3 = new Stick(24.8f,15.0f,4.5f,2.95f,&timer,QPixmap(":/stick.png").scaled(130,90),world,scene);
    birdCounting = 8;
    kick = true;


}


void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);

    if ( ( birdD->DetectBound() == true || birdD->GetLinearVelocity().x - 1 <= 0 || birdD->GetLinearVelocity().y - 5 == 0 )&& birdCounting == 7)
    {
        kick = true;
        birdCounting--;
    }

    if (birdCounting == 7 && abs(birdD->GetOriginPosition().x)>5 && flag == true)
    {
        flag = false;
        birdC = new Bird(3.0f, 8.0f, 1.0f,&timer,QPixmap(":/birdD.png").scaled(60, 60),world,scene,10);
    }

    if (birdCounting == 5)
    if ( ( birdC->DetectBound() == true || birdC->GetLinearVelocity().x - 1 <= 0 || birdC->GetLinearVelocity().y - 1 == 0 ))
    {
        kick = true;
        birdCounting--;
    }

    if (birdCounting == 5 && abs(birdC->GetOriginPosition().x)>5 && flag == false)
    {
        flag = true;
        birdB = new Bird(3.0f, 8.0f, 1.0f,&timer,QPixmap(":/birdC.png").scaled(60, 60),world,scene,10);
    }

    if (birdCounting == 3)
    if (birdB->DetectBound() == true || birdB->GetLinearVelocity().x - 1 <= 0 || birdB->GetLinearVelocity().y - 1 == 0 )
    {
        kick = true;
        birdCounting--;
    }

    if (birdCounting == 3 && abs(birdB->GetOriginPosition().x)>5 && flag == true)
    {
        flag = false;
        birdA = new Bird(3.0f, 8.0f, 1.0f,&timer,QPixmap(":/birdB.png").scaled(60, 60),world,scene,10);
    }



    /*
     *
    if ( ( birdA->DetectBound() == true || birdA->GetLinearVelocity().x - 1 <= 0 || birdA->GetLinearVelocity().y - 1 == 0 )&& birdCounting == 7)
    {
        kick = true;

    }

    if (birdCounting == 1 && birdD->GetOriginPosition().x>6 && flag == true)
    {
        flag = false;

    }
    */
    scene->update();

}

void MainWindow::QUITSLOT()
{
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

