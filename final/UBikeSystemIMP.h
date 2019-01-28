#ifndef UBikeSystemIMP_h
#define UBikeSystemIMP_h

#include "readonly/UBikeSystemADT.h"

class UBikeSystemIMP : public UBikeSystemADT
{
public:
    void InitDistTable (std::string MapFile)
    {
        priceTable.calcAllPairsShortestPath(MapFile);
    }
    void NewBike (std::string classType, std::string license,int mile, std::string station)
    {
        UBike * bike = new UBike;
        bike->isRented = false;
        bike->mileage = mile;
        bike->license = license;
        bike->station = station;
        bike->classType = classType;
        ubStations[station][classType].addUBikePtr(bike);
        ubHashTable.addUBikePtr(bike);
    }

    void JunkIt (std::string license)
    {
        UBike * ptr = ubHashTable.findUBikePtr(license,true);
		if( !ptr ) return ;
        ubStations[ptr->station][ptr->classType].removeUBikePtr(ptr->heapIndex);
        delete ptr;
    }

    void Rent (std::string classType, std::string station)
    {
        if( ubStations[station][classType].isEmpty() )
        {
            return ;
        }
        UBike * ptr = ubStations[station][classType].removeUBikePtr(1);
        ubStations[station]["Rented"].addUBikePtr(ptr);
        ptr->isRented = true;
    }

    void Return (std::string station, std::string license, int returnMile)
    {
        UBike * ptr = ubHashTable.findUBikePtr(license,false);
        if( !ptr || !ptr->isRented )
        {
            return ;
        }

        int diff = returnMile - ptr->mileage; //= returnMile ??
        net += priceTable.calcPrice(diff,ptr->classType,ptr->station,station);

        ptr->mileage += diff;
        ptr->isRented = false;
        
        ubStations[ptr->station]["Rented"].removeUBikePtr(ptr->heapIndex);
        //ptr->station = station; //??
        ubStations[ptr->station][ptr->classType].addUBikePtr(ptr);
    }

    void Trans (std::string station, std::string license)
    {
        UBike * ptr = ubHashTable.findUBikePtr(license,false);
        if( !ptr || ptr->isRented )
        {
            return ;
        }
        ubStations[ptr->station][ptr->classType].removeUBikePtr(ptr->heapIndex);
        ptr->station = station;
        ubStations[ptr->station][ptr->classType].addUBikePtr(ptr);
    }

    void ShutDown()
    {
        //?
    }
};

#endif
