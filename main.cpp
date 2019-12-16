#include <iostream>
#include "LinkedList.h"
int main() {

    LinkedList<int> list;

    // Add few items to the end of LinkedList
    list.insert(1);
    list.insert(2);
    list.insert(3);

    std::cout<< list<<std::endl;

    list.popFront();

    std::cout<< list<<std::endl;






    return 0;


    return 0;
}