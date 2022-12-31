#include <iostream>
#include <iomanip>
#include <utility>
// #include <limits>

int max(int a, int b) {
    return a > b ? a : b;
}

struct interval {
    int start_time;
    int finish_time;
    int weight;
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
        const int padding = (arr[i].finish_time - arr[i].start_time)*2 - 1;
        std::cout << std::setfill(char(178)) << std::setw(padding+2) << arr[i].weight << std::setw(padding) << "\n" << std::setfill(' ');
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

// Apply iterative maximising algorithm
int calculate_optimal(interval arr[], const int length, int& weighted_sum) {
    int optimal_solution = 0;
    struct {
        int optimal_till_now = 0;
        int last_compatible_interval = -1;
    } optimal_solution_array[length];

    // Find C[i] for every interval
    for(int i = 0; i < length; ++i) {
        for(int j = i-1; j >= 0; --j)
        if(arr[j].finish_time <= arr[i].start_time) {
            optimal_solution_array[i].last_compatible_interval = j;
        }
    }

    // Find the optimal till i for each interval i
    optimal_solution_array[0].optimal_till_now = arr[0].weight;
    for(int i = 1; i < length; ++i) {
        const int previous_compatible_optimal = optimal_solution_array[i].last_compatible_interval >= 0 
        ? optimal_solution_array[optimal_solution_array[i].last_compatible_interval].optimal_till_now 
        : 0;
        optimal_solution_array[i].optimal_till_now = max(previous_compatible_optimal + arr[i].weight, optimal_solution_array[i-1].optimal_till_now);
    }

    // Set the global optimal as optimal of last interval
    weighted_sum = optimal_solution_array[length-1].optimal_till_now;

    // Find the number of intervals scheduled
    int current_parent = length-1;
    while(current_parent >= 0) {
        const int previous_optimal_value = current_parent-1 >= 0 ? optimal_solution_array[current_parent-1].optimal_till_now : -1;

        // If optimal different, picked this interval, jump to last compatible interval
        if(previous_optimal_value != optimal_solution_array[current_parent].optimal_till_now) {
            current_parent = optimal_solution_array[current_parent].last_compatible_interval;
            optimal_solution += 1;
        } else {
        // If optimal same, did not pick this interval, check previous interval
            current_parent = current_parent-1;
        }
    }
    return optimal_solution;
}

int main() {
    interval interval_arr[] = { interval{ 5, 9, 20 }, interval{ 4, 6, 100 }, interval{ 2, 5, 70 }, interval{ 4, 8, 50 } };
    const int interval_arr_length = sizeof(interval_arr)/sizeof(interval);
    // int min_start_time = std::numeric_limits<int>::max();
    const int max_finish_time = print_interval_array("Input Intervals:", interval_arr, interval_arr_length);
    insertion_sort(interval_arr, interval_arr_length);
    int weighted_sum = 0;
    print_interval_array("Sorted Intervals:", interval_arr, interval_arr_length, max_finish_time);
    const int optimal_result = calculate_optimal(interval_arr, interval_arr_length, weighted_sum);
    std::cout << "\nOptimal solution can schedule " << optimal_result << " intervals and weighted sum = " << weighted_sum << "!";
    return 0;
}