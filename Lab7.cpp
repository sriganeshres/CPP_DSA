#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <list>

class Parcel
{
public:
    int time_tick;
    std::string parcel_id;
    std::string origin;
    std::string destination;
    int priority;
    bool delivered;
    bool loaded;
    std::string current_location;

    Parcel() = default;
    Parcel(int time_tick, std::string parcel_id, std::string origin, std::string destination, int priority)
    {
        this->time_tick = time_tick;
        this->parcel_id = parcel_id;
        this->origin = origin;
        this->destination = destination;
        this->priority = priority;
        this->delivered = false;
        this->current_location = origin;
        this->loaded = false;
    }
};

class MaxHeap
{
public:
    std::vector<Parcel *> heap;

    int parent(int i)
    {
        return (i - 1) / 2;
    }

    int left(int i)
    {
        return 2 * i + 1;
    }

    int right(int i)
    {
        return 2 * (i + 1);
    }

    Parcel *get_max()
    {
        return heap[0];
    }

    Parcel *extract_max()
    {
        Parcel *front = heap[0];
        swap(0, heap.size() - 1);
        heap.pop_back();
        max_heapify(0);
        return front;
    }

    void max_heapify(int i)
    {
        if (parent(i) >= 0)
        {
            if (heap[parent(i)]->priority < heap[i]->priority)
            {
                swap(i, parent(i));
                max_heapify(parent(i));
            }
            else if (right(i) >= heap.size() || left(i) >= heap.size())
                return;
            else if (!(heap[i]->priority > heap[right(i)]->priority) || !(heap[i]->priority > heap[left(i)]->priority))
            {
                int max = i;
                if (heap[right(i)]->priority > heap[i]->priority)
                {
                    max = right(i);
                }
                if (heap[left(i)]->priority > heap[i]->priority)
                {
                    max = left(i);
                }
                if (max != i)
                {
                    swap(max, i);
                    max_heapify(max);
                }
            }
            else
                return;
        }
        else
            return;
    }
    void insert(Parcel *item)
    {
        heap.push_back(item);
        if (heap.size() == 1)
            return;
        max_heapify(heap.size() - 1);
    }

    bool is_empty()
    {
        return heap.empty();
    }
    void swap(int a, int b)
    {
        Parcel *temp = heap[a];
        heap[a] = heap[b];
        heap[b] = temp;
    }
};

class FreightCar
{
public:
    int max_parcel_capacity;
    std::vector<Parcel *> parcels;
    std::string destination_city;
    std::string next_link;
    std::string current_location;
    std::vector<std::string> visted;
    bool sealed;

    FreightCar(int max_parcel_capacity)
    {
        this->max_parcel_capacity = max_parcel_capacity;
        // instantiate parcels vector as empty initially
        this->parcels = {};
        this->destination_city = "";
        this->next_link = "";
        this->current_location = "";
        this->sealed = false;
    }

    void load_parcel(Parcel *parcel)
    {
        this->parcels.push_back(parcel);
    }

    bool can_move()
    {
        if (parcels.size() == max_parcel_capacity)
            return true;
        return false;
    }

    void move(std::string destination)
    {
        // function that moves freight car to destination (link)
        this->current_location = destination;
    }
};

enum Color
{
    WHITE,
    GRAY,
    BLACK
};

class Vertex
{
public:
    std::string name;
    std::vector<FreightCar *> freight_cars;
    std::vector<Vertex *> neighbors;
    // trains_to_move is dict of destination and freight cars
    std::map<std::string, std::vector<FreightCar *>> trains_to_move;
    std::map<std::string, std::vector<FreightCar *>> int_trains_to_move;
    int min_freight_cars_to_move;
    int max_parcel_capacity;
    std::unordered_map<std::string, MaxHeap> parcel_destination_heaps;
    std::vector<FreightCar *> sealed_freight_cars;
    std::vector<Parcel *> all_parcels;
    Color color;
    Vertex *predessor;
    Vertex() = default;
    Vertex(std::string name, int min_freight_cars_to_move, int max_parcel_capacity)
    {
        this->name = name;
        this->freight_cars = {};
        this->neighbors = {};
        this->trains_to_move = {};
        this->min_freight_cars_to_move = min_freight_cars_to_move;
        this->max_parcel_capacity = max_parcel_capacity;
        this->parcel_destination_heaps = {};
        this->sealed_freight_cars = {};
        this->all_parcels = {};
        this->color = WHITE;
        this->predessor = nullptr;
    }

