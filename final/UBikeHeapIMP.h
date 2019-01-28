#ifndef UBikeHeapIMP_h
#define UBikeHeapIMP_h

#include "readonly/UBikeHeapADT.h"
#include<algorithm>

class UBikeHeapIMP : public UBikeHeapADT
{
public:
	int push(int id){
		while(id>1&&(*this)[id]->mileage<(*this)[id/2]->mileage){
			std::swap((*this)[id],(*this)[id/2]);
			std::swap((*this)[id]->heapIndex,(*this)[id/2]->heapIndex);
		}
		return id;
	}
	void pop(int id){
		int l,r,next_id;
		for(;;){
			l=id*2,r=id*2+1;
			if(l<=number&&r<=number){
				next_id=(*this)[l]<(*this)[r]?l:r;
			}else if(l<=number){
				next_id=l;
			}else if(r<=number){
				next_id=r;
			}else return;
			if((*this)[next_id]->mileage<(*this)[id]->mileage){
				std::swap((*this)[id],(*this)[next_id]);
				std::swap((*this)[id]->heapIndex,(*this)[next_id]->heapIndex);
			}else break;
		}
	}
	void addUBikePtr(UBike* ubptr){
		ubptr->heapIndex=++number;
		(*this)[number]=ubptr;
		push(number);
	}
	UBike* removeUBikePtr(int heapIndex){
		UBike* res=(*this)[heapIndex];
		std::swap((*this)[heapIndex],(*this)[number--]);
		(*this)[heapIndex]->heapIndex=heapIndex;
		heapIndex=push(heapIndex);
		pop(heapIndex);
		return res;
	}
};

#endif
