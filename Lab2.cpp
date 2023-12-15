#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

class StudentRecord
{
private:
    std::string studentName;
    std::string rollNumber;

public:
    std::string get_studentName()
    {
        return studentName;
    }
    void set_studentName(std::string Name)
    {
        studentName = Name;
    }
    std::string get_rollNumber()
    {
        return rollNumber;
    }
    void set_rollNumber(std::string rollnum)
    {
        rollNumber = rollnum;
    }
};

class Node
{
private:
    Node *next;
    StudentRecord *element;

public:
    Node *get_next()
    {
        return next;
    }
    StudentRecord *get_element()
    {
        return element;
    }

    Node *set_next(Node *value)
    {
        next = value;
    }
    StudentRecord *set_element(StudentRecord *student)
    {
        element = student;
    }
};
std::ostream &operator<<(std::ostream &os, StudentRecord &obj)
{
    os << obj.get_studentName() << " " << obj.get_rollNumber() << " ";
    return os;
}
class Entity
{
private:
    std::string name;
    Node *iterator;

public:
    std::string get_name()
    {
        return name;
    }
    void set_name(std::string Name)
    {
        name = Name;
    }
    Node *get_iterator()
    {
        return iterator;
    }
    void set_iterator(Node *iter)
    {
        iterator = iter;
    }
};

class LinkedList : public Entity
{
    int size;

public:
    LinkedList(std::string name)
    {
        set_name(name);
        set_iterator(nullptr);
        size = 0;
    }
    void add_student_record(StudentRecord &student)
    {
        Node *newNode = new Node();
        StudentRecord *newRecord = new StudentRecord(student);
        newNode->set_element(newRecord);
        if (get_iterator() == nullptr)
        {
            set_iterator(newNode);
            get_iterator()->set_next(nullptr);
        }
        else
        {
            Node *temp = get_iterator();
            while (temp->get_next() != nullptr)
            {
                temp = temp->get_next();
            }
            temp->set_next(newNode);
        }
        size++;
    }
    void delete_student_record(StudentRecord *obj)
    {
        if (get_iterator()->get_element()->get_rollNumber() == obj->get_rollNumber())
        {
            Node *temp = get_iterator();
            set_iterator(get_iterator()->get_next());
            delete temp;
        }
        else
        {
            Node *Current = get_iterator();
            while (Current != nullptr)
            {
                if (Current->get_next()->get_element()->get_rollNumber() == obj->get_rollNumber())
                {
                    Node *temp = Current->get_next();
                    Current->set_next(temp->get_next());
                    delete temp;
                    break;
                }
                else
                    Current->set_next(Current->get_next());
            }
        }
        size--;
    }
    void Display()
    {
        Node *temp = get_iterator();
        std::cout << get_name() << "\n";
        while (temp != nullptr)
        {
            std::cout << *(temp->get_element()) << " ";
            temp = temp->get_next();
        }
    }
    int getsize()
    {
        return size;
    }
};
std::vector<StudentRecord> students;
std::vector<LinkedList> EntityArray;
bool check_entity(std::string word)
{
    for (LinkedList &L : EntityArray)
    {
        if (L.get_name().compare(word) == 0)
            return true;
    }
    return false;
}
int list_num(std::string word)
{
    int i{};
    for (LinkedList &L : EntityArray)
    {
        if (L.get_name().compare(word) == 0)
            return i;
        else
            i++;
    }
}
void PrintDet(std::string word)
{
    for (LinkedList e : EntityArray)
    {
        if (e.get_name().compare(word) == 0)
            e.Display();
    }
}
int main()
{
    std::ifstream fp("Details.txt");
    std::string line;
    std::vector<std::string> words;
    int stud_cnt{};
    while (getline(fp, line))
    {
        std::string out, word;
        for (char c : line)
        {
            if (c == ',')
                out += ' ';
            else if (c == '[' || c == ']')
                out = out;
            else
                out += c;
        }
        for (char c : out)
        {
            if (c == ' ')
            {
                words.push_back(word);
                word.clear();
            }
            else
                word += c;
        }
        words.push_back(word);
        StudentRecord s1;
        s1.set_studentName(words[0]);
        s1.set_rollNumber(words[1]);
        students.push_back(s1);
        for (std::string wordi : words)
        {
            if (wordi.compare(words[0]) == 0 || wordi.compare(words[1]) == 0)
            {
                continue;
            }
            else
            {
                if (check_entity(wordi))
                {
                    int i = list_num(wordi);
                    EntityArray[i].add_student_record(s1);
                }
                else
                {
                    LinkedList L(wordi);
                    L.add_student_record(s1);
                    EntityArray.push_back(L);
                }
            }
        }
        stud_cnt++;
        words.clear();
    }
}