#include "Character.h"

Character::Character(Vec2d pos, int hp, int atk, Vec2d spd, Vec2d vel)
    : GameObject(pos),
      hitPoints(hp),
      attackPower(atk),
      speed(spd),
      velocity(vel)
{}

Character::~Character() {}

void Character::takeDamage(int dmg) {
    hitPoints -= dmg;
    if (hitPoints <= 0)
        this->active = false;
}

int Character::getHP() const {
    return hitPoints;
}

void Character::move() {
    position.x += velocity.x * speed.x;
    position.y += velocity.y * speed.y;
}

bool Character::isActive() const{
    return active;
}

int Character::getDamage(){
    return attackPower;
}

void Character::changeVel(float amount){
    if(amount==0){
        velocity.x=0;
    }
    velocity.x += amount;
}
