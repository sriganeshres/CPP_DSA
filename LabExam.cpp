#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

bool stringCompare(std::string a, std::string b)
{
    return a.compare(b) < 0;
}
class Vertex
{
public:
    std::string name;
    std::vector<Vertex *> outN;
    std::vector<Vertex *> inN;
    std::string colors[2];
    Vertex *pred[2];
    Vertex(std::string a)
    {
        this->name = a;
        this->colors[0] = "white";
        this->colors[1] = "white";
    }
    void inNeighbours(Vertex *v)
    {
        this->inN.push_back(v);
    }
    void outNeighbours(Vertex *v)
    {
        this->outN.push_back(v);
    }
};
class Graph
{
public:
    int numVertices, numEdges;
    std::vector<Vertex *> vertices;
    std::vector<std::pair<Vertex *, Vertex *>> edges;
    void bfs(Vertex *v)
    {
        for (Vertex *a : vertices)
        {
            if (a->name != v->name)
                a->colors[0] = "white";
            else
                a->colors[0] = "gray";
        }
        std::queue<Vertex *> q;
        q.push(v);
        while (!q.empty())
        {
            Vertex *u = q.front();
            q.pop();
            for (Vertex *v : u->outN)
            {
                if (v->colors[0] == "white")
                {
                    q.push(v);
                    v->colors[0] == "gray";
                }
            }
            u->colors[0] = "black";
        }
    }
    void bfs(Vertex *v, int choice)
    {
        for (Vertex *a : vertices)
        {
            if (a->name != v->name)
                a->colors[choice] = "white";
            else
                a->colors[choice] = "gray";
            a->pred[choice] = nullptr;
        }
        std::queue<Vertex *> q;
        q.push(v);
        while (!q.empty())
        {
            Vertex *u = q.front();
            q.pop();
            for (Vertex *v : u->outN)
            {
                if (v->colors[choice] == "white")
                {
                    if (choice == 1)
                    {
                        if (v->pred[0] == u)
                            v->colors[0] = "gray";
                    }
                    q.push(v);
                    v->colors[choice] == "gray";
                    v->pred[choice] = u;
                }
            }
            u->colors[choice] = "black";
        }
    }
    std::vector<std::string> reachable(std::string a)
    {
        Vertex *v;
        for (Vertex *u : vertices)
        {
            if (u->name == a)
            {
                v = u;
                break;
            }
        }
        bfs(v);
        std::vector<std::string> result;
        for (Vertex *u : vertices)
        {
            if (u->colors[0] == "black" && u->name != a)
                result.push_back(u->name);
        }
        std::sort(result.begin(), result.end(), stringCompare);
        return result;
    }
    std::vector<std::string> joint(std::string a, std::string b)
    {
        bool flag1 = false, flag2 = false;
        for (Vertex *u : vertices)
        {
            if (flag1 && flag2)
            {
                break;
            }
            if (u->name == a && !flag1)
            {
                bfs(u, 0);
                flag1 = true;
            }
            if (u->name == b && !flag2)
            {
                bfs(u, 1);
                flag2 = true;
            }
        }
        std::vector<std::string> result;
        for (Vertex *u : vertices)
        {
            if (u->colors[0] == "black" && u->colors[1] == "black")
            {
                result.push_back(u->name);
            }
        }
        return result;
    }
    void addEdge(std::string a, std::string b)
    {
        Vertex *src = nullptr, *dest = nullptr;
        for (Vertex *v : vertices)
        {
            if (v->name == a)
            {
                src = v;
                break;
            }
        }
        for (Vertex *v : vertices)
        {
            if (v->name == b)
            {
                dest = v;
                break;
            }
        }
        src->outNeighbours(dest);
        dest->inNeighbours(src);
        edges.push_back({src, dest});
    }
    void readGraph()
    {
        int a, b;
        std::cin >> a;
        for (int i = 0; i < a; i++)
        {
            std::string v;
            std::cin >> v;
            vertices.push_back(new Vertex(v));
        }
        std::cin >> b;
        for (int i = 0; i < b; i++)
        {
            std::string x, y;
            std::cin >> x >> y;
            addEdge(x, y);
        }
    }
    std::vector<std::string> resulter()
    {
        int a;
        std::cin >> a;
        if (a == 1)
        {
            std::string n;
            std::cin >> n;
            return reachable(n);
        }
        else
        {
            std::string n, m;
            std::cin >> n >> m;
            return joint(n, m);
        }
    }
};

int main()
{
    Graph g;
    g.readGraph();
    std::vector<std::string> res = g.resulter();
    for (std::string &a : res)
    {
        std::cout << a << " ";
    }
    std::cout << std::endl;
}