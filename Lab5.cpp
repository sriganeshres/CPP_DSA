#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <cmath>
#include <cstring>
#include <cassert>
#include <functional>
#include <set>
#include <algorithm>

// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;

// MetroStop class
class MetroStop
{
private:
    std::string stopName;
    MetroStop *nextStop;
    MetroStop *prevStop;
    MetroLine *line;
    int fare;

public:
    MetroStop(std::string name, MetroLine *metroLine, int fare);

    // Getter methods
    std::string getStopName() const;
    MetroStop *getNextStop() const;
    MetroStop *getPrevStop() const;
    MetroLine *getLine() const;
    int getFare() const;

    // Setter methods
    void setNextStop(MetroStop *next);
    void setPrevStop(MetroStop *prev);
};

MetroStop::MetroStop(std::string name, MetroLine *metroLine, int fare)
{
    stopName = name;
    nextStop = nullptr;
    prevStop = nullptr;
    line = metroLine;
    this->fare = fare;
}

std::string MetroStop::getStopName() const
{
    return stopName;
}

MetroStop *MetroStop::getNextStop() const
{
    return nextStop;
}

MetroStop *MetroStop::getPrevStop() const
{
    return prevStop;
}

MetroLine *MetroStop::getLine() const
{
    return line;
}

int MetroStop::getFare() const
{
    return fare;
}

void MetroStop::setNextStop(MetroStop *next)
{
    nextStop = next;
}

void MetroStop::setPrevStop(MetroStop *prev)
{
    prevStop = prev;
}

// MetroLine class
class MetroLine
{
private:
    std::string lineName;
    MetroStop *node;

public:
    MetroLine(std::string name);

    // Getter methods
    std::string getLineName() const;
    MetroStop *getNode() const;

    // Setter methods
    void setNode(MetroStop *node);

    void populateLine(std::string filename);

    // helper function
    void printLine() const;
    int getTotalStops() const;
};

MetroLine::MetroLine(std::string name)
{
    lineName = name;
    node = nullptr;
}

std::string MetroLine::getLineName() const
{
    return lineName;
}

MetroStop *MetroLine::getNode() const
{
    return node;
}

void MetroLine::setNode(MetroStop *node)
{
    this->node = node;
}

void MetroLine::printLine() const
{
    MetroStop *stop = node;
    while (stop != nullptr)
    {
        std::cout << stop->getStopName() << std::endl;
        stop = stop->getNextStop();
    }
}

int MetroLine::getTotalStops() const
{
    int stops = 0;
    MetroStop *temp = this->getNode();
    while (temp != nullptr)
    {
        stops++;
        temp = temp->getNextStop();
    }
    return stops;
}

void MetroLine::populateLine(std::string filename)
{
    // Read the file and populate the line
    std::ifstream file;
    file.open(filename);
    std::string line, word, name;
    int fare;
    std::vector<std::string> words;
    while (getline(file, line))
    {
        for (char c : line)
        {
            if (c == ' ')
            {
                words.push_back(word);
                word.clear();
            }
            else if (c == ',')
                continue;
            else
                word += c;
        }

        words.push_back(word);
        fare = std::stoi(words.back());
        words.pop_back();
        for (std::string w : words)
        {
            if (w == words[0])
                name += w;
            else
                name += " " + w;
        }
        MetroStop *temp = this->getNode();
        if (temp == nullptr)
            this->setNode(new MetroStop(name, this, fare));
        else
        {
            while (temp->getNextStop() != nullptr)
                temp = temp->getNextStop();
            temp->setNextStop(new MetroStop(name, this, fare));
            temp->getNextStop()->setPrevStop(temp);
        }
        words.clear();
        word.clear();
        name.clear();
        line.clear();
    }
    file.close();
}

// AVLNode class
class AVLNode
{
private:
    std::string stopName;
    std::vector<MetroStop *> stops;
    AVLNode *left;
    AVLNode *right;
    AVLNode *parent;

public:
    AVLNode(std::string name);

