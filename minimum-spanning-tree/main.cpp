// main.cpp : Defines the entry point for the application.
//

#include <vector>
#include "model/subsets.h"
#include "model/solver.h"
#include "geometry/visualization.h"
#include "common/types.h"

int main()
{
    // Define a set of 2D vertices (nodes) in Cartesian coordinates.
    // These represent the vertices of the graph.
	std::vector<Point> vertices = generateUniquePoints(18);

    // Build a complete undirected graph by connecting each pair of vertices
    // and computing the Euclidean distance between them as the edge cost.
    std::vector<Edge> edges;
    int n = vertices.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            double distance = euclidean(vertices[i], vertices[j]);
            edges.push_back({ i, j, distance });
        }
    }

    // Solve the Minimum Spanning Tree (MST) problem using an IP solver (CPLEX),
    // applying subset-based cycle elimination constraints.
    // Returns a list of edges that form the MST.
    auto mst_edges = solveMST(vertices, edges);

    // Visualize the result:
    // - Blue dots represent the vertices
    // - Gray lines are from the Delaunay triangulation
    // - Red lines indicate the MST edges selected by the solver
    drawSVG(vertices, mst_edges);

    return 0;
}
