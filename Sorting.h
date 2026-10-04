#ifndef SORTING_H
#define SORTING_H

#include "Resource.h"
#include <iostream>

using namespace std;

class Sorter {
private:
    static void swap(Resource& a, Resource& b);
    static int partition(Resource arr[], int low, int high);

public:
    // Sorting (O(n^2) and O(n log n))
    static void bubbleSort(Resource arr[], int n);
    static void quickSort(Resource arr[], int low, int high);

    // Searching
    static int linearSearch(Resource arr[], int n, string id);
    static int binarySearch(Resource arr[], int low, int high, string id);
};

#endif // SORTING_H
