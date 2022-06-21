#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "timer.h"

#ifndef SPACE_INVADERS_FUNCTIONS_H
#define SPACE_INVADERS_FUNCTIONS_H

class Player_projectile;

class Enemy_projectile;

class Enemy;

class Player;

class Health_bar;

void loadGraphics();

bool my_random(int P);

void display_start_screen(sf::RenderWindow& win, sf::Font font);

void display_win_screen(sf::RenderWindow& win, sf::Font font);

void display_lose_screen(sf::RenderWindow& win, sf::Font font);

void fill_enemies(std::vector<Enemy*>& enemies);

///Class responsible for managing entire game
class Manager {
public:
    ///Pointer to Player instance
    Player* player;
    ///Vector of Player_projectile pointers
    ///
    ///This vector stores all existing projectiles shot by Player
    std::vector<Player_projectile*>player_projectiles;
    ///Variable event used to track events occurring while game is running
    sf::Event event;
    ///Variable state used to track the state of the game
    unsigned int state = 0;
    ///Variable used to track how many moves enemies did from last ChangeMoveDirection()
    unsigned int move_count;
    ///Vector of Enemy pointers storing all enemies
    std::vector<Enemy*>enemies;
    ///This vector stores all existing projectiles shot by Enemies
    std::vector<Enemy_projectile*>enemy_projectiles;
    ///Pointer to a Timer object used to track time between calling Enemy::move() function
    Timer* enemy_move_timer = new Timer();
    ///Pointer to a Timer object used to track time between calling Player::shot() function
    Timer* player_shot_timer = new Timer();

    void loadGraphics();

    void eventManager(sf::RenderWindow& win);

    void enemyMoveManager();

    void fill_enemies();

    void manageEnemies();

    void resetGame();

    void isGameOver();

    void showEnemies(sf::RenderWindow& win);

    void playerProjectilesManager(sf::RenderWindow& win);

    void enemyProjectilesManager(sf::RenderWindow& win);

    void checkPlayerCollisions();

    void checkEnemyCollisions();

};
///Pure virtual class which is base class for all entities in the game
class Entity {
protected:
    ///Pair of integers used to store location of Entity
    std::pair<int, int> position;
public:
    ///Parametric constructor
    Entity(int x, int y);
    ///Default constructor
    Entity() = default;
    ///Pure virtual function show
    virtual void show(sf::RenderWindow& win) = 0;
};

///Class Enemy is pure virtual class, base for three types of enemies
class Enemy : public Entity {
public:
    ///Default destructor
    virtual ~Enemy() = default;
    ///Parametric constructor
    Enemy(int x, int y) : Entity(x, y) {};

    static void change_move_direction();

    void move();

    void move_down();

    bool isAlive();

    virtual void shot(std::vector<Enemy_projectile*>& e_bullet) = 0;

    friend void Manager::checkEnemyCollisions();

    friend void Manager::resetGame();

    int get_y_position();

protected:
    ///Static boolean variable keeping track of side in which enemies should move (rue - right, false -left)
    static bool move_side;
    ///Variable indicating health level of enemy, set by default at 1
    unsigned int health = 1;
};

///First sub-class of Enemy representing fire type opponent
class Fire_enemy : public Enemy {
public:
    ///Sprite storing texture of this enemy type
    static sf::Sprite graphics;
    ///Default destructor
    ~Fire_enemy() override = default;
    ///Parametric constructor
    Fire_enemy(int x, int y) : Enemy(x, y) {}

    void show(sf::RenderWindow& win) override;

    void shot(std::vector<Enemy_projectile*>& e_bullet)override;

};

///Second sub-class of Enemy representing stone type opponent
class Stone_enemy : public Enemy {
public:
    ///Sprites storing textures for different hp-levels of this enemy type
    static sf::Sprite graphics_hp1;
    static sf::Sprite graphics_hp2;
    static sf::Sprite graphics_hp3;
    ///Default destructor
    ~Stone_enemy() override = default;
    ///Parametric constructor setting Stone_Enemy::health at 3
    Stone_enemy(int x, int y) : Enemy(x, y) { health = 3; }

    void show(sf::RenderWindow& win) override;

    void shot(std::vector<Enemy_projectile*>& e_bullet)override;
};

