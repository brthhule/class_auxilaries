// check_stat_answers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <iostream>
#include <Vector>
#include <unordered_set>
#include "HGLO208.h"
#include <fstream>
#include <string.h>
#include <string>
#include <vector>
#include <unordered_map>

std::vector<char> randomizeList(int n, int m);
void methodOne();

class Stakeholder {
public:
    Stakeholder() {
    }
    Stakeholder(std::string name, std::string date) {
        this->name = name;
        this->date = date;
    }
    std::string name;
    std::string date;
    std::vector<std::string> background, goals, contributions, implementations;
    std::vector<std::string> sectionNames = { "background", "goals", "contributions", "implementations" };
    static enum Content {
        BACKGROUND, GOALS, CONTRIBUTIONS, IMPLEMENTATIONS
    };
    std::vector<std::vector<std::string>*> content = { &background, &goals, &contributions, &implementations };
    std::unordered_map < std::string, std::vector < std::string>*> contentMap = {
        {"Background", &background},
        {"Goals", &goals},
        {"Contributions", &contributions},
        {"Implementation", &implementations}
    };
    void print() {
        std::cout << "{";
        std::cout << "\t\"stakeholder\": " << "\"" << name << "\",\n";
        std::cout << "\t\"date\": " << "\"" << date << "\",\n";


        for (int i = 0; i < 4; i++) {
            std::cout << "\t\"" << sectionNames[i] << "\": " << "[\n";
            std::vector<std::string>* vectorThing = content[i];
            for (std::string line : *vectorThing) { 
                std::cout << "\t\t\"" << line << "\"\n"; 
            }
            std::cout << "\t]\n";
        }
        std::cout << "}";
        
    }
};

void humanPracticesParser() {
    std::vector<Stakeholder*> stakeholders;
    std::string line;
    std::ifstream file("test.txt");

    Stakeholder* currentStakeholder = nullptr;
    std::vector<std::string>* currentVector = nullptr;
    std::string currentParagraph;

    std::cout << "Is open " << file.is_open() << "\n";
    while (1) {
        while (std::getline(file, line)) {
            std::cout << line << "\n";
            std::cout << "Find |: " << line.find("|") << "\n";

            if (line.find("|") < line.length()) {
                currentStakeholder = new Stakeholder();
                std::cout << "Created new stakeholder\n";
                currentStakeholder->name = line.substr(0, line.find("|") - 2);
                currentStakeholder->date = line.substr(line.find("|") + 2);
                continue;
                std::cout << "Name: " << currentStakeholder->name << "\n";
            }
            if (currentStakeholder != nullptr && currentStakeholder->contentMap.count(line) > 0) {
                currentVector = currentStakeholder->contentMap.at(line);
                currentParagraph = "";
            } else {
                currentParagraph += line;
                if (line.find("\n") != -1) {
                    currentVector->push_back(currentParagraph);
                    currentParagraph = "";
                }
            }
        }
    }
    
    for (Stakeholder* person : stakeholders) {
        person->print();
        std::cout << "\n";
    }
    file.close();
}

void foo () {
    std::string line;
    std::ifstream file("member_bios.csv");
    std::cout << file.is_open() << " hey\n";

    while (std::getline(file, line)) {
        std::cout << "{\n";
        std::cout << "\t\"name\" : \"" << line.substr(0, line.find(",")) << "\",\n";
        line = line.substr(line.find(",") + 1);

        std::cout << "\t\"year\" : \"" << line.substr(0, line.find(",")) << "\",\n";
        line = line.substr(line.find(",") + 1);

        std::cout << "\t\"major\" : \"" << line.substr(0, line.find(",")) << "\",\n";
        line = line.substr(line.find(",") + 1);

        std::cout << "\t\"committees\" : \"" << line << "\",\n";
        std::cout << "\t\"src\" : \"\"\n";
        std::cout << "},\n";
    }


    file.close();
}

int main() 
{
    foo();

}

void methodOne() {
    srand(time(NULL));

    int n = rand() % 1000000 + 10;  //Total number of balls
    int m = rand() % n + 1;  //Number of white balls
    int k = rand() % n + 1;  //Number of balls selected at a time

    std::cout << "n: " << n;
    std::cout << "m: " << m;
    std::cout << "k: " << k;

    std::vector<char> list = randomizeList(n, m);
    std::cout << "List: ";
    for (auto i : list) {
        std::cout << i << " ";
    }


    int count = 0;
    for (int i = 0; i < k; i++) {
        if (list[i] == 'W') {
            count++;
        }
    }

    std::cout << "\n\n";
    std::cout << "Count: " << count << "/" << k << "\n";
    std::cout << "Result count: " << (double)count / k << "\n";
    std::cout << "Estimated 1: " << ((double)m * k) / n << "\n";
    std::cout << "Estimated 2: " << (double)k / n << "\n";
    std::cout << "Estimated 3: " << (double)m / n << "\n";




    //Find probability that i of k balls are white
}

std::vector<char> randomizeList(int n, int m) {
    std::vector<char> whiteBalls = {};
    for (int i = 0; i < m; i++) {
        whiteBalls.push_back('W'); 
    }

    std::vector<char> list = {};
    for (int i = 0; i < n; i++) {
        list.push_back('E');
    }

    srand(time(NULL));

    std::unordered_set<int> indices = {};

    for (char foo : whiteBalls) {
        while (1) {
            int index = rand() % n + 1; 
            indices.insert(index);
            
            ///std::cout << "Result: " << indices.count(index) << "\n";
            if (indices.count(index) == 0) { 
                continue;
            }

            //std::cout << "Index: " << index << "\n";
            list[index] = 'W';
            
            break;
        }
    }
    return list;
}