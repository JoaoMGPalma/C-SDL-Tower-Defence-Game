#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
// LeftBound = 200, 570
// RightBound = 800, 570

class Enemy : public Character {
    protected:
        int reward;

    private:
        int variant=0;

    public:
        Enemy(Vec2d pos, int hp, int atk, int reward, Vec2d spd, Vec2d vel);
        ~Enemy();
        // REQUIRED overrides
        void update() override;
        void draw(SDLWindow& window) override;
        void drawVariantA(SDLWindow& window);
        void drawVariantB(SDLWindow& window);
        SDL_Rect getBounds() const override;
        void drawHpBar(SDLWindow& window);

        Vec2d getPosition();
};


#endif // ENEMY_H

