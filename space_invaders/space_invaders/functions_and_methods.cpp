#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "classes_and_functions.h"

///Parameterized constructor for Entity class, given x, y integers creates Entity witch at x, y location
Entity::Entity(int x, int y) {
    position.first = x;
    position.second = y;
}
///Method responsible for side enemies movement
///
///Depending on boolean move_side variable x-position of enemy is enlarged, or decreased by 50 pixels
void Enemy::move() {
    if (move_side)
        position.first += 50;
    else
        position.first -= 50;
}
///Method responsible for moving down enemies
///
///While called y-position of enemy is incremented by 70 pixels
void Enemy::move_down() {
    position.second += 70;
}
///Method returning y value of position
int Enemy::get_y_position() {
    return position.second;
}
///Method checking if enemy is alive
///
/// \return true - if enemy's health is larger than zero and false - if not
bool Enemy::isAlive() {
    return (health > 0);
}

///Static Method used to change direction of movement of all enemies based of boolean variable move_side
void Enemy::change_move_direction() {
    if (move_side)
        move_side = false;
    else
        move_side = true;
}
///Method providing shot feature for fire enemy
///
///If both calls of Method my_random(int) returns true fire projectile is added to a given vector.
///Probability of emplacement is set to 0,001%.
void Fire_enemy::shot(std::vector<Enemy_projectile*>& e_projectiles) {
    if (my_random(1) && my_random(1))
        e_projectiles.emplace_back(new Fire_projectile(position.first + 55, position.second + 20));
}
///Method displaying fire enemy sprite at object location in given window
void Fire_enemy::show(sf::RenderWindow& win) {
    graphics.setPosition(position.first, position.second);
    graphics.setScale(0.3, 0.3);
    win.draw(graphics);
}

///Method providing shot feature for stone enemy
///
///If both calls of Method my_random(int) returns true stone projectile is added to a given vector.
///Probability of emplacement is set to 0,001%.
void Stone_enemy::shot(std::vector<Enemy_projectile*>& e_projectiles) {
    if (my_random(1) && my_random(1))
        e_projectiles.emplace_back(new Stone_projectile(position.first + 55, position.second + 20));
}
///Method displaying stone enemy sprite at object location in given window
///
///Depending on health value of enemy different texture is shown
void Stone_enemy::show(sf::RenderWindow& win) {
    if (health == 3) {
        graphics_hp3.setPosition(position.first, position.second);
        graphics_hp3.setScale(0.28, 0.28);
        win.draw(graphics_hp3);
    }
    else if (health == 2) {
        graphics_hp2.setPosition(position.first, position.second);
        graphics_hp2.setScale(0.28, 0.28);
        win.draw(graphics_hp2);
    }
    else if (health == 1) {
        graphics_hp1.setPosition(position.first, position.second);
        graphics_hp1.setScale(0.28, 0.28);
        win.draw(graphics_hp1);
    }
}

///Method displaying toxic enemy sprite at object location in given window
void Toxic_enemy::show(sf::RenderWindow& win) {
    graphics.setPosition(position.first, position.second);
    graphics.setScale(0.26, 0.26);
    win.draw(graphics);
}
///Method providing shot feature for stone enemy
///
///If both calls of Method my_random(int) returns true stone projectile is added to a given vector.
///Probability of emplacement is set to 0,015%.
void Toxic_enemy::shot(std::vector<Enemy_projectile*>& e_bullet) {
    if (my_random(3) && my_random(5))
        e_bullet.emplace_back(new Toxic_projectile(position.first + 55, position.second + 20));
}

///Method displaying player sprite at object location in given window
void Player::show(sf::RenderWindow& win) {
    graphics.setPosition(position.first, position.second);
    graphics.setScale(0.3, 0.3);
    win.draw(graphics);
}

