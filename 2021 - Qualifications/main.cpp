//
//  main.cpp
//  hashcode_2021
//
//  Created by Yu Cheuk Hei on 26/2/2021.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class Car
{
public:
    int numOfStreetsPassed;
    vector<string> streetsPassed;
    
    Car(int numOfStreetsPassed, vector<string> streetsPassed) {
        this->numOfStreetsPassed = numOfStreetsPassed;
        this->streetsPassed = streetsPassed;
    }
    
    friend ostream& operator<< (ostream& os, const Car& car);
    
};

ostream& operator<< (ostream& os, const Car& car) {
    os << car.numOfStreetsPassed << " ";
    for (int i = 0; i < car.numOfStreetsPassed; ++i) {
        os << car.streetsPassed[i] << " ";
    }

    return os;
}

class Street
{
public:
    int from;
    int to;
    string name;
    int travelTime;
    int numOfCarsPassing;
    
    Street(int from, int to, string name, int travelTime) {
        this->from = from;
        this->to = to;
        this->name = name;
        this->travelTime = travelTime;
        numOfCarsPassing = 0;
    }
    
    friend ostream& operator<< (ostream& os, const Street& street);
};

ostream& operator<< (ostream& os, const Street& street) {
    os << street.from << " " << street.to << " " << street.name << " " << street.travelTime;
    return os;
}

class Intersection
{
public:
    vector<Street*> inStreets;
    // vector<int> trafficLightTime;
    
    vector<Street*> outStreets;
    
    Intersection() {}
    
    friend ostream& operator<< (ostream& os, const Intersection& intersection);
};

ostream& operator<< (ostream& os, const Intersection& intersection) {
    os << "Incoming: ";
    for (vector<Street*>::const_iterator it = intersection.inStreets.begin(); it != intersection.inStreets.end(); ++it) {
        os << *it << " ";
    }
    os << endl;
    
    os << "Outcoming: ";
    for (vector<Street*>::const_iterator it = intersection.outStreets.begin(); it != intersection.outStreets.end(); ++it) {
        os << *it << " ";
    }
    
    return os;
}

/*
bool streetHasCar(Street street) {
    
}
 */

