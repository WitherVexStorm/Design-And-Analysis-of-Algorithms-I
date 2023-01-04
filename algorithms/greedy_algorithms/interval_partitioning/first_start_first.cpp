#include <iostream>
#include <iomanip>

struct interval {
    int start_time;
    int finish_time;
    std::string color;
};

void print_interval_arr(const std::string title, interval arr[], const int length, int& max_finish_time) {
    std::cout << "\n" << title << "\n";
    for(int i = 0; i < length; ++i) {
        max_finish_time = arr[i].finish_time > max_finish_time ? arr[i].finish_time : max_finish_time;
        std::cout << "i = " << std::setw(2) << i << " |" << std::setw(arr[i].start_time*4-1) << "";
        const int padding = ((arr[i].finish_time - arr[i].start_time) * 4 - arr[i].color.length()) / 2;
        std::cout << std::setfill(char(178)) << std::setw(padding) << arr[i].color << std::setw(padding) << "" << std::setfill(' ');
        std::cout << "\n";
    }
    std::cout << std::setw(8) << "+" << std::setw(max_finish_time * 4) << std::setfill('-') << "" << std::setfill(' ') << "\n";
    std::cout << std::setw(4) << "Time";
    for(int i = 0; i <= max_finish_time; ++i)
    std::cout << std::setw(4) << i;
    std::cout << "\n";
}

int find_overlap_count(interval arr[], const int length, const int max_finish_time) {
    int overlap_count[max_finish_time] = {0};
    // Set the overlaps for each interval
    for(int i = 0; i < length; ++i) {
        for(int j = arr[i].start_time; j <= arr[i].finish_time; ++j) {
            overlap_count[j] += 1;
        }
    }
    // Find the max over the running time of intervals
    int max_overlap = 0;
    for(int i = 0; i < max_finish_time; ++i) {
        max_overlap = overlap_count[i] > max_overlap ? overlap_count[i] : max_overlap;
    }
    // Return it
    return max_overlap;
}

int main() {
    interval arr[] = { interval{ 5, 9, "" }, interval{ 4, 6, "" }, interval{ 2, 5, "" }, interval{ 4, 8, "" } };
    const int length = sizeof(arr)/sizeof(interval);
    int max_finish_time = 0;
    print_interval_arr("Input Intervals:", arr, length, max_finish_time);
    std::cout << find_overlap_count(arr, length, max_finish_time);
    return 0;
}