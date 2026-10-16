// Drone.cpp
// ESE 224 Fall 2026 Midterm Project (starter code)
// Team members: Daniel Zhou, Ella Chen, Logan Jeong
//
// Every function below compiles but does nothing useful yet.
// Replace each TODO with your implementation (see Section 3 of the handout)



//I MADE A CHANGE

//checking git
#include "Drone.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "myDouble.h"
using std::string;


// ---------- Constructors ----------

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

Drone::Drone(int x, int y)
{
    setPosition(0, x);
    setPosition(1, y);
}


// ---------- Accessors ----------

string Drone::getName() const { return name; }
int Drone::getID() const { return ID; }
string Drone::getModel() const { return model; }
double Drone::getBattery() const { return battery; }
double Drone::getMaxPayload() const { return maxPayload; }
string Drone::getStatus() const { return status; }
int Drone::getDeliveriesCompleted() const { return deliveriesCompleted; }

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

void Drone::setName(const string& n)
{
    name = n;
}

bool Drone::setID(int id)
{
    if(id > 0)
    {
        ID = id;
        return true;
    }
    return false;
}

bool Drone::setModel(string& m)
{
    if(m == "Kestral" || m == "Falcon" || m == "Condor")
    {
        model = m;
        return true;
    }
    return false;
}

bool Drone::setBattery(double b)
{
    if(b >= 0 && b <= 100)
    {
        battery = b;
        return true;
    }
    return false;
}

bool Drone::setMaxPayload(double p)
{
    if(p > 0)
    {
        maxPayload = p;
        return true;
    }
    return false;
}

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

double Drone::distanceTo(int x, int y) const
{
    double distance = 0;
    myDouble deltaY = (position[1]-y);
    myDouble deltaX = (position[0] - x);
    distance = sqrt((deltaX^2) + (deltaY^2));
    return distance;    
}

double Drone::batteryNeeded(int x, int y, double weight) const
{
    double batteryNeeded = distanceTo(x, y) * BATTERY_PER_UNIT *(1 + PAYLOAD_FACTOR * weight);
    return batteryNeeded;
}

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
    if(canDeliver(x, y, weight))
    {
        battery -= batteryNeeded(x, y, weight);
        position[0] = x;
        position[1] = y;
        deliveriesCompleted++;
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

void Drone::displayDrone() const
{
    std::cout << "Name: " << name << " | ID:" << ID << " | Model:" << model << " | Battery:" <<  " | Max Payload: " << 
    maxPayload << " | Position: " << getPosition(0) << ", " << getPosition(1) << " | Status: " << status <<
    " | Completed Delivery Count: " << deliveriesCompleted << std::endl;
}

bool Drone::operator==(const Drone& other) const
{
    if (ID == other.ID) return true;
    return false;
}
