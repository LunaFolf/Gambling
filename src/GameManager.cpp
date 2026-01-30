#include <iostream>
#include <ostream>
#include <Gambling/GameManager.h>

GameManager::GameManager() {
    std::cout << "GameManager created" << std::endl;
    reset();
}

void GameManager::reset() {
    std::cout << "GameManager reset" << std::endl;
    shotsFired = 0;
    rivalsKilled = 0;
    moneyEarned = 0;
    itemsUsed = 0;
    bulletsUsed = 0;
    lastFiredBulletWasLive = false;
}

void GameManager::setLastFiredBulletWasLive(const bool value) { lastFiredBulletWasLive = value; }
void GameManager::addShotsFired(const int amount) { shotsFired += amount; }
void GameManager::addRivalsKilled(const int amount) { rivalsKilled += amount; }
void GameManager::addMoneyEarned(const int amount) { moneyEarned += amount; }
void GameManager::addItemsUsed(const int amount) { itemsUsed += amount; }
void GameManager::addBulletsUsed(const int amount) { bulletsUsed += amount; }
