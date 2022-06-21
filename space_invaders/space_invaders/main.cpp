#include <iostream>
#include <SFML/Graphics.hpp>

#include <SFML/OpenGL.hpp>
#include "classes_and_functions.h"
#include <SFML/Audio.hpp>

bool Enemy::move_side = true;
sf::Sprite Fire_enemy::graphics;
sf::Sprite Stone_enemy::graphics_hp1;
sf::Sprite Stone_enemy::graphics_hp2;
sf::Sprite Stone_enemy::graphics_hp3;
sf::Sprite Toxic_enemy::graphics;
sf::Sprite Player::graphics;
sf::Sprite Player_projectile::graphics;
sf::Sprite Fire_projectile::graphics;
sf::Sprite Stone_projectile::graphics;
sf::Sprite Toxic_projectile::graphics;
sf::Sprite Health_bar::graphics;
sf::Sound audioManager::shot;
sf::Sound audioManager::hpLoss;
sf::Sound audioManager::victory;
sf::Sound audioManager::game_over;
sf::Music audioManager::mainThemeLowPass;
sf::Music audioManager::mainTheme;


int main() {
    srand(time(nullptr));

    ///setting up the window
    sf::RenderWindow win(sf::VideoMode(1200, 1400), "Space Invaders");

    win.setMouseCursorVisible(false);

    sf::Image forest;
    forest.loadFromFile("graphics\\forest.jpg");
    sf::Texture texture_1;
    texture_1.loadFromImage(forest);
    sf::Sprite background;
    background.setTexture(texture_1);
    background.setPosition(0, -200);

    sf::Font font;
    font.loadFromFile("dakota\\Dakota-Regular.ttf");


    Manager manager;
    manager.loadGraphics();
    manager.fill_enemies();
    manager.player = new Player;
    

    audioManager AudioManager;
    AudioManager.loadAudio();
    
    audioManager::mainThemeLowPass.play();
    audioManager::mainThemeLowPass.setLoop(true);

    while (win.isOpen()) {

        manager.eventManager(win);

        win.clear();

        win.draw(background);

        switch (manager.state) {
        case 0: {
            display_start_screen(win, font);
            break;
        }
        case 1: {            
            manager.enemy_move_timer->Tick();
            manager.player_shot_timer->Tick();

            manager.checkPlayerCollisions();
            manager.checkEnemyCollisions();
            manager.manageEnemies();

            manager.enemyMoveManager();

            manager.showEnemies(win);

            manager.playerProjectilesManager(win);

            manager.enemyProjectilesManager(win);

            manager.player->update(win);
            manager.player->show(win);
            manager.player->mHealthBar.show(win);

            manager.isGameOver();

            break;
        }
        case 2: {
            display_win_screen(win, font);
            break;
        }
        case 3:
            display_lose_screen(win, font);
            break;
        }
        win.display();
    }
}
