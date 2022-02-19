#include <iostream>
using namespace std;


class Node{
    public:
    int data;
    Node* next;
};



int main(){

    Node* head = new Node();
    Node* one = new Node();
    Node* two = new Node();

    head->data = 1;

    head->next = one;
    head->next->data = 2;

    head->next->next = two;
    head->next->next->data = 3;

    cout << head->data << endl;
    cout << head->next->data << endl;
    cout << head->next->next->data << endl;

    return 0;
};
