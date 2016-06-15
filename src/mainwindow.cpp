#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());
    // Create ground (You can edit here)
    itemList.push_back(new Land(16,1.5,32,3,QPixmap(":/ground.png").scaled(960,90),world,scene));

    // Create bird (You can edit here)


    birdA = new Bird(0.0f,10.0f,0.4f,&timer,QPixmap(":/birdA.png").scaled(60, 60),world,scene);
    birdB = new Bird(2.0f,10.0f,0.4f,&timer,QPixmap(":/birdB.png").scaled(60, 60),world,scene);
    birdC = new Bird(4.0f,10.0f,0.4f,&timer,QPixmap(":/birdC.png").scaled(60, 60),world,scene);
    birdD = new Bird(6.0f,10.0f,0.4f,&timer,QPixmap(":/birdD.png").scaled(60, 60),world,scene);
    Pig *pig = new Pig(25.0f,10.0f,0.4f,&timer,QPixmap(":/pig.png").scaled(60, 60),world,scene);
    Block *left = new Block(23.0f,10.0f,.2f,1.4,&timer,QPixmap(":/redblock.png").scaled(30,105),world,scene);
    Block *right = new Block(28.0f,10.0f,.2f,1.4f,&timer,QPixmap(":/redblock.png").scaled(30,105),world,scene);
    birdCounting = 4;
    //Block *left = new Block(23.0f,10.0f,0.18f,1.5f,&timer,QPixmap(":/redblock.png").scaled(60,100),world,scene);


    final_x = abs(x_start)-abs(x_end);
    final_y =abs(y_start)-abs(y_end);

    // Setting the Velocity
   // birdA->setLinearVelocity(b2Vec2(50,0));


    itemList.push_back(birdA);
   // itemList.push_back(pig);
    // Timer


    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{



    QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);

    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress)
    {

        //birdA->setLinearVelocity(b2Vec2(mouse_event->x(), mouse_event->y()));
            kick = true;
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

        if (birdCounting == 1 && kick == true)
        {
            birdA->setLinearVelocity(b2Vec2(final_x/4,final_y/4));
            birdCounting--;
            kick = false;
        }
        if (birdCounting == 2 && kick == true)
        {
            birdB->setLinearVelocity(b2Vec2(final_x/4,final_y/4));
            birdCounting--;
            kick = false;
        }
        if (birdCounting == 3 && kick == true)
        {
            birdC->setLinearVelocity(b2Vec2(final_x/4,final_y/4));
            birdCounting--;
            kick = false;
        }
        if (birdCounting == 4 && kick == true)
        {
            birdD->setLinearVelocity(b2Vec2(final_x/4,final_y/4));
            birdCounting--;
            kick = false;
        }

        std::cout << 'x=' <<final_x <<std::endl<<'y='<< final_y << std::endl ;
        //std::cout << x_end << x_end << std::endl ;
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);

    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}
