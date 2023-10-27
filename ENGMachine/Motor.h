#include <AFMotor.h>

class Motor 
{
  private:
    int motorNumber;
    int speed;
    String status;
    AF_DCMotor motor;
    int triggerOffset;
    int lastTriggerTime;
    int nextTriggerTime;
    int triggerTime;

  public:
    Motor(int motorNumber, int triggerTime) : motorNumber(motorNumber), motor(motorNumber), triggerTime(triggerTime)
    {
      speed = 0;
      stop();
    }

    void stop()
    {
      motor.run(RELEASE);
      status = "STOPPED";
    }

    // Function to get the status of a specified motor
    String getStatus()
    {
      return status;
    }

    // Function to set the speed of a a specified motor
    void setSpeed(int speed)
    {
      motor.setSpeed(speed);
    }

    // Function to set a specified motor to rotate forwards at a specified speed
    void forward()
    {
      motor.run(FORWARD);
      status = "MOVING";
    }

    // Function to set a specified motor to rotate backwards at a specified speed
    void backward()
    {
      motor.run(BACKWARD);
      status = "MOVING";
    }

    // Function to get the trigger offset value of a specified motor
    int offset()
    {
      return triggerOffset;
    }

    // Function to calculate the next trigger time of a specified motor
    void calcNextTriggerTime(int lastTriggerTime)
    {
      nextTriggerTime = lastTriggerTime + triggerOffset;
    }

    int getMotorNumber()
    {
      return motorNumber;
    }
};