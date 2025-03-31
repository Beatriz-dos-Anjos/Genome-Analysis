#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Node
{
public:
    string data; // rocar pra values
    Node *nextNode;
    int appearances;
    Node(string v)
    {
        data = v;
        nextNode = NULL;
        appearances = 1;
    }
};
class LinkedList
{
private:
    Node *head;
    Node *tail;

public:
    LinkedList();
    void insert(string data);
    int print();
    Node *getHead() { return head; }
};

LinkedList::LinkedList()
{
    head = NULL;
    tail = NULL;
}

void LinkedList::insert(string data)
{
    Node *current = head;
    while (current != nullptr)
    {
        if (current->data == data)
        {
            current->appearances++;
            return;
        }
        current = current->nextNode;
    }

    Node *newNode = new Node(data);
    if (head == nullptr)
    {
        head = tail = newNode;
    }
    else
    {
        tail->nextNode = newNode;
        tail = newNode;
    }
}

int LinkedList::print()
{
    Node *current = head;
    int count = 0;
    while (current != NULL)
    {
        cout << current->data << " " << current->appearances << endl;
        current = current->nextNode;
        count++;
    }
    return count;
}
class HashTable
{
private:
    vector<LinkedList> *table;

public:
    HashTable(int size);
    void insert(string data);
    int hashFunction(string data);
    void saveFile(string filename);
};

HashTable::HashTable(int size)
{
    table = new vector<LinkedList>(size);
}

int HashTable::hashFunction(string K)
{
    int len = K.length();
    int intLength = len / 4;
    long long sum = 0;

    for (int i = 0; i < intLength; i++)
    {
        long long mult = 1;
        for (int j = 0; j < 4; j++)
        {
            char c = K[i * 4 + j];
            sum += c * mult;
            mult *= 256;
        }
    }

    // Processa o restante (menos de 4 caracteres)
    long long mult = 1;
    for (int j = intLength * 4; j < len; j++)
    {
        sum += K[j] * mult;
        mult *= 256;
    }

    return abs(sum) % 20011;
}

void HashTable::insert(string data)
{
    int position = hashFunction(data);
    (*table)[position].insert(data);
}

void HashTable::saveFile(string filename)
{
    ofstream out(filename);
    for (LinkedList &list : *table)
    {
        Node *current = list.getHead(); 
        while (current != nullptr)
        {
            out << current->data << " " << current->appearances << "\n";
            current = current->nextNode;
        }
    }
    out.close();
}
int main()
{
    ifstream f("randomsequence.txt");
    if (!f.is_open())
    {
        cerr << "Error opening the file!";
        return 1;
    }

    string linha, genomaTotal;
    while (getline(f, linha))
    {
        genomaTotal += linha;
    }

    int K = 6;
    HashTable tabela(20011);

    for (int i = 0; i <= (int)genomaTotal.length() - K; i++)
    {
        string bloco = genomaTotal.substr(i, K);
        tabela.insert(bloco);
    }

    tabela.saveFile("saida.txt");

    f.close();
    return 0;
}
