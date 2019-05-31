#include "graph.cpp"
#include <fstream>

int main(int argc, char* argv[])
{
  std::string flag = argv[1];
  std::string file_name = argv[2];

  std::ifstream file(file_name);

  std::vector<Edge> edges;

  int s = 0;
  int d = 0;
  while(file >> s)
  {
    file >> d;

    Edge new_edge;
    new_edge.src = s;
    new_edge.dest = d;

    edges.push_back(new_edge);
  }

  int size = edges.size();
  int max = 0;
  for(int i = 0; i < size; i++)
  {
    if(edges[i].src > max)
      max = edges[i].src;

    if(edges[i].dest > max)
      max = edges[i].dest;
  }

  int n = max;

  //std::cout << "N: " << n << std::endl;
  //std::cout << "EDGES: " << edges.size() << std::endl;

  Graph g(edges, n);

  if(flag == "-f")
  {
    //g.print_graph();

    std::cout << "THE THREE LARGEST SCC's: " << std::endl;

    g.find_scc();
  }

  if(flag == "-d")
  {
    int start = atoi(argv[3]);
    int end = atoi(argv[4]);

    std::cout << std::endl << "The shortest path distance between node " << start << " and node " << end << " is: ";
    g.shortest_path(start, end);
  }
};
