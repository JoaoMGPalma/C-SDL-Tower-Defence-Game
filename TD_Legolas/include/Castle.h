#ifndef CASTLE_H
#define CASTLE_H

#include "Character.h"
#include "Vec2D.h"

//*****************************************************************************//
// CLASSE QUE DERIVA DE CHARACTER. REPRESENTA A ESTRUTURA PRINCIPAL (CASTELO)  //
// QUE POSSUI PONTOS DE VIDA E DEVE SER DEFENDIDA PELO JOGADOR                 //
//*****************************************************************************//
class Castle : public Character {

    public:
    // Inicializa o castelo com a sua posição e total de pontos de vida
    Castle(Vec2d pos, int hp);

    // Destrutor para limpeza de recursos do castelo
    ~Castle() override;

    // Implementação vazia: o castelo é desenhado por componentes específicos
    void draw(SDLWindow& window) override {};

    // Renderiza a barra de saúde visual sobre o castelo na interface
    void drawHpBar(SDLWindow& window);

    // Implementação vazia: o castelo não possui lógica de movimento ou IA
    void update() override {};

    // Procura os limites do Castelo para efeitos de collision check
    SDL_Rect getBounds() const override;
};

#endif // CASTLE_H
