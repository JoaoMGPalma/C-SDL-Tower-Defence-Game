#include "Castle.h"
#include "DrawText.h"

int castleMaxHP;

Castle::Castle(Vec2d pos,int hp)
    : Character(
        pos, // required by GameObject
        hp,         // hit points
        0,          // attack power
        {0, 0},     // speed
        {0, 0}      // velocity
    ){castleMaxHP=hp;}

Castle::~Castle(){};

SDL_Rect Castle::getBounds() const{
    int width=100;
    int height=150;
    return SDL_Rect{
        (int)position.x,
        (int)position.y,
        width,
        height
    };
}

void Castle::drawHpBar(SDLWindow& window){
    // Bar size
    const int barWidth  = 100;
    const int barHeight = 15;

    // Position above the castle
    int x = (int)position.x - barWidth / 2;
    int y = (int)position.y+80;   // adjust as needed

    // Background (black)
    window.setColor(SDLColor(0, 0, 0, 255));
    window.drawFilledRect(x, y, barWidth, barHeight);

    // Avoid negative HP
    int hpClamped = std::max(0, this->getHP());
    int maxHpClamped = std::max(1, castleMaxHP);

    // Foreground (red)
    float ratio = (float)hpClamped / (float)maxHpClamped;
    int filledWidth = (int)(barWidth * ratio);

    window.setColor(SDLColor(200, 0, 0, 255));
    window.drawFilledRect(x, y, filledWidth, barHeight);

    SDLColor textColor(255,255,255,255);
    if(this->getHP()==100)
        drawText(window, std::to_string(this->getHP()), x+30, y, 2, textColor);
    else if(this->getHP()<100 && this->getHP()>=10)
        drawText(window, std::to_string(this->getHP()), x+40, y, 2, textColor);
    else if(this->getHP()<10)
        drawText(window, std::to_string(this->getHP()), x+48, y, 2, textColor);
}
