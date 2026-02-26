#include "Arrow.h"

Arrow::Arrow(Vec2d pos, int atk, Vec2d vel)
    :Character(pos,
                0,
                atk,
                {0.01,0.01},
                vel)
{};

Arrow::~Arrow(){};
void Arrow::draw(SDLWindow& window){};

void Arrow::draw(SDLWindow& window, Texture arrowTexture){
    float angleDeg = atan2(velocity.y, velocity.x) * 180.0f / M_PI;
    window.renderTexture(arrowTexture, position.x, position.y, 255, angleDeg);
}

void Arrow::update() {
    if(active){
        move();
    }

    if (position.y > 570){
        speed={0,0};
        this->setDealDamage(false);
    }


    if (position.x<0||position.x>810||position.y<0)
        active=false;
}

SDL_Rect Arrow::getBounds() const {
    return SDL_Rect{
        position.x,
        position.y,
        40,
        30
    };
}



