#pragma once
#include "Pet.h"

class PetGame {
public:
    PetGame();          // 构造函数
    void startGame();    // 统一启动函数

private:
    bool _isRunning;
    Pet _pet;           // 组合关系

    void showMenu() const;
    void handleInput(char input);
    void forceMedicalCheck();
};