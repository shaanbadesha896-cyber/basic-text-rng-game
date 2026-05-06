#include "combat.h"

void combatmode(Player& player, Enemy& enemy, Mage& mage, bool helper) {
    while (enemy.hp > 0 && player.current_hp > 0) {
        player.playercombat(enemy);

        if (helper) mage.mage_combat(enemy);

        if (enemy.hp <= 0) {
            player.full_heal();
            mage.full_heal();
            slowdown(slowdown1);
            std::cout << "Enemy is dead!\n";
            player.player_xp += enemy.xp;
            LevelUp(player);
            return;
        }

        Knight* knight = dynamic_cast<Knight*>(&enemy);
        if (knight != nullptr) {
            int ability_chance = randomint(1, 100);
            if (ability_chance <= 30) {
                knight->Charge(player, mage);
            } else {
                enemy.enemy_combat(player, enemy, mage, helper);
            }
        } else {
            enemy.enemy_combat(player, enemy, mage, helper);
        }

        if (player.current_hp <= 0) {
            GameOver();
            return;
        }
    }
}


void LevelUp(Player& player) {
    if (player.player_xp >= player.level_up_xp[player.level]) {
        player.player_xp -= player.level_up_xp[player.level];
        player.level++;
        slowdown(slowdown1);
        slowdown(slowdown1);
        std::cout << "You have leveled up to level " << player.level << "!!\n";
        slowdown(slowdown1);
        switch (player.level) {
            case 1: {
                player.max_hp += 5;
                player.current_hp = player.max_hp;
                player.evade += 3;
                player.dmg += 5;
                std::cout << "Your stats have increased, Max HP = " << player.max_hp << ", Damage = " << player.dmg << "\n";
                break;
            }
        }
    }
}

void GameOver() {
    typewrite("YOU DIED!!\n", 120);
    exit(0);
}

