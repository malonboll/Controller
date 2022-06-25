#include "TemperatureController.h"

TemperatureController::TemperatureController(Machine* pMachine, TemperatureSensor* pTempSensor, MovingAverageFilter* pMovingAverageFilter) :
delay_ms(0),
machinObject(pMachine),
tSensor(pTempSensor),
movingFilter(pMovingAverageFilter),
delayController(2,1,0,1,0,100000)
{

}

TemperatureController::~TemperatureController()
{

}

eTemperatureStatus TemperatureController::process(const int wantedTemperature)
{
    int curTemperature = getTemperature();

    if(curTemperature == -1)
        return eTemperatureStatus::TEMPERATURE_SENSOR_ERROR; 
        // Temperature sensor measure error escape -->

    int filteredData = filter(curTemperature);
    
    delay_ms = delayController.process(wantedTemperature, filteredData);
    delay(delay_ms);

    return indicator(filteredData);
}

int TemperatureController::getTemperature() const
{
    return tSensor.getTemperature();
}

int TemperatureController::filter(const int data) const
{
    return movingFilter.filtering(data);
}

void TemperatureController::delay(const int time) const
{
    systemDelay(time);
}

eTemperatureStatus TemperatureController::indicator(const int temperature)
{
    if(LOW_TEMPERATURE > temperature) return eTemperatureStatus::TOO_LOW;
    else if(HIGH_TEMPERATURE < temperature) return eTemperatureStatus::TOO_HIGH;
    else return eTemperatureStatus::OK;
}