#ifndef MINHEAP_H
#define MINHEAP_H
#include <iostream>
using namespace std;





class minHeap
{
private:
  int* heaparray; 
  int capacity; 
  int num; 
public:
  minHeap(){heaparray = NULL; capacity = 0; num = 0;}
  minHeap(int c){capacity = c; heaparray = new int[capacity]; num = 0;};
  ~minHeap(){if(heaparray!=NULL)delete [] heaparray;}
  void percolateDown(int* curDist, int* locator, int i);
  void percolateUp(int* curDist, int* locator, int i);
  void insert(int* curDist, int* locator, int el);
  int find(int key) const; 
  void remove(int* curDist, int* locator, int i);
  int getMin(int* curDist, int* locator);
  void fixHeap(int* curDist, int* locator, int i);
  int getNum() const;
};


void exchange(int &num1, int &num2)
{
  int temp = num1;
  num1 = num2;
  num2 = temp;
}

//You need to implement all the memeber functions above.
void minHeap::percolateDown(int* curDist, int* locator, int i)
{
  int l = (2 * i) + 1;
  int r = (2 * i) + 2;
  int smallest = i;
  
  if (l < num && curDist[heaparray[l]] < curDist[heaparray[smallest]])
    {
      smallest = l;
    }
  if (r < num && curDist[heaparray[r]] < curDist[heaparray[smallest]])
    {
      smallest = r;
    }

  if (smallest != i)
    {
      locator[heaparray[i]] = smallest;
      locator[heaparray[smallest]] = i;
      exchange(heaparray[i], heaparray[smallest]);
      percolateDown(curDist, locator, smallest);
    }
}
                                                                                              
void minHeap::percolateUp(int* curDist, int* locator, int i)
{
  int parent = (i-1) / 2; //find the parent node
  int child = i;
  while(child > 0 && curDist[heaparray[parent]] > curDist[heaparray[child]]) //the child is smaller 
    {
      locator[heaparray[child]] = parent;//swap locator
      locator[heaparray[parent]] = child;
      exchange(heaparray[parent], heaparray[child]); //swap
      child=parent; //make i the new parent
      parent = (parent-1) / 2; //find the parent of i
    }
}

void minHeap::insert(int* curDist, int* locator, int el)
{
  if(num >= capacity)
    {
      cout << "array is full" << endl;
      return;
    }
  else
    {
      int ind = num - 1;
      heaparray[num++] = el;
      
      percolateUp(curDist, locator, ind);
    }
}


int minHeap::find(int key) const
{
  for(int i = 0; i < num; i++) 
    if(heaparray[i] == key)
      return i;
   
  cout << "not found" << endl;   
}

void minHeap::remove(int* curDist, int* locator, int i)
{
  if(i >= num)
    {
      cout << "Bad index" << endl;
    }
  else
    {
      int l = 2 * i + 1;
      int r = 2 * i + 2;
      int last = num - 1;
      
      locator[heaparray[i]] = last;
      locator[heaparray[last]] = i;
      exchange(heaparray[last], heaparray[i]);
      num--;
      fixHeap(curDist, locator, i);
  
    }
}


int minHeap::getMin(int* curDist, int* locator)
{
  int top = heaparray[0];
  remove(curDist, locator, 0);
  return top;
}


void minHeap::fixHeap(int* curDist, int* locator, int i)
{

  if(i<num && i >= 0) 
    {
      if(curDist[heaparray[i]] < curDist[heaparray[(i-1)/2]]) 
	percolateUp(curDist, locator, i);
      else if(curDist[heaparray[i]] > curDist[heaparray[2*i+1]] || curDist[heaparray[i]] > curDist[heaparray[2*i+2]]) 
	percolateDown(curDist, locator, i);
    }
}


int minHeap::getNum() const
{
  return num;
}

#endif