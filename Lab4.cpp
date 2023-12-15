#include <iostream>
#include <vector>
#include <map>
#include <string>

class Vehicle;

class Trip
{
public:
    Trip(Vehicle *vehicle, std::string pick_up_location, std::string drop_location, int departure_time)
        : vehicle(vehicle), pick_up_location(pick_up_location), drop_location(drop_location), departure_time(departure_time), booked_seats(0) {}

    // Getter functions
    Vehicle *getVehicle() const
    {
        return vehicle;
    }

    std::string getPickUpLocation() const
    {
        return pick_up_location;
    }

    std::string getDropLocation() const
    {
        return drop_location;
    }

    int getDepartureTime() const
    {
        return departure_time;
    }

    int getBookedSeats() const
    {
        return booked_seats;
    }

    // Setter functions
    void setVehicle(Vehicle *v)
    {
        vehicle = v;
    }

    void setPickUpLocation(std::string location)
    {
        pick_up_location = location;
    }

    void setDropLocation(std::string location)
    {
        drop_location = location;
    }

    void setDepartureTime(int time)
    {
        departure_time = time;
    }

    void setBookedSeats(int seats)
    {
        booked_seats = seats;
    }

private:
    Vehicle *vehicle;
    std::string pick_up_location;
    std::string drop_location;
    int departure_time;
    int booked_seats;
};

class BinaryTreeNode
{
public:
    BinaryTreeNode(int departuretime = 0, Trip *tripenodeptr = nullptr, BinaryTreeNode *parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr) {}

    // Getter functions
    BinaryTreeNode *getLeftPtr() const
    {
        return leftptr;
    }

    BinaryTreeNode *getRightPtr() const
    {
        return rightptr;
    }

    BinaryTreeNode *getParentPtr() const
    {
        return parentptr;
    }

    int getDepartureTime() const
    {
        return departuretime;
    }

    Trip *getTripNodePtr() const
    {
        return tripnodeptr;
    }

    // Setter functions
    void setLeftPtr(BinaryTreeNode *left)
    {
        leftptr = left;
    }

    void setRightPtr(BinaryTreeNode *right)
    {
        rightptr = right;
    }

    void setParentPtr(BinaryTreeNode *parent)
    {
        parentptr = parent;
    }

    void setDepartureTime(int time)
    {
        departuretime = time;
    }

    void setTripNodePtr(Trip *trip)
    {
        tripnodeptr = trip;
    }

private:
    BinaryTreeNode *leftptr;
    BinaryTreeNode *rightptr;
    BinaryTreeNode *parentptr;
    int departuretime;
    Trip *tripnodeptr;
};

class TransportService
{
public:
    TransportService(std::string name) : name(name), BSThead(nullptr) {}

    // Getter functions
    std::string getName() const
    {
        return name;
    }

    BinaryTreeNode *getBSTHead() const
    {
        return BSThead;
    }

    // Setter functions
    void setName(std::string service_name)
    {
        name = service_name;
    }

    void setBSTHead(BinaryTreeNode *node)
    {
        BSThead = node;
    }

    void addTrip(int key, Trip *trip)
    {
        BinaryTreeNode *current = this->BSThead, *par = nullptr;
        if (current == nullptr)
            this->setBSTHead(new BinaryTreeNode(key, trip, nullptr));
        else
        {
            BinaryTreeNode *temp = new BinaryTreeNode(key, trip, nullptr);
            while (current)
            {
                par = current;
                if (current->getDepartureTime() > temp->getDepartureTime())
                    current = current->getLeftPtr();
                else
                    current = current->getRightPtr();
            }
            temp->setParentPtr(par);
            if (par->getDepartureTime() > temp->getDepartureTime())
                par->setLeftPtr(temp);
            else
                par->setRightPtr(temp);
        }
    }

private:
    std::string name;
    BinaryTreeNode *BSThead;
};

void inOrderTransversal(BinaryTreeNode *node, std::vector<Trip *> &trips)
{
    if (node == nullptr)
        return;
    inOrderTransversal(node->getLeftPtr(), trips);
    if (node != nullptr)
        trips.push_back(node->getTripNodePtr());
    inOrderTransversal(node->getRightPtr(), trips);
}

class Vehicle
{
public:
    Vehicle(std::string vehicle_number, int seating_capacity)
        : vehicle_number(vehicle_number), seating_capacity(seating_capacity) {}

    // Getter functions
    std::string getVehicleNumber() const
    {
        return vehicle_number;
    }

    int getSeatingCapacity() const
    {
        return seating_capacity;
    }

    // Setter functions
    void setVehicleNumber(std::string number)
    {
        vehicle_number = number;
    }

    void setSeatingCapacity(int capacity)
    {
        seating_capacity = capacity;
    }

    void addTrip(Trip *trip)
    {
        trips.push_back(trip);
    }

    std::vector<Trip *> getTrips()
    {
        return trips;
    }

private:
    std::string vehicle_number;
    int seating_capacity;
    std::vector<Trip *> trips;
};

