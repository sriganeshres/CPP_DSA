#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
class HybridNode
{
public:
    std::string key;             // Word
    std::string element;         // Chapter
    HybridNode *parent;          // Parent node
    HybridNode *left_child;      // Left child node
    HybridNode *right_child;     // Right child node
    HybridNode *next_node;       // Next node in the linked list
    std::string color = "black"; // Color of the node

    HybridNode(std::string key_val, std::string element_val) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr) {}
};

class RedBlackTree
{
private:
    HybridNode *root; // Root node
    void fixtreeInsert(HybridNode *ptr)
    {

        if (ptr == nullptr || ptr == this->getRoot() || ptr->parent == this->getRoot())
        {

            std::cout << "case1" << std::endl;
            return;
        }
        HybridNode *par = ptr->parent, *grandPar = ptr->parent->parent, *uncle = par == grandPar->left_child ? grandPar->right_child : grandPar->left_child;
        if (par->color == "black")
        {
            std::cout << "case2" << std::endl;
            return;
        }
        else if (grandPar == this->getRoot())
        {
            if (uncle)
            {
                if (uncle->color == "red")
                {
                    par->color = "black";
                    uncle->color = "black";
                    return;
                }
                else
                {
                    if (par == grandPar->right_child)
                    {
                        if (ptr == par->left_child)
                        {
                            std::string temp = grandPar->color;

                            grandPar->color = ptr->color;
                            ptr->color = temp;

                            rotateRight(par);
                            rotateLeft(grandPar);
                        }
                        else
                        {
                            std::string temp = grandPar->color;

                            grandPar->color = par->color;
                            par->color = temp;
                            rotateLeft(grandPar);
                        }
                    }
                    else
                    {
                        if (ptr == par->right_child)
                        {
                            std::string temp = grandPar->color;

                            grandPar->color = ptr->color;
                            ptr->color = temp;

                            rotateLeft(par);
                            rotateRight(grandPar);
                        }
                        else
                        {
                            std::string temp = grandPar->color;

                            grandPar->color = par->color;
                            par->color = temp;
                            rotateRight(grandPar);
                        }
                    }
                }
                root->color = "black";
            }
            else
            {
                std::cout << "case4";
                if (par == grandPar->left_child)
                {
                    if (ptr == par->right_child)
                    {
                        std::string temp = grandPar->color;

                        grandPar->color = ptr->color;
                        ptr->color = temp;
                        rotateRight(par);
                        rotateLeft(grandPar);
                    }
                    else
                    {
                        std::string temp = grandPar->color;

                        grandPar->color = par->color;
                        par->color = temp;
                        rotateLeft(grandPar);
                    }
                }
                else
                {
                    if (ptr == par->left_child)
                    {
                        std::string temp = grandPar->color;
                        grandPar->color = ptr->color;
                        ptr->color = temp;
                        rotateLeft(par);
                        rotateRight(grandPar);
                    }
                    else
                    {
                        std::string temp = grandPar->color;
                        grandPar->color = par->color;
                        par->color = temp;
                        rotateLeft(grandPar);
                    }
                }
            }
            root->color = "black";
            return;
        }
        else
        {
            if (uncle)
            {
                if (uncle->color == "red")
                {
                    par->color = "black";
                    uncle->color = "black";
                    grandPar->color = "red";
                    return fixtreeInsert(grandPar);
                }
                else
                {
                    if (par == grandPar->right_child)
                    {

                        if (ptr == par->left_child)
                        {
                            std::string temp = grandPar->color;
                            grandPar->color = ptr->color;
                            ptr->color = temp;
                            rotateRight(par);
                            rotateLeft(grandPar);
                        }
                        else
                        {
                            std::string temp = grandPar->color;
                            grandPar->color = par->color;
                            par->color = temp;
                            rotateLeft(grandPar);
                        }
                    }
                    else
                    {
                        if (ptr == par->right_child)
                        {
                            std::string temp = grandPar->color;
                            grandPar->color = ptr->color;
                            ptr->color = temp;

                            rotateLeft(par);
                            rotateRight(grandPar);
                        }
                        else
                        {
                            std::string temp = grandPar->color;
                            grandPar->color = par->color;
                            par->color = temp;
                            rotateRight(grandPar);
                        }
                    }
                }
            }
            else
            {
                if (par == grandPar->right_child)
                {
                    if (ptr == par->left_child)
                    {
                        std::string temp = grandPar->color;
                        grandPar->color = ptr->color;
                        ptr->color = temp;
                        rotateRight(par);
                        rotateLeft(grandPar);
                    }
                    else
                    {
                        std::string temp = grandPar->color;
                        grandPar->color = par->color;
                        par->color = temp;
                        rotateLeft(grandPar);
                    }
                }
                else
                {
                    if (ptr == par->right_child)
                    {
                        std::string temp = grandPar->color;
                        grandPar->color = ptr->color;
                        ptr->color = temp;
                        rotateLeft(par);
                        rotateRight(grandPar);
                    }
                    else
                    {
                        std::string temp = grandPar->color;
                        grandPar->color = par->color;
                        par->color = temp;
                        rotateRight(grandPar);
                    }
                }
            }
        }
    }
    void replaceNode(HybridNode *node, HybridNode *newChild)
    {
        if (node->parent == nullptr)
        {
            root = newChild;
        }
        else
        {
            if (node == node->parent->left_child)
            {
                node->parent->left_child = newChild;
            }
            else
            {
                node->parent->right_child == newChild;
            }
            if (newChild)
            {
                newChild->parent = node->parent;
            }
        }
    }
    void rotateLeft(HybridNode *node)
    {
        if (node != nullptr && node->right_child != nullptr)
        {
            HybridNode *x = node->right_child;
            HybridNode *y = x->left_child;
            x->left_child = node;
            node->right_child == y;
            if (y != nullptr)
            {
                y->parent = node;
            }
            if (node->parent == nullptr)
            {
                this->setRoot(x);
            }
            else
            {
                if (node->parent->left_child == node)
                {
                    node->parent->left_child = x;
                }
                else
                {
                    node->parent->right_child == x;
                }
            }
            x->parent = node->parent;
            node->parent = x;
        }
    }
    void rotateRight(HybridNode *node)
    {
        if (node != nullptr && node->left_child != nullptr)
        {
            HybridNode *x = node->left_child;
            HybridNode *y = x->right_child;
            x->right_child == node;
            node->left_child = y;
            if (y != nullptr)
            {
                y->parent = node;
            }
            if (node->parent == nullptr)
            {
                this->setRoot(x);
            }
            else
            {
                if (node->parent->left_child == node)
                {
                    node->parent->left_child = x;
                }
                else
                {
                    node->parent->right_child == x;
                }
            }
            x->parent = node->parent;
            node->parent = x;
        }
    }
    void fixtreeDelete(HybridNode *node)
    {
        if (node->parent == nullptr)
        {
            return;
        }

        HybridNode *sibling = (node == node->parent->left_child) ? node->parent->right_child : node->parent->left_child;

        if (sibling->color == "red")
        {
            // Case 1: Sibling is red
            node->parent->color = "red";
            sibling->color = "black";
            if (node == node->parent->left_child)
            {
                rotateLeft(node->parent);
                sibling = node->parent->right_child;
            }
            else
            {
                rotateRight(node->parent);
                sibling = node->parent->left_child;
            }
        }

        // Case 2: Sibling is black, and both sibling's children are black
        if ((sibling->left_child == nullptr || sibling->left_child->color == "black") &&
            (sibling->right_child == nullptr || sibling->right_child->color == "black"))
        {
            sibling->color = "red";
            if (node->parent->color == "black")
            {
                fixtreeDelete(node->parent);
            }
            else
            {
                node->parent->color = "black";
            }
            return;
        }

        if (node == node->parent->left_child)
        {
            // Case 3: Sibling is black, and sibling's left child is red
            if (sibling->right_child == nullptr || sibling->right_child->color == "black")
            {
                sibling->color = "red";
                sibling->left_child->color = "black";
                rotateRight(sibling);
                sibling = node->parent->right_child;
            }

            // Case 4: Sibling is black, and sibling's right child is red
            sibling->color = node->parent->color;
            node->parent->color = "black";
            sibling->right_child->color = "black";
            rotateLeft(node->parent);
        }
        else
        {
            // Symmetrical cases for right child
            if (sibling->left_child == nullptr || sibling->left_child->color == "black")
            {
                sibling->color = "red";
                sibling->right_child->color = "black";
                rotateLeft(sibling);
                sibling = node->parent->left_child;
            }

            sibling->color = node->parent->color;
            node->parent->color = "black";
            sibling->left_child->color = "black";
            rotateRight(node->parent);
        }
    }

public:
    RedBlackTree() : root(nullptr) {}

