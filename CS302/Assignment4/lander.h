#include<cmath>

const int time = 1;

class lander {
public:
    lander ( double = 0 , double = 0 , double = 0 , double = 0 , double = 0 , int = 0);
    double get_velocity () const;
    double get_altitude () const;
    double get_fuel_amount () const;
    int get_id () const;
    double get_mass () const;
    char get_status () const;
    bool change_flow_rate ( double );
    void simulate ();
    bool operator>(const lander &) const;
private:
    double flow_rate;
    double velocity;
    double altitude;
    double fuel_amount;
    bool stillLanding;
    int id;
    int timesSimulated;
    double LANDER_MASS;
    double MAX_FUEL_CONSUMPTION_RATE;
    double MAX_THRUST;
};

lander::lander(double mass, double max_thrust, double max_fuel, 
double alt, double fuel, int id){
    LANDER_MASS = mass;
    MAX_THRUST = max_thrust;
    MAX_FUEL_CONSUMPTION_RATE = max_fuel;
    altitude = alt;
    fuel_amount = fuel;
    this->id = id;
    timesSimulated = 0;
    flow_rate = 0.0;
    velocity = 0;
    stillLanding = true;
}

double lander::get_velocity() const{
    return velocity;
}

double lander::get_altitude() const{
    return altitude;
}

double lander::get_mass() const{
    return LANDER_MASS;
}

double lander::get_fuel_amount() const{
    return fuel_amount;
}

int lander::get_id() const{
    return id;
}

char lander::get_status() const{
    if(stillLanding)
        return 'a';
    if(!stillLanding && velocity <= -2)
        return 'c';
    return 'l';
}

bool lander::change_flow_rate(double r){
    if(r<=1 && r>=0){
        if(fuel_amount>0)
            this->flow_rate = r;
        return true;
    }
    return false;
}

void lander::simulate(){
    double v = time * ((flow_rate*MAX_THRUST)/(LANDER_MASS+fuel_amount))-1.62;  // Calculate the instantaneous velocity 
    velocity += v;                                                              // Increment/update velocity field by v
    altitude += velocity;                                                       // Increment/update altitude field by TIME × velocity field
    if(altitude <= 0)                                                           // Update stillLanding field if necessary
        stillLanding = false;
    fuel_amount -= time*MAX_FUEL_CONSUMPTION_RATE*fabs(v);                       // Decrement/update fuel amount by TIME × MAX FUEL RATE × |v
    if(fuel_amount < 0)                                                         // Set fuel amount to 0 if negative
        fuel_amount = 0;
    timesSimulated++;                                                           // Increment/update timesSimulated by 1
    return;
}

bool lander::operator>(const lander& rhs) const{

    if(this->timesSimulated < rhs.timesSimulated)   //compare times simulated
        return true;
    else if(this->timesSimulated > rhs.timesSimulated)
        return false;
    if(this->altitude < rhs.altitude)               //compare altitude
        return true;
    else if(this->altitude > rhs.altitude)
        return false;
    if(this->fuel_amount < rhs.fuel_amount)         //compare  fuel
        return true;
    else if(this->fuel_amount > rhs.fuel_amount)
        return false;
    if(this->LANDER_MASS > rhs.LANDER_MASS)         //compare mass
        return true;
    else if(this->LANDER_MASS < rhs.LANDER_MASS)
        return false;
    if(this->id < rhs.id)                           //compare ids
        return true;
    else
        return false;
    
}