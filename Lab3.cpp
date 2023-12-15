#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <utility>
#include <cassert>

using namespace std; // I don't like to use this but in case you dont use in testcases it might encouter an error so this is written.

bool check_number(std::string obj)
{
    for (char ch : obj)
    {
        if (ch < '0' || ch > '9')
            return false;
    }
    return true;
}

class PhoneRecord
{
private:
    std::string name;
    std::string organisation;
    std::vector<std::string> phoneNumbers;

public:
    PhoneRecord(const std::string &n, const std::string &org, const std::vector<std::string> &numbers)
        : name(n), organisation(org), phoneNumbers(numbers) {}

    std::string getName() const
    {
        return name;
    }

    std::string getOrganisation() const
    {
        return organisation;
    }

    std::vector<std::string> getPhoneNumbers() const
    {
        return phoneNumbers;
    }
    bool operator==(const PhoneRecord &obj)
    {
        bool flag = true;
        if (this->getName() == obj.getName())
            if (this->getOrganisation() == obj.getOrganisation())
                flag = true;
            else
                return false;
        else
            return false;
        return flag;
    }
};

class HashTableRecord
{
private:
    int key;
    PhoneRecord *record;
    HashTableRecord *next;

public:
    HashTableRecord(int k, PhoneRecord *rec)
        : key(k), record(rec), next(nullptr) {}

    int getKey() const
    {
        return key;
    }

    PhoneRecord *getRecord() const
    {
        return record;
    }

    HashTableRecord *getNext() const
    {
        return next;
    }

    void setNext(HashTableRecord *nxt)
    {
        next = nxt;
    }
};

class PhoneBook
{
private:
    static const int HASH_TABLE_SIZE = 263;
    HashTableRecord *hashTable[HASH_TABLE_SIZE];

public:
    PhoneBook()
    {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i)
        {
            hashTable[i] = nullptr;
        }
    }
    long long computeHash(const std::string &str)
    {
        long long key = 0, p = 1000000007;
        for (int i{}; i < str.size(); i++)
        {
            long long d = pow(HASH_TABLE_SIZE, i);
            key += str[i] * (d % p);
        }
        key %= HASH_TABLE_SIZE;
        return key;
    }

    void addContact(PhoneRecord *record)
    {
        std::vector<std::string> names;
        std::string name;
        for (char ch : record->getName())
        {
            if (ch == ' ')
            {
                names.push_back(name);
                name.clear();
            }
            else
            {
                name += ch;
            }
        }
        names.push_back(name);
        for (std::string i : names)
        {
            long long key = computeHash(i);
            HashTableRecord *rec = new HashTableRecord(key, record);
            rec->setNext(nullptr);
            if (hashTable[rec->getKey()] == nullptr)
            {
                hashTable[rec->getKey()] = rec;
            }
            else
            {
                HashTableRecord *temp = hashTable[key];
                while (temp->getNext() != nullptr)
                    temp = temp->getNext();
                temp->setNext(rec);
            }
        }
    }

    bool deleteContact(const std::string *searchName)
    {
        std::vector<PhoneRecord *> Deleters = this->fetchContacts(searchName);
        PhoneRecord *Deleted;
        for (PhoneRecord *hi : Deleters)
        {
            if (hi->getName().find(*searchName) != std::string::npos)
            {
                Deleted = hi;
                break;
            }
        }
        std::vector<std::string> names;
        int p = 0;
        std::string name;
        for (char ch : Deleted->getName())
        {
            if (ch == ' ')
            {
                names.push_back(name);
                name.clear();
            }
            else
            {
                name += ch;
            }
        }
        names.push_back(name);
        for (std::string &i : names)
        {
            long long key = computeHash(i);
            if (hashTable[key]->getRecord()->getName() == Deleted->getName())
            {
                HashTableRecord *temp = hashTable[key];
                hashTable[key] = hashTable[key]->getNext();
                delete temp;
                p++;
            }
            else
            {
                HashTableRecord *temp = hashTable[key];
                HashTableRecord *prev = nullptr;
                while (temp != nullptr && !(*(temp->getRecord()) == *Deleted))
                {
                    prev = temp;
                    temp = temp->getNext();
                }
                if (temp != nullptr)
                {
                    prev->setNext(temp->getNext());
                    delete temp;
                    p++;
                }
            }
        }
        if (p > 0)
            return true;
        else
            return false;
    }

    std::vector<PhoneRecord *> fetchContacts(const std::string *query)
    {

        std::vector<std::string> names;
        std::vector<PhoneRecord *> result, inter;
        std::string name;
        for (char ch : *query)
        {
            if (ch == ' ')
            {
                names.push_back(name);
                name.clear();
            }
            else
            {
                name += ch;
            }
        }
        names.push_back(name);
        for (std::string &i : names)
        {
            long long key = computeHash(i);
            HashTableRecord *temp = hashTable[key];
            while (temp != nullptr)
            {
                inter.push_back(temp->getRecord());
                temp = temp->getNext();
            }
        }
        std::vector<std::pair<PhoneRecord *, int>> unique;
        for (PhoneRecord *ph : inter)
        {
            bool flag = false;
            for (std::pair<PhoneRecord *, int> u : unique)
            {
                if (u.first == ph)
                {
                    flag = true;
                    u.second++;
                    break;
                }
            }
            if (!flag)
            {
                std::pair<PhoneRecord *, int> p{ph, 1};
                unique.push_back(p);
            }
        }
        auto customComparator = [](const std::pair<PhoneRecord *, int> &a, const std::pair<PhoneRecord *, int> &b)
        {
            return a.second > b.second;
        };
        std::sort(unique.begin(), unique.end(), customComparator);
        for (std::pair<PhoneRecord *, int> p : unique)
        {
            for (std::string &i : names)
            {
                if (p.first->getName().find(i) != std::string::npos)
                {
                    result.push_back(p.first);
                    break;
                }
            }
        }
        return result;
    }
    void readRecordsFromFile(std::string path)
    {
        std::ifstream file(path);
        std::vector<std::string> words, numbers;
        std::string word, line, name, org;
        while (getline(file, line))
        {
            for (char ch : line)
            {
                if (ch == ',')
                {
                    words.push_back(word);
                    word.clear();
                }
                else
                {
                    word += ch;
                }
            }
            words.push_back(word);
            word.clear();
            for (std::string word : words)
            {
                if (word == words[0])
                {
                    name = word;
                }
                else
                {
                    if (check_number(word))
                    {
                        numbers.push_back(word);
                    }
                    else
                    {
                        org = word;
                    }
                }
            }
            PhoneRecord *ph = new PhoneRecord(name, org, numbers);
            this->addContact(ph);
            words.clear();
            name.clear();
            numbers.clear();
            org.clear();
            line.clear();
        }
    }
    int countRecordsPointingTo(const PhoneRecord *record) const
    {
        std::string p = std::string(record->getName());
        std::string name;
        std::vector<std::string> names;
        for (char ch : p)
        {
            if (ch == ' ')
            {
                names.push_back(name);
                name.clear();
            }
            else
                name += ch;
        }
        names.push_back(name);
        return names.size();
    }
};