#include <gtest/gtest.h>
#include <regex>

#include "AdjacentVectorGraph.h"
#include "StrengthComponents.h"
#include "TopologicalSort.h"

static std::string delim(80, '=');

TEST(GraphSuit, KosarajuTest)
{
    std::unique_ptr<graph::BaseGraph> g(new graph::AdjacentVectorGraph(8, 3));

    EXPECT_EQ(g->sizeE(), 0);
    EXPECT_EQ(g->sizeV(), 8);

    EXPECT_TRUE(g->insert({ 0, 1 }));
    EXPECT_EQ(g->sizeE(), 1);

    EXPECT_TRUE(g->insert({ 1, 4 }));
    EXPECT_TRUE(g->insert({ 1, 5 }));
    EXPECT_TRUE(g->insert({ 1, 2 }));
    EXPECT_EQ(g->sizeE(), 4);

    EXPECT_TRUE(g->insert({ 2, 3 }));
    EXPECT_TRUE(g->insert({ 2, 6 }));
    EXPECT_EQ(g->sizeE(), 6);

    EXPECT_TRUE(g->insert({ 3, 2 }));
    EXPECT_TRUE(g->insert({ 3, 7 }));
    EXPECT_EQ(g->sizeE(), 8);

    EXPECT_TRUE(g->insert({ 4, 0 }));
    EXPECT_TRUE(g->insert({ 4, 5 }));
    EXPECT_EQ(g->sizeE(), 10);

    EXPECT_TRUE(g->insert({ 5, 6 }));
    EXPECT_EQ(g->sizeE(), 11);

    EXPECT_TRUE(g->insert({ 6, 5 }));
    EXPECT_EQ(g->sizeE(), 12);

    EXPECT_TRUE(g->insert({ 7, 3 }));
    EXPECT_TRUE(g->insert({ 7, 6 }));
    EXPECT_EQ(g->sizeE(), 14);

    std::unique_ptr<graph::BaseGraph> gReverse(new graph::AdjacentVectorGraph(8, 3));

    graph::reverseGraph(*g, *gReverse);

    graph::StrengthComponentsK sc(*g);

    auto* result = sc.result();

    std::cerr << "Strength components: ";
    for (size_t i = 0; i < g->sizeV(); ++i) {
        std::cerr << result[i] << " ";
    }
    std::cerr << std::endl;

    EXPECT_TRUE(result[5] == result[6]);
    EXPECT_TRUE(result[0] == result[1] && result[0] == result[4]);
    EXPECT_TRUE(result[2] == result[3] && result[2] == result[7]);
}

#define TMP_MACROS(x1, x2) EXPECT_EQ(x1, x2)

TEST(GraphSuit, DemucronTest)
{
    std::unique_ptr<graph::BaseGraph> g(new graph::AdjacentVectorGraph(14, 5));

    EXPECT_TRUE(g->insert({ 0, 2 }));
    EXPECT_TRUE(g->insert({ 0, 12 }));
    EXPECT_TRUE(g->insert({ 1, 12 }));
    EXPECT_TRUE(g->insert({ 3, 2 }));
    EXPECT_TRUE(g->insert({ 4, 2 }));
    EXPECT_TRUE(g->insert({ 4, 8 }));
    EXPECT_TRUE(g->insert({ 4, 9 }));
    EXPECT_TRUE(g->insert({ 5, 3 }));
    EXPECT_TRUE(g->insert({ 5, 10 }));
    EXPECT_TRUE(g->insert({ 5, 11 }));
    EXPECT_TRUE(g->insert({ 5, 12 }));
    EXPECT_TRUE(g->insert({ 6, 10 }));
    EXPECT_TRUE(g->insert({ 7, 1 }));
    EXPECT_TRUE(g->insert({ 7, 3 }));
    EXPECT_TRUE(g->insert({ 7, 5 }));
    EXPECT_TRUE(g->insert({ 7, 6 }));
    EXPECT_TRUE(g->insert({ 8, 0 }));
    EXPECT_TRUE(g->insert({ 8, 13 }));
    EXPECT_TRUE(g->insert({ 9, 0 }));
    EXPECT_TRUE(g->insert({ 9, 6 }));
    EXPECT_TRUE(g->insert({ 9, 11 }));
    EXPECT_TRUE(g->insert({ 10, 2 }));
    EXPECT_TRUE(g->insert({ 12, 2 }));
    EXPECT_TRUE(g->insert({ 13, 5 }));
    EXPECT_EQ(g->sizeE(), 24);

    graph::TopologicalSort ts(*g);
    const auto& result = ts.result();
    EXPECT_EQ(result.size(), 6);
    EXPECT_EQ(result.get(0).size(), 2);
    EXPECT_EQ(result.get(0).get(0), 4);
    EXPECT_EQ(result.get(0).get(1), 7);

    EXPECT_EQ(result.get(1).size(), 3);
    EXPECT_EQ(result.get(1).get(0), 8);
    EXPECT_EQ(result.get(1).get(1), 9);
    EXPECT_EQ(result.get(1).get(2), 1);

    EXPECT_EQ(result.get(2).size(), 3);
    EXPECT_EQ(result.get(2).get(0), 13);
    EXPECT_EQ(result.get(2).get(1), 0);
    EXPECT_EQ(result.get(2).get(2), 6);

    EXPECT_EQ(result.get(3).size(), 1);
    EXPECT_EQ(result.get(3).get(0), 5);

    EXPECT_EQ(result.get(4).size(), 4);
    EXPECT_EQ(result.get(4).get(0), 3);
    EXPECT_EQ(result.get(4).get(1), 10);
    EXPECT_EQ(result.get(4).get(2), 11);
    EXPECT_EQ(result.get(4).get(3), 12);

    EXPECT_EQ(result.get(5).size(), 1);
    EXPECT_EQ(result.get(5).get(0), 2);
}
