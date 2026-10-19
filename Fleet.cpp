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
    //linear congruential generator: updates state and returns the new value
    state = (state * 1103515245ULL + 12345ULL) % 2147483648ULL;
    return state;
} 

void Fleet::swapDrones(int i, int j)
{
    // TODO: exchange drones[i] and drones[j] using a temporary Drone
    //classic three-step swap through a temporary
    Drone temp = drones.at(i);
    drones.at(i)= drones.at(j);
    drones.at(j) = temp;

}

bool Fleet::validIndex(int index) const
{
    // TODO: true if 0 <= index < number of drones
    //index must be inside the bounds of the vector
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
    //check every existing drone for a matching ID
    for (int i=0; i < getSize(); i++) {
        if (d.getID() == drones.at(i).getID()) { // duplicate id found
            std::cout << "Drone ID already exists" << std::endl;
            return false;
        }
    }
    //no duplicate, so append it
    drones.push_back(d);
    return true;
}

Drone Fleet::getDrone(int index) const
{
    // TODO: check the range; print an error and return Drone() if invalid
    //return a default drone if the index is out of range
    if (!validIndex(index)) {
        std::cerr << "outside of range" << std::endl;
        return Drone();
    } else {
        return drones.at(index);
    }
}

int Fleet::getSize() const
{
    //cast since vector size is unsigned
    return (int)drones.size();
}

// ---------- Sorting ----------
// Follow the counting rules in Section 4.2 exactly; your counts are checked.

void Fleet::selectionSortByID()
{
    int comparisons = 0, swaps = 0;

    //each pass places the next smallest ID at position i
    for (int i = 0; i < getSize() - 1; i++) {
        int smallest = i;

        //scan the unsorted part for the smallest ID
        for (int j = i + 1; j < getSize(); j++) {
            if (drones.at(j).getID() < drones.at(smallest).getID()) {
                comparisons++;
                smallest = j; 
            }
        }

        //only count a swap if the smallest wasn't already in place
        if (i != smallest) swaps++;
        std::swap(drones[i], drones[smallest]);
        std::cout << comparisons << " comparisons, " << swaps << " swaps." << std::endl;
    }
}

void Fleet::insertionSortByBattery()
{
    int comparisons = 0, shifts = 0;
    int N = getSize();

    //grow a sorted section on the left one drone at a time
    for (int i = 1; i < getSize(); i++){
        Drone key = drones.at(i);
        int j = i - 1;

        //shift drones right until the key's spot is found
        while(j >= 0 && drones.at(j).getBattery() < key.getBattery()){
            drones.at(j+1) = drones.at(j); 
            comparisons++;
            shifts++;
            j--;
        }
        
        //the comparison that ended the loop also counts (unless j ran off the front)
        if (j >= 0) {
            comparisons++;          //avoiding undercounting the last comparison
        }

        //drop the key into the gap
            drones.at(j+1) = key;
    }
    std::cout << comparisons << " comparisons, " << shifts << " shifts." << std::endl;

}

void Fleet::sortByName()
{
    int comparisons = 0, shifts = 0;
    int N = getSize();

    //same insertion sort as above, but alphabetical by name
    for (int i = 1; i < getSize(); i++){
        Drone key = drones.at(i);
        int j = i - 1;

        //shift names that come after the key one spot right
        while(j >= 0 && drones.at(j).getName() > key.getName()){
            drones.at(j+1) = drones.at(j); 
            comparisons++;
            shifts++;
            j--;
        }
        
        //count the final comparison that stopped the loop
        if (j >= 0) {
            comparisons++;          //avoiding undercounting the last comparison
        }

        //insert the key in its sorted position
            drones.at(j+1) = key;
    }
    std::cout << comparisons << " comparisons, " << shifts << " shifts." << std::endl;

}

bool Fleet::isSortedByID() const
{
    //any neighbor pair out of order means not sorted
    for (int i = 0; i < getSize() - 1; i++){
        if (drones.at(i).getID() > drones.at(i+1).getID()) return false;
    }
    return true;
}

// ---------- Searching ----------

int Fleet::linearSearchByName(const string& name) const
{
    //check each drone in order until the name matches
    for (int i = 0; i < getSize(); i++){
        if (drones.at(i).getName() == name){
            std::cout << i << " comparisons." << std::endl;
            return i;
        }
    }
    //not found: every drone was compared
    std::cout<<getSize()<<" comparisons"<<std::endl;
    return -1;
}

int Fleet::binarySearchByID(int id)
{
    int comparisons = 0;

    //binary search only works on sorted data
    if (!isSortedByID()){
        selectionSortByID();
    }

    //search window covers the whole fleet to start
    int low = 0;
    int high = getSize() - 1;
    while (low <= high) {
        //middle of the window (written this way to avoid overflow)
        int mid = low + ((high - low) / 2);

        //found it
        if (drones.at(mid).getID() == id){ 
            comparisons++;              //one comparison not counted at end of loop when index is found
            std::cout << comparisons << " comparisons." << std::endl;
            return mid;
        }
        //target is larger, so search the right half
        else if (drones.at(mid).getID() < id)
        {
            low = mid + 1;
        } 
        //target is smaller, so search the left half
        else 
        {
            high = mid - 1;
        }

        comparisons++;                  //each time the loop passes, one comparison is made
    }
    //window emptied without a match
    return -1;
}

