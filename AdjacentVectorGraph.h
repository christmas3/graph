#include "BaseGraph.h"

namespace graph {
class AdjacentVectorGraph : public BaseGraph
{
public:
    AdjacentVectorGraph(size_t v, size_t s);
    ~AdjacentVectorGraph() override;

    size_t sizeV() const override;
    size_t sizeE() const override;
    Iterator begin(size_t v) override;
    Iterator end(size_t v) override;
    const Iterator cbegin(size_t v) const override;
    const Iterator cend(size_t v) const override;
    void print() const override;
    bool insert(const Edge&) override;
    std::unique_ptr<BaseGraph> createEmpty() const override;

private:
    size_t sizeV_;
    size_t sizeE_;
    size_t sizeS_;
    int** graph_;
    int* end_;
};
} // namespace graph
