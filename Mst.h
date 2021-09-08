#pragma once

#include "Arrays.h"
#include "BaseGraph.h"

namespace graph {

class Mst
{
public:
    explicit Mst(const BaseGraphWeighted&);

    VectorArray<EdgeWeighted> getResult();

private:
    static VectorArray<EdgeWeighted> edges(const BaseGraphWeighted&);

    class Dfs
    {
    public:
        explicit Dfs(const BaseGraphWeighted&, int vFrom, int vTo);
        ~Dfs() { delete[] used_; }

        bool getResult() const { return result_; }

    private:
        void dfs(const BaseGraphWeighted&, int vSearch, int v);

        bool result_;
        bool* used_;
    };

    const BaseGraphWeighted& graph_;
    std::unique_ptr<BaseGraphWeighted> mst_;
};

} // namespace graph
