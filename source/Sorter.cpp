#include "Sorter.h"

// Where all the sorting algorithms are defined.

// Every special sorter class inherits from one base class so its possible to call special sort and activate function with base pointer.

void Sorter::swap(int * a, int * b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void BubbleSort::activate(std::vector<int>* _steps, int * _i, int * _j) {
	steps = _steps;
	i = _i;
}

void BubbleSort::sort(){
	if (steps->at(*i - 1) > steps->at(*i)){
		swap(&steps->at(*i - 1), &steps->at(*i));
	}

	*i = *i + 1;
	if (*i >= steps->size()) *i = 1;
}

void OptimizedBubbleSort::activate(std::vector<int>* _steps, int * _i, int * _j){
	steps = _steps;
	i = _i;
	sortSize = steps->size();
}

void OptimizedBubbleSort::sort(){
	if (steps->at(*i - 1) > steps->at(*i)){
		swap(&steps->at(*i - 1), &steps->at(*i));
	}
	*i += 1;

	if (*i >= sortSize){
		sortSize -= 1;
		*i = 1;
	}
}

void ShakerSort::activate(std::vector<int>* _steps, int * _i, int * _j) {
	steps = _steps;
	i = _i;
	direction = 1;
}

void ShakerSort::sort() {
	if (steps->at(*i - 1) > steps->at(*i)) {
		swap(&steps->at(*i - 1), &steps->at(*i));
	}	

	*i = *i + direction;
	if (*i >= steps->size()) {
		*i = steps->size() - 1;
		direction = -1;
	} else if (*i < 1) {
		*i = 1;
		direction = 1;
	}
}

void OptimizedShakerSort::activate(std::vector<int>* _steps, int * _i, int * _j) {
	steps = _steps;
	i = _i;
	direction = 1;
	lowerBound = 1;
	higherBound = steps->size();
}

void OptimizedShakerSort::sort() {
	if (steps->at(*i - 1) > steps->at(*i)) {
		swap(&steps->at(*i - 1), &steps->at(*i));
	}

	*i = *i + direction;
	if (*i >= higherBound) {
		*i = higherBound - 1;
		direction = -1;
		higherBound--;
	} else if (*i < lowerBound) {
		*i = lowerBound;
		direction = 1;
		lowerBound++;
	}
}

void SelectionSort::activate(std::vector<int>* _steps, int * _i, int * _j) {
	steps = _steps;
	i = _i;
	j = _j;
	*i = 0;
	lowerBound = 0;
	minIndex = 0;
}

void SelectionSort::sort() {
	if (steps->at(*i) < steps->at(minIndex)) {
		minIndex = *i;
	}	

	if (*i >= steps->size() - 1) {
		swap(&steps->at(lowerBound), &steps->at(minIndex));
		lowerBound++;		
		*i = lowerBound;
		minIndex = lowerBound;
		return;
	}

	*i += 1;
	*j = lowerBound;
}

void InsertionSort::activate(std::vector<int>* _steps, int * _i, int * _j) {
	steps = _steps;
	i = _i;
	j = _j;
	lowerBound = 1;
}

void InsertionSort::sort() {

	if (steps->at(*i - 1) < steps->at(*i)) {
		lowerBound++;
		*i = lowerBound;
	} else {
		swap(&steps->at(*i - 1), &steps->at(*i));
		*i -= 1;
	}

	if (*i <= 0) {
		lowerBound++;
		*i = lowerBound;
	}

	*j = lowerBound;
}

void BogoSort::activate(std::vector<int>* _steps, int * _i, int * _j) {
	steps = _steps;
	i = _i;
}

void BogoSort::sort() {
	std::random_shuffle(steps->begin(), steps->end());
}


void QuickSort::activate(std::vector<int>* _steps, int * _i, int * _j) {
	steps = _steps;
	i = _i;
	j = _j;

	stack.push_back(Boundary(0, steps->size()-1));
	bounds = stack.back();
	leftIndex = stack.back().left;
	pivotIndex = stack.back().right;
	leftBoudary = leftIndex - 1;
	stack.pop_back();
	dividing = true;
}

void QuickSort::sort() {	

	if (dividing) {
		if (leftIndex < pivotIndex) {
			if (steps->at(leftIndex) <= steps->at(pivotIndex)) {
				leftBoudary++;
				swap(&steps->at(leftBoudary), &steps->at(leftIndex));
			}
			leftIndex++;
		} else {
			swap(&steps->at(leftBoudary + 1), &steps->at(pivotIndex));
			pivotIndex = leftBoudary + 1;
			dividing = false;
		}
	} else {
		if (pivotIndex - 1 > bounds.left) {
			stack.push_back(Boundary(bounds.left, pivotIndex - 1));
		}
		if (pivotIndex + 1 < bounds.right) {
			stack.push_back(Boundary(pivotIndex + 1, bounds.right));
		}

		if (stack.size() > 0) {
			bounds = stack.back();
			leftIndex = stack.back().left;
			pivotIndex = stack.back().right;
			leftBoudary = leftIndex - 1;
			stack.pop_back();
			dividing = true;
		}
	}

	*i = leftIndex;
	*j = pivotIndex;	
}