    HybridNode *getRoot()
    {
        return root; // Return the root node
    }

    void setRoot(HybridNode *node)
    {
        root = node; // Set the root node
    }

    HybridNode *insert(std::string key, std::string element)
    {
        HybridNode *newNode = new HybridNode(key, element);
        HybridNode *parent = nullptr;
        HybridNode *current = this->root;

        // Perform a standard BST insert
        while (current != nullptr)
        {
            parent = current;
            if (key < current->key)
                current = current->left_child;
            else if (key > current->key)
                current = current->right_child;
            else
            {
                std::cout << "Same element" << std::endl;
                while (current->next_node)
                    current = current->next_node;
                current->next_node = new HybridNode(key, element);
                current->next_node->color = current->color;
                current->next_node->parent = current->parent;
                return current->next_node;
            }
        }

        // Attach the new node to the parent
        newNode->parent = parent;
        if (parent == nullptr)
            this->root = newNode; // The tree is empty, so make the new node the root
        else if (key < parent->key)
        {
            newNode->color = "red";
            parent->left_child = newNode;
        }
        else
        {
            newNode->color = "red";
            parent->right_child == newNode;
        }
        // Fix the Red-Black Tree properties
        fixtreeInsert(newNode);
        return newNode;
    }

    bool deleteNode(string key)
    {
        HybridNode *node = search(key);
        if (node == nullptr)
        {
            return false;
        }
        HybridNode *node1 = node;
        if (node->left_child != nullptr && node->right_child != nullptr)
        {
            node1 = getSuccessor(node);
        }
        if (node1 != node)
        {
            node->key = node1->key;
            node->element = node1->element;
        }

        HybridNode *v = nullptr;
        if (node1->left_child != nullptr)
        {
            v = node1->left_child;
        }
        else
        {
            v = node1->right_child;
        }
        if (v != nullptr)
        {

            v->parent = node1->parent;
        }
        if (node1->parent == nullptr)
        {
            this->setRoot(v);
        }
        else
        {
            if (node1->parent->left_child == node1)
            {
                node1->parent->left_child = v;
            }
            else
            {
                node1->parent->right_child = v;
            }
        }
        if (node1->color == "red" || (v != nullptr && v->color == "red"))
        {

            if (node1->color != "red")
                v->color = "black";
            return true;
        }
        else if (node1->color == "black" && (v == nullptr || v->color == "black"))
        {
            fixtree(v, node1->parent);
            delete (node1);
            return true;
        }
        else
        {
            return true;
        }
    }
    void fixtree(HybridNode *v, HybridNode *parent)
    {
        if (v == root)
        {
            return;
        }
        if (v == nullptr || v->color == "black")
        {
            HybridNode *s = nullptr;

            if ((v != nullptr && v->parent->left_child == v) || (v == nullptr && parent->left_child == v))
            {
                if (v != nullptr)
                    s = v->parent->right_child;
                else
                    s = parent->right_child;
            }
            else
            {
                if (v != nullptr)
                    s = v->parent->left_child;
                else
                    s = parent->left_child;
            }
            if (s == nullptr)
            {
                if ((v == nullptr && parent->color == "black") || (v != nullptr && v->parent->color == "black"))
                {
                    if (v == nullptr)
                        fixtree(parent, nullptr);
                    else
                        fixtree(v->parent, nullptr);
                }
                else
                {
                    if (v == nullptr)
                        parent->color = "black";
                    else
                        v->parent->color = "black";
                }
            }
            if (s != nullptr && s->color == "red")
            {
                s->parent->color = "red";
                s->color = "black";
                if ((v != nullptr && v->parent->left_child == s) || (v == nullptr && parent->left_child == s))
                {
                    rotateRight(s->parent);
                }
                else if ((v != nullptr && v->parent->right_child == s) || (v == nullptr && parent->right_child == s))
                {
                    rotateLeft(s->parent);
                }
                fixtree(v, parent);
            }
            else if (s != nullptr && s->color == "black")
            {
                if ((s->left_child != nullptr && s->left_child->color == "red") || (s->right_child != nullptr && s->right_child->color == "red"))
                {
                    if ((v != nullptr && v->parent->left_child == s) || (v == nullptr && parent->left_child == s))
                    {
                        if ((s->left_child != nullptr && s->left_child->color == "red"))
                        {
                            s->left_child->color = s->color;
                            s->color = s->parent->color;
                            s->parent->color = "black";
                            rotateRight(s->parent);
                        }
                        else
                        {
                            s->right_child->color = s->parent->color;
                            s->parent->color = "black";
                            rotateLeft(s);
                            rotateRight(s->parent->parent);
                        }
                    }
                    if ((v != nullptr && v->parent->right_child == s) || (v == nullptr && parent->right_child == s))
                    {

                        if ((s->right_child != nullptr && s->right_child->color == "red"))
                        {
                            s->right_child->color = s->color;
                            s->color = s->parent->color;
                            s->parent->color = "black";
                            rotateLeft(s->parent);
                        }
                        else
                        {
                            s->left_child->color = s->parent->color;
                            s->parent->color = "black";
                            rotateRight(s);
                            rotateLeft(s->parent->parent);
                        }
                    }
                }
                else if ((s != nullptr) && (s->left_child == nullptr || s->left_child->color == "black") && (s->right_child == nullptr || s->right_child->color == "black"))
                {
                    s->color = "red";
                    if (s->parent->color == "black")
                    {
                        fixtree(s->parent, nullptr);
                        return;
                    }
                    else
                    {
                        s->parent->color = "black";
                        return;
                    }
                }
            }
        }
    }
    HybridNode *getSuccessor(HybridNode *ptr)
    {
        HybridNode *temp = ptr;
        if (ptr->right_child)
        {
            temp = temp->right_child;
            while (temp->left_child)
                temp = temp->left_child;
            return temp;
        }
        return nullptr;
    }
    vector<HybridNode *> preOrderTraversal(HybridNode *node, int depth)
    {
        vector<HybridNode *> nodes;
        if (node == nullptr || depth < 0)
        {
            return nodes;
        }
        else
        {
            depth--;
            HybridNode *temp = node;
            nodes.push_back(temp);
            vector<HybridNode *> leftSubtree = preOrderTraversal(node->left_child, depth);
            vector<HybridNode *> rightSubtree = preOrderTraversal(node->right_child, depth);
            nodes.insert(nodes.end(), leftSubtree.begin(), leftSubtree.end());
            nodes.insert(nodes.end(), rightSubtree.begin(), rightSubtree.end());
        }
        // Perform pre-order traversal staying within specified depth
    }
    HybridNode *search(std::string key)
    {
        HybridNode *current = this->getRoot();
        while (current)
        {
            if (current->key.compare(key) > 0)
                current = current->left_child;
            else if (current->key.compare(key) < 0)
                current = current->right_child;
            else
                return current;
        }
        return nullptr;
    }

