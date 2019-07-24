#pragma once
#include <iostream>
#include <iomanip>
#include <exception>

template <typename T>
class Stack {
private:
	T *stackPtr;                      
	const int size;                   
	int top;                          
public:
	Stack(int = 10);                 
	~Stack();               

	void push(const T &);        
	void printStack();         
	T peek(int) ;
	T pop();
	T *getPtr() ;
	int getStackSize() ;  
	int getTop() ;        
};

template <typename T>
Stack<T>::Stack(int maxSize) : size(maxSize) {
	stackPtr = new T[size];
	top = 0; 
	setlocale(LC_ALL, "Ru");
}

template <typename T>
Stack<T>::~Stack(){ delete[] stackPtr;  }

template <typename T>
void Stack<T>::push(const T &value) {
	if (top > size) { std::cout << "Переполнение" << std::endl; }
	else { stackPtr[top++] = value; }
}
	
template <typename T>
T Stack<T>::pop(){
	if (top <= 0) { std::cout << "Номер элемента не больше 0" << std::endl; }
	else { stackPtr[--top]; }
}

template <class T>
T Stack<T>::peek(int element_position) {
	if(element_position >= top) { std::cout << "Индекс за границами стека" << std::endl; }
	else { return stackPtr[top - element_position]; }
}

template <typename T>
void Stack<T>::printStack(){
	for (int iterator = top - 1; iterator >= 0; iterator--) {
		std::cout << std::setw(4) << stackPtr[iterator];
	}
	std::cout << std::endl;
}

template <typename T>
int Stack<T>::getStackSize() { return size; }

template <typename T>
T *Stack<T>::getPtr() { return stackPtr; }

template <typename T>
int Stack<T>::getTop()  { return top; }