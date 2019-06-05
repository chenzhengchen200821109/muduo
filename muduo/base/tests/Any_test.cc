#include <muduo/base/Any.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

using namespace muduo;

struct AClass
{
    void AFunction()
    {
        std::cout << "AClass:AFunction()" << std::endl;
    }
};

struct BClass
{
    void BFunction()
    {
        std::cout << "BClass::BFunction()" << std::endl;
    }
};

void printAny(muduo::Any& a)
{
    if (AClass* pAClass = muduo::any_cast<AClass>(&a))
    {
        pAClass->AFunction();
    }
    else if (BClass* pBClass = muduo::any_cast<BClass>(&a))
    {
        pBClass->BFunction();
    }
}

int main()
{
    //std::vector<muduo::Any> store_anything;

    //store_anything.push_back(AClass());
    //store_anything.push_back(BClass());

    //for_each(store_anything.begin(), store_anything.end(), printAny);
    //
    muduo::Any a1(100);
    muduo::Any a2(std::string("200"));

    std::string str = muduo::any_cast<std::string>(a2);
    std::cout << "str = " << str << std::endl;

    return 0;
}
