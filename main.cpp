#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    char values[7]; // Sabendo que uma string possui 6 caracteres + '\0'
    Node *nextNode;
    int appearances;

    Node(const char *v)
    {
        for (int i = 0; i < 6; i++)
        {
            values[i] = v[i]; // copia dos 6 valores para o nó
        }
        values[6] = '\0'; // quando a string é criada, adiciona o terminador
        nextNode = NULL;  // e inicializa o ponteiro para o próximo nó como nulo
        appearances = 1;  // importante considerar a primeira aparição
    }
};

class LinkedList
{
private:
    Node *head;
    Node *tail;

public:
    LinkedList();
    void insert(const char *values);
    void saveToFile(ofstream &out); // essas funções de salvar arquivo e lê-lo foram obtidas a partir do site geekies for geeks
    Node *getHead();
};
Node *LinkedList::getHead()
{
    return head;
}
LinkedList::LinkedList()
{
    head = NULL;
    tail = NULL;
}

void LinkedList::insert(const char *values)
{
    Node *current = head; // ponteiro auxiliar para percorrer a lista
    while (current != nullptr)
    {
        bool similar = true;
        for (int i = 0; i < 6; i++) // compara os valores do nó atual com os novos valores
        {
            if (current->values[i] != values[i]) // e, se nao forem iguais, o booleano é marcado como falso
            {
                similar = false;
                break;
            }
        } // porém, caso contrário, ele incrementa o número de aparições
        if (similar)
        {
            current->appearances++;
            return;
        }
        current = current->nextNode; // para o próximo nó
    }

    Node *newNode = new Node(values); // alocacão dinamica de um novo nó
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

void LinkedList::saveToFile(ofstream &out)
{
    Node *current = head;
    while (current != nullptr)
    {
        out << current->values << " " << current->appearances << "\n";
        current = current->nextNode;
    }
}

class HashTable
{
private:
    vector<LinkedList> *table;
    int tableSize;

public:
    HashTable(int size);
    void insert(const char *values);
    int hashFunction(const char *values);
    void saveFile(string filename);
};

HashTable::HashTable(int size)
{
    tableSize = size;
    table = new vector<LinkedList>(size); // a hash é inicializada com um tamanho fixo, cuja table é um vetor de listas encadeadas para armazenar os dados
}

int HashTable::hashFunction(const char *values) // funcao de espelhamento que transforma os valores em numeros
{
    long hashValue = 0;
    int prime = 37; // escolhi  37 pois é um número primo , dificultando a colisão
    for (int i = 0; i < 6; i++)
    {
        hashValue = (hashValue * prime + values[i]) % tableSize;
    }
    return hashValue;
}

void HashTable::insert(const char *values)
{
    int position = hashFunction(values);
    (*table)[position].insert(values); // acessando a lista encadeada na posição correspondente
    // e chamando a função de inserção implementada na classe LinkedList
}

void HashTable::saveFile(string filename)
{
    ofstream out(filename);
    for (LinkedList &list : *table)
    {
        list.saveToFile(out);
    }
    out.close();
}

int main()
{
    ifstream f("sequencia.txt"); // sequencia tirada do arquivo geekies for geeks
    if (!f.is_open())
    {
        cerr << "Erro ao abrir o arquivo!\n";
        return 1;
    }

    string linha;
    HashTable table(20011);
    char section[7]; // armazena os 6 caracteres + o terminador

    while (getline(f, linha))
    {
        if (linha.size() < 60)
            continue; // percorrer todas as 60 linhas

        for (int i = 0; i < 60; i += 6)
        {
            for (int j = 0; j < 6; j++)
            {
                section[j] = linha[i + j];
            }
            section[6] = '\0'; // se o ultimo char for o terminador, insere todo o bloco
            table.insert(section);
        }
    }

    table.saveFile("saida.txt");
    f.close();
    return 0;
}
