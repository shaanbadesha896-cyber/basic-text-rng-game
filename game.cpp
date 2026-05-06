#include <iostream> 
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <random>
#include "combat.h"
#include "utils.h"



int main() {
    Player player;
    Mage mage;

    int pickupslow = 2;
    bool game_over = false;
    std::string confirmation;
    int direction1;
    std::vector<std::string> inventory;
    bool has_a_helper = false;

    std::string character_name;
    std::cout << "Welcome!!\n";
    slowdown(slowdown1);
    std::cout << "What is your name: ";
    std::getline(std::cin >> std::ws, character_name);
    slowdown(slowdown1);

    do {
        std::cout << "Press any key to begin: ";
        std::cin >> confirmation;
    } while (confirmation.empty());

    std::cout << "You wake up in a dungeon.\n";
    slowdown(slowdown1);
    do {
        std::cout << "You look around and see 2 paths- One to your left (1) and One in front of you (2): ";
        std::cin >> std::ws >> direction1;
    } while (direction1 != 1 && direction1 != 2);

    switch (direction1) {
        case 1:
            std::cout << "You see a rotting dead body with an old sword lying nearby\n";
            slowdown(slowdown1);
            std::cout << "Old sword has been added to your inventory\n";
            slowdown(pickupslow);
            inventory.push_back("Old Sword");
            player.dmg += 2;
            std::cout << "You head back up into the other path you previously saw\n";
            break;
    }

    std::cout << "As you head up the path, you are attacked by a goblin.\n";
    Enemy goblin(20, 1, 5, 50, false);
    combatmode(player, goblin, mage, has_a_helper);

    slowdown(slowdown1);
    std::cout << "You deal with the goblin and head up the path, eventually emerging out of the dungeon to a forest\n";
    slowdown(slowdown1);

    std::cout << "You are met by an old white bearded man as you walk in the forest\n";
    slowdown(slowdown1);
    typewrite("Man: A fellow traveller? ", 50);
    slowdown(slowdown1);
    typewrite("From the dungeon I assume?\n", 50);
    slowdown(slowdown1);
    has_a_helper = true;

    std::cout << "A movement in the bushes catches the eyes of both of you. Something feels off...\n";
    slowdown(slowdown1);
    std::cout << "An armored beast of a knight pops out of the bushes. Without saying anything, he lunges straight for the 2 of you.\n";
    slowdown(slowdown1);

    Knight knight(200, 5, 10, 150, false);
    combatmode(player, knight, mage, has_a_helper);

    return 0;
}