    int blackheight(HybridNode *node)
    {
        // Implement blackheight
        int bh = 0;
        HybridNode *temp = node;
        while (temp != nullptr)
        {
            if (temp->color == "black")
                bh++;

            temp = temp->left_child;
        }
        return bh;
    }
    int NoOfNodes(HybridNode *ptr)
    {
        if (ptr == nullptr)
            return 0;
        return 1 + NoOfNodes(ptr->left_child) + NoOfNodes(ptr->right_child);
    }
};

class bin
{
public:
    bin *nextptr;

    string word;
    int count;
    string chapter;
    bin(string a, string b)
    {
        word = a;
        chapter = b;
        count = 0;
    }
};
class Histogram
{
public:
    bin *head = nullptr;
    bin *tail;
    string word;

    Histogram(string a)
    {
        word = a;
    }
    bin *search(string name, string chr)
    {

        bin *temp = head;

        while (temp != nullptr && strcmp(temp->chapter.c_str(), chr.c_str()) != 0)
        {
            temp = temp->nextptr;
        }
        if (temp != nullptr && strcmp(temp->chapter.c_str(), chr.c_str()) == 0)
        {

            return temp;
        }
        else
        {

            return nullptr;
        }
    }
    int totalbins()
    {
        bin *temp = head;
        int p = 0;
        while (temp != nullptr)
        {
            p++;
            temp = temp->nextptr;
        }
        return p;
    }
    void addbin(string chapter)
    {
        bin *newnode = new bin(word, chapter);

        newnode->count = 1;
        if (head == nullptr)
        {

            newnode->nextptr = nullptr;
            head = newnode;
        }
        else
        {
            bin *temp = head;
            while (temp->nextptr != nullptr)
            {
                temp = temp->nextptr;
            }
            newnode->nextptr = nullptr;
            temp->nextptr = newnode;
        }
    }
};
class IndexEntry
{
private:
    string word;
    vector<pair<string, int>> chapter_word_counts; // List of (chapter, word_count) tuples

public:
    IndexEntry(string word_val) : word(word_val) {}

