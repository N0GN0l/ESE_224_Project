// Fleet.cpp
// ESE 224 Fall 2026 Midterm Project (starter code)
// Team members: Daniel Zhou, Ella Chen, Logan Jeong
//
// Every function below compiles but does nothing useful yet.
// Replace each TODO with your implementation (see Section 4 of the handout).
// Remember: no <algorithm>, no std::sort, std::swap, std::find, or std::shuffle.

#include "Fleet.h"
#include <climits>
#include <iostream>
#include <ostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
using std::string;

//I MADE A COMMENT
// ---------- Private helpers ----------

// Provided random number generator. Copy exactly; do not change.
unsigned long long Fleet::nextRandom(unsigned long long &state) const
{
    state = (state * 1103515245ULL + 12345ULL) % 2147483648ULL;
    return state;
} 

void Fleet::swapDrones(int i, int j)
{
    // TODO: exchange drones[i] and drones[j] using a temporary Drone
    Drone temp = drones.at(i);
    drones.at(i)= drones.at(j);
    drones.at(j) = temp;

}

bool Fleet::validIndex(int index) const
{
    // TODO: true if 0 <= index < number of drones
    if (index >= 0 && index < getSize()) {
        return true;
    } else {
        return false;
    }
}

// ---------- Accessors and mutators ----------

bool Fleet::addDrone(const Drone& d)
{
    // TODO: reject a duplicate ID (use operator==), otherwise add to the end
    // for (int i=0; i < getSize(); i++) {
        // if (d.getID() == drones.at(i).getID()) { // duplicate id found
            // std::cout << "Drone ID already exists" << std::endl; 
            // return false;
        // } 
        // else {
            drones.push_back(d);
            return true;
        // }
    // }
    // return false;
}

Drone Fleet::getDrone(int index) const
{
    // TODO: check the range; print an error and return Drone() if invalid
    if (!validIndex(index)) {
        std::cerr << "outside of range" << std::endl;
        return Drone();
    } else {
        return drones.at(index);
    }
}

int Fleet::getSize() const
{
    return (int)drones.size();
}

// ---------- Sorting ----------
// Follow the counting rules in Section 4.2 exactly; your counts are checked.

void Fleet::selectionSortByID()
{
    int comparisons = 0, swaps = 0;
    for (int i = 0; i < getSize() - 1; i++) {
        int smallest = i;

        for (int j = i + 1; j < getSize(); j++) {
            if (drones.at(j).getID() < drones.at(smallest).getID()) {
                comparisons++;
                smallest = j; 
            }
        }
        if (i != smallest) swaps++;
        std::swap(drones[i], drones[smallest]);
        std::cout << comparisons << " comparisons, " << swaps << " swaps." << std::endl;
    }
}

void Fleet::insertionSortByBattery()
{
    int comparisons = 0, shifts = 0;
    int N = getSize();
    for (int i = 1; i < getSize(); i++){
        Drone key = drones.at(i);
        int j = i - 1;
        while(j >= 0 && drones.at(j).getBattery() < key.getBattery()){
            drones.at(j+1) = drones.at(j); 
            comparisons++;
            shifts++;
            j--;
        }
        
        if (j >= 0) {
            comparisons++;          //avoiding undercounting the last comparison
        }
            drones.at(j+1) = key;
    }
    std::cout << comparisons << " comparisons, " << shifts << " shifts." << std::endl;

}

void Fleet::sortByName()
{
    int comparisons = 0, shifts = 0;
    int N = getSize();
    for (int i = 1; i < getSize(); i++){
        Drone key = drones.at(i);
        int j = i - 1;
        while(j >= 0 && drones.at(j).getName() > key.getName()){
            drones.at(j+1) = drones.at(j); 
            comparisons++;
            shifts++;
            j--;
        }
        
        if (j >= 0) {
            comparisons++;          //avoiding undercounting the last comparison
        }
            drones.at(j+1) = key;
    }
    std::cout << comparisons << " comparisons, " << shifts << " shifts." << std::endl;

}

bool Fleet::isSortedByID() const
{
    for (int i = 0; i < getSize() - 1; i++){
        if (drones.at(i).getID() > drones.at(i+1).getID()) return false;
    }
    return true;
}

// ---------- Searching ----------

int Fleet::linearSearchByName(const string& name) const
{
    for (int i = 0; i < getSize(); i++){
        if (drones.at(i).getName() == name){
            std::cout << i << " comparisons." << std::endl;
            return i;
        }
    }
    std::cout<<getSize()<<" comparisons"<<std::endl;
    return -1;
}

int Fleet::binarySearchByID(int id)
{
    int comparisons = 0;
    if (!isSortedByID()){
        selectionSortByID();
    }

    int low = 0;
    int high = getSize() - 1;
    while (low <= high) {
        int mid = low + ((high - low) / 2);
        if (drones.at(mid).getID() == id){ 
            comparisons++;              //one comparison not counted at end of loop when index is found
            std::cout << comparisons << " comaprisons." << std::endl;
            return mid;
        }
        else if (drones.at(mid).getID() < id)
        {
            low = mid + 1;
        } 
        else 
        {
            high = mid - 1;
        }

        comparisons++;                  //each time the loop passes, one comparison is made
    }
    std::cout << "Comparisons: " << comparisons << std::endl;
    return -1;
}

// ---------- Dispatching ----------

