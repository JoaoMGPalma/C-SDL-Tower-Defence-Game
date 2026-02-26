#include "Legolas.h"
//*****************************************************************************//
// IMPLEMENTAÇÃO DA CLASSE LEGOLAS. GERE A RENDERIZAÇÃO DO CORPO POR           //
// PRIMITIVAS GRÁFICAS E O ARCO ROTATIVO QUE SEGUE A POSIÇÃO DO RATO.          //
//*****************************************************************************//

Legolas::Legolas(Vec2d pos, int hp, int atk, Vec2d spd, Vec2d vel)
    : Character(pos, hp, atk, spd, vel)
{};

Legolas::~Legolas(){};

SDL_Rect Legolas::getBounds() const {
    return {(int)position.x, (int)position.y, 20, 42}; // Define área de colisão
};

void Legolas::draw(SDLWindow& window) {
    drawBody(window); // Implementação obrigatória da classe base
};

void Legolas::loadAssets(SDLWindow& window) {
    bowTexture = window.readFile("assets/bowSprite.png"); // Carrega textura
}

void Legolas::limitMovement() {
    // Restrições de movimento lateral
    if(position.x <= leftBound)
        velocity.x += 1;
    if(position.x >= rightBound)
        velocity.x -= 1;
}

void Legolas::update() {
    limitMovement();
    move();
};

void Legolas::drawBody(SDLWindow& window) {
    int x = (int)position.x;
    int y = (int)position.y;

    // Cores do herói
    SDLColor skin(255, 220, 150, 255);
    SDLColor hair(240, 220, 40, 255);
    SDLColor tunic(200, 200, 255, 255);
    SDLColor trim(80, 120, 255, 255);
    SDLColor eyes(0, 0, 0, 255);

    // Cabeça
    window.setColor(skin);
    window.drawFilledRect(x + 2, y - 12, 16, 12);

    // Cabelo
    window.setColor(hair);
    window.drawFilledRect(x + 2,  y - 16, 16, 6);
    window.drawFilledRect(x + 1,  y - 12, 3, 12);
    window.drawFilledRect(x + 16, y - 12, 3, 12);

    // Olhos
    window.setColor(eyes);
    window.drawFilledRect(x + 6,  y - 9, 3, 3);
    window.drawFilledRect(x + 11, y - 9, 3, 3);

    // Túnica
    window.setColor(tunic);
    window.drawFilledRect(x, y, 20, 20);

    // Detalhe azul
    window.setColor(trim);
    window.drawFilledRect(x, y + 18, 20, 4);

    // Robe/Pernas superiores
    window.setColor(tunic);
    window.drawFilledRect(x, y + 20, 20, 12);

    // Braços
    window.setColor(skin);
    window.drawFilledRect(x - 6,  y + 4, 6, 16);
    window.drawFilledRect(x + 20, y + 4, 6, 16);

    // Pernas inferiores
    window.setColor(trim);
    window.drawFilledRect(x + 2,  y + 28, 6, 14);
    window.drawFilledRect(x + 12, y + 28, 6, 14);
}

void Legolas::drawBow(SDLWindow& window, int mouseX, int mouseY) {
    if (!bowTexture) return;

    // Lógica de rotação para o rato
    float dx = mouseX - position.x;
    float dy = mouseY - position.y;
    float angleRad = atan2(dy, dx);
    float angleDeg = angleRad * (180.0f / M_PI);

    int bowX = (int)position.x - 10;
    int bowY = (int)position.y - 6;

    window.renderTexture(bowTexture, bowX, bowY, 255, angleDeg);
}

void Legolas::draw(SDLWindow& window, int mouseX, int mouseY) {
    drawBody(window);               // Renderiza corpo
    drawBow(window, mouseX, mouseY); // Renderiza arco
}
