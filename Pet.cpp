#include "Pet.h"
#include <iostream>
#include <algorithm>  // for std::clamp
using namespace std;

// 严苛的初始状态
Pet::Pet(const string& name) :
    _name(name),
    _satiety(55),
    _happiness(53),
    _cleanliness(43),
    _coins(30),
    _isSick(false) {
}

void Pet::checkHealth() {
    _isSick = (_satiety <= 20 || _cleanliness <= 20);
}

// 喂食需5金币（饱食+15，快乐+5）
bool Pet::feed() {
    if (_coins < 5) {
        cout << " >> Need 5 coins to feed!\n";
        return false;
    }
    _coins -= 5;
    _satiety = min(100, _satiety + 20);//-每小时自动降低=15
    _happiness = min(100, _happiness + 8);//-每小时自动降低=5
    cout << " >> " << _name << " ate food!\n";
    return true;
}

// 卖艺赚20金币（快乐-20，饱食-15，清洁-10）
void Pet::perform() {
    _coins += 20;
    _happiness = max(0, _happiness - 17);
    _satiety = max(0, _satiety - 12);
    _cleanliness = max(0, _cleanliness - 7);
    cout << " >> " << _name << " performed! Earned 15 coins\n";
}

// 玩耍（快乐+20，饱食-10）
void Pet::play() {
    _happiness = min(100, _happiness + 23);
    _satiety = max(0, _satiety - 5);
    cout << " >> " << _name << " played happily!\n";
}

// 清洁（清洁+25）
void Pet::clean() {
    _cleanliness = min(100, _cleanliness + 28);
    cout << " >> " << _name << " took a bath!\n";
}

void Pet::spendCoins(int amount) {
    _coins = max(0, _coins - amount);
}

void Pet::obtainCrown() {
    _hasCrown = true;
}

bool Pet::hasCrown() const {
    return _hasCrown;
}

// 看病需20金币（解除生病状态）
bool Pet::seeDoctor() {
    if (_coins < 20) {
        cout << " >> Need 20 coins to see doctor!\n";
        return false;
    }
    _coins -= 20;
    _isSick = false;

    // 看病后顺便改善身体状况
    _satiety = max(_satiety, 30);         // 饱食回升（不低于30）
    _cleanliness = max(_cleanliness, 40); // 清洁回升（不低于40）
    cout << " >> " << _name << " recovered after treatment!\n";
    return true;
}
// 每小时变化（饱食-5，快乐-3，清洁-3）
void Pet::timePass(int hours) {
    _satiety = max(0, _satiety - 5 * hours);
    _happiness = max(0, _happiness - 3 * hours);
    _cleanliness = max(0, _cleanliness - 3 * hours);
    checkHealth();
}

// 显示完整状态
void Pet::showStatus() const {
    cout << "\n=== " << _name << "'s Status ==="
        << "\n| Coins:     " << _coins
        << "\n| Satiety:   " << _satiety << "/100"
        << "\n| Happiness: " << _happiness << "/100"
        << "\n| Clean:     " << _cleanliness << "/100"
        << "\n| Health:    " << (_isSick ? "[SICK]" : "Healthy")
        << "\n============================\n";
}