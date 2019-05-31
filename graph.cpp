#include <iostream>
#include <stack>
#include <list>
#include <queue>
#include <vector>

struct Edge
{
  int src, dest;
};

class Graph
{
  public:
    std::vector<std::vector<int> > scc;
    std::vector<std::vector<int> > paths;
    std::vector<std::vector<int> > adj; //vector of adjacency lists
    int v; // number of vertices

    Graph(std::vector<Edge> const &edges, int n)
    {
      v = n;
      adj.resize(v + 1);
      scc.resize(v + 1);

      int num_edges = edges.size();
      for(int i = 0; i < num_edges; i++)
      {
        int src = edges[i].src;
        int dest = edges[i].dest;

        adj[src].push_back(dest);
      }
    }

    Graph(int n)
    {
      v = n;
      adj.resize(v + 1);
      scc.resize(v + 1);
    }

    Graph get_transpose()
    {
      Graph g(v);
      for(int i = 1; i < v + 1; i++)
      {
        for(int n : adj[i])
          g.adj[n].push_back(i);
      }

      return g;
    }

    void print_graph()
    {
      for(int i = 0; i < v; i++)
      {
        for(int n : adj[i])
          std::cout << "(" << i << " -> " << n << ")";

        std::cout << std::endl;
      }
    }

    void fill_order(int num, std::vector<bool> &visited, std::stack<int> &s, std::vector<bool> &in_stack)
    {
      std::queue<int> stack;
      std::stack<int> s2;
      stack.push(num);

      while(!stack.empty())
      {
        num = stack.front();
        stack.pop();

        if(!visited[num])
        {
          s2.push(num);
        }
        visited[num] = true;


        for(int n : adj[num])
        {
          if(!visited[n])
            stack.push(n);
          else
          {
            if(!in_stack[n])
            {
              s.push(num);
              in_stack[num] = true;
            }
            //std::cout << "ADDING TO S: " << num << std::endl;
          }
        }
      }
      while(!s2.empty())
      {
        int val = s2.top();
        s2.pop();
        if(!in_stack[val])
        {
          s.push(val);
          in_stack[val] = true;
        }
      }
      /*


      visited[num] = true;
      for(int n : adj[num])
        if(!visited[n])
          fill_order(n, visited, s);

      s.push(num);
      std::cout << "ADDING TO S: " << num << std::endl;*/
    }

    void dfs(int s, std::vector<bool> &visited, int i)
    {
      std::stack<int> stack;
      stack.push(s);

      while(!stack.empty())
      {
        s = stack.top();
        stack.pop();

        visited[s] = true;
        //std::cout << s << " ";
        scc[i].push_back(s);

        for(int n : adj[s])
          if(!visited[n])
            stack.push(n);
      }
    }

    void find_scc()
    {
      std::stack<int> s;
      std::vector<bool> in_stack;
      std::vector<bool> visited;
      visited.resize(v+1, false);
      in_stack.resize(visited.size(), false);

      for(int i = 1; i <=v; i++)
        if(!visited[i])
          fill_order(i, visited, s, in_stack);

      Graph g = get_transpose();

      for(int i = 1; i <= v; i++)
        visited[i] = false;

      int j = 1;
      while(!s.empty())
      {
        int V = s.top();
        s.pop();

        if(!visited[V])
        {
          g.dfs(V, visited, j);
          //std::cout << std::endl;
          j++;
        }
      }

      int size = g.scc.size();
      for(int k = 0; k < size; k++)
      {
        for(int n : g.scc[k])
          scc[k].push_back(n);
      }
      print_3_largest();
    }

    void print_3_largest()
    {
      int max1 = 0;
      int max2 = 0;
      int max3 = 0;
      int index1 = -1;
      int index2 = -1;
      int index3 = -1;

      int size = scc.size();
      for(int i = 0; i < size; i++)
      {
        if(scc[i].size() > max1)
        {
          max2 = max1;
          index2 = index1;
          max1 = scc[i].size();
          index1 = i;
        }
        else if(scc[i].size() > max2 && scc[i].size() < max1)
        {
          max3 = max2;
          index3 = index2;
          max2 = scc[i].size();
          index2 = i;
        }
        else if(scc[i].size() > max3 && scc[i].size() < max2)
        {
          max3 = scc[i].size();
          index3 = i;
        }
        else
          continue;
      }

      std::cout << std::endl << "#1: " << std::endl << std::endl;
      if(index1 == -1)
        std::cout << "none";
      for(int e : scc[index1])
        std::cout << e << ", ";
      std::cout << std::endl;

      std::cout << std::endl << "#2: " << std::endl << std::endl;
      if(index2 == -1)
        std::cout << "none";
      for(int e : scc[index2])
        std::cout << e << ", ";
      std::cout << std::endl;

      std::cout << std::endl << "#3: " << std::endl << std::endl;
      if(index3 == -1)
        std::cout << "none";
      for(int e : scc[index3])
        std::cout << e << ", ";
      std::cout << std::endl << std::endl;
    }

    bool bfs(int src, int dest, int pred[], int dist[])
    {
      std::list<int> queue;
      bool visited[v+1];
      for(int i = 1; i <= v; i++)
      {
        visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
      }

      visited[src] = true;
      dist[src] = 0;
      queue.push_back(src);

      while(!queue.empty())
      {
        int u = queue.front();
        queue.pop_front();
        for(int i = 0; i < adj[u].size(); i++)
        {
          if(visited[adj[u][i]] == false)
          {
            visited[adj[u][i]] = true;
            dist[adj[u][i]] = dist[u] + 1;
            pred[adj[u][i]] = u;
            queue.push_back(adj[u][i]);

            if(adj[u][i] == dest)
              return true;
          }
        }
      }
      return false;
    }

    void shortest_path(int v1, int v2)
    {
      int pred[v], dist[v];

      if(bfs(v1, v2, pred, dist) == false)
      {
        std::cout << std::endl << "The given nodes are not connected!" << std::endl << std::endl;

        return;
      }

      std::vector<int> path;
      int crawl = v2;
      path.push_back(crawl);
      while(pred[crawl] != -1)
      {
        path.push_back(pred[crawl]);
        crawl = pred[crawl];
      }

      std::cout << dist[v2] << std::endl;

      std::cout << "The path is: ";
      int path_size = path.size();
      for(int i = path_size - 1; i >= 0; --i)
        std::cout << path[i] << " ";

      std::cout << std::endl << std::endl;
    }
};