class Location
{
public:
    Location(std::string name) : name(name) {}

    // Getter functions
    std::string getName() const
    {
        return name;
    }

    TransportService *getServicePtr(std::string droplocation) const
    {
        for (TransportService *t : serviceptrs)
        {
            if (t->getName() == droplocation)
                return t;
        }
        return nullptr;
    }
    std::vector<TransportService *> getServicePtrs() const
    {
        return serviceptrs;
    }
    // Setter functions
    void setName(std::string location_name)
    {
        name = location_name;
    }

    TransportService *setServicePtr(std::string droplocation)
    {
        return nullptr;
    }

    void addTrip(Trip *trip)
    {
        trips.push_back(trip);
        bool tflag = false;
        for (TransportService *t : serviceptrs)
        {
            if (trip->getDropLocation() == t->getName())
            {
                t->addTrip(trip->getDepartureTime(), trip);
                tflag = true;
                break;
            }
        }
        if (!tflag)
        {
            serviceptrs.push_back(new TransportService(trip->getDropLocation()));
            serviceptrs[serviceptrs.size() - 1]->addTrip(trip->getDepartureTime(), trip);
        }
    }

private:
    std::string name;
    std::vector<TransportService *> serviceptrs;
    std::vector<Trip *> trips;
};

class BinaryTree
{
protected:
    BinaryTreeNode *root;

public:
    BinaryTree() : root(nullptr) {}

    int getHeight() const
    {
        // Implement this function to return the height of the tree
        BinaryTreeNode *node = root;
        if (node == nullptr)
            return 0;
        BinaryTree *left, *right;
        left->root = node->getLeftPtr();
        right->root = node->getLeftPtr();
        return 1 + std::max(left->getHeight(), right->getHeight()); // Placeholder
    }

    int getNumberOfNodes() const
    {
        // Implement this function to return the number of nodes in the tree
        BinaryTreeNode *node = root;
        if (root == nullptr)
            return 0;
        BinaryTree *left, *right;
        left->root = node->getLeftPtr();
        right->root = node->getRightPtr();
        return 1 + left->getNumberOfNodes() + right->getNumberOfNodes();
    }
};

class BinarySearchTree : public BinaryTree
{
public:
    BinarySearchTree() {}

    BinaryTreeNode *getElementWithMinimumKey() const
    {
        // Implement this function to return the element with the minimum key
        BinaryTreeNode *node = this->root;
        if (node == nullptr)
            return nullptr;
        if (node->getLeftPtr() == nullptr)
            return node;
        while (node->getLeftPtr() != nullptr)
            node = node->getLeftPtr();
        return node;
    }

    BinaryTreeNode *getElementWithMaximumKey() const
    {
        // Implement this function to return the element with the maximum key
        BinaryTreeNode *node = this->root;
        if (node == nullptr)
            return nullptr;
        if (node->getRightPtr() == nullptr)
            return node;
        while (node->getRightPtr() != nullptr)
            node = node->getRightPtr();
        return node;
    }

    BinaryTreeNode *searchNodeWithKey(int key) const
    {
        // Implement this function to search for a node with the given key or the next larger key
        BinaryTreeNode *temp = this->root;
        std::vector<BinaryTreeNode *> nodes;
        std::vector<int> times;
        while ((temp->getLeftPtr() != nullptr) || (temp->getRightPtr() != nullptr))
        {
            if (temp->getDepartureTime() > key)
            {
                nodes.push_back(temp);
                times.push_back(temp->getDepartureTime());
                temp = temp->getLeftPtr();
            }
            else if (temp->getDepartureTime() < key)
            {
                nodes.push_back(temp);
                times.push_back(temp->getDepartureTime());
                temp = temp->getRightPtr();
            }
            else
                return temp;
        }
        int mini = 10000, minidx;
        for (int i = 0; i < times.size(); i++)
        {
            times[i] -= key;
            if (times[i] < 0)
                times[i] = times[i] * -1;
            if (times[i] < mini)
            {
                mini = times[i];
                minidx = i;
            }
        }
        return nodes[minidx]; // Placeholder
    }

    BinaryTreeNode *getSuccessorNode(BinaryTreeNode *node) const
    {
        // Implement this function to return the successor node of the given node
        if (node->getRightPtr() != nullptr)
        {
            BinaryTreeNode *current = node->getRightPtr();
            while (current->getLeftPtr() != nullptr)
                current = current->getLeftPtr();
            return current;
        }
        else
        {
            BinaryTreeNode *current = node->getLeftPtr();
            while (current->getRightPtr() != nullptr)
                current = current->getRightPtr();
            return current;
        }
    }

    BinaryTreeNode *getSuccessorNodeByKey(int key) const
    {
        // Implement this function to return the successor node by key
        BinaryTreeNode *current = this->searchNodeWithKey(key);
        return this->getSuccessorNode(current); // Placeholder
    }

