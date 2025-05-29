#include "Shop.h"
#include <iostream>
using namespace std;

void Shop::show(Pet& pet, bool& gameRunning) {
    cout << "\n=== Pet Shop ==="
        << "\n1.  Premium Food (20 coins) - Satiety +30, Happiness +10"
        << "\n2.  Toy Pack (25 coins) - Happiness +30"
        << "\n3.  Clean Spray (20 coins) - Cleanliness +50"
        << "\n4.  Crown (500 coins) - Win the game"
        << "\n0. Exit shop"
        << "\n=====================\nChoice: ";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        if (pet.getCoins() >= 20) {
            pet.spendCoins(20);
            cout << " >> Yum! Premium food eaten.\n";
            pet.timePass(-6); // 饱食+30
            pet.play();       // 快乐+15，自带饥饿+10
        }
        else cout << " >> Not enough coins.\n";
        break;
    case 2:
        if (pet.getCoins() >= 25) {
            pet.spendCoins(25);
            cout << " >> Pet enjoyed new toys!\n";
            pet.play(); pet.play(); // 快乐+30
        }
        else cout << " >> Not enough coins.\n";
        break;
    case 3:
        if (pet.getCoins() >= 20) {
            pet.spendCoins(20);
            cout << " >> Clean spray used!\n";
            pet.clean(); pet.clean(); // 清洁+50
        }
        else cout << " >> Not enough coins.\n";
        break;
    case 4:
        if (pet.getCoins() >= 500 && !pet.hasCrown()) {
            pet.spendCoins(500);
            pet.obtainCrown();
            cout << "\n👑 You bought the CROWN! Victory achieved!\n";
            gameRunning = false;
        }
        else cout << " >> Not enough coins or already purchased.\n";
        break;
    case 0:
        cout << " >> Leaving shop.\n";
        break;
    default:
        cout << " >> Invalid option.\n";
        break;
    }
}
