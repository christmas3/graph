#include "Spt.h"

#include <cassert>
#include <cstring>
#include <limits>

namespace graph {
Spt::Spt(const BaseGraphWeighted& g, int fromV)
    : wt_(new int[g.sizeV()])
    , st_(new int[g.sizeV()])
{
    for (int i = 0; i < g.sizeV(); ++i) {
        wt_[i] = std::numeric_limits<int>::max();
    }

    auto spt = g.createEmpty();
    wt_[fromV] = 0;

    auto curV = fromV;
    while (spt->sizeE() < g.sizeV() - 1) {
        for (auto iter = g.cbegin(curV); iter != g.cend(curV); ++iter) {
            auto w = iter->v1 == curV ? iter->v2 : iter->v1;
            if (w == fromV || spt->cbegin(w) != spt->cend(w)) {
                continue;
            }
            auto cost = wt_[curV] + iter->weight;
            if (cost < wt_[w]) {
                wt_[w] = cost;
                st_[w] = curV;
            }
        }
        auto min = std::numeric_limits<int>::max();
        auto minV = fromV;
        for (int i = 0; i < g.sizeV(); ++i) {
            if (i == fromV || spt->cbegin(i) != spt->cend(i)) {
                continue;
            }
            if (wt_[i] < min) {
                min = wt_[i];
                minV = i;
            }
        }
        assert(minV != fromV);
        auto e = getEdge(g, st_[minV], minV);
        assert(e != EdgeWeighted{});
        spt->insert(e);
        curV = minV;
    }
    result_ = edges<VectorArray<EdgeWeighted>>(*spt);
}

Spt::~Spt()
{
    delete[] wt_;
    delete[] st_;
}

} // namespace graph
