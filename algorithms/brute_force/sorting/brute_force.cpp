#include <iostream>

template< typename T >
inline void print_arr(const std::string title, T arr[], const int length) {
    std::cout << "\n" << title << "\n{  ";
    for(int i = 0; i < length; ++i) {
        std::cout << arr[i] << ", ";
    }
    std::cout << "\b\b }\n";
}
template< typename T >
inline void print_2d_arr(const std::string title, const std::string line_header, T arr[][4], const int rows, const int columns) {
    std::cout << "\n" << title << "\n";
    for(int i = 0; i < rows; ++i) {
        std::cout << line_header << i << ": {  ";
        for(int j = 0; j < columns; ++j)
        std::cout << arr[i][j] << ", ";
        std::cout << "\b\b }\n";
    }
}

int calc_permutations(const int n, const int i, int pdt = 1) {
    if(n < 0 || i < 0 || i > n) return -1;
    for(int j = n; j > n-i && j > 1; --j) {
        pdt *= j;
    }
    return pdt;
}

void generate_permutations(int arr[], const int arr_length, int permutations[][4], const int start_index = 0, const int insert_index = 0) {
    if(arr_length < 1) return;
    for(int i = 0; i < arr_length; ++i) {
        // fix current element in insertion place
        const int interval = calc_permutations(arr_length-1, arr_length-1);
        for(int j = start_index + (i+1) * interval - 1; j >= start_index + i * interval; --j ) {
            permutations[j][insert_index] = arr[i];
        }
        // create subarray removing fixed element
        int sub_arr[arr_length-1] = {0};
        for(int j = 0, k = 0; j < arr_length; ++j) {
            if(j == i) continue;
            sub_arr[k++] = arr[j];
        }
        // recurse into the subarray
        generate_permutations(sub_arr, arr_length-1, permutations, start_index + i*calc_permutations(arr_length-1, arr_length-1), insert_index+1);
    }
}

void filter_feasible(int possible_permutations[][4], int& possible_permutations_length, const int arr_length) {
    for(int i = 0; i < possible_permutations_length; ++i) {
        for(int j = 1; j < arr_length; ++j) {
            // If not sorted array
            if(possible_permutations[i][j-1] > possible_permutations[i][j]) {
                // Shift all permutations up
                for(int k = i+1; k < possible_permutations_length; ++k) {
                    for(int l = 0; l < arr_length; ++l) {
                        possible_permutations[k-1][l] = possible_permutations[k][l];
                    }
                }
                // Adjust i
                possible_permutations_length -= 1;
                i -= 1;
                break;
            }
        }
    }
}

int main() {
    // int arr[] = {4, 7, 1, 5, 2, 9};
    int arr[] = {4, 7, 1, 5};
    const int length = sizeof(arr)/sizeof(int);
    print_arr("Input Array:", arr, length);
    // std::cout << calc_permutations(5, -1) << "\n" << calc_permutations(0, -1) << "\n" << calc_permutations(0, 5) << "\n";
    // std::cout << calc_permutations(1, 5) << "\n" << calc_permutations(5, 0) << "\n" << calc_permutations(5, 1) << "\n";
    // std::cout << calc_permutations(5, 2) << "\n" << calc_permutations(5, 3) << "\n" << calc_permutations(5, 4) << "\n";
    // std::cout << calc_permutations(5, 5) << "\n" << calc_permutations(5, 6) << "\n" << calc_permutations(5, 7) << "\n";
    int permutations_length = calc_permutations(length, length);
    int possible_permutations[permutations_length][length] = {0};
    generate_permutations(arr, length, possible_permutations);
    print_2d_arr("Total Permutations:", "i = ", possible_permutations, permutations_length, length);
    filter_feasible(possible_permutations, permutations_length, length);
    print_2d_arr("Sorted Arrays:", "i = ", possible_permutations, permutations_length, length);
    return 0;
}