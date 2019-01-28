#ifndef PriceTableIMP_h
#define PriceTableIMP_h

#include "readonly/PriceTableADT.h"

#include<fstream>
#include<string>
#include<sstream>
#include<set>
#include<climits>
#include<algorithm>

using namespace std;
class PriceTableIMP : public PriceTableADT
{
public:
    void calcAllPairsShortestPath(std::string mapFile)
    {
        std::ifstream ss(mapFile);
        std::string s,t;
        int dist;
        std::set<std::string> v;
		for(auto p:distTable)
			v.insert(p.first);
		for(auto S:v)
        {
            for(auto E:v)
            {
				if( S==E )distTable[S][E] = 0;
				else distTable[S][E] = distTable[E][S] = INT_MAX/2;
			}
		}
        while(ss>>s>>t>>dist){
            v.insert(s);
            v.insert(t);
            distTable[s][t]=distTable[t][s]=dist;
        }
		ss.close();
        for(auto K:v)
            for(auto I:v)
                for(auto J:v)
                    if( distTable[I][J] > distTable[I][K]+distTable[K][J] )
                        distTable[I][J] = distTable[I][K]+distTable[K][J];
    }

    int calcPrice(int milageDiff, std::string bClass, std::string from, std::string toStation)
    {
        int dist = distTable[from][toStation];

        int discount_d = std::min(milageDiff,dist);
        int ori_d = milageDiff - discount_d;

        int dp,op;
        if( bClass == "Electric" )dp=25,op=40;
        else if( bClass == "Lady" )dp=20,op=30;
        else if( bClass == "Road" )dp=10,op=20;
        else dp=15,op=25;//Hybrid
        return milageDiff * ( milageDiff<=dist?dp:op );
    }

    // Add your code here
};

#endif
