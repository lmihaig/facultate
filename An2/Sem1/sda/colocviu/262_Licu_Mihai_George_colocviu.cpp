/*
Colocviu Structuri de Date si Algoritmi
28/01/2022
CTI 262 Licu Mihai-George
*/
#include <string>
#include <iostream>

// 1)
bool isPow(const std::string &s)
{
    // construim un string dublu al stringului initial fara prima si ultima litera din acesta de ex pentru s = "abcdabcd" avem "bcdabcdabcdabc"
    std::string string1 = s.substr(1);
    std::string string2 = s.substr(0, s.size() - 1);
    std::string dubluString = string1 + string2;

    // cautam daca stringul initial s se gaseste in noul string dublat, daca da atunci inseamna ca stringul este format doar din repetitia unui substring din el
    int Pow = dubluString.find(s);
    return Pow != -1;
}

// 2)
template <typename T>
class Node
{
public:
    Node<T> *next;
    Node<T> *prev;
    int val;
    Node(int val)
    {
        next = nullptr;
        prev = nullptr;
        this->val = val;
    }
};

// am implementat folosind o lista dublu inlantuita deoarece ofera capabilitatea de a scoate in O(1) elementul k daca acesta exista dar si cel mai nou element daca k nu exista
// de asemenea adaugarea si verificarea daca este goala sunt in O(1)
template <typename T>
class DataStructure
{
    Node<T> *head;
    Node<T> *k;
    int size;
    const int kIndex;

public:
    DataStructure(int kIndex) : kIndex(kIndex)
    {
        head = nullptr;
        k = nullptr;
        size = 0;
    }

    bool empty()
    {
        return size == 0;
    }

    void add(int val)
    {
        // daca nu sunt elemente in structura noul element devine cap
        if (!head)
            head = k = new Node<T>(val);

        // altfel se adauga la cap
        else
        {
            Node<T> *node = new Node<T>(val);
            node->next = head;
            head->prev = node;
            head = node;
        }
        // daca marimea creste peste indexului k, se schimba care este al k-lea element
        if (size++ > kIndex)
            k = k->prev;
    }

    T next()
    {
        // daca sunt suficiente elemente atunci se scoate al k-lea element
        if (size > kIndex)
        {
            if (k->prev)
                k->prev->next = k->next;
            if (k->next)
                k->next->prev = k->prev;
            int val = k->val;
            k = k->next;
            size--;
            return val;
        }
        // altfel scoatem cel mai recent adaugat element
        else
        {
            int val = head->val;
            head = head->next;
            size--;
            return val;
        }
    }
};

int main()
{
    // ex1
    std::cout << "PARTEA 1: \n";

    std::string a = "aaaa";
    std::string b = "abcabcabc";
    std::string c = "abcd";
    std::string d = "abac";
    std::cout << isPow(a) << "\n";
    std::cout << isPow(b) << "\n";
    std::cout << isPow(c) << "\n";
    std::cout << isPow(d) << "\n";

    // ex2
    std::cout << "\nPARTEA 2:\n";

    DataStructure<int> test(3);
    std::cout << "Is empty? " << test.empty() << "\n";
    test.add(6);
    test.add(5);
    std::cout << "kth element: " << test.next() << "\n"; // nu exista k (3) elemente deci scoate cel mai nou element, 5
    test.add(5);
    test.add(4);
    test.add(3);
    test.add(2);
    std::cout << "Is empty? " << test.empty() << "\n";
    test.add(1);
    test.add(0);
    std::cout << "kth element: " << test.next() << "\n"; // scoate al k-lea (3) cel mai vechi element

    return 0;
}