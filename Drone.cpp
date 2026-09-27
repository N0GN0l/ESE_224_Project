// Drone.cpp
// ESE 224 Fall 2026 Midterm Project (starter code)
// Team members: Daniel Zhou, Ella Chen, Logan Jeong
//
// Every function below compiles but does nothing useful yet.
// Replace each TODO with your implementation (see Section 3 of the handout)

#include "Drone.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <iomanip>
#include <cmath>
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

Drone::Drone(const string& n, int id, const string& m, double b, double p,
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
    // TODO: valid when id > 0
    if(id > 0)
    {
        this->ID = id;
        return true;
    }
    return false;
}

bool Drone::setModel(const string& m)
{
    // TODO: valid when m is "Kestrel", "Falcon", or "Condor"
    make_entire_string_lower(m);
    if(m == "kestral" || m == "falcon" || m == "condor")
    {
        this->model = m;
        return true;
    }
    return false;
}

bool Drone::setBattery(double b)
{
    // TODO: valid when 0 <= b <= 100
    if(b >= 0 && b <= 100)
    {
        this->battery = b;
        return true;
    }
    return false;
}

bool Drone::setMaxPayload(double p)
{
    // TODO: valid when p > 0
    if(p > 0)
    {
        this->maxPayload = p;
        return true;
    }
    return false;
}

bool Drone::setPosition(int index, int value)
{
    // TODO: valid when index is 0 or 1 and value >= 0
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
    // TODO: valid when s is "IDLE", "CHARGING", or "MAINTENANCE"
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
    // TODO: straight-line distance from this drone to (x, y)
    return 0.0;
}

double Drone::batteryNeeded(int x, int y, double weight) const
{
    // TODO: distanceTo(x, y) * BATTERY_PER_UNIT * (1 + PAYLOAD_FACTOR * weight)
    return 0.0;
}

bool Drone::canDeliver(int x, int y, double weight) const
{
    // TODO: IDLE, weight <= maxPayload, and enough battery to keep SAFETY_RESERVE
    return false;
}

void Drone::completeDelivery(int x, int y, double weight)
{
    // TODO: use battery, move to (x, y), count the delivery, switch to CHARGING if below LOW_BATTERY
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
