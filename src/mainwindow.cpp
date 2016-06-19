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
    itemList.clear();


    birdD = new Bird(3.0f, 8.0f, 1.0f,&timer,QPixmap(":/birdA.png").scaled(60, 60),world,scene,10);
    pig = new Pig(25.0f,4.0f, 1.0f,&timer,QPixmap(":/pig.png").scaled(60, 60),world,scene);
    left = new Block(23.0f,5.0f,1.0f,4.0f,&timer,QPixmap(":/redblock.png").scaled(30,120),world,scene);
    right = new Block(27.0f,5.0f,1.0f,4.0f,&timer,QPixmap(":/redblock.png").scaled(30,120),world,scene);
    shelf = new Block(3.0f,5.0f,1.0f,4.0f,&timer,QPixmap(":/redblock.png").scaled(30,120),world,scene);
    stick1 = new Stick(24.8f,10.0f,4.5f,2.95f,&timer,QPixmap(":/stick.png").scaled(130,90),world,scene);
    stick2 = new Stick(24.8f,13.0f,4.5f,2.95f,&timer,QPixmap(":/stick.png").scaled(130,90),world,scene);
    stick3 = new Stick(24.8f,15.0f,4.5f,2.95f,&timer,QPixmap(":/stick.png").scaled(130,90),world,scene);
    score = 0;
    ScoreStart = false;
    itemList.push_back(birdD);
    itemList.push_back(pig);
    itemList.push_back(left);
    itemList.push_back(right);
    itemList.push_back(shelf);
    itemList.push_back(stick1);
    itemList.push_back(stick2);
    itemList.push_back(stick3);

    birdCounting = 8;
    kick = true;
    notboom = true;


    Reset = new QPushButton(this);
    Reset->setGeometry(30,10,125,50);
    connect(Reset, SIGNAL (released()), this, SLOT (on_Reset_clicked()));
    Reset->setObjectName("Reset");
    Reset->show();
    Reset->setStyleSheet("#Reset{border-image:url(:/newb.png)}");


    Quit = new QPushButton(this);
    Quit->setGeometry(160,10,125,50);
    connect(Quit, SIGNAL (released()), this, SLOT (close()));
    Quit->setObjectName("Quit");
    Quit->show();
    Quit->setStyleSheet("#Quit{border-image:url(:/quit.png)}");


    label_Score = new QLabel(this);
    Score = "Score: " + QString::number(score);
    label_Score->setText(Score);
    label_Score->setGeometry(50,460,300,100);
    label_Score->setFont(QFont("Minion Pro Med",20));
    colour.setColor(QPalette::WindowText,Qt::white);
    label_Score->setPalette(colour);
    label_Score->show();




    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));

    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}


bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    mouse_event = static_cast<QMouseEvent*>(event);

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

            if (abs(final_x) >= 10 || abs(final_y) >= 10)
            {
                birdA->g_body->SetType(b2_dynamicBody);
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

            if (abs(final_x) >= 10 || abs(final_y) >= 10)
            {
                birdB->g_body->SetType(b2_dynamicBody);
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

            if (abs(final_x) >= 10 || abs(final_y) >= 10)
            {
                birdC->g_body->SetType(b2_dynamicBody);
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

            if (abs(final_x) >= 10 || abs(final_y) >= 10)
            {
                birdD->g_body->SetType(b2_dynamicBody);
                birdD->setLinearVelocity(b2Vec2(final_x/4,final_y/4));
                birdCounting--;
                flag = true;
                kick = false;
            }
        }

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


    while (!itemList.isEmpty())
    {
        if (itemList.back() == birdB)
            birdB->deletethem();
        if (itemList.back() == birdA)
            birdA->deletethem();

        if (notboom == false && itemList.back()== pig)
            itemList.pop_back();

        delete itemList.back();
        itemList.pop_back();


    }


    birdD = new Bird(3.0f, 8.0f, 1.0f,&timer,QPixmap(":/birdA.png").scaled(60, 60),world,scene,10);
    pig = new Pig(25.0f,4.0f, 1.0f,&timer,QPixmap(":/pig.png").scaled(60, 60),world,scene);
    left = new Block(23.0f,5.0f,1.0f,4.0f,&timer,QPixmap(":/redblock.png").scaled(30,120),world,scene);
    right = new Block(27.0f,5.0f,1.0f,4.0f,&timer,QPixmap(":/redblock.png").scaled(30,120),world,scene);
    shelf = new Block(3.0f,5.0f,1.0f,4.0f,&timer,QPixmap(":/redblock.png").scaled(30,120),world,scene);
    stick1 = new Stick(24.8f,10.0f,4.5f,2.95f,&timer,QPixmap(":/stick.png").scaled(130,90),world,scene);
    stick2 = new Stick(24.8f,13.0f,4.5f,2.95f,&timer,QPixmap(":/stick.png").scaled(130,90),world,scene);
    stick3 = new Stick(24.8f,15.0f,4.5f,2.95f,&timer,QPixmap(":/stick.png").scaled(130,90),world,scene);
    birdCounting = 8;
    kick = true;
    notboom = true;
    score = 0;
    Score = "Score: " + QString::number(score);
    label_Score->setText(Score);
    ScoreStart = false;
    itemList.push_back(birdD);
    itemList.push_back(pig);
    itemList.push_back(left);
    itemList.push_back(right);
    itemList.push_back(shelf);
    itemList.push_back(stick1);
    itemList.push_back(stick2);
    itemList.push_back(stick3);


}


void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);




    if ( ( birdD->DetectBound() == true || birdD->GetLinearVelocity().x  <= 0 || birdD->GetLinearVelocity().y - 5 == 0 )&& birdCounting == 7)
    {
        kick = true;
        birdCounting--;
        ScoreStart = true;
    }

    if (birdCounting == 7 && (abs(birdD->GetOriginPosition().x-3)>2 || abs(birdD->GetOriginPosition().y-3)>8) && flag == true)
    {
        flag = false;
        birdC = new Bird(3.0f, 8.0f, 1.0f,&timer,QPixmap(":/birdD.png").scaled(60, 60),world,scene,10);
        birdC->g_body->SetType(b2_staticBody);
        itemList.push_back(birdC);

    }

    if (birdCounting == 5)
    if ( ( birdC->DetectBound() == true || birdC->GetLinearVelocity().x  <= 0 || birdC->GetLinearVelocity().y - 1 == 0 ))
    {
        kick = true;
        birdCounting--;

    }

    if (birdCounting == 5 && (abs(birdC->GetOriginPosition().x-3)>2 || abs(birdC->GetOriginPosition().y-3)>8) && flag == false)
    {
        flag = true;
        birdB = new Bird(3.0f, 8.0f, 1.0f,&timer,QPixmap(":/birdC.png").scaled(60, 60),world,scene,10);
        birdB->g_body->SetType(b2_staticBody);
        itemList.push_back(birdB);
    }

    if (birdCounting == 3)
    if (birdB->DetectBound() == true || birdB->GetLinearVelocity().x - 1 <= 0 || birdB->GetLinearVelocity().y - 1 == 0 )
    {
        kick = true;
        birdCounting--;
    }

    if (birdCounting == 3 && (abs(birdB->GetOriginPosition().x-3)>2 || abs(birdB->GetOriginPosition().y-3)>8) && flag == true)
    {
        flag = false;
        birdA = new Bird(3.0f, 8.0f, 1.0f,&timer,QPixmap(":/birdB.png").scaled(60, 60),world,scene,10);
        birdA->g_body->SetType(b2_staticBody);
        itemList.push_back(birdA);
    }

    if (birdCounting == 1)
    if (birdA->DetectBound() == true || birdA->GetLinearVelocity().x - 1 <= 0 || birdA->GetLinearVelocity().y - 1 == 0 )
    {
        kick = true;
        birdCounting--;
    }
    if (notboom)
        if (pig->GetLinearVelocity().x > 0 || pig->GetLinearVelocity().y > 0 )
        {
            delete pig;
            notboom = false;
            score = score + 10000;
            Score = "Score: " + QString::number(score);
            label_Score->setText(Score);
            label_Score->show();
        }

    if ((stick1->GetLinearVelocity().x > 0 || stick1->GetLinearVelocity().y > 0) && ScoreStart && !(stick1->DetectBound()))
    {
        score = score + abs(stick1->GetLinearVelocity().x);
        score = score + abs(stick1->GetLinearVelocity().y);
        Score = "Score: " + QString::number(score);
        label_Score->setText(Score);
    }
    if ((stick2->GetLinearVelocity().x > 0 || stick2->GetLinearVelocity().y > 0) && ScoreStart && !(stick2->DetectBound()))
    {
        score = score + abs(stick2->GetLinearVelocity().x);
        score = score + abs(stick2->GetLinearVelocity().y);
        Score = "Score: " + QString::number(score);
        label_Score->setText(Score);
    }
    if ((stick3->GetLinearVelocity().x > 0 || stick3->GetLinearVelocity().y > 0) && ScoreStart && !(stick3->DetectBound()))
    {
        score = score + abs(stick3->GetLinearVelocity().x);
        score = score + abs(stick3->GetLinearVelocity().y);
        Score = "Score: " + QString::number(score);
        label_Score->setText(Score);
    }
    scene->update();

}

void MainWindow::QUITSLOT()
{
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

