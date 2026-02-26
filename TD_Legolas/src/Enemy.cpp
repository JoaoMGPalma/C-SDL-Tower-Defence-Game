#include "RandomFunc.h"
#include "Enemy.h"

int enemyMaxHp;

Enemy::Enemy(Vec2d pos, int hp, int atk, int reward, Vec2d spd, Vec2d vel)
    :Character(pos, hp, atk, spd, vel),
     reward(reward)
{
    variant=randomInt(0,1);
    enemyMaxHp=hp;
}

Enemy::~Enemy(){};

void Enemy::update() {
    if(velocity.x>-1)
        velocity.x--;
    move();
}

SDL_Rect Enemy::getBounds() const {
    int height;
    int width;
    int x_pos;
    int y_pos;
    switch(variant){
        case 0:
            height = 50;
            width = 35;
            x_pos = position.x-10;
            y_pos = position.y-16;
            break;
        case 1:
            height = 76;
            width = 38;
            x_pos = position.x-6;
            y_pos = position.y-18;
            break;
    }

    return SDL_Rect{
        (int)x_pos,
        (int)y_pos,
        width,
        height
    };
}





void Enemy::draw(SDLWindow& window){
    switch(variant){
        case 0:
            drawVariantA(window);
            break;
        case 1:
            drawVariantB(window);
            break;
    }
}

void Enemy::drawVariantA(SDLWindow& window) {
    int x = (int)position.x;
    int y = (int)position.y;

    // COLORS
    SDLColor skin(20, 90, 20, 255);
    SDLColor armor(110, 60, 20, 255);
    SDLColor eyes(0, 0, 0, 255);
    SDLColor mace(180, 180, 180, 255);

    // HEAD
    window.setColor(skin);
    window.drawFilledRect(x + 2, y - 12, 16, 12);

    // HELMET
    window.setColor(SDLColor(70, 70, 70, 255));
    window.drawFilledRect(x + 2, y - 16, 16, 6);
    // EYES
    window.setColor(eyes);
    window.drawFilledRect(x + 6,  y - 9, 3, 3);
    window.drawFilledRect(x + 11, y - 9, 3, 3);

    // BODY ARMOR
    window.setColor(armor);
    window.drawFilledRect(x, y, 20, 20);

    // BELT
    window.setColor(SDLColor(60, 30, 10, 255));
    window.drawFilledRect(x, y + 18, 20, 4);

    // LOWER ARMOR
    window.setColor(armor);
    window.drawFilledRect(x, y + 20, 20, 12);

    // ARMS (skin)
    window.setColor(skin);
    window.drawFilledRect(x - 6,  y + 4, 6, 16);
    window.drawFilledRect(x + 20, y + 4, 6, 16);

    // LEGS (armor)
    window.setColor(armor);
    window.drawFilledRect(x + 2,  y + 28, 6, 14);
    window.drawFilledRect(x + 12, y + 28, 6, 14);

    // SHIELD (dark brown rectangle)
    window.setColor(SDLColor(80, 40, 10, 255));
    window.drawFilledRect(x - 10, y + 6, 12, 20);

    // HAMMER
    window.setColor(mace);
    window.drawFilledRect(x + 10, y + 12, 12, 4);
    window.drawFilledRect(x + 5, y + 12, 10, 10);

    drawHpBar(window);
}
void Enemy::drawVariantB(SDLWindow& window) {
    int x = (int)position.x;
    int y = (int)position.y;

    int yOffset = -15; // now shifted 10px upward

    // COLORS
    SDLColor skin(20, 90, 20, 255);
    SDLColor armor(110, 60, 20, 255);
    SDLColor eyes(0, 0, 0, 255);
    SDLColor steel(180, 180, 180, 255);

    // --- HEAD ---
    window.setColor(skin);
    window.drawFilledRect(x + 2, y - 14 + yOffset, 16, 14);

    // --- HELMET ---
    window.setColor(SDLColor(70, 70, 70, 255));
    window.drawFilledRect(x + 2, y - 18 + yOffset, 16, 6);
    window.drawFilledRect(x + 2, y - 14 + yOffset, 16, 4);

    // --- EYES ---
    window.setColor(eyes);
    window.drawFilledRect(x + 6,  y - 11 + yOffset, 3, 3);
    window.drawFilledRect(x + 11, y - 11 + yOffset, 3, 3);

    // --- BODY ARMOR ---
    window.setColor(armor);
    window.drawFilledRect(x, y + yOffset, 20, 24);

    // --- BELT ---
    window.setColor(SDLColor(60, 30, 10, 255));
    window.drawFilledRect(x, y + 22 + yOffset, 20, 4);

    // --- LOWER ARMOR ---
    window.setColor(armor);
    window.drawFilledRect(x, y + 24 + yOffset, 20, 16);

    // --- ARMS ---
    window.setColor(skin);
    window.drawFilledRect(x - 6,  y + 6  + yOffset, 6, 18);
    window.drawFilledRect(x + 20, y + 6  + yOffset, 6, 18);

    // --- LEGS ---
    window.setColor(armor);
    window.drawFilledRect(x + 2,  y + 40 + yOffset, 6, 18);
    window.drawFilledRect(x + 12, y + 40 + yOffset, 6, 18);

    // --- BIG SWORD ---
    window.setColor(steel);

    // handle
    window.drawFilledRect(x + 22, y + 10 + yOffset, 4, 14);

    // blade
    window.drawFilledRect(x + 26, y - 10 + yOffset, 6, 40);

    drawHpBar(window);
}

void Enemy::drawHpBar(SDLWindow& window){
    const int barWidth=50;
    const int barHeight=5;

    int x = (int)this->getBounds().x-(barWidth/2)+20;
    int y = (int)this->getBounds().y-(this->getBounds().h/3);


    window.setColor(SDLColor(0, 0, 0, 255));
    window.drawFilledRect(x, y, barWidth, barHeight);


    int hpClamped = std::max(0, this->getHP());
    int maxHpClamped = std::max(1, enemyMaxHp);


    float ratio = (float)hpClamped / (float)maxHpClamped;
    int filledWidth = (int)(barWidth * ratio);

    window.setColor(SDLColor(200, 0, 0, 255));
    window.drawFilledRect(x, y, filledWidth, barHeight);
}



Vec2d Enemy::getPosition(){
    return position;
}