    void add_neighbor(Vertex *neighbor)
    {
        this->neighbors.push_back(neighbor);
    }

    // add get neighbors function
    std::vector<Vertex *> get_neighbors()
    {
        return this->neighbors;
    }

    std::vector<Parcel *> get_all_current_parcels()
    {
        return this->all_parcels;
    }

    void clean_unmoved_freight_cars()
    {
        for (FreightCar *f : freight_cars)
        {
            for (Parcel *p : f->parcels)
            {
                p->loaded = false;
                loadParcel(p);
            }
            f->parcels.clear();
        }
        freight_cars.clear();
    }

    void loadParcel(Parcel *parcel)
    {
        bool flag = false;
        for (auto &[destination, heap] : this->parcel_destination_heaps)
        {
            if (destination == parcel->destination)
            {
                this->parcel_destination_heaps[parcel->destination].insert(parcel);
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            MaxHeap *heap = new MaxHeap();
            heap->insert(parcel);
            this->parcel_destination_heaps.insert({parcel->destination, *heap});
        }
        this->all_parcels.push_back(parcel);
    }

    void loadFreightCars()
    {
        for (auto &j : parcel_destination_heaps)
        {
            FreightCar *f = new FreightCar(max_parcel_capacity);
            f->current_location = name;
            f->destination_city = j.first;
            freight_cars.push_back(f);
            for (auto &k : j.second.heap)
            {
                if (freight_cars[freight_cars.size() - 1]->parcels.size() < freight_cars[freight_cars.size() - 1]->max_parcel_capacity)
                {
                    freight_cars[freight_cars.size() - 1]->load_parcel(j.second.extract_max());
                }
                else
                {
                    FreightCar *f = new FreightCar(max_parcel_capacity);
                    f->current_location = name;
                    f->visted.push_back(name);
                    f->destination_city = j.first;
                    freight_cars.push_back(f);
                    freight_cars[freight_cars.size() - 1]->load_parcel(j.second.extract_max());
                }
            }
        }
        // load parcels into freight cars (making sure that each freight car has parcels from only one destination, and # parcels == min_parcel_capacity)
        std::vector<FreightCar *> dummy;
        for (FreightCar *f : freight_cars)
        {
            if (f->parcels.size() == f->max_parcel_capacity)
            {
                sealed_freight_cars.push_back(f);
            }
            else
                dummy.push_back(f);
        }
        freight_cars.swap(dummy);
    }

    void print_parcels_in_freight_cars()
    {
        for (auto &[destination, heap] : this->parcel_destination_heaps)
        {
            for (auto &parcel : heap.heap)
            {
                std::cout << "Parcel ID: " << parcel->parcel_id << ", Parcel origin: " << parcel->origin << ", Parcel destination: " << parcel->destination << ", Parcel priority: " << parcel->priority << std::endl;
            }
        }
    }
};

class Graph
{

public:
    std::list<Vertex *> vertices;
    std::vector<std::pair<Vertex *, Vertex *>> edges;
    std::vector<std::string> stranded_parcels;
    std::vector<std::vector<std::string>> paths;
    std::vector<std::string> simple_path;
    void add_edge(std::string source, std::string destination, int min_freight_cars_to_move, int max_parcel_capacity)
    {
        Vertex *src = nullptr, *dest = nullptr;
        for (Vertex *v : vertices)
        {
            if (v->name == source)
            {
                src = v;
                break;
            }
        }
        for (Vertex *v : vertices)
        {
            if (v->name == destination)
            {
                dest = v;
                break;
            }
        }
        if (!src && !dest)
        {
            src = new Vertex(source, min_freight_cars_to_move, max_parcel_capacity);
            dest = new Vertex(destination, min_freight_cars_to_move, max_parcel_capacity);
            src->add_neighbor(dest);
            dest->add_neighbor(src);
            vertices.push_back(src);
            vertices.push_back(dest);
        }
        else if (!src && dest)
        {
            src = new Vertex(source, min_freight_cars_to_move, max_parcel_capacity);
            dest->add_neighbor(src);
            src->add_neighbor(dest);
            vertices.push_back(src);
        }
        else if (src && !dest)
        {
            dest = new Vertex(destination, min_freight_cars_to_move, max_parcel_capacity);
            src->add_neighbor(dest);
            dest->add_neighbor(src);
            vertices.push_back(dest);
        }
        else
        {
            src->add_neighbor(dest);
            dest->add_neighbor(src);
        }
        edges.push_back({src, dest});
    }

