#ifndef ARROW_H
#define ARROW_H

#include "Character.h"

//*****************************************************************************//
// CLASSE QUE DERIVA DE CHARACTER. REPRESENTA UM PROJÉTIL (FLECHA) QUE SE      //
// DESLOCA NO ESPAÇO E INTERAGE COM OUTRAS ENTIDADES ATRAVÉS DE COLISÕES       //
//*****************************************************************************//
class Arrow : public Character {
    private:
        bool canDealDamage;
    public:
        // Inicializa a flecha com posição, poder de ataque e vetor de direção
        Arrow(Vec2d pos, int atk, Vec2d vel);

        // Destrutor para limpar recursos específicos da flecha
        ~Arrow();

        // Atualiza a lógica da flecha (movimento e tempo de vida)
        void update() override;

        // Renderiza a flecha na janela utilizando a textura interna
        void draw(SDLWindow& window) override;

        // Devolve a caixa de colisão da flecha para deteção de impactos
        SDL_Rect getBounds() const override;

        // Sobrecarga de desenho que permite passar uma textura externa
        void draw(SDLWindow& window, Texture arrowTexture);

        // Retorna o estado atual da capacidade de causar dano
        bool dealDamageState() { return canDealDamage; }

        // Define se a flecha está autorizada a causar dano
        void setDealDamage(bool isAllowed) { canDealDamage = isAllowed; }
};

#endif // ARROW_H

