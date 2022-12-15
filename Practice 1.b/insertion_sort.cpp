#include <iostream>

void insertion_helper(int arr[], int i) {
    int element = arr[i], j = i-1;
    for(; j >= 0 && arr[j] > element; --j) {
        arr[j+1] = arr[j];
    }
    arr[j+1] = element;
}

void insertion_sort(int arr[], int length) {
    for(int i = 1, j; i < length; ++i) {
        insertion_helper(arr, i);
    }
}

int main() {
    std::cout << "Using Array = {4, 8, 2, 7, 9, 1, 6, 5, 3, 0}\n\n";
    int arr[] = { 4, 8, 2, 7, 9, 1, 6, 5, 3, 0 };
    std::cout << "Starting Insertion Sort: ...\n";
    insertion_sort(arr, sizeof(arr)/sizeof(int));
    std::cout << "Done.\n\nResulting Array = {";
    for(uint16_t i = 0; i < sizeof(arr)/sizeof(int); ++i)
    std::cout << arr[i] << ", ";
    std::cout << "\b\b}";
    return 0;
}