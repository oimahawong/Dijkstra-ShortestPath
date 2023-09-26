#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include "graph.h"

using namespace std;
struct city
{
   int ID;
   string city_code;
   string city_name;
   int population;
   int elevation; 
};

struct road 
{
   string From_City;
   string To_City; 
   string Distance;
};

vector<city> readCity()
{
    vector <city> vector_city;

    ifstream fin;
    fin.open("city.txt");

    if(!fin)
    {
        cout << "city.txt cant open" << endl;
    }
    else
    {
        while(fin)
        {
            city c;
            fin >> c.ID >> c.city_code >> c.city_name >> c.population >> c.elevation;
            vector_city.push_back(c);
        }
    }

    return vector_city;
}

int main(int argc, char* argv[])//argc = amount of argument, argv = search arguments
{

    vector<city> city = readCity();
    stack<int> c;
    Graph map(20);//return the size of the city.
    int v, u, w;
    int from, to = -1;

    

    ifstream fin;
    fin.open("road.txt");//Open the road.txt file to read data
    
    if(!fin){
        cout<< "road.txt can't open"<< endl;
    }
    else
    {
        fin >> v >> u >> w;//read in the file before begin the while loop
        while (fin)
        {

             map.addEdge(v, u, w);//insert in the graph 
            fin >> v >> u >> w; //be sure to read it again so we can update our values as we add edges
        }
        
    }

    if (argc < 3)
    {
        cout << "needs input from 2 cities" << endl;
        return 0;
    }
    else if (argc == 3)
    {
        for (int i = 0; i < (int)city.size(); i++)
        {
            if (argv[1] == city[i].city_code)//if the argument we passed in exists inside our vector
            {
                from = city[i].ID;
            }
            if (argv[2] == city[i].city_code)
            {
                to = city[i].ID;
            }
        }
    }
    if(from == -1 || to == -1)
    {
        cout << "city code is invalid" << endl;
        return 0;
    }

    cout << "From City: " << city[from].city_name << ", population " << city[from].population <<", elevation " << city[from].elevation << endl;

    cout << "To City: " << city[to].city_name << ", population " << city[to].population <<", elevation " << city[to].elevation << endl;
    cout << "The shortest distance from " << city[from].city_name << " to " << city[to].city_name << " is ";

    cout << " ==========================" << endl;
    /*
    for (int i = 0; i < city.size(); i++)
    {
        cout << city[i].city_name << endl;
    }
    */
    map.Dijkstra(from, to, c);
    
    cout << "Through the route ";
    while (!c.empty()) 
    {
        cout << city[c.top()].city_name << "->";// print the shortest route
        c.pop();
    }

    return 0;
}