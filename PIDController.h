#pragma once
class PIDController
{
    public:
    PIDController(const int _kp, const int _ki, const int _kd, const int _dt, const int _min, const int _max);
    ~PIDController();

    int process(const int setpoint, const int data);

    private:
    int kp;
    int ki;
    int kd;

    int integral;
    int dt;

    int min;
    int max;
    int preError;
};
