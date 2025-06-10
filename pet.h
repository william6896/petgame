#pragma once
#include <string>
using namespace std;

class Pet {
public:
    // 构造函数（必须含参数）
    explicit Pet(const string& name);

    // 核心功能
    bool feed();         // 喂食（返回是否成功）
    void perform();      // 卖艺赚金币
    void play();         // 玩耍
    void clean();        // 清洁
    bool seeDoctor();    // 看医生（返回是否成功）
    void showStatus() const;
    void timePass(int hours);  // 时间流逝

    // 状态访问器
    bool isSick() const { return _isSick; }
    int getCoins() const { return _coins; }
    void spendCoins(int amount);
    void obtainCrown();
    bool hasCrown() const;
    const string& getName() const { return _name; }

private:
    string _name;
    int _satiety;        // 0-100
    int _happiness;     // 0-100
    int _cleanliness;   // 0-100
    int _coins;         // 金币系统
    bool _hasCrown;
    bool _isSick;

    void checkHealth();  // 健康检测
};