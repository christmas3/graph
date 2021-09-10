#pragma once

#include "Arrays.h"
#include "BaseGraph.h"

namespace graph {
class Spt
{
public:
    Spt(const BaseGraphWeighted&, int fromV);
    ~Spt();

    const VectorArray<EdgeWeighted>& getResult() { return result_; }

private:
    int* wt_;
    int* st_;
    VectorArray<EdgeWeighted> result_;
};

} // namespace graph
