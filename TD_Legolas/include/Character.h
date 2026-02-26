#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include "Vec2D.h"

//*****************************************************************************//
// CLASSE QUE DERIVA DE GAMEOBJECT. REPRESENTA ENTIDADES COM VIDA, CAPACIDADE  //
// DE ATAQUE E MOVIMENTAÇÃO NO MUNDO DE JOGO.                                  //
//*****************************************************************************//
class Character : public GameObject {
    protected:
        int hitPoints = 0;      // Quantidade de saúde atual do personagem
        int attackPower = 0;    // Valor de dano causado em ataques
        Vec2d velocity = {0,0}; // Direção atual do movimento (vetor unitário ou relativo)
        Vec2d speed = {0,0};    // Multiplicador de velocidade para os eixos X e Y

    public:
        // Inicializa os atributos de combate e física do personagem
        Character(Vec2d pos, int hp, int atk, Vec2d spd, Vec2d vel);

        // Destrutor virtual para garantir a limpeza de classes derivadas
        virtual ~Character();

        // Devolve o valor de poder de ataque
        int getDamage();

        // Subtrai pontos de vida e desativa o objeto se HP chegar a zero
        void takeDamage(int dmg);

        // Retorna a vida atual do personagem
        int getHP() const;

        // Verifica se o personagem ainda está ativo/vivo
        bool isActive() const;

        // Ajusta a velocidade no eixo X (ex: para movimentos laterais)
        void changeVel(float amount);

        // Atualiza a posição com base nos vetores de velocidade e speed
        void move();
};

#endif // CHARACTER_H