    void print_graph()
    {
        std::cout << "Printing graph, vertices: " << vertices.size() << std::endl;
        for (auto &vertex : this->vertices)
        {
            std::cout << "Vertex: " << vertex->name << " " << vertex->all_parcels.size() << std::endl;
            std::cout << "Neighbors: ";
            for (auto &neighbor : vertex->neighbors)
            {
                std::cout << neighbor->name << " ";
            }
            std::cout << std::endl;
        }
    }
    void bfs(std::string source)
    {
        Vertex *src;
        for (Vertex *v : vertices)
        {
            if (v->name == source)
            {
                src = v;
                src->color = GRAY;
                src->predessor = nullptr;
            }
            else
            {
                v->color = WHITE;
            }
            v->predessor = nullptr;
        }
        std::queue<Vertex *> q;
        q.push(src);
        while (!q.empty())
        {
            Vertex *u = q.front();
            q.pop();
            u->color = BLACK;
            for (Vertex *v : u->get_neighbors())
            {
                if (v->color == WHITE)
                {
                    v->color = GRAY;
                    v->predessor = u;
                    q.push(v);
                }
            }
        }
    }

    std::vector<std::string> bfs(std::string source, std::string destination)
    {
        bfs(source);
        std::vector<std::string> result;
        Vertex *src = nullptr, *dest = nullptr;
        for (Vertex *v : vertices)
        {
            if (v->name == source)
            {
                src = v;
                break;
            }
        }
        for (Vertex *v : vertices)
        {
            if (v->name == destination)
            {
                dest = v;
                break;
            }
        }
        while (true)
        {
            if (src == dest)
            {
                result.push_back(dest->name);
                break;
            }
            else if (dest->predessor == nullptr)
            {
                break;
            }
            else
            {
                result.push_back(dest->name);
                dest = dest->predessor;
            }
        }
        for (int i = 0; i < (result.size() + 1) / 2; i++)
        {
            std::string temp = result[i];
            result[i] = result[result.size() - i - 1];
            result[result.size() - i - 1] = temp;
        }
        return result;
    }

    std::vector<std::string> dfs(std::string source, std::string destination, bool isFirstCall = true)
    {
        Vertex *Source;
        for (auto &i : vertices)
        {
            if (i->name == source)
            {
                Source = i;
                break;
            }
        }

        if (isFirstCall)
        {
            for (auto &i : vertices)
            {
                i->color = WHITE;
            }
            simple_path.clear();
        }
        Source->color = BLACK;
        simple_path.push_back(source);
        if (source == destination)
        {
            Source->color = WHITE;
            paths.push_back(simple_path);
            simple_path.pop_back();
            return paths[0];
        }

        for (auto &i : Source->neighbors)
        {

            if (i->color == WHITE)
            {
                dfs(i->name, destination, false);
            }
        }

        simple_path.pop_back();
        return paths[0];
        // function to return path from source to destination using dfs
    }

    void groupFreightCars()
    {
        // for every vertex, group freight cars by links
        for (Vertex *v : vertices)
        {
            v->loadFreightCars();
            for (FreightCar *f : v->sealed_freight_cars)
            {
                f->next_link = bfs(f->current_location, f->destination_city)[1];
                bool flag = false;
                for (auto &[next, cars] : v->int_trains_to_move)
                {
                    if (next == f->next_link)
                    {
                        v->int_trains_to_move[next].push_back(f);
                        flag = true;
                        break;
                    }
                }
                if (!flag)
                {
                    std::vector<FreightCar *> list;
                    list.push_back(f);
                    v->int_trains_to_move.insert({f->next_link, list});
                    flag = false;
                }
            }
            v->sealed_freight_cars.clear();
            for (auto &[next, cars] : v->int_trains_to_move)
            {
                if (cars.size() >= v->min_freight_cars_to_move)
                {
                    v->trains_to_move.insert({next, cars});
                }
                else
                {
                    for (FreightCar *car : v->int_trains_to_move[next])
                    {
                        v->sealed_freight_cars.push_back(car);
                    }
                }
            }
            for (FreightCar *f : v->sealed_freight_cars)
            {
                f->next_link = dfs(f->current_location, f->destination_city)[1];
                bool flag = false;
                for (auto &[next, cars] : v->int_trains_to_move)
                {
                    if (next == f->next_link)
                    {
                        v->int_trains_to_move[next].push_back(f);
                        flag = true;
                        break;
                    }
                }
                if (!flag)
                {
                    std::vector<FreightCar *> list;
                    list.push_back(f);
                    v->int_trains_to_move.insert({f->next_link, list});
                }
            }
            v->sealed_freight_cars.clear();
            for (auto &[next, cars] : v->int_trains_to_move)
            {
                if (cars.size() >= v->min_freight_cars_to_move)
                {
                    v->trains_to_move.insert({next, cars});
                }
                else
                {
                    for (FreightCar *car : v->int_trains_to_move[next])
                    {
                        v->sealed_freight_cars.push_back(car);
                    }
                }
            }
            for (FreightCar *f : v->sealed_freight_cars)
                v->freight_cars.push_back(f);
        }
    }

