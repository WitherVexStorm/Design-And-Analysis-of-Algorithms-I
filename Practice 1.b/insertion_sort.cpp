#include <iostream>

int insertion_algorithm(int arr[], int i) {
    int element = arr[i], j = i-1;
    for(; j >= 0 && arr[j] > element; --j) {
        arr[j+1] = arr[j];
    }
    arr[j+1] = element;
    return j + 1;
}

void insertion_sort(int arr[], int length) {
    for(int i = 1, j; i < length; ++i) {
        insertion_algorithm(arr, i);
    }
}

inline unsigned int calc_factorial(int n, unsigned int pdt = 1) {
    for(int i = n; i > 1; --i) {
        pdt *= i;
    }
    return pdt;
}

void generate_permutations(int table[][4], int possible_values[], int possible_values_length, int permutation_length, int starting_permutation_number = 0) {
    unsigned const int factorial = calc_factorial(possible_values_length-1);

    // Debug
    // std::cout << "Original values x" << factorial << ": { ";
    // for(int i = 0; i < possible_values_length; ++i)
    // std::cout << possible_values[i] << ", ";
    // std::cout << "\b\b }\n";
    
    // For every possible digit
    for(int value_i = 0; value_i < possible_values_length; ++value_i) {

        // Set all permutation numbers
        for(int permutation_number = 0; permutation_number < factorial; ++permutation_number) {
            table[permutation_number + starting_permutation_number + factorial*value_i][permutation_length - possible_values_length] = possible_values[value_i];
        }

        // Remove current digit from further permutations
        int new_possible_values[possible_values_length-1] = { 0 };
        for(int check_value_index = 0, insert_value_index = 0; check_value_index < possible_values_length; ++check_value_index) {
            if(check_value_index != value_i) {
                new_possible_values[insert_value_index++] = possible_values[check_value_index];
            }
        }

        // Debug
        // std::cout << "Current value at " << value_i << " : " << possible_values[value_i] << " = ";
        // for(int i = 0; i < possible_values_length-1; ++i)
        // std::cout << new_possible_values[i] << ", ";
        // std::cout << "\b\b \n\n";

        // Recurse further in
        generate_permutations(table, new_possible_values, possible_values_length-1, permutation_length, starting_permutation_number + factorial*value_i);
    }
}

