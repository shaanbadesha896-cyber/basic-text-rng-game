#include "classes.h"
#include <iostream>
#include <algorithm>

void Player::playercombat(Enemy& enemy) {
    char action;
    do {
        std::cout << "Press A to attack, H to heal: ";
        std::cin >> std::ws >> action;
        action = tolower(action);
    } while (action != 'a' && action != 'h');

    if (action == 'a') {
        enemy.hp -= dmg;
        if (enemy.hp <= 0) enemy.hp = 0;
        slowdown(slowdown1);
        std::cout << "You attack for " << dmg << " damage! Enemy HP: " << enemy.hp << "\n";
    } else {
        current_hp += 5;
        if (current_hp >= max_hp) current_hp = max_hp;
        slowdown(slowdown1);
        std::cout << "You heal! Your HP: " << current_hp << "\n";
    }
}

void Player::full_heal() { 
    current_hp = max_hp; 
}

void Enemy::silent() {
    if (IsSilenced) hp -= hp * 0.05;
}

void Enemy::Charge(Player& player, Mage& mage) {}

void Enemy::enemy_combat(Player& player, Enemy& enemy, Mage& mage, bool helper) {
    int enemy_dmg = randomint(enemy.min_damage, enemy.max_damage);
    int dodge = randomint(1, 100);
    if (dodge <= player.evade) {
        slowdown(slowdown1);
        std::cout << "You dodge the enemy attack\n";
        if (helper) {
            mage.evade_after_evade(player, enemy, enemy_dmg, helper);
            return;
        }
        return;
    }

    int attack_decider = helper ? randomint(1, 2) : 1;
    if (attack_decider == 1) {
        player.current_hp -= enemy_dmg;
        if (player.current_hp < 0) player.current_hp = 0;
        slowdown(slowdown1);
        std::cout << "Enemy attacks for " << enemy_dmg << " damage! Your HP: " << player.current_hp << "\n";
    } else {
        mage.mage_damage(player, enemy, enemy_dmg, helper);
    }
}

void Knight::Charge(Player& player, Mage& mage) {
    int charge_dmg = randomint(6, 8) * 5;
    player.current_hp -= charge_dmg;
    mage.current_hp -= charge_dmg;
    slowdown(slowdown1);
    slowdown(slowdown1);
    std::cout << "The knight charges at both of you for " << charge_dmg << " damage! Your HP: " << player.current_hp << " Mage HP: " << mage.current_hp << "\n";
}

void Mage::mage_combat(Enemy& enemy) {
    int mage_dmg = randomint(mage_min_dmg, mage_max_dmg) * 5;
    enemy.hp -= mage_dmg;
    current_mana -= 10;
    slowdown(slowdown1);
    std::cout << "Mage casts a spell for " << mage_dmg << " dmg\n";
    if (randomint(1, 100) <= silence) enemy.IsSilenced = true;
    enemy.silent();
}

void Mage::mage_damage(Player& player, Enemy& enemy, int damage, bool& helper) {
    current_hp -= damage;
    if (current_hp < 0) current_hp = 0;
    slowdown(slowdown1);
    std::cout << "Enemy attacks the mage for " << damage << " damage! Mage HP: " << current_hp << "\n";
    if (current_hp <= 0) mage_game_over(player, helper);
}

void Mage::mage_game_over(Player& player, bool& helper) {
    player.current_hp += player.max_hp * 0.2;
    helper = false;
    std::cout << "The mage passed away in battle\n";
}

void Mage::full_heal() { current_hp = max_hp; current_mana = max_mana; }

void Mage::evade_after_evade(Player& player, Enemy& enemy, int enemy_dmg, bool helper) {
    int double_evade = evade * 2;
    if (double_evade > 100) double_evade = 100;
    if (randomint(1, 100) <= double_evade) {
        std::cout << "The mage dodges too!\n";
        combatmode(player, enemy, *this, helper);
    } else {
        std::cout << "But the mage gets hit instead\n";
        mage_damage(player, enemy, enemy_dmg, helper);
    }
}