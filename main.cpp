#include "ft_container.hpp"
#include <vector>
#include <iostream>

int main()
{
    ft::vector<int> i2;
    ft::vector<int> i1;
    i1.push_back(1);
    i1.push_back(2);
    i1.push_back(3);
    

    i2.push_back(1);
    i2.push_back(2);
    i2.push_back(3);
    if(i2 )
    

    ft::vector<int>::iterator it = i.begin();
    ft::vector<int>::iterator it1 = i.end();
    for(;it != it1;it++)
        std::cout << *it << " ";
    std::cout << std::endl;
    // std::cout << "size : " << i.size() << std::endl;
    // std::cout << "capacity : " << i.capacity() << std::endl;
    // std::cout << "----------------\n";
    // i.push_back(1);
    // std::cout << "size : " << i.size() << std::endl;
    // std::cout << "capacity : " << i.capacity() << std::endl;
    // std::cout << "----------------\n";
    // i.push_back(1);
    // std::cout << "size : " << i.size() << std::endl;
    // std::cout << "capacity : " << i.capacity() << std::endl;
    // std::cout << "----------------\n";
    // i.push_back(1);
    // std::cout << "size : " << i.size() << std::endl;
    // std::cout << "capacity : " << i.capacity() << std::endl;
    // std::cout << "----------------\n";
    // i.push_back(1);
    // i.push_back(1);
    // i.push_back(1);
    // i.push_back(1);
    // i.push_back(1);
    // std::cout << "size : " << i.size() << std::endl;
    // std::cout << "capacity : " << i.capacity() << std::endl;
    // std::cout << "----------------\n";
    
    // std::vector<int> i();

    // std::vector<int>::iterator it = i.begin();
    // for (; it < i.end(); it++)
    // {
    //     std::cout << *it << std::endl;
    // }
    return 0;
}