// Thermometer.cpp : Defines the entry point for the console application.
//

using namespace std; 

typedef enum
{
	celsius, fahrenheit
} TemperatureScale;

typedef enum
{
	up, down
} TemperatureDirection;


class AlarmCondition
{
private:

	double target;
	float tolerance;
	TemperatureDirection direction;
	char action[255];
	bool reported;

public:
	// Constructor
	AlarmCondition(double target, float tolerance, TemperatureDirection direction, char* action, TemperatureScale scale = celsius);
	// Destructor
	~AlarmCondition();

	// Setter and getters
	bool getReported();
	void setReported(bool value);
	double getTarget();
	float getTolerance();
	TemperatureDirection getDirection();
	char* getAction();

};
	
class Thermometer
{
private:
	
	static const int MaxTempHistory = 5;
	static const int MaxAlarmMonitors = 5;

	double currentTemp;
	double histroyTemp[MaxTempHistory];
	AlarmCondition* alarmConditions[MaxAlarmMonitors];
	int numAlarmMonitors;

	// Check the alarm conditions
	void checkAlarmCondition();

public:
	// Constructor
	Thermometer(double value, TemperatureScale scale = celsius);
	// Destructor
	~Thermometer();

	// Setter and getters
	double getTemperature(TemperatureScale scale = celsius);
	void setTemperature(double value, TemperatureScale scale = celsius);

	// Add Alarms
	bool addAlarmMonitor(AlarmCondition* alarmCondition);
	void removeAllAlarmMonitors();
	
	// utility functions
	void printTemperatureReadings(TemperatureScale scale = celsius);
	void printAlarmMonitors(TemperatureScale scale = celsius);
}; 