int Fleet::findNearestAvailable(int x, int y, double weight) const
{
    int smallest_index = -1;
    Drone closest_available(INT_MAX, INT_MAX);
    closest_available.setID(INT_MAX);

    for (int i = 0; i < getSize(); i++){
        if (!(drones.at(i).canDeliver(x, y, weight)))
        {
            continue;
        }
        if (drones.at(i).squaredDistanceTo(x, y) < closest_available.squaredDistanceTo(x, y))
        {
            closest_available = drones.at(i);
            smallest_index = i;
            continue;
        }
        if (drones.at(i).squaredDistanceTo(x, y) == closest_available.squaredDistanceTo(x, y))
        {
            if(drones.at(i).getID() < closest_available.getID())
            {
                closest_available = drones.at(i);
                smallest_index = i;
            }
            continue;
        }
    }
    return smallest_index;
}

bool Fleet::dispatchDrone(int index, int x, int y, double weight)
{
    if (drones.at(index).canDeliver(x, y, weight)) {
        drones.at(index).completeDelivery(x, y, weight);
        return true;
    }
    return false;
}

bool Fleet::rechargeDrone(int id)
{
    int index = binarySearchByID(id);
    if (drones.at(index).getStatus() == "MAINTENANCE, a"){
        std::cout << "Drone currently in maintenance, cannot charge" << std::endl;
        return false;
    } 
    drones.at(index).setBattery(100);
    drones.at(index).setStatus("IDLE");
    return false;
}

void Fleet::countByStatus() const
{
    int idleCount = 0, chargingCount = 0, maintCount = 0, totalCharge = 0;
    for (int i = 0; i < getSize(); i++){
        if(drones.at(i).getStatus() == "IDLE") idleCount++;
        if(drones.at(i).getStatus() == "CHARGING") chargingCount++;
        if(drones.at(i).getStatus() == "MAINTENANCE") maintCount++;
        totalCharge += drones.at(i).getBattery(); 
    }
    std::cout << "Idle Count: " << idleCount << " | Charging count: " << chargingCount 
    << " | Maintenance Count: " << maintCount << " | Average battery: " 
    << totalCharge/ (double) getSize() << std::endl;
}

void Fleet::processOrders(const string& orderFile, const string& logFile)
{
    std::ifstream fin(orderFile);
    std::ofstream fout(logFile);
    if (!fin || !fout){
        std::cout << "ERROR OPENNING FILE" << std::endl;
    }
    std::string id;
    int x, y, ordersComp = 0, ordersTotal = 0;
    double weight, totalDistance = 0;

    fout << std::setprecision(1);
    std::cout << std::setprecision(1);
    while (fin >> id >> x >> y >> weight){
        ordersTotal++;
        if (findNearestAvailable(x, y, weight) != -1){
            ordersComp++;
            int index = findNearestAvailable(x, y, weight);
            totalDistance += drones.at(index).distanceTo(x,y);
            double oldBat = drones.at(index).getBattery();
            dispatchDrone(index, x, y, weight);

            fout << "Order: " << id << ": Drone: " << index << " (" << drones.at(index).getName() << ") distance " 
            << drones.at(index).distanceTo(x, y) << " battery " << oldBat << " -> " << drones.at(index).getBattery() << std::endl;
                    
            std::cout << "Order: " << id << ": Drone: " << index << " (" << drones.at(index).getName() << ") distance " 
            << drones.at(index).distanceTo(x, y) << " battery " << oldBat << " -> " << drones.at(index).getBattery() << std::endl;
        }
        else {
            fout << "Order: " << id << ": UNASSIGNED" << std::endl;
            std::cout << "Order: " << id << ": UNASSIGNED" << std::endl;
        }
    }
    fout << "Assigned " << ordersComp << " of " << ordersTotal << ". Total distance flown: " << totalDistance << std::endl;
    std::cout << "Assigned " << ordersComp << " of " << ordersTotal << ". Total distance flown: " << totalDistance << std::endl;


}

// ---------- Other ----------

void Fleet::shuffleFleet(unsigned long long seed)
{
    // TODO: Fisher-Yates. state = seed; for i from n-1 down to 1:
    //       j = nextRandom(state) % (i + 1), then swap drones i and j.
    int j;
    int n = getSize();
    for(int i = (n-1); i > 1; i--)
    {
        j = nextRandom(seed) % (i+1);
        swapDrones(i, j);
    }
}

void Fleet::displayAll() const
{
    // TODO: print every drone with its index
    for(int i = 0; i < getSize(); i++)
    {
        displayDrone(i);
    }
}

void Fleet::displayDrone(int index) const
{
    // TODO: check the range, then print one drone
    if(!(validIndex(index)))
    {
        std::cout<<"That is an invalid index"<<std::endl;
        return;
    }
    std::cout<<drones.at(index).getName()<<" "
        <<drones.at(index).getID()<<" "
        <<drones.at(index).getModel()<<" "
        <<drones.at(index).getBattery()<<" "
        <<drones.at(index).getMaxPayload()<<" "
        <<drones.at(index).getPosition(0)<< " " <<drones.at(index).getPosition(1)<<" "
        <<drones.at(index).getStatus()<<std::endl;
}

void Fleet::writeFleetToFile(const string& filename) const
{
    // TODO: same format as drones.txt plus deliveriesCompleted; one decimal for battery and payload
    std::ofstream fout(filename);    
    for(int i = 0; i < getSize(); i++)
    {
        fout<<drones.at(i).getName()<<" "
            <<drones.at(i).getID()<<" "
            <<drones.at(i).getModel()<<" "
            <<drones.at(i).getBattery()<<" "
            <<drones.at(i).getMaxPayload()<<" "
            <<drones.at(i).getPosition(0)<< " " <<drones.at(i).getPosition(1)<< " "
            <<drones.at(i).getStatus()<<std::endl;
    }
}