    void setWord(string word_val)
    { // Set the word
        word = word_val;
    }

    string getWord()
    { // Get the word
        return word;
    }

    void setChapterWordCounts(vector<pair<string, int>> chapter_word_counts_val)
    { // Set the list of (chapter, word_count) tuples
        chapter_word_counts = chapter_word_counts_val;
    }

    vector<pair<string, int>> getChapterWordCounts()
    { // Get the list of (chapter, word_count) tuples
        return chapter_word_counts;
    }
};

class Lexicon
{
private:
    RedBlackTree red_black_tree; // Red-Black Tree
public:
    vector<string> chapters;
    vector<Histogram *> histograms;
    Lexicon() {}

    void setRedBlackTree(RedBlackTree tree)
    { // Set the Red-Black Tree
        red_black_tree = tree;
    }

    RedBlackTree getRedBlackTree()
    { // Get the Red-Black Trees
        return red_black_tree;
    }

    void readChapters(vector<string> chapter_name)
    {

        chapters = chapter_name;
        vector<string> deleted;
        for (auto j : chapter_name)
        {

            string data;
            string file = j;
            stringstream buffer;
            ifstream inputfile(file);

            if (inputfile.is_open())
            {
                buffer << inputfile.rdbuf();
                inputfile.close();
                data = buffer.str();
            }
            istringstream iss(data);
            string token;
            while (getline(iss, token, ' '))
            {

                if (token.empty())
                    continue;

                for (char &i : token)
                {
                    i = tolower(i);
                }

                if (red_black_tree.search(token) == nullptr)
                {
                    int p = 0;
                    for (auto i : deleted)
                    {
                        if (i == token)
                        {
                            p = 1;
                            break;
                        }
                    }
                    if (p == 1)
                    {
                        continue;
                    }
                    Histogram *newhist = new Histogram(token);
                    newhist->addbin(j.substr(0, 8));
                    histograms.push_back(newhist);
                    red_black_tree.insert(token, j.substr(0, 8));
                }
                else
                {
                    for (auto i : histograms)
                    {
                        if (i->word == token)
                        {
                            bin *temp = i->search(token, j.substr(0, 8));
                            if (temp != nullptr)
                            {

                                temp->count = temp->count + 1;

                                break;
                            }
                            else
                            {

                                i->addbin(j.substr(0, 8));
                                if (i->totalbins() == chapter_name.size())
                                {
                                    deleted.push_back(token);
                                    red_black_tree.deleteNode(i->word);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    vector<IndexEntry> buildIndex()
    {
        vector<IndexEntry> index;
        vector<pair<string, int>> p;
        for (auto i : histograms)
        {
            IndexEntry k(i->word);
            bin *temp = i->head;

            while (temp != nullptr)
            {
                pair<string, int> a(temp->chapter, temp->count);
                p.push_back(a);
                temp = temp->nextptr;
            }

            vector<pair<string, int>> t;
            for (auto l : chapters)
            {
                int z = 0;
                for (auto j : p)
                {
                    if (j.first == l.substr(0, 8))
                    {
                        t.push_back(j);
                        z = 1;
                        break;
                    }
                }
                if (z == 0)
                {
                    pair<string, int> page(l.substr(0, 8), 0);
                    t.push_back(page);
                }
            }
            k.setChapterWordCounts(t);
            index.push_back(k);
            p.clear();
        }
        return index;
    }
};
