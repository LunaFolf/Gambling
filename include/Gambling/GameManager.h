#pragma once

class GameManager {
public:
    int shotsFired = 0;
    int rivalsKilled = 0;
    int moneyEarned = 0;
    int itemsUsed = 0;
    int bulletsUsed = 0;

    bool lastFiredBulletWasLive = false;

    GameManager();

    void reset();
    void setLastFiredBulletWasLive(bool value);
    void addShotsFired(int amount);
    void addRivalsKilled(int amount);
    void addMoneyEarned(int amount);
    void addItemsUsed(int amount);
    void addBulletsUsed(int amount);
};