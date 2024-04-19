#include <iostream>
using namespace std; 

template <typename T>
class CircularDoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& data) : data(data), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    int length;

public:
    CircularDoublyLinkedList() : head(nullptr), length(0) {}

    ~CircularDoublyLinkedList() {}

    T front() {
        if (empty()) {throw out_of_range("Lista vacia");}
        return head->data;
    }

    T back() {
        if (empty()) {throw out_of_range("Lista vacia");}
        return head->prev->data;
    }

    void push_front(const T& value) {
        Node* newNode = new Node(value);
        if (empty()) {
            head = newNode;
            head->prev = head;
            head->next = head;
        } else {
            newNode->next = head;
            newNode->prev = head->prev;
            head->prev->next = newNode;
            head->prev = newNode;
            head = newNode;
        }
        length++;
    }

    void push_back(const T& value) {
        push_front(value);
        head = head->next;
    }

    T pop_front() {
        if (empty()) {throw out_of_range("Lista vacia");}
        T value = head->data;
        if (length == 1) {
            delete head;
            head = nullptr;
        } else {
            Node* temp = head;
            head->prev->next = head->next;
            head->next->prev = head->prev;
            head = head->next;
            delete temp;
        }
        length--;
        return value;
    }

    T pop_back() {
        if (empty()) {throw out_of_range("Lista vacia");}
        T value = head->prev->data;
        remove(length - 1);
        return value;
    }

    void insert(const T& value, int position) {
        if (position == 0) {
            push_front(value);
        } else {
            Node* current = head;
            for (int i = 0; i < position - 1; ++i) {
                current = current->next;
            }
            Node* newNode = new Node(value);
            newNode->prev = current;
            newNode->next = current->next;
            current->next->prev = newNode;
            current->next = newNode;
            length++;
        }
    }

    void remove(int position) {
        if (empty()) {throw out_of_range("Lista vacia");}
        if (position == 0) {
            pop_front();
        } else {
            Node* current = head;
            for (int i = 0; i < position; ++i) {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            length--;
        }
    }

    T operator[](int position) {
        Node* current = head;
        for (int i = 0; i < position; ++i) {
            current = current->next;
        }
        return current->data;
    }

    bool empty() {
        return length == 0;
    }

    int size() {
        return length;
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    void reverse() {
        if (empty()) {
            return;
        }
        Node* current = head;
        do {
            Node* temp = current->next;
            current->next = current->prev;
            current->prev = temp;
            current = temp;
        } while (current != head);
        head = head->next;
    }

    void printlist() {
        if (empty()) {return;}
        Node* current = head;
        do {
            cout << current->data << " ";
            current = current->next;
        } while (current != head);
        cout << endl;
    }
};


// Cases zzzz
int main() {
    CircularDoublyLinkedList<int> list;

    list.push_front(1);
    list.push_front(2);
    list.push_back(3);
    list.push_back(4);
    list.printlist();

    cout << "Front: " << list.front() << endl;
    cout << "Back: " << list.back() << endl;
    cout << "Size: " << list.size() << endl;

    list.insert(5, 2);
    list.printlist();

    cout << "Element at position 2: " << list[2] << endl;

    cout << "Removing element at position 3: "<< list[3] << endl;
    list.remove(3);
    list.printlist();
    
    cout << "Removing last element: " << list.pop_back() << endl; 
    list.printlist();

    cout << "Size after removals: " << list.size() << endl;
    list.printlist();

    list.reverse();

    cout << "Elements after reversal: ";
    list.printlist();

    list.clear();

    cout << "Is the list empty after clearing? " << (list.empty() ? "Yes" : "No") << endl;
    list.printlist();

    return 0;
}
