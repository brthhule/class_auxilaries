#include "HGLO208.h"
#include <fstream>
#include<string>


std::vector<AirBase*> AirBase::bases;


AirBase::AirBase(std::string name, double longitude, double latitude) {
	this->name = name;
	this->longitude = longitude;
	this->latitude = latitude;
}

std::string AirBase::getName() {
	return this->name;
}

double AirBase::getLatitude() {
	return this->latitude;
}
double AirBase::getLongitude() {
	return this->longitude;
}

double AirBase::convertDMS(std::string DMS) {
	if (DMS.find(".") == -1) {
		return std::stod(DMS);
	}

	std::cout << "DMS 1: " << DMS << "\n";
	double D = std::stod(DMS.substr(0, DMS.find("."))); 
	DMS = DMS.substr(DMS.find(".") + 1); 
	std::cout << "DMS 2: " << DMS << "\n";
	double M = std::stod(DMS.substr(0, DMS.find("'"))); 
	double S = 0;
	char letter;
	if (DMS.find("\"") != -1) {
		DMS = DMS.substr(DMS.find("'") + 1);
		std::cout << "DMS 3: " << DMS << "\n";
		S = std::stod(DMS.substr(0, DMS.find("\"")));
		letter = DMS.substr(DMS.find("\"") + 1).at(0);
	} else {
		letter = DMS.substr(DMS.find("'") + 1).at(0);
	}
	
	std::cout << "DMS 4: " << letter << "\n";

	double returnValue = S / 60;
	returnValue += M;
	returnValue /= 60;
	returnValue += D;

	if (letter == 'W' || letter == 'S') {
		returnValue *= -1;
	}
	return returnValue;
}



void AirBase::readText() {
	std::string text;
	std::ifstream file("HGLO208_2.txt");
	std::cout << "Is open " << file.is_open() << "\n";
	while (std::getline(file, text)) {
		int dataIndex = text.find(", DATA: ");
		std::string name = text.substr(0, dataIndex);
		std::cout << "Name: " << name << "\n";
		text = text.substr(dataIndex + 7);
		std::string latitude = text.substr(0, text.find(", "));
		std::string longitude = text.substr(text.find(", ") + 2);
		AirBase::bases.push_back(new AirBase(name, convertDMS(latitude), convertDMS(longitude)));
	}
	file.close();

	print();
};

void AirBase::print() {
	std::string fileContent =  "Bases: \n";
	for (AirBase* base : bases) {
		fileContent += base->getName();
		fileContent+="\n";
	}
	fileContent += "\n\nLatitude: \n";
	for (AirBase* base : bases) {
		fileContent += std::to_string(base->getLatitude());
		fileContent += "\n";
	}
	fileContent += "\n\nLongitude: \n";
	for (AirBase* base : bases) {
		fileContent += std::to_string(base->getLongitude());
		fileContent += "\n";
	}

	std::cout << "File content: " << fileContent << "\n";


	std::ofstream file("./HGLO_results.txt");
	file << fileContent;
	file.close();
}

