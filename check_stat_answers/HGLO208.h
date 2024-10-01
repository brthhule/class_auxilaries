#pragma once

#include <iostream>
#include <vector>

class AirBase {
public:
	AirBase(std::string name, double latitude, double longitude);
	std::string getName();
	double getLatitude();
	double getLongitude();
	static void readText();
	static double convertDMS(std::string DMS);
	static void print();
	static std::vector<AirBase*> bases;

private:
	std::string name;
	double latitude;
	double longitude;
};