    void moveTrains()
    {
        for (Vertex *v : vertices)
        {
            for (auto &[name, cars] : v->trains_to_move)
            {
                for (Vertex *u : vertices)
                {
                    if (u->name == name)
                    {

                        for (FreightCar *car : cars)
                        {
                            car->current_location = u->name;
                            if (car->destination_city == car->current_location)
                            {
                                for (Parcel *p : car->parcels)
                                {
                                    p->delivered = true;
                                }
                            }
                            for (Parcel *p : car->parcels)
                            {
                                u->all_parcels.push_back(p);
                                p->current_location = u->name;
                            }
                            u->sealed_freight_cars.push_back(car);
                        }
                        v->trains_to_move[name].clear();
                        break;
                    }
                }
            }
            v->clean_unmoved_freight_cars();
            std::vector<Parcel *> dummy;
            for (Parcel *p : v->all_parcels)
            {
                if (!p->loaded)
                {
                    stranded_parcels.push_back(p->parcel_id);
                }
                if (p->current_location == v->name)
                {
                    dummy.push_back(p);
                }
            }
            v->all_parcels.clear();
            for (Parcel *p : dummy)
            {
                v->all_parcels.push_back(p);
            }
        }
    }
};

class PRC
{
public:
    Graph graph;
    std::vector<FreightCar *> freight_cars;
    std::map<std::string, Parcel *> parcels;
    std::map<int, std::vector<Parcel *>> parcels_with_time_tick;
    int max_parcel_capacity;
    int min_freight_cars_to_move;
    int time_tick;
    std::map<std::string, std::string> old_state;
    std::vector<Parcel *> total_parcels;
    std::vector<Parcel *> parcel;
    std::map<std::string, std::string> new_state;
    int max_time_tick;

    PRC(int max_parcel_capacity, int min_freight_cars_to_move)
    {
        this->max_parcel_capacity = max_parcel_capacity;
        this->min_freight_cars_to_move = min_freight_cars_to_move;
        this->time_tick = 1;
        this->max_time_tick = 100;
        this->freight_cars = {};
        this->parcels = {};
        this->parcels_with_time_tick = {};
        this->old_state = {};
        this->new_state = {};
    }

    void create_graph(std::string path)
    {
        // read graph.txt file and create graph
        std::ifstream file;
        file.open(path);
        std::string line, a, b;
        while (getline(file, line))
        {
            std::istringstream iss(line);
            iss >> a >> b;
            graph.add_edge(a, b, this->min_freight_cars_to_move, this->max_parcel_capacity);
        }
    }

