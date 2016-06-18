#ifndef STICK_H
#define STICK_H


#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define STICK_DENSITY 20.0f
#define STICK_FRICTION 0.2f
#define STICK_RESTITUTION 0.5f

class Stick : public GameItem
{
public:
    Stick(float x, float y, float w, float d, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);

};
#endif // STICK_H
