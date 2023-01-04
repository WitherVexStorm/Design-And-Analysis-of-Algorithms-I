#include <iostream>
#include <iomanip>
#include <utility>
// #include <limits>

struct interval {
    int start_time;
    int finish_time;
};

bool operator >(const interval& i1, const interval& i2) {
    return i1.finish_time > i2.finish_time;
}

template< typename T >
void insertion_sort(T arr[], const int length) {
    for(int i = 1, j; i < length; ++i) {
        const T element = std::move(arr[i]);
        for(j = i-1; j >= 0 && arr[j] > element; --j) {
            arr[j+1] = arr[j];
        }
        arr[j+1] = std::move(element);
    }
}

int print_interval_array(const std::string title, interval arr[], const int length, int max_finish_time = 0) {
    bool calc_max_time = max_finish_time == 0;
    std::cout << "\n" << title << "\n";
    for(int i = 0, j; i < length; ++i) {
        if(calc_max_time && arr[i].finish_time > max_finish_time) {
            max_finish_time = arr[i].finish_time;
        }
        std::cout << "i = " << std::setw(2) << i << " |";
        for(j = 0; j < arr[i].start_time; ++j)
        std::cout << "    ";
        for(; j < arr[i].finish_time; ++j)
        std::cout << char(178) << char(178) << char(178) << char(178);
        std::cout << "\n";
    }
    std::cout << std::setw(8) << "+";
    for(int i = 0; i < max_finish_time; ++i)
    std::cout << "----";
    std::cout << "\n" << std::setw(8) << "time";
    for(int i = 0; i < max_finish_time; ++i)
    std::cout << std::setw(4) << i;
    std::cout << "\n";
    return max_finish_time;
}

int calculate_optimal(interval arr[], const int length) {
    int optimal_solution = 0, i = 0, j;
    while(i < length) {
        // Pick a[i] as part of optimal solution
        optimal_solution += 1;
        // Skip all a[j] that conflict with a[i]
        for(j = i+1; j < length && arr[j].start_time < arr[i].finish_time; ++j);
        // Update i to pick next a[i]
        i = j;
    }
    return optimal_solution;
}

int main() {
    interval interval_arr[] = { interval{ 5, 9 }, interval{ 4, 6 }, interval{ 2, 5 }, interval{ 4, 8 } };
    const int interval_arr_length = sizeof(interval_arr)/sizeof(interval);
    // int min_start_time = std::numeric_limits<int>::max();
    const int max_finish_time = print_interval_array("Input Intervals:", interval_arr, interval_arr_length);
    insertion_sort(interval_arr, interval_arr_length);
    print_interval_array("Sorted Intervals:", interval_arr, interval_arr_length, max_finish_time);
    const int optimal_result = calculate_optimal(interval_arr, interval_arr_length);
    std::cout << "\nOptimal solution can schedule " << optimal_result << " intervals!";
    return 0;
}