#include <iostream>
#include <exception>

using namespace std;



template <typename type>
class GenStack
{
    public:
    GenStack(); //constructor
    GenStack(int maxSize); //overloaded constructor
    ~GenStack(); //destructor

    void push(type d);
    type pop();
    type peek(); //aka top()

    bool isFull();
    bool isEmpty();
    int length();



    int size;
    int top;

    type *myArray;
    type *tempArray;


};


template <typename type>
GenStack<type>::GenStack() //default constructor
{
    myArray = new type[100];
    size = 100;
    top = -1;
}

template <typename type>
GenStack<type>::GenStack(int maxSize)
{
    myArray = new type[maxSize];
    size = maxSize;
    top = -1;
}

template <typename type>
GenStack<type>::~GenStack()
{
    delete myArray;
}

template <typename type>
void GenStack<type>::push(type d)
{
    if(top==size-1) //if array is full
    {
        tempArray = new type[size*2]; //creates a temp array twice as big to store arrays data
        for(int i = 0; i<size ; i++)
        {
            tempArray[i]=myArray[i]; //copies data from myArray to tempArray
        }
        myArray=new type[size*2]; //creates a new array with same name as originally, twice as long
        for(int i = 0; i<size; i++)
        {
            myArray[i]=tempArray[i];//copies data from temp array to new array
        }
        size=size*2; //updates size
        delete tempArray;
    }

    myArray[++top] = d; //increments top and assigns value to position

}

template <typename type>
type GenStack<type>::pop()
{
    if(top==-1)
    {
        throw "Exception: You cannot remove an element from an empty stack.\n";
    }
    else
        return myArray[top--];
}

template <typename type>
type GenStack<type>::peek()
{
    if(top==-1)
        return '\0';
    else
        return myArray[top];
}

template <typename type>
bool GenStack<type>::isFull()
{
    return (top == size-1);
}

template <typename type>
bool GenStack<type>::isEmpty()
{
    return (top == -1);
}

template <typename type>
int GenStack<type>::length()
{
    return size;
}
