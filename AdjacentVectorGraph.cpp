#include "AdjacentVectorGraph.h"

#include <cstring>
#include <iostream>

namespace graph {

AdjacentVectorGraph::AdjacentVectorGraph(size_t v, size_t s)
    : sizeV_(v)
    , sizeE_(0)
    , sizeS_(s)
    , graph_(new int*[sizeV_])
    , end_(new int[sizeV_])
{
    for (size_t i = 0; i < sizeV_; ++i) {
        graph_[i] = new int[sizeS_];
        memset(graph_[i], -1, sizeof(int) * sizeS_);
        end_[i] = 0;
    }
}

AdjacentVectorGraph::~AdjacentVectorGraph()
{
    for (size_t i = 0; i < sizeV_; ++i) {
        delete[] graph_[i];
    }
    delete[] graph_;
    delete[] end_;
}

size_t AdjacentVectorGraph::sizeV() const
{
    return sizeV_;
}

size_t AdjacentVectorGraph::sizeE() const
{
    return sizeE_;
}

BaseGraph::Iterator AdjacentVectorGraph::begin(size_t v)
{
    return Iterator(graph_[v]);
}

BaseGraph::Iterator AdjacentVectorGraph::end(size_t v)
{
    return Iterator(graph_[v] + end_[v]);
}

const BaseGraph::Iterator AdjacentVectorGraph::cbegin(size_t v) const
{
    return Iterator(graph_[v]);
}

const BaseGraph::Iterator AdjacentVectorGraph::cend(size_t v) const
{
    return Iterator(graph_[v] + end_[v]);
}

void AdjacentVectorGraph::print() const
{
    for (size_t i = 0; i < sizeV_; ++i) {
        auto iter = cbegin(i);
        auto end = cend(i);
        std::cerr << i << ": ";
        while (iter != end) {
            std::cerr << *iter++ << " ";
        }
        std::cerr << std::endl;
    }
}

bool AdjacentVectorGraph::insert(const Edge& e)
{
    if (std::max(e.v1, e.v2) >= sizeV_) {
        return false;
    }

    if (end_[e.v1] == sizeS_) {
        return false;
    }

    for (auto iter = begin(e.v1); iter != end(e.v1); ++iter) {
        if (e.v2 == *iter) {
            return false;
        }
    }

    *(end(e.v1)) = e.v2;
    end_[e.v1] += 1;
    ++sizeE_;

    return true;
}

std::unique_ptr<BaseGraph> AdjacentVectorGraph::createEmpty() const
{
    return std::unique_ptr<BaseGraph>(new AdjacentVectorGraph(sizeV_, sizeS_));
}

} // namespace graph