int main() {
    std::cout << "Using Array = {4, 8, 2, 7, 9, 1, 6, 5, 3, 0}\n\n";
    int arr[] = { 4, 1, 2, 3 };
    const int arr_length = sizeof(arr)/sizeof(int);
    std::cout << "Starting Insertion Sort: ...\n";
    insertion_sort(arr, arr_length);
    const int max_element = arr[arr_length-1];
    std::cout << "Done.\n\nResulting Array = {";
    for(int i = 0; i < arr_length; ++i)
    std::cout << arr[i] << ", ";
    const unsigned int total_permutations = calc_factorial(arr_length);
    int table[total_permutations][arr_length] = { 0 };
    std::cout << "\b\b}\n\nTable of Permutations:\n\n";
    generate_permutations(table, arr, arr_length, arr_length);
    for(int i = 0; i < total_permutations; ++i) {
        std::cout << i << ": ";
        for(int j = 0; j < arr_length; ++j)
        std::cout << table[i][j] << ", ";
        std::cout << "\b\b \n";
    }

    // Define structure to map array element with it's permutation details
    struct element_to_permutations {
        int a_val;
        int ** permutation_details = 0;
        int permutation_count[arr_length] = { 0 };
    };

    struct index_to_element {
        int i_val;
        element_to_permutations permutations[arr_length];
        int final_count_at_j[arr_length] = { 0 };
        int comparisons_to_insert_at_j[arr_length] = { 0 };
        int total_comparisons = 0;
    } array_element_permutations_arr[arr_length];
    // For each index for each permutation for each ai to be placed in j location

    // Initialise Permutation table
    for(int i = 0; i < arr_length; ++i) {
        array_element_permutations_arr[i].i_val = i;
        for(int j = 0; j < arr_length; ++j) {
            array_element_permutations_arr[i].permutations[j].a_val = arr[j];
            array_element_permutations_arr[i].permutations[j].permutation_details = new int*[arr_length];
            for(int k = 0; k < arr_length; ++k) {
                array_element_permutations_arr[i].permutations[j].permutation_details[k] = new int[total_permutations]{ 0 };
            }
        }
    }

    // Create reversed array that maps array elements to their indexes
    int indexed_arr[max_element+1] = { -1 };
    for(int i = 0; i < arr_length; ++i) {
        indexed_arr[arr[i]] = i;
    }
    // Debug
    // for(int i = 0; i < max_element+1; ++i) {
    //     std::cout << indexed_arr[i] << "\n";
    // }
    // std::cout << "End.\n";
    // int a_i_inserted_at_j_array[arr_length][arr_length][total_permutations] = {0};
    // int a_i_inserted_at_j_counts[arr_length] = {0};
    for(int j = 0; j < arr_length; ++j) {
        for(int i = 0; i < total_permutations; ++i) {
            int a_i = table[i][j];
            int a_i_inserted_at_j = insertion_algorithm(table[i], j);
            // a_i_inserted_at_j_array[a_i-1][a_i_inserted_at_j][a_i_inserted_at_j_counts[a_i_inserted_at_j]++] = i;
            element_to_permutations& current_array_element_permutations = array_element_permutations_arr[j].permutations[indexed_arr[a_i]];
            // std::cout << current_array_element_permutations.a_val << " == " << a_i << "\n";
            current_array_element_permutations.permutation_details[a_i_inserted_at_j][current_array_element_permutations.permutation_count[a_i_inserted_at_j]++] = i;
            // std::cout << "Count: " << a_i_inserted_at_j << ", " << current_array_element_permutations.permutation_count[a_i_inserted_at_j] << " - " << current_array_element_permutations.permutation_details[a_i_inserted_at_j][0] << "\n";
            array_element_permutations_arr[j].final_count_at_j[a_i_inserted_at_j] += 1;
        }
    }
    std::cout << "\nTable of Insertions of A[i] at jth location:";
    for(int i = 0; i < arr_length; ++i) {
        std::cout << "\n\nFor i = " << i << ":\n\n";
        for(int j = 0; j < arr_length; ++j) {
            std::cout << "For arr[i] = " << array_element_permutations_arr[i].permutations[j].a_val << "\n";
            for(int k = 0; k < arr_length; ++k) {
                std::cout << "For j = " << k << ": {" << (array_element_permutations_arr[i].permutations[j].permutation_count[k] > 0 ? " " : "  ");
                for(int l = 0; l < array_element_permutations_arr[i].permutations[j].permutation_count[k]; ++l) {
                    std::cout << array_element_permutations_arr[i].permutations[j].permutation_details[k][l] << ", ";
                }
                std::cout << "\b\b }\n";
            }
        }
        // To calculate probability of a[i] being inserted at jth location for each permutation for each a[i] for each index 1 = 1...4
        std::cout << "\nFinal counts for j:\n";
        for(int j = 0; j < arr_length; ++j) {
            std::cout << "For j = " << j << ": " << array_element_permutations_arr[i].final_count_at_j[j] << "\n";
        }
        // To calculate total comparisons
        std::cout << "\nTotal Comparisons for j:\n";
        for(int j = 0; j < arr_length; ++j) {
            if(j <= i)
            array_element_permutations_arr[i].comparisons_to_insert_at_j[j] = (i - j + 1) * array_element_permutations_arr[i].final_count_at_j[j];
            array_element_permutations_arr[i].total_comparisons += array_element_permutations_arr[i].comparisons_to_insert_at_j[j];
            std::cout << "For j = " << j << ": " << array_element_permutations_arr[i].comparisons_to_insert_at_j[j] << "\n";
        }
    }
    
    // To calculate average comparisons
    std::cout << "\nAverage Comparisons for i:";
    for(int i = 0; i < arr_length; ++i) {
        std::cout << "\nFor i = " << i << ": " << array_element_permutations_arr[i].total_comparisons * 1.0 / total_permutations;
    }

    // Delete dynamic memory
    for(int i = 0; i < arr_length; ++i) {
        for(int j = 0; i < arr_length; ++j) {
            for(int k = 0; k < arr_length; ++k) {
                delete[] array_element_permutations_arr[i].permutations[j].permutation_details[k];
            }
            delete[] array_element_permutations_arr[i].permutations[j].permutation_details;
        }
    }
    return 0;
}