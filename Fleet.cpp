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
#include <fstream>
#include <iomanip>
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
}

bool Fleet::validIndex(int index) const
{
    // TODO: true if 0 <= index < number of drones
    return false;
}

// ---------- Accessors and mutators ----------

bool Fleet::addDrone(const Drone& d)
{
    // TODO: reject a duplicate ID (use operator==), otherwise add to the end
    return false;
}

Drone Fleet::getDrone(int index) const
{
    // TODO: check the range; print an error and return Drone() if invalid
    return Drone();
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
    int N = drones.size();
    for (int i = 1; i < drones.size() - 1; i++){
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
        drones.at(j+1);
    }
    std::cout << comparisons << " comparisons, " << shifts << " shifts." << std::endl;

}

void Fleet::sortByName()
{
    int comparisons = 0, shifts = 0;
    int N = drones.size();
    for (int i = 1; i < drones.size() - 1; i++){
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
        drones.at(j+1);
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
        if (drones.at(mid).getID() < id)
        {
            low = mid + 1;  
        } 
        else high = mid - 1;
        comparisons++;                  //each time the loop passes, one comparison is made
    }
    return -1;
}

// ---------- Dispatching ----------

int Fleet::findNearestAvailable(int x, int y, double weight) const
{
    int smallest_index = -1;
    Drone closest_available(INT_MAX, INT_MAX);
    closest_available.setID(INT_MAX);

    for (int i = 0; i < drones.size(); i++){
        if (drones.at(i).canDeliver(x, y, weight))
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
    // TODO: check index and canDeliver, then completeDelivery
    return false;
}

bool Fleet::rechargeDrone(int id)
{
    // TODO: battery 100 and IDLE, unless MAINTENANCE; message if not found
    return false;
}

void Fleet::countByStatus() const
{
    // TODO: counts of IDLE, CHARGING, MAINTENANCE and the average battery
}

void Fleet::processOrders(const string& orderFile, const string& logFile)
{
    // TODO: for each order in file order, find the nearest available drone and dispatch it.
    // Write one line per order to the screen and the log, then the summary line.
    // Sum the exact distances; round only when printing.
}

// ---------- Other ----------

void Fleet::shuffleFleet(unsigned long long seed)
{
    // TODO: Fisher-Yates. state = seed; for i from n-1 down to 1:
    //       j = nextRandom(state) % (i + 1), then swap drones i and j.
}

void Fleet::displayAll() const
{
    // TODO: print every drone with its index
}

void Fleet::displayDrone(int index) const
{
    // TODO: check the range, then print one drone
}

void Fleet::writeFleetToFile(const string& filename) const
{
    // TODO: same format as drones.txt plus deliveriesCompleted; one decimal for battery and payload
}
