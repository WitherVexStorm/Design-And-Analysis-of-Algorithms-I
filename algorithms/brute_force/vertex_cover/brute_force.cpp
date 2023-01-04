#include <iostream>

struct edge {
    std::string from;
    std::string to;
    int weight;
};

template< typename T >
void print_arr(std::string title, T arr[], int length) {
    std::cout << "\n" << title << "\n{  ";
    for(int i = 0; i < length; ++i) {
        std::cout << arr[i] << ", ";
    }
    std::cout << "\b\b }\n";
}

int calc_combinations(const int n, const int i, int pdt = 1) {
    if(n < 0 || i > n || i < 0) return -1;
    for(int j = 1, num = n, den = 1; j <= i; ++j, --num, ++den) {
        pdt = pdt * num / den;
    }
    return pdt;
}

void generate_combinations(const std::string values[], const int n, std::string result[], const int i, const int start_index = 0) {
    if(n < 1 || i < 1 || n < i) return;
    for(int j = 0; j <= n - i; ++j) {
        for(int k = start_index + calc_combinations(n-j-1, i-1) - 1; k >= start_index; --k) {
            result[k] += values[j];
        }
        std::string sub_arr[n-j-1];
        for(int k = j+1; k < n; ++k) {
            sub_arr[k-j-1] = values[k];
        }
        generate_combinations(sub_arr, n-j-1, result, i-1, start_index + calc_combinations(n-j-1, i-1));
    }
}

void filter_feasible(edge graph[], const int graph_length, std::string vertice_combinations[], int& vertice_combinations_length) {
    for(int i = 0, filtered_index = 0; i < vertice_combinations_length; ++i) {
        // See how many edges are covered by the vertices
        bool edge_covered[graph_length] = { false };
        for(int j = 0; j < vertice_combinations[i].length(); ++j) {
            for(int k = 0; k < graph_length; ++k) {
                if(graph[k].from == std::string(1, vertice_combinations[i][j]) || graph[k].to == std::string(1, vertice_combinations[i][j])) {
                    // std::cout << "I: " << i << ", J: " << j << ", K: " << k << ", vertice_from: " << graph[k].from << ", vertice_to: " << vertice_combinations[i][j] << "\n";
                    edge_covered[k] = true;
                }
            }
        }

        // Check if all edges were covered
        bool all_edges_covered = true;
        // std::cout << "I: " << i << " -> ";
        for(int j = 0; j < graph_length; ++j) {
            // std::cout << edge_covered[j] << ", ";
            if(edge_covered[j] == false) {
                all_edges_covered = false;
                break;
            }
        }
        // std::cout << "\n";

        // If unfeasible, remove current combination by shifting all others remaining up
        if(!all_edges_covered) {
            for(int j = i+1; j < vertice_combinations_length; ++j) {
                vertice_combinations[j-1] = vertice_combinations[j];
            }
            vertice_combinations_length -= 1;
            i -= 1;
        }
    }
}

int main() {
    edge graph[] = {
        edge{ "A", "B", 2 }, edge{ "A", "C", 6 }, edge{ "A", "D", 7 }, edge{ "A", "E", 1 }, 
        edge{ "B", "C", 5 }, edge{ "C", "D", 4 }, edge{ "C", "E", 8 }, edge{ "D", "E", 3 }, 
        edge{ "B", "A", 2 }, edge{ "C", "A", 6 }, edge{ "D", "A", 7 }, edge{ "E", "A", 1 }, 
        edge{ "C", "B", 5 }, edge{ "D", "C", 4 }, edge{ "E", "C", 8 }, edge{ "E", "D", 3 } 
    };
    std::string vertices[] = { "A", "B", "C", "D", "E" };
    // std::cout << calc_combination_count(5, 0) << "\n" << calc_combination_count(5, 1) << "\n" << calc_combination_count(5, 2) << "\n";
    // std::cout << calc_combination_count(5, 3) << "\n" << calc_combination_count(5, 4) << "\n" << calc_combination_count(5, 5) << "\n";
    int camera_placed_combinations_length = calc_combinations(5, 3);
    std::string camera_placed_combinations[camera_placed_combinations_length];
    generate_combinations(vertices, 5, camera_placed_combinations, 3);
    print_arr("Possible Camera Positions:", camera_placed_combinations, camera_placed_combinations_length);
    filter_feasible(graph, sizeof(graph)/sizeof(edge), camera_placed_combinations, camera_placed_combinations_length);
    print_arr("Valid Camera Positions:", camera_placed_combinations, camera_placed_combinations_length);
    return 0;
}