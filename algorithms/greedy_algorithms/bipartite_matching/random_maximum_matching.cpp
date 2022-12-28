#include <iostream>

struct edge {
    std::string from;
    std::string to;
};

void print_bipartite_graph(const std::string title, edge graph[], const int length) {
    std::string current_from = "";
    std::cout << "\n" << title << "\n";
    for(int i = 0; i < length; ++i) {
        // If new vertice from
        if(current_from != graph[i].from) {
            // If started listing vertices to, close it
            if(current_from != "") {
                std::cout << "\b\b }\n";
            }
            // Output new vertice from
            current_from = graph[i].from;
            std::cout << "From: " << current_from << " to -> { ";
        }
        // Output vertices to
        std::cout << graph[i].to << ", ";
    }
    // Close last open vertice from
    std::cout << "\b\b }\n";
}

template< typename T >
int remove_at(T arr[], const int length, const int index) {
    for(int i = index; i < length-1; ++i) {
        arr[i] = arr[i+1];
    }
    return length-1;
}

int pick(edge graph[], const int length, const int start_index, const int end_index) {
    return end_index-1;
}

void apply_matching(edge graph[], int& length) {
    for(int i = 0, j; i < length; ++i) {
        // Pick graph[i] to be in matching
        int start_index = i, end_index = i+1;
        // Pick all graph[i] where vertice from is identical
        while(end_index < length && graph[end_index++].from == graph[start_index].from);
        // Pick one of these graph[i]
        int picked_i = pick(graph, length, start_index, end_index);
        // Remove conflicting graph[j]
        for(j = i; j < length; ++j) {
            // Don't remove picked i
            if(j == picked_i) continue;
            // Remove graph[j] if conflict with graph[picked i]
            if(graph[picked_i].from == graph[j].from || graph[picked_i].to == graph[j].to) {
                length = remove_at(graph, length, j--);
                // Adjust picked_i index
                if(picked_i > j)
                picked_i -= 1;
            }
        }
    }
}

int main() {
    edge bipartite_graph[] = {
        edge{ "Seema", "Computer Graphics" }, edge{ "Seema", "Algorithms" }, edge{ "Ankit", "DBMS" }, edge{ "Ankit", "Algorithms" },
        edge{ "Ankit", "Theory of Computation" }, edge{ "Sonia", "Artificial Intelligence" }, edge{ "Rahul", "Artificial Intelligence" },
        edge{ "Puja", "Theory of Computation" }
    };
    int bipartite_graph_length = sizeof(bipartite_graph)/sizeof(edge);
    print_bipartite_graph("Bipartite Graph:", bipartite_graph, bipartite_graph_length);
    apply_matching(bipartite_graph, bipartite_graph_length);
    print_bipartite_graph("Matched Graph:", bipartite_graph, bipartite_graph_length);
    return 0;
}