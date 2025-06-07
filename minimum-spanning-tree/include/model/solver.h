#pragma once

#pragma once

#include <vector>
#include <utility>

#include "common/types.h"

/**
 * @brief Solves the Minimum Spanning Tree (MST) problem using an Integer Programming (IP) 
 *        formulation with CPLEX and subset-based subtour elimination constraints.
 * 
 * The MST is constructed by:
 *  - Defining binary decision variables for each edge.
 *  - Minimizing the total weight of selected edges.
 *  - Enforcing:
 *      (1) Exactly (n - 1) edges must be selected.
 *      (2) No cycles are allowed, by applying subset-based constraints
 *          to all non-trivial subsets of vertices.
 *
 * This function uses exhaustive subset enumeration and is suitable for small graphs (n ≤ ~12).
 *
 * @param vertices A vector of 2D vertices (nodes), each represented by a Point struct containing x and y coordinates.
 * @param edges  A vector of edges connecting pairs of vertices, each represented by an Edge struct with 
 *               endpoints u, v and a cost (typically Euclidean distance).
 * 
 * @return std::vector<std::pair<int, int>> 
 *         A list of pairs (u, v) representing the edges selected in the MST.
 *         Also prints the total cost of the resulting MST to standard output.
 */
std::vector<std::pair<int, int>> solveMST(const std::vector<Point>& vertices, const std::vector<Edge>& edges);
