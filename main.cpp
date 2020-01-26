#include <iostream>
#include "LinkedList.cpp"

int main() {
   LinkedList* list = new LinkedList();
   list->add(40);
   list->add(2);
   list->add(23);
   list->add(14);
   list->add(5);
   list->add(6);
   list->shuffle(1);
   list->printList();
}
