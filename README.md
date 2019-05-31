# digraph

a STL vector of vectors adjacency list implementation of a directed and unweighted graph

- reads in from a file of numbers that specify edges. vertices must start from 1 not 0

usage:

to find strongly connected components:

./hw09 -f test.txt

to find shortest path between two nodes:

./hw09 -d test.txt 1 2

includes:

- bfs
- non recursive dfs
- kosaraju's algo with non recursive fill order function
- bfs algo to find shortest path between two vertices


