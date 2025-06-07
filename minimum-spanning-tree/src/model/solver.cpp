#include "model/solver.h"

#include <ilcplex/ilocplex.h>
#include <iostream>
#include <set>
#include <thread>

#include "model/subsets.h"

std::vector<std::pair<int, int>> solveMST(const std::vector<Point>& vertices, const std::vector<Edge>& edges)
{
    std::cout << "Solving MST...\n";

    std::vector<std::pair<int, int>> mst_edges;
    IloEnv env;
    try
    {
        int n = vertices.size();
        int m = edges.size();
        IloModel model(env);
        IloBoolVarArray x(env, m);

        // Objective: minimize total edge cost
        IloExpr obj(env);
        for (int e = 0; e < m; ++e)
            obj += edges[e].cost * x[e];
        model.add(IloMinimize(env, obj));
        obj.end();

        // Constraint: tree has exactly n - 1 edges
        IloExpr edge_sum(env);
        for (int e = 0; e < m; ++e)
            edge_sum += x[e];
        model.add(edge_sum == n - 1);
        edge_sum.end();

        // Subtour elimination
        auto subsets = generateSubsets(n);
        for (const auto& subset : subsets)
        {
            std::set<int> S(subset.begin(), subset.end());
            IloExpr sum_in_S(env);
            for (int e = 0; e < m; ++e)
            {
                int u = edges[e].u, v = edges[e].v;
                if (S.count(u) && S.count(v))
                    sum_in_S += x[e];
            }
            model.add(sum_in_S <= (int)S.size() - 1);
            sum_in_S.end();
        }

        // Solve
        IloCplex cplex(model);
        cplex.setOut(env.getNullStream());
        cplex.setParam(IloCplex::ParallelMode, 1); // opportunistic
        cplex.setParam(IloCplex::Threads, std::thread::hardware_concurrency());
        if (!cplex.solve())
        {
            std::cerr << "No solution found." << std::endl;
            return {};
        }

        std::cout << "Total MST cost: " << cplex.getObjValue() << std::endl;

        // Collect edges
        for (int e = 0; e < m; ++e)
            if (cplex.getValue(x[e]) > 0.5)
                mst_edges.emplace_back(edges[e].u, edges[e].v);
    }
    catch (IloException& e)
    {
        std::cerr << "CPLEX exception: " << e.getMessage() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown error solving MST." << std::endl;
    }
    env.end();
    return mst_edges;
}