    void process_parcels(std::string path)
    {
        // read parcels.txt file and create parcels
        std::ifstream file;
        file.open(path);
        std::string line, src, dest, pid;
        int time, priority;
        while (getline(file, line))
        {
            std::istringstream iss(line);
            iss >> time >> pid >> src >> dest >> priority;
            Parcel *p = new Parcel(time, pid, src, dest, priority);
            bool flag = false;
            for (auto &[times, parcels] : parcels_with_time_tick)
            {
                if (times == time)
                {
                    parcels_with_time_tick[times].push_back(p);
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                std::vector<Parcel *> pv;
                pv.push_back(p);
                parcels_with_time_tick.insert({time, pv});
            }
            parcels.insert({pid, p});
            total_parcels.push_back(p);
            for (Vertex *v : graph.vertices)
            {
                if (v->name == src)
                {
                    v->loadParcel(p);
                }
            }
        }
        this->old_state = get_state();
    }
    // function to return bookings at a particular time tick at a particular vertex
    std::vector<Parcel *> get_bookings(int time_tick, std::string vertex)
    {
        // run_simulation(time_tick);
        for (auto &i : graph.vertices)
        {
            if (i->name == vertex)
            {
                return i->all_parcels;
            }
        }
    }

    std::map<std::string, std::string> get_state()
    {
        std::map<std::string, std::string> state;
        // from this.parcels
        for (auto &parcel_pair : this->parcels)
        {
            Parcel *parcel = parcel_pair.second;
            state[parcel->parcel_id] = parcel->current_location;
        }
        return state;

        // from this.parcels
        // should return the dict of parcel_id and current_location
    }

    // run simulation function, takes run_till_time_tick as argument
    // if run_till_time_tick is not provided then run simulation till max_time_tick

    void run_simulation(int run_till_time_tick = -1)
    {
        new_state.clear();
        while (run_till_time_tick != 1 && !convergence_check())
        {
            for (auto &p : parcel)
            {
                for (auto &i : graph.vertices)
                {
                    if ((i->name == p->origin) && (time_tick == p->time_tick))
                    {

                        i->all_parcels.push_back(p);
                        i->loadParcel(p);
                    }
                }
            }
            old_state = get_state();
            time_tick++;
            graph.groupFreightCars();
            graph.moveTrains();
            run_till_time_tick--;
            new_state = get_state();
        }

        // function to run simulation
    }

    bool convergence_check()
    {
        if (new_state.size() == 0)
        {
            return false;
        }
        int p = 0;
        for (auto &i : old_state)
        {
            if (old_state[i.first] != new_state[i.first])
            {
                p = 1;
                break;
            }
        }
        if (p == 1)
        {
            return false;
        }
        else
        {
            return true;
        }
        old_state = new_state;
        // function to check convergence between old_state and new_state
    }

    bool all_parcels_delivered()
    {
        for (auto &parcel_pair : this->parcels)
        {
            Parcel *parcel = parcel_pair.second;
            if (!parcel->delivered)
            {
                return false;
            }
        }
        return true;
        // function to check if all parcels are delivered
        // return true if all parcels are delivered else return false
    }

    std::vector<std::string> get_stranded_parcels()
    {
        std::vector<std::string> ids;
        for (auto &i : graph.vertices)
        {

            for (auto &j : i->all_parcels)
            {
                if (!j->delivered)
                {
                    ids.push_back(j->parcel_id);
                }
            }
        }
        return ids;
        // return parcel_ids of stranded parcels
    }

    std::vector<std::string> get_delivered_parcels()
    {
        std::vector<std::string> ids;
        for (auto &i : graph.vertices)
        {

            for (auto &j : i->all_parcels)
            {
                if (j->delivered)
                {
                    ids.push_back(j->parcel_id);
                }
            }
        }
        return ids;
        // return parcel_ids of delivered parcels
    }

    // get status of all parcels at time tick t (status = id, current location, delivered/not delivered)
    std::vector<std::string> get_status_of_all_parcels(int t)
    {
        std::vector<std::string> status;
        for (auto &i : graph.vertices)
        {
            for (auto &j : i->all_parcels)
            {
                std::string info = j->parcel_id + " " + j->current_location + " " + std::to_string(j->delivered) + "\n";
                status.push_back(info);
            }
        }
        return status;
        //  std::string status = parcel.parcel_id + " " + parcel.current_location + " " + std::std::to_string(parcel.delivered) + "\n" ;
        // return the status of all parcels at time tick t as a vector of strings (each string formatted as above)
    }

    // get status of parcel_id at time tick t (status = id, current location, delivered/not delivered)
    std::string get_status_of_parcel(std::string parcel_id, int t)
    {
        std::string status;
        for (auto &i : graph.vertices)
        {
            for (auto &j : i->all_parcels)
            {
                if (j->parcel_id == parcel_id)
                    status = j->parcel_id + " " + j->current_location + " " + std::to_string(j->delivered);
            }
        }
        return status;
        // status = parcel.parcel_id + " " + parcel.current_location + " " + std::std::to_string(parcel.delivered);
        // return status of one parcel at time tick t as a string (formatted as above)
    }

    // get parcels delivered up to time tick t
    std::vector<std::string> get_parcels_delivered_up_to_time_tick(int t)
    {
        std::vector<std::string> delivered;
        for (auto &i : graph.vertices)
        {
            for (auto &j : i->all_parcels)
            {
                if (j->delivered == true)
                {
                    delivered.push_back(j->parcel_id);
                }
            }
        }
        return delivered;
        // return list of parcel_ids of parcels delivered up to time tick t
    }
};