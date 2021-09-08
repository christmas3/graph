#include "BaseGraph.h"

namespace graph {
template<typename T, typename E>
class AdjacentVectorGraph : public BaseGraph<T, E>
{
public:
    using typename BaseGraph<T, E>::Iterator;

    AdjacentVectorGraph(size_t v, size_t s);
    ~AdjacentVectorGraph() override;

    size_t sizeV() const override;
    size_t sizeE() const override;
    Iterator begin(size_t v) override;
    Iterator end(size_t v) override;
    const Iterator cbegin(size_t v) const override;
    const Iterator cend(size_t v) const override;
    bool insert(const E&) override;
    void print() const override;
    std::unique_ptr<BaseGraph<T, E>> createEmpty() const override;

private:
    size_t sizeV_;
    size_t sizeE_;
    size_t sizeS_;
    T** graph_;
    int* end_;
};

using AdjacentVectorVertexGraph = AdjacentVectorGraph<int, Edge>;

using AdjacentVectorWeightGraph = AdjacentVectorGraph<EdgeWeighted, EdgeWeighted>;

} // namespace graph
