#include "PIDController.h"
PIDController::PIDController()
{}


PIDController::PIDController(const int _kp, const int _ki, const int _kd, const int _dt, const int _min, const int _max) : 
kp(_kp),
ki(_ki),
kd(_kd),
integral(0),
dt(_dt),
min(_min),
max(_max),
preError(0)
{
}

PIDController::~PIDController()
{
}

int PIDController::process(const int setpoint, const int data)
{
    int error = setpoint - data;

    // P 
    int p = kp * error;

    // I
    integral += ki * dt;
    int i = ki * integral;

    // D
    int derivative = (error - preError) / dt;
    int d = kd * derivative;

    // calculate
    int output = p + i + d;
    
    if(output > max) output = max;
    else if(output < min) output = min;

    // save error to preError
    preError = error;
    
    return output;
}