// Drone.cpp
// ESE 224 Fall 2026 Midterm Project (starter code)
// Team members: Daniel Zhou, Ella Chen, Logan Jeong
//
// Every function below compiles but does nothing useful yet.
// Replace each TODO with your implementation (see Section 3 of the handout)




#include "Drone.h"
#include <cctype>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "myDouble.h"
using std::string;


// ---------- Constructors ----------

//default drone: no name, invalid ID, full battery, at the origin
Drone::Drone()
{
    name = "";
    ID = -1;
    model = "";
    battery = 100.0;
    maxPayload = 0.0;
    position[0] = 0;
    position[1] = 0;
    status = "IDLE";
    deliveriesCompleted = 0;
}

//full constructor, goes through the setters so every value gets validated
Drone::Drone(const string& n, int id, string& m, double b, double p, int x, int y, const string& s)
{
    setName(n);
    setID(id);
    setModel(m);
    setBattery(b);
    setMaxPayload(p);
    setPosition(0, x);
    setPosition(1, y);
    setStatus(s);
}

//position-only constructor (used as the "far away" placeholder in findNearestAvailable)
Drone::Drone(int x, int y)
{
    setPosition(0, x);
    setPosition(1, y);
}



// ---------- Accessors ----------

//simple getters that just return each field
string Drone::getName() const { return name; }
int Drone::getID() const { return ID; }
string Drone::getModel() const { return model; }
double Drone::getBattery() const { return battery; }
double Drone::getMaxPayload() const { return maxPayload; }
string Drone::getStatus() const { return status; }
int Drone::getDeliveriesCompleted() const { return deliveriesCompleted; }

//index 0 is x, index 1 is y, anything else returns -1
int Drone::getPosition(int index) const
{
    if(index == 0)
    {
        return position[0];
    }
    else if(index == 1)
    {
        return position[1];
    }
    return -1;
}

// ---------- Mutators ----------

//any name is allowed, so no check needed
void Drone::setName(const string& n)
{
    name = n;
}

//ID must be positive
bool Drone::setID(int id)
{
    if(id > 0)
    {
        ID = id;
        return true;
    }
    return false;
}

//only the three known models are accepted
bool Drone::setModel(string& m)
{
    if(m == "Kestrel" || m == "Falcon" || m == "Condor")
    {
        model = m;
        return true;
    }
    return false;
}

//battery is a percentage, so it has to stay between 0 and 100
bool Drone::setBattery(double b)
{
    if(b >= 0 && b <= 100)
    {
        battery = b;
        return true;
    }
    return false;
}

//payload capacity has to be positive
bool Drone::setMaxPayload(double p)
{
    if(p > 0)
    {
        maxPayload = p;
        return true;
    }
    return false;
}

//index picks x or y, and coordinates can't be negative
bool Drone::setPosition(int index, int value)
{
    if(index == 0 || index == 1)
    {
        if(value >= 0)
        {
            position[index] = value;
            return true;
        }
    }
    return false;
}

//status has to be one of the three valid states
bool Drone::setStatus(const string& s)
{
    if(s == "IDLE" || s == "CHARGING" || s == "MAINTENANCE")
    {
        status = s;
        return true;
    }
    return false;
}

// ---------- Delivery methods ----------

//straight-line distance using the pythagorean theorem
double Drone::distanceTo(int x, int y) const
{
    double distance = 0;
    //myDouble wraps the differences so ^2 means squaring
    myDouble deltaY(position[1] - y);
    myDouble deltaX(position[0] - x);
    distance = sqrt((deltaX^2) + (deltaY^2));
    return distance;
}

//same as distanceTo but skips the sqrt, good for comparing distances exactly
long int Drone::squaredDistanceTo(int x, int y) const
{
    long int distance = 0;
    myDouble deltaY(position[1] - y);
    myDouble deltaX(position[0] - x);
    distance = (deltaX^2) + (deltaY^2);
    return distance;
}


//battery cost grows with distance and with how heavy the package is
double Drone::batteryNeeded(int x, int y, double weight) const
{
    double batteryNeeded = distanceTo(x, y) * BATTERY_PER_UNIT *(1 + PAYLOAD_FACTOR * weight);
    return batteryNeeded;
}

//a drone can deliver if it's idle, can lift the weight, and keeps the safety reserve after the trip
bool Drone::canDeliver(int x, int y, double weight) const
{
    if((status == "IDLE") && (weight <= maxPayload) && (battery - batteryNeeded(x, y, weight) >= SAFETY_RESERVE))
    {
        return true;
    }
    return false;
}

void Drone::completeDelivery(int x, int y, double weight)
{
    //double-check the delivery is still possible
    if(canDeliver(x, y, weight))
    {
        //use up battery, move to the destination, and count the delivery
        battery -= batteryNeeded(x, y, weight);
        position[0] = x;
        position[1] = y;
        deliveriesCompleted++;

        //send it to charge if the battery got too low
        if(battery < LOW_BATTERY)
        {
            setStatus("CHARGING");
        }
    }
    else
    {
        std::cout<<"Drone cannot complete the delivery"<<std::endl;
    }
}

// ---------- Display and comparison ----------

//print every field on one line
void Drone::displayDrone() const
{
    std::cout << "Name: " << name << " | ID:" << ID << " | Model:" << model << " | Battery:" <<  " | Max Payload: " <<
    maxPayload << " | Position: " << getPosition(0) << ", " << getPosition(1) << " | Status: " << status <<
    " | Completed Delivery Count: " << deliveriesCompleted << std::endl;
}

//two drones are the same if they share an ID
bool Drone::operator==(const Drone& other) const
{
    if (ID == other.ID) return true;
    return false;
}