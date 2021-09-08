#pragma once

#include "Arrays.h"
#include "BaseGraph.h"

namespace graph {

template<typename T>
using DMatrix = VectorArray<VectorArray<T>>;

template<typename T>
class TopologicalSort
{
public:
    explicit TopologicalSort(const BaseGraph<T>&);
    ~TopologicalSort();

    const DMatrix<int>& result() const { return result_; }

private:
    void printSum();

    const BaseGraph<T>& graph_;

    DMatrix<int> result_;
    int* sum_;
};

} // namespace graph
