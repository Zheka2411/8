#include <iostream>
using namespace std;

// Структура для елемента списку
template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;

    Node(T val) : data(val), prev(nullptr), next(nullptr) {}
};

// Шаблонний клас двозв'язного списку
template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    // Конструктор
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Додати елемент до голови списку
    void AddToHead(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // Додати елемент до хвоста списку
    void AddToTail(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Видалити елемент з голови списку
    void DeleteFromHead() {
        if (head == nullptr) return;
        Node<T>* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }
        delete temp;
    }

    // Видалити елемент з хвоста списку
    void DeleteFromTail() {
        if (tail == nullptr) return;
        Node<T>* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }
        delete temp;
    }

    // Видалити всі елементи списку
    void DeleteAll() {
        while (head != nullptr) {
            DeleteFromHead();
        }
    }

    // Вивести всі елементи списку на екран
    void Show() {
        Node<T>* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Вставлення елемента на задану позицію
    void InsertAtPosition(T value, int position) {
        if (position < 0) return;
        Node<T>* newNode = new Node<T>(value);
        if (position == 0) {
            AddToHead(value);
            return;
        }

        Node<T>* current = head;
        int index = 0;
        while (current != nullptr && index < position - 1) {
            current = current->next;
            index++;
        }

        if (current == nullptr) {
            AddToTail(value);
        }
        else {
            newNode->next = current->next;
            if (current->next != nullptr) {
                current->next->prev = newNode;
            }
            current->next = newNode;
            newNode->prev = current;
        }
    }

    // Видалення елемента з заданої позиції
    void DeleteAtPosition(int position) {
        if (position < 0 || head == nullptr) return;
        Node<T>* current = head;
        int index = 0;
        while (current != nullptr && index < position) {
            current = current->next;
            index++;
        }

        if (current == nullptr) return;

        if (current == head) {
            DeleteFromHead();
        }
        else if (current == tail) {
            DeleteFromTail();
        }
        else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }
    }

    // Пошук елемента
    int Find(T value) {
        Node<T>* current = head;
        int index = 0;
        while (current != nullptr) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            index++;
        }
        return -1; // не знайдено
    }

    // Пошук і заміна елемента
    int Replace(T oldValue, T newValue) {
        Node<T>* current = head;
        int count = 0;
        while (current != nullptr) {
            if (current->data == oldValue) {
                current->data = newValue;
                count++;
            }
            current = current->next;
        }
        return count > 0 ? count : -1; // якщо елементів замінено, повертаємо їх кількість
    }

    // Перевернути список
    void Reverse() {
        Node<T>* current = head;
        Node<T>* temp = nullptr;

        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }

        if (temp != nullptr) {
            head = temp->prev;
        }
    }

    // Деструктор для очищення пам'яті
    ~DoublyLinkedList() {
        DeleteAll();
    }
};

int main() {
    DoublyLinkedList<int> list;

    // Додавання елементів
    list.AddToHead(10);
    list.AddToTail(20);
    list.AddToTail(30);
    list.AddToHead(5);
    list.Show();

    // Видалення елементів
    list.DeleteFromHead();
    list.DeleteFromTail();
    list.Show();

    // Вставлення елементів
    list.InsertAtPosition(25, 1);
    list.Show();

    // Пошук елемента
    int pos = list.Find(25);
    cout << "Element 25 found at position: " << pos << endl;

    // Заміна елемента
    int count = list.Replace(25, 40);
    cout << "Replaced " << count << " elements" << endl;
    list.Show();

    // Перевернути список
    list.Reverse();
    list.Show();

    return 0;
}
