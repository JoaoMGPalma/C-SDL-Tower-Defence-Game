#ifndef MOVEOBJECT_H
#define MOVEOBJECT_H

lass MovableObject {
    protected:
        Vec2d velocity;
        Vec2d speed;

    public:
        MovableObject(Vec2d spd = {0,0}, Vec2d vel = {0,0})
                                : speed(spd), velocity(vel){}

    void move(Vec2d& position) {
        position.x += velocity.x * speed.x;
        position.y += velocity.y * speed.y;
    }
};

#endif // MOVEOBJECT_H
