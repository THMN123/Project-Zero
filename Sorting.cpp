#include "Sorting.h"

void Sorter::swap(Resource& a, Resource& b) {
    Resource temp = a;
    a = b;
    b = temp;
}

void Sorter::bubbleSort(Resource arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Sort by Capacity for demonstration
            if (arr[j].getCapacity() > arr[j + 1].getCapacity()) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int Sorter::partition(Resource arr[], int low, int high) {
    // Sort by ID for demonstration
    string pivot = arr[high].getResourceID();
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].getResourceID() < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void Sorter::quickSort(Resource arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int Sorter::linearSearch(Resource arr[], int n, string id) {
    for (int i = 0; i < n; i++) {
        if (arr[i].getResourceID() == id) {
            return i;
        }
    }
    return -1;
}

int Sorter::binarySearch(Resource arr[], int low, int high, string id) {
    if (high >= low) {
        int mid = low + (high - low) / 2;

        if (arr[mid].getResourceID() == id) {
            return mid;
        }
        if (arr[mid].getResourceID() > id) {
            return binarySearch(arr, low, mid - 1, id);
        }
        return binarySearch(arr, mid + 1, high, id);
    }
    return -1;
}
