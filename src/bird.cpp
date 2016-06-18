#include "bird.h"
#include <iostream>

Bird::Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene,float BIRD_DENSITY):GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(radius*2,radius*2);

    pos_x = x;
    pos_y = y;

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2CircleShape bodyshape;
    bodyshape.m_radius = radius;
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = BIRD_DENSITY;
    fixturedef.friction = BIRD_FRICTION;
    fixturedef.restitution = BIRD_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);
    skillAcontroler = 1;
    skillCcontroler = 1;
    skillDcontroler = 1;
    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

void Bird::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}

b2Vec2 Bird::GetLinearVelocity()
{
    return g_body->GetLinearVelocity();
}

b2Vec2 Bird::GetOriginPosition()
{
    //std::cout<<g_body->GetPosition().x<<" ";
    return g_body->GetPosition();
}


bool Bird::DetectBound()
{
     if (GetOriginPosition().x >= 32.0f || GetOriginPosition().x < 0.0f ||GetOriginPosition().y > 18.0f || GetOriginPosition().y < 0.0f)  return true;
     return false;
}


void Bird::skillA(){
    if (skillAcontroler == 1)
    {
        g_pixmap.setPixmap(QPixmap(":/birdA2.png").scaled(60, 60));
        skillAcontroler++;
    }

    else if (skillAcontroler == 2)
    {
        g_pixmap.setPixmap(QPixmap(":/birdA3.png").scaled(60, 60));
        skillAcontroler++;
    }
    else if (skillAcontroler == 3)
    {
        g_pixmap.setPixmap(QPixmap(":/birdA4.png").scaled(60, 60));
        skillAcontroler++;
    }
    else if (skillAcontroler == 4)
    {
        g_pixmap.setPixmap(QPixmap(":/birdA.png").scaled(60, 60));
        skillAcontroler = 1;
    }
}

void Bird::skillB(){
    g_body->SetLinearVelocity(g_body->GetLinearVelocity()+b2Vec2(4,2));
}

void Bird::skillC(QTimer *timer,b2World *world, QGraphicsScene *scene){
    if (skillCcontroler == 1)
    {
        NewA = new Bird(GetOriginPosition().x, GetOriginPosition().y-1 , 1.0f,timer,QPixmap(":/birdA.png").scaled(60, 60),world,scene,10);
        NewB = new Bird(GetOriginPosition().x-2, GetOriginPosition().y-1 , 1.0f,timer,QPixmap(":/birdA.png").scaled(60, 60),world,scene,10);
        NewC = new Bird(GetOriginPosition().x-1, GetOriginPosition().y , 1.0f,timer,QPixmap(":/birdA.png").scaled(60, 60),world,scene,10);
        NewD = new Bird(GetOriginPosition().x-1, GetOriginPosition().y+1 , 1.0f,timer,QPixmap(":/birdA.png").scaled(60, 60),world,scene,10);
        NewE = new Bird(GetOriginPosition().x-1, GetOriginPosition().y-1 , 1.0f,timer,QPixmap(":/birdA.png").scaled(60, 60),world,scene,10);
        skillCcontroler--;
    }
}

void Bird::skillD(QTimer *timer,b2World *world, QGraphicsScene *scene){
    if (skillDcontroler == 1)
    {
        NewF = new Bird(GetOriginPosition().x, GetOriginPosition().y-2 , 1.0f,timer,QPixmap(":/shit.png").scaled(60, 60),world,scene,10);
        NewF->g_body->SetLinearVelocity(b2Vec2(g_body->GetLinearVelocity().x+20,0));
        skillDcontroler--;
    }
}

void Bird::deletethem(){
    if (skillCcontroler == 0)
    {
        delete NewA;
        delete NewB;
        delete NewC;
        delete NewD;
        delete NewE;
    }
    if (skillDcontroler == 0)
        delete NewF;

}
