#include "LL.h"
#include <iostream>

int main()
{
    LL<int> l1;
    LL<int>::Iterator it, it2, nil;

    for (int i = 0; i < 10; i++)
        l1.tailInsert(i + 1);

    LL<int> l2(l1);

    l2.tailInsert(20);

    l1.tailInsert(50);

    
    std::cout<<"\n\n\nl1:\n";
    for (it = l1.begin(); it != nil; it++)
        std::cout << *it << ", ";
    std::cout<<"\n\n\n";

    it = l1.begin();
    it2 = l1.end();
    it2--;

    l1.swapNodes(it,it2);

    std::cout<<"\n\n\nl1:\n";
    for (it = l1.begin(); it != nil; it++)
        std::cout << *it << ", ";

    return 0;
}