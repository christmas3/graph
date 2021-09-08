#include "Mst.h"
#include "QuickSort.h"

namespace graph {

static inline bool isIsolate(const BaseGraphWeighted& graph, const EdgeWeighted& edge)
{
    return graph.cbegin(edge.v1) == graph.cend(edge.v1) || graph.cbegin(edge.v2) == graph.cend(edge.v2);
}

Mst::Mst(const BaseGraphWeighted& graph)
    : graph_(graph)
    , mst_(graph.createEmpty())
{
    auto e = edges(graph_);
    QuickSort<EdgeWeighted>(&e[0], e.size());
    for (size_t i = 0; i < e.size() && mst_->sizeE() < mst_->sizeV() - 1; ++i) {
        if (isIsolate(*mst_, e[i])) {
            std::cerr << "Insert edge with isolate vertex: " << e[i] << std::endl;
            mst_->insert(e[i]);
        }
        else {
            std::cerr << "run dfs for edge: " << e[i] << std::endl;
            Dfs d(*mst_, e[i].v1, e[i].v2);
            if (!d.getResult()) {
                std::cerr << "Insert edge after dfs false" << std::endl;
                mst_->insert(e[i]);
            }
        }
    }
}

VectorArray<EdgeWeighted> Mst::getResult()
{
    auto res = edges(*mst_);
    return res;
}

VectorArray<EdgeWeighted> Mst::edges(const BaseGraphWeighted& graph)
{
    VectorArray<EdgeWeighted> result(graph.sizeE());

    for (int i = 0; i < graph.sizeV(); ++i) {
        for (auto iter = graph.cbegin(i); iter != graph.cend(i); ++iter) {
            if (iter->from(i)) {
                result.putBack(*iter);
            }
        }
    }

    return result;
}

Mst::Dfs::Dfs(const BaseGraphWeighted& graph, int vFrom, int vTo)
    : result_(false)
    , used_(new bool[graph.sizeV()])
{
    memset(used_, false, sizeof(bool) * graph.sizeV());
    auto iter = graph.cbegin(vFrom);
    dfs(graph, vTo, iter->v1);
}

void Mst::Dfs::dfs(const BaseGraphWeighted& graph, int vSearch, int v)
{
    if (used_[v] || result_) {
        return;
    }
    if (v == vSearch) {
        result_ = true;
        return;
    }
    used_[v] = true;

    for (auto iter = graph.cbegin(v); iter != graph.cend(v) && !result_; ++iter) {
        dfs(graph, vSearch, iter->from(v) ? iter->v2 : iter->v1);
    }
}

} // namespace graph
