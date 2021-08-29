#include "TopologicalSort.h"
#include "Arrays.h"

namespace graph {

TopologicalSort::TopologicalSort(const BaseGraph& g)
    : graph_(g)
    , sum_(new int[graph_.sizeV()])
{
    memset(sum_, 0, sizeof(int) * graph_.sizeV());
    for (auto v = 0; v < graph_.sizeV(); ++v) {
        for (auto iter = graph_.cbegin(v); iter != graph_.cend(v); ++iter) {
            ++sum_[*iter];
        }
    }
    VectorArray<int> level;
    for (int v = 0; v < graph_.sizeV(); ++v) {
        if (!sum_[v]) {
            level.putBack(v);
        }
    }
    result_.putBack(std::move(level));

    size_t prevSize = 0;
    while (prevSize != result_.size()) {
        prevSize = result_.size();
        VectorArray<int> nextLevel;
        for (int i = 0; i < result_.back().size(); ++i) {
            const auto& v = result_.back().get(i);
            for (auto iter = graph_.cbegin(v); iter != graph_.cend(v); ++iter) {
                if (--sum_[*iter] == 0) {
                    nextLevel.putBack(*iter);
                }
            }
        }
        if (!nextLevel.empty()) {
            result_.putBack(std::move(nextLevel));
        }
    }
}

TopologicalSort::~TopologicalSort()
{
    delete[] sum_;
}

void TopologicalSort::printSum()
{
    for (size_t i = 0; i < graph_.sizeV(); ++i) {
        std::cerr << i << ": " << sum_[i] << std::endl;
    }
}

} // namespace graph
