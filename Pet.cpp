#include "Pet.h"
#include <iostream>
#include <algorithm>  // for std::clamp
using namespace std;

// 严苛的初始状态
Pet::Pet(const string& name) :
    _name(name),
    _hunger(70),
    _happiness(40),
    _cleanliness(30),
    _coins(30),
    _isSick(false) {
}

void Pet::checkHealth() {
    _isSick = (_hunger >= 85 || _cleanliness <= 20);
}

// 喂食需5金币（饥饿-15，快乐+5）
bool Pet::feed() {
    if (_coins < 5) {
        cout << " >> Need 5 coins to feed!\n";
        return false;
    }
    _coins -= 5;
    _hunger = max(0, _hunger - 15);
    _happiness = min(100, _happiness + 5);
    cout << " >> " << _name << " ate food!\n";
    return true;
}

// 卖艺赚15金币（快乐-25，饥饿+20，清洁-15）
void Pet::perform() {
    _coins += 15;
    _happiness = max(0, _happiness - 25);
    _hunger = min(100, _hunger + 20);
    _cleanliness = max(0, _cleanliness - 15);
    cout << " >> " << _name << " performed! Earned 15 coins\n";
}

// 玩耍（快乐+15，饥饿+10）
void Pet::play() {
    _happiness = min(100, _happiness + 15);
    _hunger = min(100, _hunger + 10);
    cout << " >> " << _name << " played happily!\n";
}

// 清洁（清洁+25）
void Pet::clean() {
    _cleanliness = min(100, _cleanliness + 25);
    cout << " >> " << _name << " took a bath!\n";
}

// 看病需20金币（解除生病状态）
bool Pet::seeDoctor() {
    if (_coins < 20) {
        cout << " >> Need 20 coins to see doctor!\n";
        return false;
    }
    _coins -= 20;
    _isSick = false;
    cout << " >> " << _name << " recovered!\n";
    return true;
}

// 每小时变化（饥饿+5，快乐-3，清洁-3）
void Pet::timePass(int hours) {
    _hunger = min(100, _hunger + 5 * hours);
    _happiness = max(0, _happiness - 3 * hours);
    _cleanliness = max(0, _cleanliness - 3 * hours);
    checkHealth();
}

// 显示完整状态
void Pet::showStatus() const {
    cout << "\n=== " << _name << "'s Status ==="
        << "\n| Coins:     " << _coins
        << "\n| Hunger:    " << _hunger << "/100"
        << "\n| Happiness: " << _happiness << "/100"
        << "\n| Clean:     " << _cleanliness << "/100"
        << "\n| Health:    " << (_isSick ? "[SICK]" : "Healthy")
        << "\n============================\n";
}