// Thermometer.cpp : Defines the entry point for the console application.
//
#include <string> 
#include <iostream> 
#include <fstream> 
#include <math.h>
#include "Thermometer.h"

using namespace std; 

AlarmCondition::AlarmCondition(double target, float tolerance, TemperatureDirection direction, char* action, TemperatureScale scale)
{
	AlarmCondition::target = scale == fahrenheit ? (target + 32) * 1.8 : target;
	AlarmCondition::tolerance = tolerance;
	AlarmCondition::direction = direction;
	strncpy_s(AlarmCondition::action, action, sizeof(AlarmCondition::action));
	reported = true;
}

AlarmCondition::~AlarmCondition()
{
}

bool AlarmCondition::getReported()
{
	return reported;
}

void AlarmCondition::setReported(bool value)
{
	reported = value;
}

double AlarmCondition::getTarget()
{
	return target;
}

float AlarmCondition::getTolerance()
{
	return tolerance;
}

TemperatureDirection AlarmCondition::getDirection()
{
	return direction;
}

char* AlarmCondition::getAction()
{
	return action;
}

Thermometer::Thermometer(double value, TemperatureScale scale)
{
	currentTemp = scale == fahrenheit ? (value + 32) * 1.8 : value;
	for (int i = 0; i < MaxTempHistory; i++)
	{
		histroyTemp[i] = currentTemp;
	}
	numAlarmMonitors = 0;
}

Thermometer::~Thermometer()
{
	removeAllAlarmMonitors();
}

double Thermometer::getTemperature(TemperatureScale scale)
{
	if (scale == fahrenheit)
	{
		return ((currentTemp - 32) / 1.8);
	}
	else
	{
		return currentTemp;
	}
}

void Thermometer::setTemperature(double value, TemperatureScale scale)
{
	if (scale == fahrenheit)
	{
		currentTemp =  (value + 32) * 1.8;
	}
	else
	{
		currentTemp = value;
	}

	for (int i = 0; i < MaxTempHistory - 1; i++)
	{
		histroyTemp[i+1] = histroyTemp[i];
	}
	histroyTemp[0] = currentTemp;

	checkAlarmCondition();
}

void Thermometer::checkAlarmCondition()
{
	for (int i = 0; i < numAlarmMonitors; i++)
	{
		if (alarmConditions[i] != NULL)
		{
			if (alarmConditions[i]->getDirection() == up)
			{
				if (alarmConditions[i]->getTarget() < currentTemp && alarmConditions[i]->getReported() == false)
				{
					alarmConditions[i]->setReported(true);
					cout << "****** ALARM ****** - " << alarmConditions[i]->getAction() << endl;

				}
				else if (alarmConditions[i]->getTarget() > (currentTemp + alarmConditions[i]->getTolerance()))
				{
					alarmConditions[i]->setReported(false);
				}
			}
			else
			{
				if (alarmConditions[i]->getTarget() > currentTemp && alarmConditions[i]->getReported() == false)
				{
					alarmConditions[i]->setReported(true);
					cout << "****** ALARM ****** - " << alarmConditions[i]->getAction() << endl;
				}
				else if (alarmConditions[i]->getTarget() < (currentTemp - alarmConditions[i]->getTolerance()))
				{
					alarmConditions[i]->setReported(false);
				}
			}
		}
	}

}

bool Thermometer::addAlarmMonitor(AlarmCondition* alarmCondition)
{
	bool ret = true;

	if (numAlarmMonitors < MaxAlarmMonitors - 1)
	{
		if (alarmCondition != NULL)
		{
			alarmConditions[numAlarmMonitors] = alarmCondition;
			numAlarmMonitors++;
		}
		else
		{
			cout << "ERROR: Alarm condition is null" << endl;
			ret = false;
		}
	}
	else
	{
		cout << "ERROR: Reached maximum number of alarm" << endl;
		ret = false;
	}

	return ret;
}

void Thermometer::removeAllAlarmMonitors()
{
	for (int i = 0; i < numAlarmMonitors; i++)
	{
		if (alarmConditions[i] != NULL)
		{
			delete alarmConditions[i];
		}
	}
	numAlarmMonitors = 0;
}

void Thermometer::printTemperatureReadings(TemperatureScale scale)
{
	for (int i = 0; i < MaxTempHistory; i++)
	{
		cout << getTemperature(scale) << endl;
	}
}

void Thermometer::printAlarmMonitors(TemperatureScale scale)
{
	for (int i = 0; i < numAlarmMonitors; i++)
	{
		if (alarmConditions[i] != NULL)
		{
			cout << "Diretion:";
			if (alarmConditions[i]->getDirection() == up)
			{
				cout << "UP ";
			}
			else
			{
				cout << "DN ";
			}
			cout << "Tolerance:" << alarmConditions[i]->getTolerance();
			cout << "Target:" << (scale == fahrenheit ? (alarmConditions[i]->getTarget() + 32) * 1.8 : alarmConditions[i]->getTarget());
			if (scale == fahrenheit)
			{
				cout << " (F)" << endl;
			}
			else
			{
				cout << " (C)" << endl;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////
//
// Main entry point
//
/////////////////////////////////////////////////////////////////
int main( int argc, char *argv[ ])
{
	char c;
	double teta = 0;
	double temp = 0;

	Thermometer* thermometer = new Thermometer(25);
	AlarmCondition* freezing = new AlarmCondition( 0, 5, down, "Freezing Point Achived"); 
	AlarmCondition* boiling = new AlarmCondition( 100, 5, up, "Boiling Point Achived"); 

	thermometer->printAlarmMonitors();
	thermometer->printAlarmMonitors(fahrenheit);

	if (!thermometer->addAlarmMonitor(freezing))
	{
		cout << "EEROR: Unable to add freezing monitoring alarm." << endl;
	}
	if (!thermometer->addAlarmMonitor(boiling))
	{
		cout << "EEROR: Unable to add boiling monitoring alarm." << endl;
	}

	for (int i = 0; i < 3000; i++)
	{
		// simulating a tempurature reading [150..-150]
		temp = 110 * sin(teta);
		teta += 0.005;
		thermometer->setTemperature(temp);
		cout << "Temperature: " << temp << " (C)" << endl;
	}

	delete thermometer;

	cout << "Done." << endl;
	cout << "Press a key and ENTER to end." << endl;
	cin >> c;
	
	return 0;
}
