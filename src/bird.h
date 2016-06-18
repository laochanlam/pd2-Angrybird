#ifndef BIRD_H
#define BIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>


#define BIRD_FRICTION 0.2f
#define BIRD_RESTITUTION 0.5f

class Bird : public GameItem
{
public:
    Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene,float BIRD_DENSITY);
    void setLinearVelocity(b2Vec2 velocity);
    b2Vec2 GetLinearVelocity();
    b2Vec2 GetOriginPosition();
    bool DetectBound();


    void skillA();
    void skillB();
    void skillC(QTimer *timer,b2World *world, QGraphicsScene *scene);
    void skillD(QTimer *timer,b2World *world, QGraphicsScene *scene);
    float BLOCK_DENSITY;
    int skillAcontroler;
    int skillCcontroler;
    int skillDcontroler;
    Bird *NewA;
    Bird *NewB;
    Bird *NewC;
    Bird *NewD;
    Bird *NewE;
    Bird *NewF;
    float pos_x,pos_y;
};

#endif // BIRD_H
