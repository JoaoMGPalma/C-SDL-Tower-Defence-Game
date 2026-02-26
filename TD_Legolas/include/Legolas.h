#ifndef LEGOLAS_H
#define LEGOLAS_H

#include "Vec2D.h"
#include "Character.h"
// LeftBound = 85, 325
// RightBound = 185, 325

//*****************************************************************************//
// CLASSE QUE REPRESENTA O JOGADOR (LEGOLAS). GERE O MOVIMENTO RESTRITO AO      //
// CENÁRIO, A RENDERIZAÇÃO DO CORPO E O COMPORTAMENTO DO ARCO.                 //
//*****************************************************************************//
class Legolas : public Character {
    private:
        static Legolas* legolas;    // Instância única (Singleton pattern)
        Texture bowTexture = nullptr; // Textura do arco
        float leftBound = 85;       // Limite de movimento à esquerda
        float rightBound = 185;     // Limite de movimento à direita

    public:
        Legolas(Vec2d pos, int hp, int atk, Vec2d spd, Vec2d vel);
        ~Legolas();

        static Legolas &getLegolas(Vec2d pos); // Acesso à instância única

        void update() override;                // Atualiza lógica e movimento
        void draw(SDLWindow& window) override; // Renderização padrão

        // Sobrecarga para renderização com mira no rato
        void draw(SDLWindow& window, int mouseX, int mouseY);

        void drawBody(SDLWindow& window);      // Desenha as primitivas do corpo
        void drawBow(SDLWindow& window, int mouseX, int mouseY); // Desenha o arco

        void loadAssets(SDLWindow& window);    // Carrega texturas do herói
        void limitMovement();                  // Restringe posição aos limites

        SDL_Rect getBounds() const override;   // Retorna área de colisão
};

#endif // LEGOLAS_H
