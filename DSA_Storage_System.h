#ifndef DSA_STORAGE_SYSTEM_H_INCLUDED
#define DSA_STORAGE_SYSTEM_H_INCLUDED
#include <iostream>
#include <stdexcept>
#include <iostream>

using namespace std;

template <typename T> class Vector { //custom generic vector class

T* arr; //to store first element address of vector
int capacity; //to determine max no. elements for vector
int currentSize; //to determine current no. elements in vector

public:

Vector()
{
    capacity = 1;
    currentSize = 0; //initializing vector with capacity 1 and no current elements
    arr = new T[capacity];
}


~Vector()
{
    delete[]arr; //all elements of vector get deleted
}

void pushBack(const T& data)
{
    //first, we must check if the capacity can handle a new element being pushed into vector
    if(currentSize==capacity)   //then that means the capacity has been completely used up we need to allocate more memory
    {capacity = capacity * 4;   //increase capacity
     T* newArr = new T[capacity];   //we make a new vector that holds 4 times the capacity of the old

     for(int i = 0; i<currentSize ; i++)   //then we copy old vector elements into new vector
     { newArr[i] = arr[i]; }  //the new indices are empty and ready to be filled

     delete[] arr;  //get rid of old vector
     arr = newArr; }

     {arr[currentSize] = data;
      ++currentSize; }  //if capacity still isn't reached, we can just add the new element without issue

}

T get (int index)
{
    if(index<currentSize)
    {return arr[index];}
    else return nullptr; //element not within range
}

bool isVectorEmpty()
{
    if(currentSize == 0)
    {return 1;}
    else return 0;
}

T popBack()
{   if(!isVectorEmpty())
    {T temp = arr[currentSize-1];
     --currentSize;
     return temp;}
}

int vectorSize()
{
    return currentSize;
}

int vectorCapacity()
{
    return capacity;
}

void vectorPrinter()
{
    for(int i = 0 ; i<currentSize ; i++)
    {cout<<arr[i]<<endl;}
}

Vector (const Vector&other) : currentSize(other.currentSize) , capacity(other.capacity) //copy constructor
{  arr = new T[capacity];
   for(int i = 0 ; i < currentSize ; i++)
    {
     arr[i] = other.arr[i];
    }
}

Vector<T>& operator = (const Vector & other) //overloading = operator
{
    if(this == &other)
    {return*this;}
    delete[]arr;
    currentSize = other.currentSize;
    capacity = other.capacity;
    arr = new T[capacity];
    for(int i = 0 ; i < currentSize ; i++)
    {
        arr[i] = other.arr[i];
    }
    return *this;
}

Vector(Vector&&other) noexcept:arr(other.arr) , currentSize(other.currentSize), capacity(other.capacity)
//move constructor
//transfers ownership of memory from one object to another, leaving the first object's memory empty
{
   other.arr = nullptr;
   other.currentSize = 0;
   other.capacity = 0;
}

Vector<T>& operator = (Vector&& other) noexcept //
{ //move = operator
  // abandons current memory of our object and takes ownership of other's vector info, leaving the other object empty
    if(this==&other)
    {return *this;}
    delete[]arr;
    arr = other.arr;
    currentSize = other.currentSize;
    capacity = other.capacity;
    other.arr = nullptr;
    other.currentSize = 0;
    other.capacity = 0;
    return *this;
}

T& operator[] (int index) //overloading of [] operator
{
    if(index>= currentSize)
    {
        throw std::out_of_range("Index not in bounds");
    }
    return arr[index];
}

T vectorBack()
{ if(!isVectorEmpty)
  return arr[currentSize-1]; }

};







#endif // DSA_STORAGE_SYSTEM_H_INCLUDED
