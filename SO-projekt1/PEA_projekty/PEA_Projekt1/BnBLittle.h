#ifndef PEA_PROJEKT1_BNBLITTLE_H
#define PEA_PROJEKT1_BNBLITTLE_H

#include <vector>
#include <queue>
#include <atomic>
#include "limits.h"
#include "Graph.h"
#include "Timer.h"

class BnBLittle {
public:
    bool findTourLittle(const Graph& graph, int timeout_ms = -1, bool print_result = true);
private:
    struct Node{
        std::vector<std::vector<int>> included_paths;
        std::vector<std::vector<int>> omitted_paths;
        std::vector<bool> row_excluded;
        std::vector<bool> col_excluded;
        std::vector<std::vector<int>> cost_matrix;
        int lower_bound;
        int side_length;
        int no_of_cities;

        explicit Node(int side_length)
            : row_excluded(side_length, false),
              col_excluded(side_length, false),
              cost_matrix(side_length, std::vector<int>(side_length)),
              lower_bound(0),
              no_of_cities(side_length)
        {}
    };

    struct CompareNodes{
        bool operator()(const Node& node1, const Node& node2) const;
    };

    static std::vector<Node> createSubTrees(const Node &X, int no_of_cities);
    static int reduceCostMatrix(std::vector<std::vector<int>>& cost_matrix, int side_length, const std::vector<bool>& row_excluded, const std::vector<bool>& col_excluded);
    static std::vector<int> findDivision(const std::vector<std::vector<int>>& cost_matrix, int side_length, const std::vector<bool>& row_excluded, const std::vector<bool>& col_excluded);
    static std::vector<int> findSubTour(const std::vector<int>& path, const std::vector<std::vector<int>>& included_cities);
    static std::vector<std::vector<int>> findRemainingPaths(int no_of_cities, const std::vector<bool>& row_excluded, const std::vector<bool>& col_excluded, std::vector<std::vector<int>> included_paths);
    static void printTour(std::vector<std::vector<int>> paths, int result, int no_of_cities);
    static bool makesSubTour(int row_index, int col_index, const std::vector<std::vector<int>>& paths, bool all_connections);
};


#endif //PEA_PROJEKT1_BNBLITTLE_H
