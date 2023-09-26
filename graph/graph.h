#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <stack>
#include "minHeap.h"
using namespace std;

class Edge
{
    friend class Graph; //friend allows us to access functions from graph
    private:
    int neighbor;//neighbor
    int wt;//weight
    
    
    public:
    Edge()//default contsructor
    {
        neighbor = 999;
        wt = 999;
    }
    Edge(int u, int v)//non-default contructor
    {
        neighbor = u;//neighbor
        wt = v;//weight
    }

};

class Graph
{
    private:
    int num_ver; //number of elements inside our dynamic array
    list<Edge*>* ver_ar;//declares a dynamic array where each slot holds a linked list
    public:
    Graph(int num);
    ~Graph();
    void addEdge(int i, int u, int w);
    int nextUnvisitedNodes(int* num, int start, int s);
    void Dijkstra(int start, int dest, stack<int> &city);
};

Graph::Graph(int num) //Constructor 
{
    num_ver = num;
    ver_ar = new list<Edge*>[num_ver];//making a dynamic array with each slot that holds a linked list
}

Graph::~Graph()//Deconstructor
{
    for (int i = 0; i < num_ver; i++)//literator throught the array of num_ver
    {
        for(list<Edge*>::iterator u = ver_ar[i].begin(); u != ver_ar[i].end(); u++)//iterate linklist through slot i
        {
            delete *u;
        }
    }

    delete [] ver_ar;
}

//This function add the Edges of the vertices.
void Graph::addEdge(int i, int u, int w)
{
    //ver_ar[i] returns a linked list
    //ver_ar[i].push_back() allows us to add a element to our linked list

    //2 lines
    //Edge p = new Edge(u,w);
    //ver_ar[i].push_back(p);

    ver_ar[i].push_back(new Edge(u, w));
}

int Graph::nextUnvisitedNodes(int* num, int start, int s)
{
    for (int i = s % num_ver; i != start; i = (i + 1) % num_ver)
    {
        if (num[i] == 0)
        {
            return i;
        }
    }

    return -1;
}

//This function is the implementation of  Dijstra algorithm to find the shortest path between two cities.
void Graph::Dijkstra(int start, int dest, stack<int>& city) 
{
    minHeap toBeChecked(num_ver); 
  int *curDist = new int[num_ver];  
  int *predecessor= new int[num_ver];
  int *locator = new int[num_ver];
  int v = start;
  

  for(int i = 0; i < num_ver; i++)
    curDist[i] = 999;   
  for(int i = 0; i < num_ver; i++)
    {
      toBeChecked.insert(curDist, locator, i); 
      locator[i] = i;
      predecessor[i] = -1;
    }
  curDist[start] = 0; 
  while(toBeChecked.getNum()>0) 
    {
      
      toBeChecked.fixHeap(curDist, locator, locator[v]); 
      v = toBeChecked.getMin(curDist, locator); 
      for(list<Edge*>::iterator u = ver_ar[v].begin(); u != ver_ar[v].end(); u++) 
	{
	  
	      if(curDist[(*u)->neighbor] > ((*u)->wt+curDist[v])) 
		{
		  curDist[(*u)->neighbor] = ((*u)->wt+curDist[v]); 
		  predecessor[(*u)->neighbor] = v; 
		  toBeChecked.fixHeap(curDist, locator, locator[(*u)->neighbor]);
		}
	}
    }
    int current = curDist[dest];
    cout << "shortest Dist= " << current<< endl;   
    while (dest != start)
    {
        city.push(dest);
        dest = predecessor[dest];
    }
    city.push(start);
    delete [] predecessor;
    delete [] curDist;
    delete [] locator;
    
}