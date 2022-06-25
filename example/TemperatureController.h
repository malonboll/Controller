#include "Base/Machine.h"
#include "Base/Filters/MovingAverageFilter.h"
#include "Sensors/TemperatureSensor.h"
#include "PID/PIDController.h"

constexpr int LOW_TEMPERATURE = 12888;  // unit : LSB
constexpr int HIGH_TEMPERATURE = 66888; // unit : LSB

class TemperatureController
{
public:
    enum eTemperatureStatus
    {
        TEMPERATURE_SENSOR_ERROR,
        TOO_HIGH,
        TOO_LOW,
        OK
    };

    TemperatureController(Machine* pMachine, TemperatureSensor* pTempSensor, MovingAverageFilter* pMovingAverageFilter);
    ~TemperatureController();

    eTemperatureStatus process(const int wantedTemperature);

private:
    int getTemperature() const;
    int filter(const int data) const;
    void delay(const int time) const;
    eTemperatureStatus indicator(const temperature);

    int delay_ms;

    Machine* machinObject;
    TemperatureSensor* tSensor;
    MovingAverageFilter* movingFilter;
    PIDController delayController;
};