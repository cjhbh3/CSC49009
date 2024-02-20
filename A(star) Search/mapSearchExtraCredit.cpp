#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <map>
#include <cmath>

# define pi 3.14159265358979323846

using namespace std;

class Path {
  public:
    // Double map
    // <start, <end, distance> >
    map<string, map<string, int> > vertices;
    map<string, vector<double> > estimatedCosts;
    // idea: map of estimate straight line distance to StLouis for each location

    void add_vertex(string name, map<string, int>& e) {
      vertices.insert(map<string, map<string, int> >::value_type(name, e));
    }
    
    void add_estimatedCost(string name, double lat, double lng) {
      vector<double> coordinates;
      coordinates.push_back(lat);
      coordinates.push_back(lng);
      estimatedCosts.insert(map<string, vector<double> >::value_type(name, coordinates));
    }

    void clear_vertices() { vertices.clear(); }

    double deg2rad(double degree) {
      return degree * (pi/180);
    }

    double calculateDistance(double lat1, double long1, double lat2, double long2) {
      int radius = 6371; // radius of earth in km
      double dLat = deg2rad(lat2-lat1);
      double dLon = deg2rad(long2-long1);
      double a = sin(dLat/2) * sin(dLat/2) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * sin(dLon/2) * sin(dLon/2);
      double c = 2 * atan2(sqrt(a), sqrt(1-a));
      double d = radius * c;
      d = d * .621;
      return d;
    }

    vector<string> find_best_path(string city1, string city2) {
      // A* search
      // Returns vector that contains the names of each city in best path
      // city2 will usually be StLouis, unless we do extra credit
      vector<string> path; // Returned variable, contains each city in path
      vector<double> goalCityCoords = estimatedCosts.at(city2);
      string start; // current node 
      string next; // where we are moving to next from start
      
      // Add starting city to our list
      start = city1;
      path.push_back(city1);
      
      while (start != city2) {
        
        // current cost is what we compare each potential move before we actually
        // perform the move. starts at a very big integer
        int currentCost = numeric_limits<int>::max();
        for (auto& x: vertices) {

          if(x.first == start) {
            for (auto& y: x.second) {
              vector<double> currentCity = estimatedCosts.at(y.first); // Pull the coords for current city
              // Sends the lat/lng coordinates to our distance calculator, which is the h(n) cost.
              // Calculator uses the Haversine formula to calculate distance between two coordinate points
              int hCost = 
              static_cast<int>(calculateDistance(currentCity.at(0), currentCity.at(1), goalCityCoords.at(0), goalCityCoords.at(1)));
              int gCost = y.second; // g(n) cost is in our vertices list

              if (gCost+hCost < currentCost) {
                // new lowest move found: change the current cost to the cost of that move
                // and put the city name we are moving to as next
                currentCost = gCost+hCost; 
                next = y.first;
              }
            }
          }
        }

        // After each iteration of the for loop, we should have the smallest move possible
        // so add to our list
        path.push_back(next);
        start = next; // start is now next cause that is where we are currently
      }

      return path; 
    }
};

void readVertices(ifstream &data, Path &p) {
  // Read in data from the file
  // Currently file is setup: start end miles

  while (true) {
    string start, end; // Starting city, ending city
    int cost; // Milelage to get between

    map<string, int> def;
    
    data >> start;
    if (data.eof()) {
      // Exit condition: reach end of file
      cout << "Data Loaded" << endl << endl;
      return;
    }
    data >> end;
    data >> cost;

    p.add_vertex(start, def);

    p.vertices[start][end] = cost;
  }

}

void readEstimatedCosts(ifstream &data, Path &p) {
  // Reads in the estimated straight line distance between city and St Louis
  // from separate file

  while (true) {
    string city;
    double lat, lng;

    data >> city; // city name
    if (data.eof()) {
      // Exit condition: reach end of file.
      cout << "Estimated Costs Loaded" << endl << endl;
      return;
    }
    data >> lat; // latitude coordinate of city
    data >> lng; // longitude coordinate of city
    p.add_estimatedCost(city, lat, lng);
  }
}

int main(int argv, char *argc[]) {
  /* Currently, driver code is set up to find any city to St Louis and return the path
  ** Couple of changes will need if we want the extra credit
  ** Instead of reading in our hCosts from file, will probably implement something to calculate
  ** Take input for what city we are trying to get to
  ** 
  ** Still need graphical display.
  */
  string cityName1, cityName2; //string for the city we starting from
  
  ifstream verticesFile; // data.txt : start city, end city, cost
  ifstream estimatedCostFile; // costs.txt : city, cost
  
  Path p;

  cout << "Please enter a starting city: " << endl; //prompt user to enter file name
  cin >> cityName1; //read in file name
  cout << endl;
  cout << "Please enter a destination" << endl;
  cin >> cityName2;
  cout << endl;

  verticesFile.clear();
  estimatedCostFile.clear();
  
  verticesFile.open("data.txt");
  estimatedCostFile.open("coords.txt");
  

  if (!verticesFile) {
    cout << "Can't find data.txt" << endl; 
    return 1;
  }

  if (!estimatedCostFile) {
    cout << "Can't find coords.txt" << endl;
    return 1;
  }

  readVertices(verticesFile, p);
  readEstimatedCosts(estimatedCostFile, p);
  
  
  verticesFile.close(); //close the file
  estimatedCostFile.close();

  vector<string> path = p.find_best_path(cityName1, cityName2);

  for (auto& city: path) {
    cout << city;
    if (city != path.at(path.size()-1)) {
      cout << " -> ";
    }
  }
  cout << "" << endl;

  
  return 0;
}