///Method updating player x location to current mouse x location
void Player::update(sf::RenderWindow& win) {
    int tmp = sf::Mouse::getPosition(win).x;
    if (tmp > 1040)
        position.first = 1040;
    else if (tmp < 0)
        position.first = 0;
    else
        position.first = tmp;
}
///Every time when called Player_projectile pointer is added to a given vector
void Player::shot(std::vector<Player_projectile*>& projectiles) {
    audioManager::play_shot_sound();
    projectiles.emplace_back(new Player_projectile(position.first + 70, position.second));
}
///Method checking if player is alive
///
/// \return true - true - if enemy's health is larger than zero and false - if not
bool Player::isAlive()const {
    return health > 0;
}
///Method setting Health_bar::player pointer
void Health_bar::assignToPlayer(Player* ptr) {
    player = ptr;
}
/// <summary>
/// Fucntion showing 1-3 hearts depending on player's hp
/// </summary>
/// <param name="win"></param>
void Health_bar::show(sf::RenderWindow& win) {
    unsigned  int hp = player->health;
    if (hp >= 1) {
        graphics.setPosition(position.first, position.second);
        graphics.setScale(0.2, 0.2);
        win.draw(graphics);
        if (hp >= 2) {
            graphics.setPosition(position.first + 70, position.second);
            win.draw(graphics);
            if (hp >= 3) {
                graphics.setPosition(position.first + 140, position.second);
                win.draw(graphics);
            }
        }
    }
}

/// <summary>
/// Method checking if projectile is out of map.
/// </summary>
/// <returns>True when projectile is out of map and false if it is not.</returns>
bool Projectile::isOutOfMap() {
    return (position.second > 1500 || position.second < -100);
}

/// <summary>
/// Method displaying projectile of a player.
/// </summary>
/// <param name="win"></param>
void Player_projectile::show(sf::RenderWindow& win) {
    graphics.setPosition(position.first, position.second);
    graphics.setScale(0.5, 0.5);
    win.draw(graphics);
}

/// <summary>
/// Method decreasing y-position of player projectile.
/// </summary>
void Player_projectile::move() {
    position.second -= 2;
}

