#include "llrec.h"

using namespace std;

//*********************************************
// Provide your implementation of llpivot below
//*********************************************


void llpivot (Node*& head, Node*& smaller, Node*& larger, int pivot) {
    // base case
    if (head == nullptr) {
        smaller = nullptr;
        larger = nullptr;
        return;
    }

    // recursive step to go down the list
    llpivot(head->next, smaller, larger, pivot);

    Node* next = head->next;

    if (head->val <= pivot) {
        head->next = smaller;
        smaller = head;
    }
    else {
        head->next = larger;
        larger = head;
    }
    head = next;
}