// ---------- Dispatching ----------

int Fleet::findNearestAvailable(int x, int y, double weight) const
{
    int smallest_index = -1;

    //placeholder "closest" drone that's infinitely far away, so any real drone beats it
    Drone closest_available(INT_MAX, INT_MAX);
    closest_available.setID(INT_MAX);

    for (int i = 0; i < getSize(); i++){
        //skip drones that can't make this delivery
        if (!(drones.at(i).canDeliver(x, y, weight)))
        {
            continue;
        }

        //strictly closer than the current best: take it
        if (drones.at(i).squaredDistanceTo(x, y) < closest_available.squaredDistanceTo(x, y))
        {
            closest_available = drones.at(i);
            smallest_index = i;
            continue;
        }

        //tie on distance: the lower ID wins
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
    //-1 if no drone qualified
    return smallest_index;
}

bool Fleet::dispatchDrone(int index, int x, int y, double weight)
{
    //only complete the delivery if the drone is able to
    if (drones.at(index).canDeliver(x, y, weight)) {
        drones.at(index).completeDelivery(x, y, weight);
        return true;
    }
    return false;
}

bool Fleet::rechargeDrone(int id)
{
    //find the drone's position by ID
    int index = binarySearchByID(id);

    //separately confirm the ID exists in the fleet
    bool temp = false;
    for(int i = 0; i < getSize(); i++)
    {
        if(id == drones.at(i).getID())
        {
            temp = true;
        }
    }
    if(!temp)
    {
        std::cout<<"Drone of ID "<< id<< " could not be found"<<std::endl;
        return false;
    }

    //drones under maintenance can't be charged
    if (drones.at(index).getStatus() == "MAINTENANCE, a"){
        std::cout << "Drone currently in maintenance, cannot charge" << std::endl;
        return false;
    } 

    //fill the battery and mark the drone ready
    drones.at(index).setBattery(100);
    drones.at(index).setStatus("IDLE");
    return true;
}

void Fleet::countByStatus() const
{
    int idleCount = 0, chargingCount = 0, maintCount = 0, totalCharge = 0;

    //tally each status and add up battery levels
    for (int i = 0; i < getSize(); i++){
        if(drones.at(i).getStatus() == "IDLE") idleCount++;
        if(drones.at(i).getStatus() == "CHARGING") chargingCount++;
        if(drones.at(i).getStatus() == "MAINTENANCE") maintCount++;
        totalCharge += drones.at(i).getBattery(); 
    }

    //print the counts and the average battery
    std::cout << "Idle Count: " << idleCount << " | Charging count: " << chargingCount 
    << " | Maintenance Count: " << maintCount << " | Average battery: " 
    << totalCharge/ (double) getSize() << std::endl;
}

void Fleet::processOrders(const string& orderFile, const string& logFile)
{
    //open the orders to read and the log to write
    std::ifstream fin(orderFile);
    std::ofstream fout(logFile);
    if (!fin || !fout){
        std::cout << "ERROR OPENNING FILE" << std::endl;
        return;
    }

    std::string id;
    int x, y, ordersComp = 0, ordersTotal = 0;
    double weight, totalDistance = 0;

    //limit decimal output for both the log and the console
    fout << std::setprecision(1);
    std::cout << std::setprecision(1);

    //handle one order per line
    while (fin >> id >> x >> y >> weight){
        ordersTotal++;

        //a drone is available for this order
        if (findNearestAvailable(x, y, weight) != -1){
            ordersComp++;
            int index = findNearestAvailable(x, y, weight);

            //record distance and battery before the drone moves
            totalDistance += drones.at(index).distanceTo(x,y);
            double oldBat = drones.at(index).getBattery();
            dispatchDrone(index, x, y, weight);

            //log the assignment to the file and the screen
            fout << "Order: " << id << ": Drone: " << index << " (" << drones.at(index).getName() << ") distance " 
            << drones.at(index).distanceTo(x, y) << " battery " << oldBat << " -> " << drones.at(index).getBattery() << std::endl;
                    
            std::cout << "Order: " << id << ": Drone: " << index << " (" << drones.at(index).getName() << ") distance " 
            << drones.at(index).distanceTo(x, y) << " battery " << oldBat << " -> " << drones.at(index).getBattery() << std::endl;
        }
        //no drone could take it
        else {
            fout << "Order: " << id << ": UNASSIGNED" << std::endl;
            std::cout << "Order: " << id << ": UNASSIGNED" << std::endl;
        }
    }

    //final summary line
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

    //go backwards, swapping each drone with a random one at or before it
    for(int i = (n-1); i >= 1; i--)
    {
        j = nextRandom(seed) % (i+1);
        swapDrones(i, j);
    }
}

void Fleet::displayAll() const
{
    // TODO: print every drone with its index
    //print each drone in fleet order
    for(int i = 0; i < getSize(); i++)
    {
        displayDrone(i);
    }
}

void Fleet::displayDrone(int index) const
{
    // TODO: check the range, then print one drone
    //bail out on a bad index
    if(!(validIndex(index)))
    {
        std::cout<<"That is an invalid index"<<std::endl;
        return;
    }

    //print all fields on one line
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

    //write one drone per line, same layout as the input file
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