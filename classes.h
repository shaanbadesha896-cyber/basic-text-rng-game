#pragma once 
#include "utils.h"

extern int slowdown1;  

class Player;
class Enemy;
class Mage;
class Knight;

void combatmode(Player& player, Enemy& enemy, Mage& mage, bool helper);
int randomint(int min, int max);

class Player {
public:
    int max_hp = 100;
    int current_hp = 100;
    int dmg = 13;
    int level = 0;
    int player_xp = 0;
    int evade = 2;
    int level_up_xp[6] = {50, 150, 500, 1000, 1250, 1000000};
    void playercombat(Enemy& enemy);
    void full_heal();
};

class Enemy {
public:
    int hp;
    double min_damage;
    double max_damage;
    int xp;
    bool IsSilenced;
    Enemy(int hp, double min_damage, double max_damage, int xp, bool isSilenced)
        : hp(hp), min_damage(min_damage), max_damage(max_damage), xp(xp), IsSilenced(isSilenced) {}
    void silent();
    virtual void Charge(Player& player, Mage& mage);
    void enemy_combat(Player& player, Enemy& enemy, Mage& mage, bool helper);
};

class Knight : public Enemy {
public:
    Knight(int hp, double min_damage, double max_damage, int xp, bool isSilenced)
        : Enemy(hp, min_damage, max_damage, xp, isSilenced) {}
    void Charge(Player& player, Mage& mage) override;
};

class Mage {
public:
    int max_mana = 200;
    int current_mana = 200;
    int max_hp = 85;
    int current_hp = 85;
    int evade = 10;
    int mage_min_dmg = 2;
    int mage_max_dmg = 4;
    int silence = 5;
    void mage_combat(Enemy& enemy);
    void mage_damage(Player& player, Enemy& enemy, int damage, bool& helper);
    void mage_game_over(Player& player, bool& helper);
    void full_heal();
    void evade_after_evade(Player& player, Enemy& enemy, int enemy_dmg, bool helper);
};


