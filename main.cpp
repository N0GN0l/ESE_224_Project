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
            std::cout<<"Please input your username: ";
            std::cin>>name;
            std::cout<<endl<<"Please input your password: ";
            std::cin>>password;
            std::cout<<endl;
        }
    }
}

// TODO: read every drone from the file until the end of the file,
//       add each one to the fleet, and print how many were loaded.
void loadFleet(Fleet& fleet, const string& filename)
{
    string name;
    string model;
    int ID;
    int x;
    int y;
    double battery;
    double maxPayload;
    string status;
    int count = 0;
    std::ifstream fin(filename);
    while(fin>>name>>ID>>model>>battery>>maxPayload>>x>>y>>status)
    {
        // std::cout<<name<<ID<<model<<battery<<maxPayload<<x<<y<<status<<std::endl;
        Drone temp(name,ID,model,battery,maxPayload,x,y,status);
        // std::cout<<temp.getName()<<temp.getID()<<temp.getModel()<<temp.getBattery()<<temp.getMaxPayload()<<temp.getPosition(0)<<temp.getPosition(1)<<temp.getStatus()<<std::endl;
        if(fleet.addDrone(temp))
        {
            count++;
        }
    }
    std::cout<<count<<" drones were loaded"<<std::endl;
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
    // login();

    Fleet fleet;
    loadFleet(fleet, "drones.txt");
    int choice = -1;
    while (choice != 0)
    {
        showMenu();
        std::cout << "Choose an option: ";
        std::cin >> choice;
        while (std::cin.fail()) {
            std::cout << "Error: That is not a valid option. Try again: ";
            
            std::cin.clear(); 
            
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            
            std::cin >> choice;
        }

        string name;
        int ID;
        string model;
        int x, y, index = 0;
        double battery, maxPayload;
        string status;
        int deliveriesCompleted;
        
        int seed;
        double weight;
        int idx;

        Drone drone;
        switch (choice)
        {
            case 1:
                fleet.displayAll();
                break;
            case 2:
                fleet.selectionSortByID();
                break;
            case 3:
                fleet.insertionSortByBattery();
                break;
            case 4:
                fleet.sortByName();
                break;
            case 5:
                std::cout << "Enter seed: ";
                std::cin >> seed;
                fleet.shuffleFleet(seed);
                break;
            case 6:
                std::cout << "Enter name: ";
                std::cin >> name;

                idx = fleet.linearSearchByName(name);
                if (idx == -1) {
                    std::cout << "Drone not found";
                } else {
                    fleet.displayDrone(idx);
                }

                break;
            case 7:
                std::cout << "Enter ID: " << endl;
                std::cin >> ID;
            
                idx = fleet.binarySearchByID(ID);
                if (idx == -1) {
                    std::cout << "ID not found";
                } else {
                    fleet.displayDrone(idx);
                }

                break;
            case 8:
                std::cout << "Enter x & y in one line: " << endl;
                std::cin >> x >> y;
                std::cout << "Enter drone weight: " << endl;
                std::cin >> weight;
                idx = fleet.findNearestAvailable(x, y, weight);
                fleet.displayDrone(idx);
                break;
            case 9:
                std::cout << "Enter x & y in one line: " << endl;
                std::cin >> x >> y;
                std::cout << "Enter drone weight: " << endl;
                std::cin >> weight; 
                idx = fleet.findNearestAvailable(x, y, weight);
                fleet.displayDrone(idx);
                idx = fleet.dispatchDrone(index, x, y, weight);
                fleet.displayDrone(idx);
                break;
            case 10:
                std::cout << "ID of drone to recharge: " << endl;
                std::cin >> ID;
                fleet.rechargeDrone(ID);
                break;
            case 11:
                fleet.countByStatus();
                break;
            case 12:
                fleet.processOrders("orders.txt", "delivery_log.txt");
                break;
            case 13:
                fleet.writeFleetToFile("fleet_output.txt");
                break;
            case 14:
                std::cout << "Enter new drone's name: ";
                std::cin >> name;
                drone.setName(name);
                
                std::cout << "Enter with no commas - ID, model, battery, maxPayload, x position, y position, status (all caps): ";
                std::cin >> ID >> model >> battery >> maxPayload >> x >> y >> status;
                
                if (drone.setID(ID) && drone.setModel(model) && drone.setBattery(battery) && drone.setMaxPayload(maxPayload) && drone.setPosition(0, x) && drone.setPosition(1, y) && drone.setStatus(status)) { // validate
                    drone.setID(ID);
                    drone.setModel(model);
                    drone.setBattery(battery);
                    drone.setMaxPayload(maxPayload);
                    drone.setPosition(0, x);
                    drone.setPosition(1, y);
                    drone.setStatus(status);

                } else {
                    std::cout << "invalid specs" << endl;
                    
                }
                
                fleet.addDrone(drone);
                break;


            case 0:
                std::cout << "Goodbye!" << endl;
                break;
            default:
                std::cout << "Invalid option." << endl;
        }
    }
    return 0;
}
