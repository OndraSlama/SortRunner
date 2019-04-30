#pragma once
#include "Base.h"

// Where all the sorting algorithms are declared.
// Every special sorter class inherits from one base class so its possible to call special sort and activate function with base pointer.


class Sorter{
public:
	int* i;
	int* j;
	std::string name;
	std::vector<int>* steps;
	Sorter(){}
	virtual void activate(std::vector<int>* _steps, int* _i, int* _j) = 0;
	virtual void sort() = 0;
	void swap(int* a, int* b);
};


class BubbleSort : public Sorter{	
public:
	BubbleSort() { name = "Bubble sort"; }
	void activate(std::vector<int>* _steps, int* _i, int * _j);
	void sort();
};

class OptimizedBubbleSort : public Sorter{
public:
	int sortSize;
	OptimizedBubbleSort() { name = "Optimized Bubble sort"; }
	void activate(std::vector<int>* _steps, int* _i, int * _j);
	void sort();
};

class ShakerSort : public Sorter {
public:
	int direction;
	ShakerSort() { name = "Shaker sort"; }
	void activate(std::vector<int>* _steps, int* _i, int * _j);
	void sort();
};

class OptimizedShakerSort : public Sorter {
public:
	int direction;
	int lowerBound;
	int higherBound;
	OptimizedShakerSort() { name = "Optimized Shaker sort"; }
	void activate(std::vector<int>* _steps, int* _i, int * _j);
	void sort();
};

class SelectionSort : public Sorter {
public:
	int lowerBound;
	int minIndex;
	SelectionSort() { name = "Selection sort"; }
	void activate(std::vector<int>* _steps, int* _i, int * _j);
	void sort();
};


class InsertionSort : public Sorter {
public:
	int lowerBound;
	InsertionSort() { name = "Insertion sort"; }
	void activate(std::vector<int>* _steps, int* _i, int * _j);
	void sort();
};

class BogoSort : public Sorter {
public:
	int lowerBound;
	BogoSort() { name = "Bogo sort"; }
	void activate(std::vector<int>* _steps, int* _i, int * _j);
	void sort();
};

class Boundary {
public:
	int left;
	int right;
	Boundary() {}
	Boundary(int _left, int _right) : left(_left), right(_right) {}
};

class QuickSort : public Sorter {
public:
	int pivotIndex;
	int leftIndex;
	int leftBoudary;
	Boundary bounds;
	bool dividing;
	std::vector<Boundary> stack;
	QuickSort() { name = "Quick sort"; }
	void activate(std::vector<int>* _steps, int* _i, int* _j);
	void sort();
};