    // Getter methods
    std::string getStopName() const;
    const std::vector<MetroStop *> &getStops() const;
    AVLNode *getLeft() const;
    AVLNode *getRight() const;
    AVLNode *getParent() const;

    // Setter methods
    void addMetroStop(MetroStop *metroStop);
    void setLeft(AVLNode *left);
    void setRight(AVLNode *right);
    void setParent(AVLNode *parent);
};

AVLNode::AVLNode(std::string name)
{
    stopName = name;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

std::string AVLNode::getStopName() const
{
    return stopName;
}

const std::vector<MetroStop *> &AVLNode::getStops() const
{
    return stops;
}

AVLNode *AVLNode::getLeft() const
{
    return left;
}

AVLNode *AVLNode::getRight() const
{
    return right;
}

AVLNode *AVLNode::getParent() const
{
    return parent;
}

void AVLNode::setLeft(AVLNode *left)
{
    this->left = left;
}

void AVLNode::setRight(AVLNode *right)
{
    this->right = right;
}

void AVLNode::setParent(AVLNode *parent)
{
    this->parent = parent;
}

void AVLNode::addMetroStop(MetroStop *metroStop)
{
    stops.push_back(metroStop);
}

// AVLTree class
class AVLTree
{
    // Define your AVLTree implementation here.
private:
    AVLNode *root;

public:
    AVLTree();
    // getter methods
    AVLNode *getRoot() const;

    // setter methods
    void setRoot(AVLNode *root);

    // helper functions
    int height(AVLNode *node);
    int balanceFactor(AVLNode *node);
    void rotateLeft(AVLNode *node);
    void rotateRight(AVLNode *node);
    void balance(AVLNode *node);
    int stringCompare(std::string s1, std::string s2);
    void insert(AVLNode *node, MetroStop *metroStop);
    void populateTree(MetroLine *metroLine);
    void inOrderTraversal(AVLNode *node);
    int getTotalNodes(AVLNode *node);
    AVLNode *searchStop(std::string stopName);
};

AVLTree::AVLTree()
{
    root = nullptr;
}

AVLNode *AVLTree::getRoot() const
{
    return root;
}

void AVLTree::setRoot(AVLNode *root)
{
    this->root = root;
}

int AVLTree::height(AVLNode *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return 1 + std::max(height(node->getLeft()), height(node->getRight()));
}

int AVLTree::stringCompare(std::string s1, std::string s2)
{
    const char *c1 = s1.c_str();
    const char *c2 = s2.c_str();
    int result = strcmp(c1, c2);
    return result;
}

int AVLTree::balanceFactor(AVLNode *node)
{
    if (node == nullptr)
        return 0;
    return height(node->getLeft()) - height(node->getRight());
}

void AVLTree::rotateLeft(AVLNode *node)
{
    if (!node || !node->getRight())
    {
        return;
    }

    AVLNode *X = node->getRight();
    node->setRight(X->getLeft());

    if (X->getLeft())
    {
        X->getLeft()->setParent(node);
    }

    X->setParent(node->getParent());

    if (!node->getParent())
    {
        this->setRoot(X);
    }
    else if (node == node->getParent()->getLeft())
    {
        node->getParent()->setLeft(X);
    }
    else
    {
        node->getParent()->setRight(X);
    }

    X->setLeft(node);
    node->setParent(X);
}

void AVLTree::rotateRight(AVLNode *node)
{
    if (!node || !node->getLeft())
    {
        return;
    }

    AVLNode *X = node->getLeft();
    node->setLeft(X->getRight());

    if (X->getRight())
    {
        X->getRight()->setParent(node);
    }

    X->setParent(node->getParent());

    if (!node->getParent())
    {
        this->setRoot(X);
    }
    else if (node == node->getParent()->getLeft())
    {
        node->getParent()->setLeft(X);
    }
    else
    {
        node->getParent()->setRight(X);
    }

    X->setRight(node);
    node->setParent(X);
}

void AVLTree::balance(AVLNode *node)
{
    if (node == nullptr)
        return;
    int bf = balanceFactor(node);
    if (bf > 1)
    {
        if (balanceFactor(node->getLeft()) > 0)
        {
            rotateRight(node);
        }
        else
        {
            rotateLeft(node->getLeft());
            rotateRight(node);
        }
    }
    else if (bf < -1)
    {
        if (balanceFactor(node->getRight()) < 0)
        {
            rotateLeft(node);
        }
        else
        {
            rotateRight(node->getRight());
            rotateLeft(node);
        }
    }
}

void AVLTree::insert(AVLNode *node, MetroStop *metroStop)
{
    if (node == nullptr)
    {
        node = new AVLNode(metroStop->getStopName());
        node->addMetroStop(metroStop);
        if (this->getRoot() == nullptr)
        {
            this->setRoot(node);
            node->setParent(nullptr);
        }
        return;
    }

    int compareResult = stringCompare(node->getStopName(), metroStop->getStopName());

    if (compareResult == 0)
    {
        node->addMetroStop(metroStop);
    }
    else if (compareResult > 0)
    {
        if (node->getLeft() == nullptr)
        {
            node->setLeft(new AVLNode(metroStop->getStopName()));
            node->getLeft()->setParent(node);
            node->getLeft()->addMetroStop(metroStop);
        }
        else
        {
            insert(node->getLeft(), metroStop);
        }
    }
    else if (compareResult < 0)
    {
        if (node->getRight() == nullptr)
        {
            node->setRight(new AVLNode(metroStop->getStopName()));
            node->getRight()->setParent(node);
            node->getRight()->addMetroStop(metroStop);
        }
        else
        {
            insert(node->getRight(), metroStop);
        }
    }
    balance(node);
}

void AVLTree::populateTree(MetroLine *metroLine)
{
    MetroStop *mt = metroLine->getNode();
    while (mt != nullptr)
    {
        insert(this->getRoot(), mt);
        mt = mt->getNextStop();
    }
}

void AVLTree::inOrderTraversal(AVLNode *node)
{
    if (node == nullptr)
    {
        return;
    }
    inOrderTraversal(node->getLeft());
    std::cout << node->getStopName() << std::endl;
    inOrderTraversal(node->getRight());
}

int AVLTree::getTotalNodes(AVLNode *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return 1 + getTotalNodes(node->getLeft()) + getTotalNodes(node->getRight());
}

AVLNode *AVLTree::searchStop(std::string stopName)
{
    AVLNode *current = root;
    while (current != nullptr)
    {
        int compareResult = stringCompare(current->getStopName(), stopName);

        if (compareResult == 0)
        {
            return current;
        }
        else if (compareResult >= 1)
        {
            current = current->getLeft();
        }
        else if (compareResult <= -1)
        {
            current = current->getRight();
        }
    }

    return nullptr; // Stop not found
}

// Trip class
class Trip
{
private:
    MetroStop *node;
    Trip *prev;

public:
    Trip(MetroStop *metroStop, Trip *previousTrip);

    // Getter methods
    MetroStop *getNode() const;
    Trip *getPrev() const;
};

Trip::Trip(MetroStop *metroStop, Trip *previousTrip)
{
    node = metroStop;
    prev = previousTrip;
}

MetroStop *Trip::getNode() const
{
    return node;
}

Trip *Trip::getPrev() const
{
    return prev;
}

// Exploration class is a queue that stores unexplored Trip objects
class Exploration
{
private:
    std::queue<Trip *> trips;

public:
    Exploration();

    // Getter methods
    std::queue<Trip *> getTrips() const;

    // Setter methods
    void enqueue(Trip *trip);
    Trip *dequeue();
    bool isEmpty() const;
};

Exploration::Exploration()
{
}

std::queue<Trip *> Exploration::getTrips() const
{
    return trips;
}

void Exploration::enqueue(Trip *trip)
{
    trips.push(trip);
}

Trip *Exploration::dequeue()
{
    if (trips.empty())
    {
        return nullptr;
    }
    Trip *trip = trips.front();
    trips.pop();
    std::cout << "Dequeued: " << trip->getNode()->getStopName() << std::endl;
    return trip;
}

bool Exploration::isEmpty() const
{
    return trips.empty();
}

class Path
{
private:
    std::vector<MetroStop *> stops;
    int totalFare;

public:
    Path();

    // Getter methods
    std::vector<MetroStop *> getStops() const;
    int getTotalFare() const;

    // Setter methods
    void addStop(MetroStop *stop);
    void setStops(std::vector<MetroStop *> stops);
    void setTotalFare(int fare);

    // helper functions
    void printPath() const;
};

Path::Path()
{
    totalFare = 0;
}

std::vector<MetroStop *> Path::getStops() const
{
    return stops;
}

int Path::getTotalFare() const
{
    return totalFare;
}

void Path::addStop(MetroStop *stop)
{
    stops.push_back(stop);
}

void Path::setTotalFare(int fare)
{
    totalFare = fare;
}

void Path::setStops(std::vector<MetroStop *> stops)
{
    swap(this->stops, stops);
}
void Path::printPath() const
{
    for (auto stop : stops)
    {
        std::cout << stop->getStopName() << std::endl;
    }
}

// PathFinder class
class PathFinder
{
private:
    AVLTree *tree;
    std::vector<MetroLine *> lines;

public:
    PathFinder(AVLTree *avlTree, const std::vector<MetroLine *> &metroLines);
    void createAVLTree();
    Path *findPath(std::string origin, std::string destination);

    // Getter methods
    AVLTree *getTree() const;
    const std::vector<MetroLine *> &getLines() const;
};

PathFinder::PathFinder(AVLTree *avlTree, const std::vector<MetroLine *> &metroLines)
{
    tree = avlTree;
    lines = metroLines;
}

AVLTree *PathFinder::getTree() const
{
    return tree;
}

const std::vector<MetroLine *> &PathFinder::getLines() const
{
    return lines;
}

void PathFinder::createAVLTree()
{
    for (MetroLine *mt : this->getLines())
    {
        this->getTree()->populateTree(mt);
    }
    this->getTree()->inOrderTraversal(this->getTree()->getRoot());
}
bool isJunc(AVLNode *node)
{
    if (node->getStops().size() > 1)
        return true;
    return false;
}
Path *PathFinder::findPath(std::string origin, std::string destination)
{
    AVLNode *start = this->getTree()->searchStop(origin);
    AVLNode *end = this->getTree()->searchStop(destination);

    if (!start || !end)
    {
        return nullptr;
    }

    Path *resultPath = nullptr;

    Exploration forwardQueue;
    Exploration reverseQueue;

    Trip *initialForwardTrip = new Trip(end->getStops()[0], nullptr);
    forwardQueue.enqueue(initialForwardTrip);

    Trip *initialReverseTrip = new Trip(start->getStops()[0], nullptr);
    reverseQueue.enqueue(initialReverseTrip);

    while (!forwardQueue.isEmpty() || !reverseQueue.isEmpty())
    {
        if (!forwardQueue.isEmpty())
        {
            Trip *currentForwardTrip = forwardQueue.dequeue();
            MetroStop *currentForwardStop = currentForwardTrip->getNode();

            if (currentForwardStop->getStopName() == origin)
            {
                resultPath = new Path();
                while (currentForwardTrip != nullptr)
                {
                    resultPath->addStop(currentForwardTrip->getNode());
                    currentForwardTrip = currentForwardTrip->getPrev();
                }
                break;
            }

            MetroStop *nextForwardStop = currentForwardStop->getNextStop();
            if (nextForwardStop != nullptr)
            {
                Trip *nextForwardTrip = new Trip(nextForwardStop, currentForwardTrip);
                forwardQueue.enqueue(nextForwardTrip);
            }

            if (isJunc(tree->searchStop(currentForwardStop->getStopName())))
            {
                for (MetroLine *line : lines)
                {
                    if (line != currentForwardStop->getLine())
                    {
                        MetroStop *junctionForwardStop = line->getNode();
                        while (junctionForwardStop != nullptr)
                        {
                            if (junctionForwardStop->getStopName() == currentForwardStop->getStopName())
                            {
                                break;
                            }
                            junctionForwardStop = junctionForwardStop->getNextStop();
                        }

                        if (junctionForwardStop != nullptr)
                        {
                            Trip *junctionForwardTrip = new Trip(junctionForwardStop, currentForwardTrip);
                            forwardQueue.enqueue(junctionForwardTrip);
                        }
                    }
                }
            }
        }

        if (!reverseQueue.isEmpty())
        {
            Trip *currentReverseTrip = reverseQueue.dequeue();
            MetroStop *currentReverseStop = currentReverseTrip->getNode();

            if (currentReverseStop->getStopName() == destination)
            {
                resultPath = new Path();
                while (currentReverseTrip != nullptr)
                {
                    resultPath->addStop(currentReverseTrip->getNode());
                    currentReverseTrip = currentReverseTrip->getPrev();
                }
                break;
            }

            MetroStop *nextReverseStop = currentReverseStop->getNextStop();
            if (nextReverseStop != nullptr)
            {
                Trip *nextReverseTrip = new Trip(nextReverseStop, currentReverseTrip);
                reverseQueue.enqueue(nextReverseTrip);
            }

            if (isJunc(tree->searchStop(currentReverseStop->getStopName())))
            {
                for (MetroLine *line : lines)
                {
                    if (line != currentReverseStop->getLine())
                    {
                        MetroStop *junctionReverseStop = line->getNode();
                        while (junctionReverseStop != nullptr)
                        {
                            if (junctionReverseStop->getStopName() == currentReverseStop->getStopName())
                            {
                                break;
                            }
                            junctionReverseStop = junctionReverseStop->getNextStop();
                        }

                        if (junctionReverseStop != nullptr)
                        {
                            Trip *junctionReverseTrip = new Trip(junctionReverseStop, currentReverseTrip);
                            reverseQueue.enqueue(junctionReverseTrip);
                        }
                    }
                }
            }
        }
    }
    std::vector<MetroStop *> uniqueStops;
    std::set<std::string> seenStops;

    if (resultPath->getStops()[0]->getStopName() == origin)
    {
        std::vector<MetroStop *> revStops;
        for (int i = resultPath->getStops().size() - 1; i >= 0; i--)
        {
            revStops.push_back(resultPath->getStops()[i]);
        }
        resultPath->setStops(revStops);
    }
    for (MetroStop *mt : resultPath->getStops())
    {
        if (seenStops.find(mt->getStopName()) == seenStops.end())
        {
            uniqueStops.push_back(mt);
            seenStops.insert(mt->getStopName());
        }
    }

    resultPath->setStops(uniqueStops);

    for (MetroStop *mt : resultPath->getStops())
    {
        if (mt == resultPath->getStops()[0])
        {
            continue;
        }
        int z = 0;
        if (mt->getNextStop() != nullptr)
        {
            z = abs(mt->getNextStop()->getFare() - mt->getFare());
        }
        else
        {
            z = abs(mt->getFare() - mt->getPrevStop()->getFare());
        }
        resultPath->setTotalFare(resultPath->getTotalFare() + z);
    }

    return resultPath;
}

std::vector<MetroLine *> lines;