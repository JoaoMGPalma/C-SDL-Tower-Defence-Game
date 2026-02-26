#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Legolas.h"
#include "Enemy.h"
#include "Castle.h"
#include "Arrow.h"
#include "RandomFunc.h"
#include "DrawText.h"

#define FIRE_RATE 40 // Intervalo de frames entre ataques
//*****************************************************************************//
// CLASSE GESTORA DO JOGO (GAME MANAGER). CONTROLA O CICLO DE VIDA DOS OBJETOS,//
// GESTÃO DE ONDAS DE INIMIGOS, COLISÕES E RENDERIZAÇÃO DOS ASSETS.            //
//*****************************************************************************//
class GameManager {
    private:
        Vec2d enemySpawnPos;        // Posição de spawn dos inimigos
        Vec2d legolasSpawnPos;      // Posição inicial do herói
        Vec2d castlePos;            // Localização do castelo
        Texture arrowTex = nullptr; // Textura dos projéteis
        int arrowDelay = 0;         // Atraso de disparo

        Legolas legolas;            // O jogador
        Castle castle;              // Base a defender

        std::vector<Enemy> enemies; // Lista de inimigos em cena
        std::vector<Arrow> arrows;  // Lista de projéteis ativos

        int currentWave = 0;        // Vaga atual
        int baseEnemyCount = 2;     // Dificuldade base
        int enemyCount;             // Inimigos por vaga
        bool gameOver = false;      // Estado de fim de jogo

    public:
        GameManager();
        ~GameManager();

        // Controlo de lógica e estados
        void updateObjects();       // Atualiza todos os objetos
        //void gameStart();
        void gameEnd();             // Termina a partida
        bool isGameEnd();           // Verifica derrota

        // Gestão de colisões e ondas
        bool checkForCollision(const GameObject& a, const GameObject& b) const; // AABB Collision
        bool isWaveEnd() const;     // Verifica se a vaga acabou
        void spawnWave();           // Cria nova horda
        void objectsCollision();    // Trata interações físicas
        void pushBack(Character& character, int amount); // Aplica recuo

        // Visual e instanciar
        void drawObjects(SDLWindow& window, int mouseX, int mouseY); // Desenha tudo
        void loadAssets(SDLWindow& window); // Carrega imagens
        void spawnArrow(int mouseX, int mouseY); // Dispara projétil
};

#endif // GAME_MANAGER_H
