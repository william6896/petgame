#include "PetGame.h"
#include "Shop.h"
#include <iostream>
#include <fstream>
using namespace std;

// 构造函数初始化成员
PetGame::PetGame() : _pet("Unnamed"), _isRunning(false) {}

// 游戏主循环
void PetGame::startGame() {
    _isRunning = true;

    // 设置宠物名字
    string name;
    cout << "Enter pet's name: ";
    getline(cin, name);
    _pet = Pet(name);

    while (_isRunning) {
        _pet.timePass(1);  // 每小时自动变化
        _pet.showStatus();
        forceMedicalCheck();

        showMenu();
        char input;
        cin >> input;
        handleInput(input);
        cin.ignore();  // 清除输入缓冲
    }
    cout << "Game saved. Goodbye!\n";
}

// 强制医疗检查
void PetGame::forceMedicalCheck() {
    if (_pet.isSick()) {
        _sickRounds++;
        cout << "\n!!! WARNING !!! "
            << _pet.getName() << " is sick (Consecutive: " << _sickRounds << ")\n";

        if (_sickRounds >= 3) {
            cout << "\n!!! GAME OVER: " << _pet.getName() << " has been sick for 3 turns in a row.\n";
            _isRunning = false;
            return;
        }

        _pet.showStatus();
        while (_pet.isSick()) {
            if (!_pet.seeDoctor()) {
                cout << "1. Perform to earn coins\n"
                    << "2. Quit game\nChoice: ";
                char cmd;
                cin >> cmd;
                if (cmd == '1') _pet.perform();
                else if (cmd == '2') {
                    _isRunning = false;
                    return;
                }
            }
        }
    }
    else {
        _sickRounds = 0; // 恢复健康就重置
    }
}

// 显示交互菜单
void PetGame::showMenu() const {
    cout << "\n=== Economic System ==="
        << "\n[F] Feed (5 coins)"
        << "\n[P] Play"
        << "\n[C] Clean"
        << "\n[A] Perform (+20 coins)"
        << "\n[S] Shop"
        << "\n[D] Doctor (30 coins)"
        << "\n[Q] Quit"
        << "\n=======================\n> ";
}

// 输入处理
void PetGame::handleInput(char input) {
    switch (toupper(input)) {
    case 'F': _pet.feed(); break;
    case 'P': _pet.play(); break;
    case 'C': _pet.clean(); break;
    case 'A': _pet.perform(); break;
    case 'S': Shop::show(_pet, _isRunning); break;
    case 'D':
        if (!_pet.seeDoctor()) {
            cout << " >> Not enough coins!\n";
        }
        break;

    case 'Q': _isRunning = false; break;
    default:
        cout << " >> Invalid command!\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

void PetGame::endGame(bool victory) {
    ofstream file("game_result.txt");
    if (file.is_open()) {
        if (victory) {
            file << "Game Result: Victory! " << _pet.getName() << " earned a crown.\n";
            cout << "\n*** Congratulations! You Win! ***\n";
        }
        else {
            file << "Game Result: Defeat. " << _pet.getName() << " was sick too long.\n";
            cout << "\n*** Game Over: Your pet remained sick for 3 turns. ***\n";
        }
        file.close();
    }
}

