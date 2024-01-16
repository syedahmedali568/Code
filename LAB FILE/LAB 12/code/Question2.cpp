//<----Lab 12 - Hashing---->

// 2. Implement a hashing algorithm using Quadratic Probing.

#include <iostream>
#include <vector>
using namespace std;

class QuadraticProbingHashTable
{
private:
    static const int TABLE_SIZE = 10;
    vector<int> table;
    // Hash function (simple modulo hashing)
    int hash(int key) const
    {
        return key % TABLE_SIZE;
    }

public:
    QuadraticProbingHashTable() : table(TABLE_SIZE, -1) {}
    // Insert a key into the hash table
    void insert(int key)
    {
        int index = hash(key);
        int i = 1; // Quadratic probing increment

        // Quadratic probing to find an empty slot
        while (table[index] != -1)
        {
            index = (index + i * i) % TABLE_SIZE;
            ++i;
        }
        table[index] = key;
    }
    // Search for a key in the hash table
    bool search(int key) const
    {
        int index = hash(key);
        int i = 1; // Quadratic probing increment

        // Quadratic probing to find the key
        while (table[index] != -1)
        {
            if (table[index] == key)
            {
                return true; // Key found
            }
            index = (index + i * i) % TABLE_SIZE;
            ++i;
        }
        return false; // Key not found
    }
    // Display the hash table
    void display() const
    {
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            cout << "Index " << i << ": ";
            if (table[i] != -1)
            {
                cout << table[i];
            }
            cout << endl;
        }
    }
};
int main()
{
    QuadraticProbingHashTable hashTable;
    // Insert some keys
    hashTable.insert(12);
    hashTable.insert(25);
    hashTable.insert(35);
    hashTable.insert(45);
    hashTable.insert(55);
    hashTable.insert(5);
    // Display the hash table
    cout << "Hash Table after insertion:\n";
    hashTable.display();
    // Search for keys
    cout << "\nSearching for keys:\n";
    cout << "Key 35 " << (hashTable.search(35) ? "found" : "not found") << endl;
    cout << "Key 18 " << (hashTable.search(18) ? "found" : "not found") << endl;
    return 0;
}
