#include "GameManager.h"
//*****************************************************************************//
// IMPLEMENTAÇÃO DO GESTOR DE JOGO. CONTROLA O FLUXO DE ENTIDADES, COLISÕES,   //
// CARREGAMENTO DE ASSETS E GESTÃO DE VAGAS DE INIMIGOS (WAVES).              //
//*****************************************************************************//

GameManager::GameManager()
    : enemySpawnPos(800, 550),
      legolasSpawnPos(150, 310),
      castlePos(100, 500),
      legolas(legolasSpawnPos, 10, 5, Vec2d(0.7, 1), Vec2d(0, 0)),
      castle(castlePos, 100)
{};

GameManager::~GameManager(){};

void GameManager::loadAssets(SDLWindow& window) {
    arrowTex = window.readFile("assets/arrowSprite.png"); // Textura do projétil
    legolas.loadAssets(window);
}

bool GameManager::checkForCollision(const GameObject& a, const GameObject& b) const {
    SDL_Rect A = a.getBounds();
    SDL_Rect B = b.getBounds();

    // Verificação de sobreposição AABB
    return (A.x < B.x + B.w &&
            A.x + A.w > B.x &&
            A.y < B.y + B.h &&
            A.y + A.h > B.y);
}

void GameManager::updateObjects() {
    legolas.update();

    // Atualiza inimigos ativos
    for (Enemy& enemy : enemies)
        if(enemy.isActive()) enemy.update();

    // Atualiza projéteis ativos
    for (Arrow& arrow : arrows)
        if(arrow.isActive()) arrow.update();

    objectsCollision();
    gameEnd();
};

bool GameManager::isWaveEnd() const {
    for (const Enemy& e : enemies) {
        if (e.isActive()) return false;
    }
    return true;
}

void GameManager::spawnWave() {
    currentWave++;
    enemyCount = baseEnemyCount + currentWave;

    for (int i = 0; i < enemyCount; i++) {
        enemies.push_back(Enemy(
            enemySpawnPos,
            50, 10, 5, // HP, Atk, Reward
            Vec2d(randomFloat(0.255, 0.455), 1.0),
            Vec2d(-1, 0.0)
        ));
        enemies.back().turnOnOff(true);
    }
}

void GameManager::drawObjects(SDLWindow& window, int mouseX, int mouseY) {
    // Controlo de movimento do jogador
    legolas.changeVel(0);
    if (window.keyDown(SDLKey::A)) legolas.changeVel(-0.8);
    if (window.keyDown(SDLKey::D)) legolas.changeVel(+0.8);
    legolas.draw(window, mouseX, mouseY);

    // Gestão de disparo e cooldown
    if(window.keyDown(SDLKey::SPACE) && arrowDelay == 0) {
        spawnArrow(mouseX, mouseY);
        arrowDelay += FIRE_RATE;
    }
    if(arrowDelay > 0) arrowDelay--;

    // Renderização de projéteis e inimigos
    for(Arrow& arrow : arrows)
        if(arrow.isActive()) arrow.draw(window, arrowTex);

    for(Enemy& enemy : enemies)
        if(enemy.isActive()) enemy.draw(window);

    castle.drawHpBar(window);

    SDLColor textColor = SDLColor(255, 255, 255, 255);
    drawText(window, "Wave " + std::to_string(this->currentWave), 325, 17, 4, textColor);
}

void GameManager::pushBack(Character& character, int amount) {
    character.changeVel(amount);
}

void GameManager::objectsCollision() {
    // Colisão Projétil vs Inimigo
    for(Arrow& arrow : arrows)
        for(Enemy& enemy : enemies)
            if(checkForCollision(arrow, enemy) && arrow.dealDamageState() && enemy.isActive()) {
                enemy.takeDamage(arrow.getDamage());
                pushBack(enemy, 5);
                arrow.turnOnOff(false);
                arrow.setDealDamage(false);
            }

    // Colisão Castelo vs Inimigo
    for (Enemy& enemy : enemies) {
        if(checkForCollision(castle, enemy) && enemy.isActive()) {
            castle.takeDamage(enemy.getDamage());
            pushBack(enemy, randomInt(10, 25));
            gameEnd();
        }
    }
}

// Retorna o estado atual do jogo
bool GameManager::isGameEnd() {
    return gameOver;
}

// Verifica se o castelo foi destruído para terminar o jogo
void GameManager::gameEnd() {
    if(castle.getHP() <= 0) {
        gameOver = true;
    }
}

// Instancia um novo projétil com base na posição do rato
void GameManager::spawnArrow(int mouseX, int mouseY) {
    // Define o ponto de origem (arco) relativo ao jogador
    Vec2d bowPos(legolas.getPosition().x - 10, legolas.getPosition().y - 6);

    // Calcula o vetor de direção para o alvo
    Vec2d dir(mouseX - bowPos.x, mouseY - bowPos.y);

    // Cria e ativa o projétil
    Arrow arrow(bowPos, 10, dir);
    arrow.setDealDamage(true);
    arrow.turnOnOff(true);
    arrows.push_back(arrow);
}
