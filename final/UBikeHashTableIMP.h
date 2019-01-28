#ifndef UBikeHashTableIMP_h
#define UBikeHashTableIMP_h

#include "readonly/UBikeHashTableADT.h"

#include <string>
#include <cctype>
class UBikeHashTableIMP : public UBikeHashTableADT
{
    int to_hval(int c)
    {
        if(std::isdigit(c))return c-'0';
        return 10+c-'A';
    }
    int hash(std::string s){
        long long val = to_hval(s.at(0));
        for(int i=1;i<=4;++i)
            val = val*29+to_hval(s.at(i));
        return (val>>5)&0xFF;
    }
public:
    void addUBikePtr(UBike* ubptr)
    {
        if( !ubptr )return ;
        //Same should insert double value?
        if( !findUBikePtr(ubptr->license,false) )
        {
            int index = hash(ubptr->license);
            at(index).push_front(ubptr);
        }
    }
    UBike* findUBikePtr(std::string license, bool toRemove)
    {
        int index = hash(license);
        UBike* ptr = nullptr;
        for(auto bike:at(index))
        {
            if( bike->license == license )
            {
                ptr = bike;
                break;
            }
        }

        if( toRemove && ptr )
        {
            at(index).remove(ptr);
        }

        return ptr;
    }
};

#endif