int main()
{
    int testCase = 5;
    vector< vector<string> > fileNames{ {"a.txt", "output_a.txt"},
                                        {"b.txt", "output_b.txt"},
                                        {"c.txt", "output_c.txt"},
                                        {"d.txt", "output_d.txt"},
                                        {"e.txt", "output_e.txt"},
                                        {"f.txt", "output_f.txt"}};
    
    ifstream file(fileNames[testCase][0]);
    
    int timeOfSimulation;
    int numOfIntersections;
    int numOfStreets;
    int numOfCars;
    int bonus;
    
    string line;
    vector<Street*> streets;
    vector<Car> cars;
    
    if (file.is_open()) {
        getline(file, line, ' ');
        timeOfSimulation = stoi(line);
        
        getline(file, line, ' ');
        numOfIntersections = stoi(line);
        
        getline(file, line, ' ');
        numOfStreets = stoi(line);
        
        getline(file, line, ' ');
        numOfCars = stoi(line);
        
        getline(file, line);
        bonus = stoi(line);
        
        vector<Intersection> intersections(numOfIntersections);
        
        for (int i = 0; i < numOfStreets; ++i) {
            getline(file, line, ' ');
            int _from = stoi(line);
            
            getline(file, line, ' ');
            int _to = stoi(line);
            
            getline(file, line, ' ');
            string _name = line;
            
            getline(file, line);
            int _travelTime = stoi(line);
            
            Street* street = new Street(_from, _to, _name, _travelTime);
            streets.push_back(street);
            
            intersections[_to].inStreets.push_back(street);
            intersections[_from].outStreets.push_back(street);
        }
        
        cout << numOfCars << endl;
        for (int i = 0; i < numOfCars; ++i) {
            cout << i << endl;
            getline(file, line, ' ');
            int _numOfStreetsPassed = stoi(line);
            
            /*
            vector<string> _streets;
            for (int j = 0; j < _numOfStreetsPassed - 1; ++j) {
                getline(file, line, ' ');
                _streets.push_back(line);
            }
             */
            
            
            vector<string> _streets;
            for (int j = 0; j < _numOfStreetsPassed - 1; ++j) {
                getline(file, line, ' ');
                
                
                for (int k = 0; k < streets.size(); ++k) {
                    if (line.compare(streets[k]->name) == 0) {
                        // cout << "!" << endl;
                        ++streets[k]->numOfCarsPassing;
                        break;
                    }
                }
                
                 
                
                _streets.push_back(line);
            }
             
            
            getline(file, line);    // Last street name
            _streets.push_back(line);
            
            Car car(_numOfStreetsPassed, _streets);
            cars.push_back(car);
        }
        
        /*
        for (int i = 0; i < numOfCars; ++i) {
            for (int j = 0; j < cars[i].streetsPassed.size() - 1; ++j) {
                for (int k = 0; k < streets.size(); ++k) {
                    if (line == streets[k].name) {
                        ++streets[k].numOfCarsPassing;
                        break;
                    }
                }
            }
        }
         */
        
        /*
        for (int i = 0; i < numOfIntersections; ++i) {
            for (int j = 0; j < intersections[i].inStreets.size(); ++j) {
                if () {
                    
                }
            }
        }
         */
        
        vector< vector < pair<string, int> > > output(numOfIntersections);
        for (int i = 0; i < numOfIntersections; ++i) {
            cout << i << endl;
            
            if (intersections[i].inStreets.size() == 1) {
                output[i].push_back(make_pair(intersections[i].inStreets[0]->name, 1));
            } else {
                for (int j = 0; j < intersections[i].inStreets.size(); ++j) {
                    
                    int n = intersections[i].inStreets.size();
                    
                    /*
                    int _numOfCarPassing = 0;
                    for (int k = 0; k < streets.size(); ++k) {
                        if (intersections[i].inStreets[j]->name == streets[k]->name) {
                            _numOfCarPassing = intersections[i].inStreets[j]->numOfCarsPassing;
                        }
                    }                      */
                    
                    int r = 0; // Random Guess Number
                    // r = 1 is shit
                    // but r = 0 is good?
                    
                    int _numOfCarPassing = intersections[i].inStreets[j]->numOfCarsPassing;
                    // cout << _numOfCarPassing << endl;
                    
                    bool hasTrafficLight = false;
                    if ( _numOfCarPassing <= 0 ) {
                        // output[i].push_back(make_pair(intersections[i].inStreets[( j ) % n].name, 1));
                        // cout << i << " " << intersections[i].inStreets.size() << endl;
                        
                        if (intersections[i].inStreets.size() == 1 || (!hasTrafficLight && j == n - 1)) {
                            output[i].push_back(make_pair(intersections[i].inStreets[( j + r ) % n]->name, 1));
                        }
                    } else if ( _numOfCarPassing >= 20 ) {
                        output[i].push_back(make_pair(intersections[i].inStreets[( j + r ) % n]->name, 20));
                        hasTrafficLight = true;
                    } else {
                        output[i].push_back(make_pair(intersections[i].inStreets[( j + r ) % n]->name, _numOfCarPassing));
                        hasTrafficLight = true;
                    }
                }
            }
            
            
            
            /*
            if (intersections[i].inStreets.size() == 1) {
                pair<string, int> traffic(intersections[i].inStreets[0], 1);
                output[i] = traffic;
            }
             */
        }
        
        /*
        for (int i = 0; i < timeOfSimulation; ++i) {
            
        }
        */
        
        ofstream outputFile;
        outputFile.open(fileNames[testCase][1]);
        
        outputFile << numOfIntersections << "\n";
        
        for (int i = 0; i < output.size(); ++i) {
            outputFile << i << endl;
            outputFile << output[i].size() << endl;
            
            for (int j = 0; j < output[i].size(); ++j) {
                outputFile << output[i][j].first << " " << output[i][j].second << endl;
            }
            
        }
        
        
        // Print Debug
        /*
        for (int i = 0; i < numOfIntersections; ++i) {
            cout << "Intersection " << i << " : " << endl;
            cout << intersections[i] << endl << endl;
        }
        
        
        for (int i = 0; i < numOfStreets; ++i) {
            cout << streets[i] << endl;
        }
        
        for (int i = 0; i < numOfCars; ++i) {
            cout << cars[i] << endl;
        }
         */
        
        cout << "end" << endl;
         
    }
    
}




