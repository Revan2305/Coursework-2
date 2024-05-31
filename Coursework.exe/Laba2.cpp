
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;
using namespace chrono;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node* create_list(int n) {
    srand(time(0));
    Node* head = new Node;
    head->data = rand() % 100;
    head->prev = nullptr;
    head->next = nullptr;

    Node* current = head;
    for (int i = 1; i < n; i++) {
        Node* newNode = new Node;
        newNode->data = rand() % 100;
        newNode->prev = current;
        newNode->next = nullptr;
        current->next = newNode;
        current = newNode;
    }

    return head;
}

void print_list(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void insert_at_index(Node* head, int index, int value) {
    if (index == 0) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->prev = nullptr;
        newNode->next = head;

        head->prev = newNode;
        head = newNode;
    }
    else {
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        Node* newNode = new Node;
        newNode->data = value;
        newNode->prev = current;
        newNode->next = current->next;

        if (current->next != nullptr) {
            current->next->prev = newNode;
        }
        current->next = newNode;
    }
}

void insert_at_value(Node* head, int value) {
    Node* current = head;
    while (current->next != nullptr && current->next->data != value) {
        current = current->next;
    }

    if (current->next != nullptr) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->prev = current;
        newNode->next = current->next;

        current->next->prev = newNode;
        current->next = newNode;
    }
}

void delete_at_index(Node* head, int index) {
    if (head == nullptr || index < 0) {
        return;
    }

    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    if (current->prev != nullptr) {
        current->prev->next = current->next;
    }
    if (current->next != nullptr) {
        current->next->prev = current->prev;
    }

    delete current;
}

void delete_at_value(Node* head, int value) {
    Node* current = head;
    while (current->next != nullptr && current->next->data != value) {
        current = current->next;
    }

    if (current->next != nullptr) {
        if (current->next->next != nullptr) {
            current->next->next->prev = current;
        }
        current->next = current->next->next;

        delete current->next;
    }
}

int get_at_index(Node* head, int index) {
    if (head == nullptr || index < 0) {
        return -1;
    }

    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    return current->data;
}

int get_at_value(Node* head, int value) {
    Node* current = head;
    while (current->next != nullptr && current->next->data != value) {
        current = current->next;
    }

    if (current->next != nullptr) {
        return current->data;
    }
    else {
        return -1;
    }
}

void swap_nodes(Node* head, int index1, int index2) {
    if (head == nullptr || index1 < 0 || index2 < 0) {
        return;
    }

    Node* current1 = head;
    for (int i = 0; i < index1; i++) {
        current1 = current1->next;
    }

    Node* current2 = head;
    for (int i = 0; i < index2; i++) {
        current2 = current2->next;
    }

    int temp = current1->data;
    current1->data = current2->data;
    current2->data = temp;
}

int main() {
    time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start, end;
    nanoseconds result;
    int n;
    cout << "Enter the size of the list: ";
    cin >> n;

    Node* head = create_list(n);
    print_list(head);

    int choice;
    do {
        cout << endl;
        cout << "1. Insert at index" << endl;
        cout << "2. Insert at value" << endl;
        cout << "3. Delete at index" << endl;
        cout << "4. Delete at value" << endl;
        cout << "5. Get at index" << endl;
        cout << "6. Get at value" << endl;
        cout << "7. Swap nodes" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            int index;
            int value;
            cout << "Enter the index: ";
            cin >> index;
            cout << "Enter the value: ";
            cin >> value;
            start = steady_clock::now();
            insert_at_index(head, index, value);
            end = steady_clock::now();
            print_list(head);
            result = duration_cast<nanoseconds>(end - start);
            cout << "Time of creating the list: " << result.count() << " ns" << endl;
            break;
        case 2:
            cout << "Enter the value: ";
            cin >> value;
            start = steady_clock::now();
            insert_at_value(head, value);
            end = steady_clock::now();
            print_list(head);
            result = duration_cast<nanoseconds>(end - start);
            cout << "Time of creating the list: " << result.count() << " ns" << endl;
            break;
        case 3:
            cout << "Enter the index: ";
            cin >> index;
            start = steady_clock::now();
            delete_at_index(head, index);
            end = steady_clock::now();
            print_list(head);
            result = duration_cast<nanoseconds>(end - start);
            cout << "Time of creating the list: " << result.count() << " ns" << endl;
            break;
        case 4:
            cout << "Enter the value: ";
            cin >> value;
            start = steady_clock::now();
            delete_at_value(head, value);
            end = steady_clock::now();
            print_list(head);
            result = duration_cast<nanoseconds>(end - start);
            cout << "Time of creating the list: " << result.count() << " ns" << endl;
            break;
        case 5:
            cout << "Enter the index: ";
            cin >> index;
            start = steady_clock::now();
            cout << "The value at index " << index << " is: " << get_at_index(head, index) << endl;
            end = steady_clock::now();
            result = duration_cast<nanoseconds>(end - start);
            cout << "Time of creating the list: " << result.count() << " ns" << endl;
            break;
        case 6:
            cout << "Enter the value: ";
            cin >> value;
            start = steady_clock::now();
            cout << "The index of the value " << value << " is: " << get_at_value(head, value) << endl;
            end = steady_clock::now();
            result = duration_cast<nanoseconds>(end - start);
            cout << "Time of creating the list: " << result.count() << " ns" << endl;
            break;
        case 7:
            int index1;
            int index2;
            cout << "Enter the first index: ";
            cin >> index1;
            cout << "Enter the second index: ";
            cin >> index2;
            start = steady_clock::now();
            swap_nodes(head, index1, index2);
            end = steady_clock::now();
            print_list(head);
            result = duration_cast<nanoseconds>(end - start);
            cout << "Time of creating the list: " << result.count() << " ns" << endl;
            break;
        case 8:
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 8);

    return 0;
}
