// This program passes a structure variable to one function
// by reference and to another as a constant reference.
#include <iostream>
//#include <iomanip>
#include <string>
using namespace std;

struct Gladiator                // Holds data for an inventory item
{
    char descriptionName[50];
    /*int maxHealth;
    int currentHealth;
    double evasion;
    double crit;
    double minDamage, damageRange;*/
};

// Function prototypes
Gladiator getGladiatorData();
void showGladiator(const Gladiator &);

int main()
{
    Gladiator player;            // Define an InvItem structure variable.
    
    player = getGladiatorData();
    showGladiator(player);
    return 0;
}


Gladiator getGladiatorData()
{
    Gladiator points;
    cout << "Enter Gladiator 1: ";
    cin.get();
    //getline(cin, points.descriptionName);
    
    return points;
}

void showGladiator(const Gladiator &points)
{
    //cout << fixed << showpoint << setprecision(2) << endl;;
    cout << "Name for player 1  : "  << points.descriptionName << endl;
  
}
