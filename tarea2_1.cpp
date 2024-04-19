#include <iostream>
using namespace std;

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size_;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size_(0) {}

    ~DoublyLinkedList() {
        clear();
    }

    T front() {
        if (empty()) {throw out_of_range("Lista vacia");}
        return head->data;
    }

    T back() {
        if (empty()) {throw out_of_range("Lista vacia");}
        return tail->data;
    }

    void push_front(const T& value) {
        Node* newNode = new Node(value);
        if (empty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size_++;
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (empty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size_++;
    }

    T pop_front() {
        if (empty()) {throw out_of_range("Lista vacia");}
        T value = head->data;
        Node* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        size_--;
        return value;
    }

    T pop_back() {
        if (empty()) {throw out_of_range("Lista vacia");}
        T value = tail->data;
        Node* temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        size_--;
        return value;
    }

    void insert(const T& value, int position) {
        if (position == 0) {
            push_front(value);
        } else if (position == size_) {
            push_back(value);
        } else {
            Node* newNode = new Node(value);
            Node* current = head;
            for (int i = 0; i < position - 1; ++i) {
                current = current->next;
            }
            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;
            size_++;
        }
    }

    void remove(int position) {
        if (position == 0) {
            pop_front();
        } else if (position == size_ - 1) {
            pop_back();
        } else {
            Node* current = head;
            for (int i = 0; i < position; ++i) {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            size_--;
        }
    }

    T operator[](int position) {
        Node* current = head;
        for (int i = 0; i < position; ++i) {
            current = current->next;
        }
        return current->data;
    }

    bool empty() const {
        return size_ == 0;
    }

    int size() const {
        return size_;
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    void reverse() {
        Node* current = head;
        Node* temp = nullptr;
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

    void printlist() {
        if (empty()) {return;}
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};



// Cases zzz
int main() {
    using namespace std;

    DoublyLinkedList<int> list;

    list.push_back(1);
    cout << "Front element: " << list.front() << endl;

    list.push_back(2);
    cout << "Back element: " << list.back() << endl;

    list.push_front(0);
    cout << "List after push_front(0): ";
    list.printlist();

    list.push_back(3);
    cout << "List after push_back(3): ";
    list.printlist();

    cout << "Popped front element: " << list.pop_front() << endl;
    cout << "List after pop_front(): ";
    list.printlist();

    cout << "Popped back element: " << list.pop_back() << endl;
    cout << "List after pop_back(): ";
    list.printlist();

    list.insert(5, 1);
    cout << "List after insert(5, 1): ";
    list.printlist();

    list.remove(1);
    cout << "List after remove(1): ";
    list.printlist();

    cout << "Element at position 0: " << list[0] << endl;

    cout << "Is list empty? " << (list.empty() ? "Yes" : "No") << endl;
    cout << "Lista actual: ";
    list.printlist();

    cout << "Size of list: " << list.size() << endl;

    list.clear();
    cout << "List cleared. Is list empty now? " << (list.empty() ? "Yes" : "No") << endl;
    cout << "Lista actual: ";
    list.printlist();

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    cout << "Original list: ";
    list.printlist();
    list.reverse();
    cout << "Reversed list: ";
    list.printlist();

    return 0;
}
