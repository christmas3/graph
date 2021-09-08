#include "AdjacentVectorGraph.h"

#include <cstring>
#include <iostream>

namespace graph {

template<typename T, typename E>
AdjacentVectorGraph<T, E>::AdjacentVectorGraph(size_t v, size_t s)
    : sizeV_(v)
    , sizeE_(0)
    , sizeS_(s)
    , graph_(new T*[sizeV_])
    , end_(new int[sizeV_])
{
    for (size_t i = 0; i < sizeV_; ++i) {
        graph_[i] = new T[sizeS_];
        memset(graph_[i], -1, sizeof(int) * sizeS_);
        end_[i] = 0;
    }
}

template<typename T, typename E>
AdjacentVectorGraph<T, E>::~AdjacentVectorGraph()
{
    for (size_t i = 0; i < sizeV_; ++i) {
        delete[] graph_[i];
    }
    delete[] graph_;
    delete[] end_;
}

template<typename T, typename E>
size_t AdjacentVectorGraph<T, E>::sizeV() const
{
    return sizeV_;
}

template<typename T, typename E>
size_t AdjacentVectorGraph<T, E>::sizeE() const
{
    return sizeE_;
}

template<typename T, typename E>
typename AdjacentVectorGraph<T, E>::Iterator AdjacentVectorGraph<T, E>::begin(size_t v)
{
    return Iterator(graph_[v]);
}

template<typename T, typename E>
typename AdjacentVectorGraph<T, E>::Iterator AdjacentVectorGraph<T, E>::end(size_t v)
{
    return Iterator(graph_[v] + end_[v]);
}

template<typename T, typename E>
const typename AdjacentVectorGraph<T, E>::Iterator AdjacentVectorGraph<T, E>::cbegin(size_t v) const
{
    return Iterator(graph_[v]);
}

template<typename T, typename E>
const typename AdjacentVectorGraph<T, E>::Iterator AdjacentVectorGraph<T, E>::cend(size_t v) const
{
    return Iterator(graph_[v] + end_[v]);
}

template<typename T, typename E>
void AdjacentVectorGraph<T, E>::print() const
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

template<>
bool AdjacentVectorGraph<int, Edge>::insert(const Edge& e)
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

template<typename T, typename E>
std::unique_ptr<BaseGraph<T, E>> AdjacentVectorGraph<T, E>::createEmpty() const
{
    return std::unique_ptr<BaseGraph<T, E>>(new AdjacentVectorGraph(sizeV_, sizeS_));
}

template<>
bool AdjacentVectorGraph<EdgeWeighted, EdgeWeighted>::insert(const EdgeWeighted& e)
{
    if (std::max(e.v1, e.v2) >= sizeV_) {
        return false;
    }

    if (end_[e.v1] == sizeS_) {
        return false;
    }

    for (auto iter = begin(e.v1); iter != end(e.v1); ++iter) {
        if (e.v2 == iter->v2) {
            return false;
        }
    }

    *(end(e.v1)) = e;
    end_[e.v1] += 1;

    *(end(e.v2)) = e;
    end_[e.v2] += 1;

    ++sizeE_;

    return true;
}

template class AdjacentVectorGraph<int, Edge>;
template class AdjacentVectorGraph<EdgeWeighted, EdgeWeighted>;

} // namespace graph
