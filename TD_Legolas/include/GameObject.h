#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vec2D.h"
#include "MiniGfx.h"
//*****************************************************************************//
// CLASSE BASE ABSTRATA PARA OBJETOS DO JOGO. DEFINE A INTERFACE PARA POSIÇÃO, //
// ESTADO DE ATIVAÇÃO E RENDERIZAÇÃO EM ECRÃ.                                  //
//*****************************************************************************//
class GameObject {
    protected:
        Vec2d position;     // Coordenadas bidimensionais (X, Y) do objeto no mundo
        bool active = false; // Flag que indica se o objeto deve ser processado/desenhado

    public:
        // Inicializa a posição e o estado base do objeto
        GameObject(Vec2d pos) : position(pos) {}

        // Garante a destruição segura das classes que herdam de GameObject
        virtual ~GameObject() = default;

        // Método obrigatório para processar a lógica interna e movimento
        virtual void update() = 0;

        // Retorna o estado de atividade (vivo/morto ou visível/invisível)
        bool isActive() { return active; };

        // Alterna a presença do objeto no motor de jogo (útil para reutilização)
        void turnOnOff(bool on_off) { active = on_off; };

        // Método obrigatório para renderizar a textura ou forma na janela SDL
        virtual void draw(SDLWindow& window) = 0;

        // Retorna o retângulo de colisão para interações físicas
        virtual SDL_Rect getBounds() const = 0;

        // Devolve o vetor de posição atual para cálculos externos
        Vec2d getPosition() { return position; };
};

#endif //GAMEOBJECT_H