///Second sub-class of Enemy representing stone type opponent
class Toxic_enemy : public Enemy {
public:
    ///Sprite storing texture of this enemy type
    static sf::Sprite graphics;
    ///Default constructor
    ~Toxic_enemy() override = default;
    ///Parametric constructor
    Toxic_enemy(int x, int y) : Enemy(x, y) {}

    void show(sf::RenderWindow& win) override;

    void shot(std::vector<Enemy_projectile*>& e_bullet)override;
};

///Pure virtual class, base for enemy's and players projectiles
class Projectile : public Entity {
public:
    ///Parametric constructor
    Projectile(int x, int y) : Entity(x, y) {}

    bool isOutOfMap();
};

///Class responsible for managing player's projectiles
class Player_projectile : public Projectile {
public:
    ///Sprite storing texture of Player's projectiles
    static sf::Sprite graphics;
    ///Parametric constructor
    Player_projectile(int x, int y) : Projectile(x, y) {}

    void show(sf::RenderWindow& win) override;

    void move();

    friend void Manager::checkEnemyCollisions();
};

///Pure virtual class responsible for managing enemy's projectiles
class Enemy_projectile : public Projectile {
public:
    ///Parametric constructor
    Enemy_projectile(int x, int y) : Projectile(x, y) {}
    ///Virtual destructor
    virtual ~Enemy_projectile() = default;

    friend void Manager::checkPlayerCollisions();

    void move();
};

///Sub-class of Enemy_projectiles representing projectiles of stone opponent
class Stone_projectile : public Enemy_projectile {
public:
    ///Sprite storing texture of stone enemy's projectiles
    static sf::Sprite graphics;

    void show(sf::RenderWindow& win) override;

    Stone_projectile(int x, int y) : Enemy_projectile(x, y) {}
};

///Sub-class of Enemy_projectiles representing projectiles of toxic opponent
class Toxic_projectile : public Enemy_projectile {
public:
    ///Sprite storing texture of toxic enemy's projectiles
    static sf::Sprite graphics;

    void show(sf::RenderWindow& win) override;

    Toxic_projectile(int x, int y) : Enemy_projectile(x, y) {}
};

///Sub-class of Enemy_projectiles representing projectiles of fire opponent
class Fire_projectile : public Enemy_projectile {
public:
    ///Sprite storing texture of fire enemy's projectiles
    static sf::Sprite graphics;

    void show(sf::RenderWindow& win) override;

    Fire_projectile(int x, int y) : Enemy_projectile(x, y) {}
};

///Class managing a health bar of the player
class Health_bar : public Entity {
private:
    ///Pointer to owner of health bar
    Player* player = nullptr;

    void assignToPlayer(Player* ptr);

public:
    ///Sprite storing texture of health bar
    static sf::Sprite graphics;

    void show(sf::RenderWindow& win);
    ///Parametric constructor
    Health_bar(Player* ptr) { assignToPlayer(ptr); position.first = 20; position.second = 20; };
};

///Player class providing all of functionalities of the player
class Player : public Entity {
private:
    ///Variable keeping track of player's health, set by default at 3
    unsigned int health = 3;
public:
    ///Sprite storing texture of a plaer
    static sf::Sprite graphics;
    ///Parametric constructor
    Player() : Entity(550, 1150) {}
    ///Health_bar of player
    Health_bar mHealthBar = Health_bar(this);

    void update(sf::RenderWindow& win);

    void show(sf::RenderWindow& win) override;

    void shot(std::vector<Player_projectile*>& projectiles);

    friend void Manager::checkPlayerCollisions();

    friend void Health_bar::show(sf::RenderWindow& win);

    bool isAlive()const;

    friend void Manager::resetGame();
};
/// <summary>
/// Class responsible for storying and playing sounds.
/// </summary>
class audioManager {
public:
    void loadAudio();
    static void play_shot_sound();
    static void play_hpLoss_sound();
    static void play_victory_sound();
    static void play_game_over_sound();
    static sf::Sound shot;
    static sf::Sound hpLoss;
    static sf::Sound victory;
    static sf::Sound game_over;
    static sf::Music mainThemeLowPass;
    static sf::Music mainTheme;

private:
     sf::SoundBuffer shot_b;
     sf::SoundBuffer hpLoss_b;
     sf::SoundBuffer victory_b;
     sf::SoundBuffer game_over_b;
     
};
#endif //SPACE_INVADERS_FUNCTIONS_H