/// <summary>
/// Method increasing y-position of enemy projectile.
/// </summary>
void Enemy_projectile::move() {
    position.second++;
}
/// <summary>
/// Method displaying fire enemy's texture at it's position
/// </summary>
/// <param name="win"></param>
void Fire_projectile::show(sf::RenderWindow& win) {
    graphics.setPosition(position.first, position.second);
    graphics.setScale(0.25, 0.25);
    win.draw(graphics);
}
/// <summary>
/// Method displaying stone enemy's texture at it's position
/// </summary>
/// <param name="win"></param>
void Stone_projectile::show(sf::RenderWindow& win) {
    graphics.setPosition(position.first, position.second);
    graphics.setScale(0.5, 0.5);
    win.draw(graphics);
}
/// <summary>
/// Method displaying toxic enemy's texture at it's position
/// </summary>
/// <param name="win"></param>
void Toxic_projectile::show(sf::RenderWindow& win) {
    graphics.setPosition(position.first, position.second);
    graphics.setScale(0.2, 0.2);
    win.draw(graphics);
}
/// <summary>
/// Method wchih checks if given Player_projectile collides with given Enemy
/// </summary>
void Manager::checkEnemyCollisions() {
    for (int i = enemies.size() - 1; i >= 0; i--) {
        for (int j = player_projectiles.size() - 1; j >= 0; j--) {
            int bullet_x = player_projectiles[j]->position.first;
            int bullet_y = player_projectiles[j]->position.second;
            int enemy_x = enemies[i]->position.first;
            int enemy_y = enemies[i]->position.second;
            bool isCollidingX = bullet_x > enemy_x - 30 && bullet_x < enemy_x + 100;
            bool isCollidingY = bullet_y < enemy_y + 100 && bullet_y > enemy_y;
            if (isCollidingX && isCollidingY) {
                player_projectiles[j]->position.second = 2000;
                enemies[i]->health--;
            }
        }
    }
}
/// <summary>
/// Method wchih checks if given Enemy_projectile collides with Player
/// </summary>
void Manager::checkPlayerCollisions() {
    for (int i = enemy_projectiles.size() - 1; i >= 0; i--) {
        int bullet_x = enemy_projectiles[i]->position.first;
        int bullet_y = enemy_projectiles[i]->position.second;
        int player_x = player->position.first;
        int player_y = player->position.second;
        bool isCollidingX = bullet_x > player_x - 20 && bullet_x < player_x + 120;
        bool isCollidingY = bullet_y < player_y + 50 && bullet_y > player_y - 100;
        if (isCollidingX && isCollidingY) {
            enemy_projectiles[i]->position.second = 2000;
            player->health--;
            audioManager::play_hpLoss_sound();
       
        }
    }
}
/// <summary>
/// Function responsible for randomless in project.
/// </summary>
/// <param name="P"></param>
/// <returns>True with given probability P</returns>
bool my_random(int P) {
    int tmp = rand() % 100;
    return tmp < P;
}
/// <summary>
/// Method which loads graphics for enemies, projectiles and player.
/// </summary>
void Manager::loadGraphics() {

    static sf::Texture fire;
    fire.loadFromFile("graphics\\fire.png");
    Fire_enemy::graphics.setTexture(fire);

    static sf::Texture stone_hp1;
    stone_hp1.loadFromFile("graphics\\rock_hp1.png");
    Stone_enemy::graphics_hp1.setTexture(stone_hp1);

    static sf::Texture stone_hp2;
    stone_hp2.loadFromFile("graphics\\rock_hp2.png");
    Stone_enemy::graphics_hp2.setTexture(stone_hp2);

    static sf::Texture stone_hp3;
    stone_hp3.loadFromFile("graphics\\rock_hp3.png");
    Stone_enemy::graphics_hp3.setTexture(stone_hp3);

    static sf::Texture toxic;
    toxic.loadFromFile("graphics\\toxic.png");
    Toxic_enemy::graphics.setTexture(toxic);

    static sf::Texture ghost;
    ghost.loadFromFile("graphics\\ghost.png");
    Player::graphics.setTexture(ghost);

    static sf::Texture plant;
    plant.loadFromFile("graphics\\plant.png");
    Player_projectile::graphics.setTexture(plant);

    static sf::Texture rock;
    rock.loadFromFile("graphics\\stone_p.png");
    Stone_projectile::graphics.setTexture(rock);

    static sf::Texture flame;
    flame.loadFromFile("graphics\\fire_p.png");
    Fire_projectile::graphics.setTexture(flame);

    static sf::Texture chemical;
    chemical.loadFromFile("graphics\\toxic_p.png");
    Toxic_projectile::graphics.setTexture(chemical);

    static sf::Texture heart;
    heart.loadFromFile("graphics\\heart.png");
    Health_bar::graphics.setTexture(heart);
}
/// <summary>
/// This method fills Manager::enemies vector witch enemies of random types.
/// </summary>
void Manager::fill_enemies() {

    enemies.clear();

    enemies.reserve(22);

    for (int i = 0; i < 5; i++) {
        if (my_random(50))
            enemies.emplace_back(new Fire_enemy(100 + 160 * i, 100));
        else
            enemies.emplace_back(new Toxic_enemy(100 + 160 * i, 100));
    }
    for (int i = 0; i < 6; i++) {
        if (my_random(70))
            enemies.emplace_back(new Fire_enemy(20 + 160 * i, 250));
        else if (my_random(30))
            enemies.emplace_back(new Stone_enemy(20 + 160 * i, 250));
        else
            enemies.push_back(new Toxic_enemy(20 + 160 * i, 250));
    }
    for (int i = 0; i < 5; i++) {
        if (my_random(70))
            enemies.emplace_back(new Fire_enemy(100 + 160 * i, 400));
        else if (my_random(50))
            enemies.emplace_back(new Stone_enemy(100 + 160 * i, 400));
        else
            enemies.emplace_back(new Toxic_enemy(100 + 160 * i, 400));
    }
    for (int i = 0; i < 6; i++) {
        if (my_random(700))
            enemies.emplace_back(new Stone_enemy(20 + 160 * i, 550));
        else
            enemies.emplace_back(new Fire_enemy(20 + 160 * i, 550));
    }
}
/// <summary>
/// Method setting key parameters to starting values to reset the game.
/// </summary>
void Manager::resetGame() {
    fill_enemies();
    Enemy::move_side = true;
    move_count = 0;
    enemy_move_timer->reset();
    player->health = 3;
}
/// <summary>
/// Function displaying start screen.
/// </summary>
/// <param name="win"></param>
/// <param name="font"></param>
void display_start_screen(sf::RenderWindow& win, sf::Font font) {
    sf::Text text1("Forest Invaders", font);
    text1.setCharacterSize(180);
    text1.setPosition(100, 120);
    text1.setStyle(sf::Text::Bold);
    text1.setFillColor(sf::Color::Black);

    sf::Text text2("press Enter to start", font);
    text2.setCharacterSize(90);
    text2.setPosition(250, 375);
    text2.setStyle(sf::Text::Bold);
    text2.setFillColor(sf::Color::Black);

    win.draw(text1);
    win.draw(text2);
}
/// <summary>
/// Function displaying win screen.
/// </summary>
/// <param name="win"></param>
/// <param name="font"></param>
void display_win_screen(sf::RenderWindow& win, sf::Font font) {
    sf::Text text("You   Won", font);
    text.setCharacterSize(180);
    text.setPosition(320, 300);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Black);

    sf::Text text1("press Enter to restart", font);
    text1.setCharacterSize(90);
    text1.setPosition(250, 500);
    text1.setStyle(sf::Text::Bold);
    text1.setFillColor(sf::Color::Black);

    win.draw(text);
    win.draw(text1);
}
/// <summary>
/// Function displaying lose screen.
/// </summary>
/// <param name="win"></param>
/// <param name="font"></param>
void display_lose_screen(sf::RenderWindow& win, sf::Font font) {
    sf::Text text("Game Over", font);
    text.setCharacterSize(180);
    text.setPosition(250, 300);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Black);

    sf::Text text1("press Enter to try again", font);
    text1.setCharacterSize(90);
    text1.setPosition(200, 500);
    text1.setStyle(sf::Text::Bold);
    text1.setFillColor(sf::Color::Black);

    win.draw(text);
    win.draw(text1);
}
/// <summary>
/// Method which take certain actions when different events are occuring 
/// </summary>
/// <param name="win"></param>
void Manager::eventManager(sf::RenderWindow& win) {
    while (win.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            win.close();
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter) {
                if (state != 1) {
                    audioManager::mainThemeLowPass.stop();
                    audioManager::mainTheme.play();
                    audioManager::mainTheme.setLoop(true);
                    resetGame();
                    state = 1;
                }
            }
            else if (event.key.code == sf::Keyboard::Space) {
                if (player_shot_timer->DeltaTime() > 0.5) {
                    player->shot(player_projectiles);
                    player_shot_timer->reset();
                }
            }
        }
    }
}
/// <summary>
/// Method calling Enemy::move() method for all the enemies in Manager::enemies vector and after 5 moves changing move direstion.
/// </summary>
void Manager::enemyMoveManager() {
    if (enemy_move_timer->DeltaTime() > 1.5f) {
        if (move_count == 5) {
            Enemy::change_move_direction();
            move_count = 0;
            for (Enemy* E : enemies) {
                E->move_down();
            }
        }
        else {
            for (Enemy* E : enemies) {
                E->move();
            }
        }
        enemy_move_timer->reset();
        move_count++;
    }
}
/// <summary>
/// Method calling Enemy::shot() method for every enemy in Manager::enemies vector.
/// This method also checks whether any enemy is dead and if it is frees memory alocated for it and removes pointer to it from the vector.
/// </summary>
void Manager::manageEnemies() {
    for (int i = enemies.size() - 1; i >= 0; i--) {
        enemies[i]->shot(enemy_projectiles);
        if (!enemies[i]->isAlive()) {
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
        }
    }
}
/// <summary>
/// This method checks whether game is won or lose, if one of this events happened changes state appropriately.
/// </summary>
void Manager::isGameOver() {
    if (enemies.empty()) {
        state = 2;
        audioManager::mainTheme.stop();
        audioManager::play_victory_sound();
    }
        
    else if (!player->isAlive() || enemies.back()->get_y_position() > 900) {
        player_projectiles.clear();
        enemy_projectiles.clear();
        state = 3;
        audioManager::mainTheme.stop();
        audioManager::play_game_over_sound();
    }
}
/// <summary>
/// Method calling Enemy::show() Method for all enemies in Manager::enemies vector.
/// </summary>
/// <param name="win"></param>
void Manager::showEnemies(sf::RenderWindow& win) {
    for (Enemy* E : enemies) {
        E->show(win);
    }
}
/// <summary>
/// Method which moves all existing player_projectile objects, deleting ones out of screen and showing ones inside the screen. 
/// </summary>
/// <param name="win"></param>
void Manager::playerProjectilesManager(sf::RenderWindow& win) {
    for (int i = player_projectiles.size() - 1; i >= 0; i--) {
        player_projectiles[i]->move();
        if (player_projectiles[i]->isOutOfMap()) {
            delete player_projectiles[i];
            player_projectiles.erase(player_projectiles.begin() + i);
        }
        else
            player_projectiles[i]->show(win);
    }
}
/// <summary>
/// /// Method which moves all existing enemy_projectile objects, deleting ones out of screen and showing ones inside the screen. 
/// </summary>
/// <param name="win"></param>
void Manager::enemyProjectilesManager(sf::RenderWindow& win) {
    for (int i = enemy_projectiles.size() - 1; i >= 0; i--) {
        enemy_projectiles[i]->move();
        if (enemy_projectiles[i]->isOutOfMap()) {
            delete enemy_projectiles[i];
            enemy_projectiles.erase(enemy_projectiles.begin() + i);
        }
        else
            enemy_projectiles[i]->show(win);
    }
}
/// <summary>
/// Method loading all needed audio files.
/// </summary>
void audioManager::loadAudio() {

    shot_b.loadFromFile("audio/shot5.ogg");
    
    shot.setBuffer(shot_b);
    shot.setVolume(40);

    hpLoss_b.loadFromFile("audio/hpLoss.ogg");
    
    hpLoss.setBuffer(hpLoss_b);
    hpLoss.setVolume(40);

    victory_b.loadFromFile("audio/win.ogg");
    
    victory.setBuffer(victory_b);

    game_over_b.loadFromFile("audio/gameOver.ogg");

    game_over.setBuffer(game_over_b);

    mainThemeLowPass.openFromFile("audio/mainThemeLowPass.ogg");

    mainTheme.openFromFile("audio/mainTheme.ogg");

}
/// <summary>
/// Method which plays sound of player shoting. 
/// </summary>
void audioManager::play_shot_sound() {
    shot.stop();
    shot.play();
}
/// <summary>
/// Method playing sound of taking damage by the player.
/// </summary>
void audioManager::play_hpLoss_sound() {
    hpLoss.stop();
    hpLoss.play();
}
/// <summary>
/// 
///Method which plays victory sound.
/// </summary>
void audioManager::play_victory_sound() {
    victory.stop();
    victory.play();
}
/// <summary>
/// Method which plays game over sound.
/// </summary>
void audioManager::play_game_over_sound() {
    game_over.stop();
    game_over.play();
}