// Drone.cpp
// ESE 224 Fall 2026 Midterm Project (starter code)
// Team members: Daniel Zhou, Ella Chen, Logan Jeong
//
// Every function below compiles but does nothing useful yet.
// Replace each TODO with your implementation (see Section 3 of the handout)


//checking git
#include "Drone.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "myDouble.h"
using std::string;

// ------------- String helper methods ----------------------
char to_upper(unsigned char c)
{
    return std::toupper(c);
}

void to_upper_inplace(char& c)
{
    c = to_upper(c);
}

void make_entire_string_upper(const string& word)
{
    std::transform(word.cbegin(), word.cend(), word.begin(), to_upper);
}

char to_lower(unsigned char c)
{
    return std::tolower(c);
}

void to_lower_inplace(char& c)
{
    c = to_lower(c);
}

void make_entire_string_lower(const string& word)
{
    std::transform(word.cbegin(), word.cend(), word.begin(), to_lower);
}



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

Drone::Drone(const string& n, int id, string& m, double b, double p,
             int x, int y, const string& s) : Drone()
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
        this->ID = id;
        return true;
    }
    return false;
}

bool Drone::setModel(string& m)
{
    make_entire_string_lower(m);
    if(m == "kestral" || m == "falcon" || m == "condor")
    {
        to_upper_inplace(m[0]);
        this->model = m;
        return true;
    }
    return false;
}

bool Drone::setBattery(double b)
{
    if(b >= 0 && b <= 100)
    {
        this->battery = b;
        return true;
    }
    return false;
}

bool Drone::setMaxPayload(double p)
{
    if(p > 0)
    {
        this->maxPayload = p;
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
            this->position[index] = value;
            return true;
        }
    }
    return false;
}

bool Drone::setStatus(const string& s)
{
    make_entire_string_upper(s);
    if(s == "IDLE" || s == "CHARGING" || s == "MAINTENANCE")
    {
        this->status = s;
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
    if(status == "IDLE" && weight <= maxPayload && battery - batteryNeeded(x, y, weight) >= SAFETY_RESERVE)
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
    // TODO: print every member with a label
}

bool Drone::operator==(const Drone& other) const
{
    // TODO: two drones are equal if they have the same ID
    return false;
}
