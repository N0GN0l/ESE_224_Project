// main.cpp
// ESE 224 Fall 2026 Midterm Project (starter code)
// Team members: Daniel Zhou, Ella Chen, Logan Jeong
//
// This skeleton compiles and shows the menu. Fill in each TODO (see Section 5 of the handout).

#include "Drone.h"
#include "Fleet.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <limits>
#include <vector>
using std::string;
using std::endl;

// TODO: ask for a username and password until the pair appears in users.txt,
//       then greet the user by name.
void login()
{
    struct namePassCombo{
        string validName;
        string validPass;
    };
    
    std::vector<namePassCombo> validCombos;

    std::ifstream userIn("users.txt");

    string name;
    string password;
    while(userIn>>name>>password)
    {
        namePassCombo temp;
        temp.validName = name;
        temp.validPass = password;
        validCombos.push_back(temp); 
    }

    std::cout<<"Please input your username: ";
    std::cin>>name;
    std::cout<<endl<<"Please input your password: ";
    std::cin>>password;
    std::cout<<endl;

    bool loggedIn = false;

    for(;;)
    {
        for(int i = 0; i < validCombos.size(); i++)
        {
            if(name == validCombos.at(i).validName && password == validCombos.at(i).validPass)
            {
                std::cout<<"Hello "<<name<<" welcome to SkyDrop"<<endl;
                loggedIn = true;
            }
        }
        if(loggedIn)
        {
            break;
        }
        else {
            std::cout<<"Please input a valid username and password pair"<<endl;
        }
    }
}

// TODO: read every drone from the file until the end of the file,
//       add each one to the fleet, and print how many were loaded.
void loadFleet(Fleet& fleet, const string& filename)
{
}

void showMenu()
{
    std::cout << endl
         << "===== SkyDrop Menu =====" << endl
         << " 1. Display all drones" << endl
         << " 2. Sort by ID" << endl
         << " 3. Sort by battery" << endl
         << " 4. Sort by name" << endl
         << " 5. Shuffle fleet" << endl
         << " 6. Search by name" << endl
         << " 7. Search by ID" << endl
         << " 8. Find nearest available drone" << endl
         << " 9. Dispatch a delivery" << endl
         << "10. Recharge a drone" << endl
         << "11. Fleet status summary" << endl
         << "12. Process orders file" << endl
         << "13. Write fleet to file" << endl
         << "14. Add a new drone" << endl
         << " 0. Quit" << endl;
}

int main()
{
    login();

    Fleet fleet;
    loadFleet(fleet, "drones.txt");

    int choice = -1;
    while (choice != 0)
    {
        showMenu();
        std::cout << "Choose an option: ";
        std::cin >> choice;
        // TODO: if the user types a letter, cin fails. Recover (cin.clear and
        //       cin.ignore from <limits>) instead of crashing or looping forever.

        switch (choice)
        {
        case 1:
            fleet.displayAll();
            break;
        case 2:
            
            break;
        case 3:
            
            break;
        case 4:
            
            break;
        case 5:
            
            break;
        case 6:
            
            break;
        case 7:
            
            break;
        case 8:
            
            break;
        case 9:
            
            break;
        case 10:
            
            break;
        case 11:
            
            break;
        case 12:
            
            break;
        case 13:
            
            break;
        case 14:
            
            break;
        // TODO: cases 2 to 14 (table in Section 5)
        case 0:
            std::cout << "Goodbye!" << endl;
            break;
        default:
            std::cout << "Invalid option." << endl;
        }
    }
    return 0;
}
