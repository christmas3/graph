# Теория графов

Реализация представления графа в виде вектора смежности и алгоритма Косарайю для поиска сильных компонентов графа.
Топологическая сортировка алгоритмом Демукрона. Алгоритм Крускала вычисления MST

# Зависимости сборки

* c++17
* cmake
* gtest

# Сборка cmake

``` shell
mkdir ../build
cd ../build
cmake ..
cmake --build .
```

## Запуск тестов

```shell 
./graph --gtest_filter=GraphSuit.KosarajuTest
./graph --gtest_filter=GraphSuit.DemucronTest
./graph --gtest_filter=GraphSuit.MstTest
```

# Docker

```shell
docker build -t testing .
docker run -it testing sh
/src/testing/build/testing
```