    BinaryTreeNode *maxNode(BinaryTreeNode *node) const
    {
        while (node->getRightPtr() != nullptr)
        {
            node = node->getRightPtr();
        }
        return node;
    }

    BinaryTreeNode *getPredecessorNode(BinaryTreeNode *node) const
    {
        // Implement this function to return the predecessor node of the given node
        BinaryTreeNode *temp = root;
        BinaryTreeNode *previous = nullptr;
        while (temp != nullptr)
        {
            if (temp->getDepartureTime() == node->getDepartureTime())
            {
                if (temp->getLeftPtr() != nullptr)
                {
                    previous = maxNode(temp->getLeftPtr());
                    break;
                }
            }
            else if (temp->getDepartureTime() < node->getDepartureTime())
            {
                previous = temp;
                temp = temp->getRightPtr();
            }
            else
            {
                temp = temp->getLeftPtr();
            }
        }
        return previous;
    }

    BinaryTreeNode *getPredecessorNodeByKey(int key) const
    {
        // Implement this function to return the predecessor node by key
        BinaryTreeNode *temp = root;
        BinaryTreeNode *previous = nullptr;
        while (temp != nullptr)
        {
            if (temp->getDepartureTime() == key)
            {
                if (temp->getLeftPtr() != nullptr)
                {
                    previous = maxNode(temp->getLeftPtr());
                    break;
                }
            }
            else if (temp->getDepartureTime() < key)
            {
                previous = temp;
                temp = temp->getRightPtr();
            }
            else
            {
                temp = temp->getLeftPtr();
            }
        }
        return previous;
    }
};

class TravelDesk
{
public:
    void addTrip(std::string vehicle_number, int seating_capacity, std::string pick_up_location, std::string drop_location, int departure_time)
    {
        // Implement this function to add a trip
        Vehicle *current = nullptr;
        bool tflag = false;
        for (Vehicle *v : vehicles)
        {
            if (v->getVehicleNumber() == vehicle_number)
            {
                tflag = true;
                current = v;
                break;
            }
        }
        if (!tflag)
        {
            current = new Vehicle(vehicle_number, seating_capacity);
            current->addTrip(new Trip(current, pick_up_location, drop_location, departure_time));
            vehicles.push_back(current);
        }

        bool lflag = false;
        for (Location *L : locations)
        {
            if (L->getName() == pick_up_location)
            {
                lflag = true;
                L->addTrip(new Trip(current, pick_up_location, drop_location, departure_time));
                break;
            }
        }
        if (!lflag)
        {
            locations.push_back(new Location(pick_up_location));
            locations[locations.size() - 1]->addTrip(new Trip(current, pick_up_location, drop_location, departure_time));
        }
    }

    std::vector<Trip *> showTrips(std::string pick_up_location, int after_time, int before_time)
    {
        // Implement this function to retrieve trips within a specified time range
        std::vector<Trip *> trips;
        Location *L = this->getLocation(pick_up_location);
        std::vector<TransportService *> Services = L->getServicePtrs();
        for (TransportService *t : Services)
        {
            std::vector<Trip *> inter;
            inOrderTransversal(t->getBSTHead(), inter);
            for (Trip *t : inter)
            {
                if ((t->getDepartureTime() >= after_time) && (t->getDepartureTime() < before_time))
                {
                    trips.push_back(t);
                }
            }
        }
        return trips; // Placeholder
    }

    std::vector<Trip *> showTripsbydestination(std::string pick_up_location, std::string destination, int after_time, int before_time)
    {
        // Implement this function to retrieve trips within a specified time range form pickup to droplocatin
        std::vector<Trip *> trips, inter;
        Location *L = this->getLocation(pick_up_location);
        BinaryTreeNode *current = L->getServicePtr(destination)->getBSTHead();
        inOrderTransversal(current, inter);
        for (Trip *t : inter)
        {
            if ((t->getDepartureTime() > after_time) && (t->getDepartureTime() < before_time))
                trips.push_back(t);
        }
        return trips; // Placeholder
    }

    Trip *bookTrip(std::string pick_up_location, std::string drop_location, std::string vehicle_number, int departure_time)
    {
        // Implement this function to book a trip
        Location *l = this->getLocation(pick_up_location);
        int book = l->getServicePtr(drop_location)->getBSTHead()->getTripNodePtr()->getBookedSeats();
        int maxsize = l->getServicePtr(drop_location)->getBSTHead()->getTripNodePtr()->getVehicle()->getSeatingCapacity();
        if (maxsize >= book + 1)
        {
            l->getServicePtr(drop_location)->getBSTHead()->getTripNodePtr()->setBookedSeats(book + 1);
            return l->getServicePtr(drop_location)->getBSTHead()->getTripNodePtr();
        }
        return nullptr; // Placeholder
    }
    Location *getLocation(std::string location)
    {
        for (Location *l : locations)
        {
            if (l->getName() == location)
            {
                return l;
            }
        }
        return nullptr;
    }

private:
    std::vector<Vehicle *> vehicles;
    std::vector<Location *> locations;
};