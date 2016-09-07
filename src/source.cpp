#include <iostream>
#include <omp.h>
#include <ctime>
#include <bitset> 

using namespace std;


template <typename Type>
Type* allocateAlign(unsigned long long count, int length = 64) {
	return static_cast<Type*>(_mm_malloc(count*sizeof(Type), length));
}

template <typename Type>
void freeAlign(Type* pointer) {
	if (pointer) {
		_mm_free(pointer);
	}
}


struct ProductSet {
	size_t		 Support;
	size_t		 StopNo;
	size_t		 K;
	bitset<16>	 BitMask;
	short		 Type;
};

size_t* DashedCircle;
size_t* DashedBox;
size_t* SolidCircle;
size_t* SolidBox;

ProductSet* Products;

size_t DashedCircleCount=0;
size_t DashedBoxCount=0;
size_t SolidCircleCount=0;
size_t SolidBoxCount=0;

unsigned long long count=1000;

void fillDashedCircle()
{

}

bool dashedIsEmpty()
{
	return (DashedBoxCount+DashedCircleCount)==0;
}

bool checkBitMask(bitset<16> &ItemBitMask, bitset<16> &NoItemBitMask)
{
	return (ItemBitMask&NoItemBitMask)==ItemBitMask;
}

inline void CountSupport(size_t &stopNo, size_t &M) 
{
	size_t first=M*(stopNo-1);
	size_t last=M*stopNo-1;
	
	for(size_t i=first; i<=last;i++)
	{
		for(size_t j=0; j<DashedCircleCount; j++)
		{
			Products[DashedCircle[j]].StopNo++;
			if(checkBitMask(Products[DashedCircle[j]].BitMask, Products[DashedCircle[j]].BitMask))
			{
				Products[DashedCircle[j]].Support++;
			}
		}
		for(size_t j=0; j<DashedBoxCount; j++)
		{
			Products[DashedBox[j]].StopNo++;
			if(checkBitMask(Products[DashedBox[j]].BitMask, Products[DashedBox[j]].BitMask))
			{
				Products[DashedBox[j]].Support++;
			}
		}
	}
}

inline void GenerateCandidates(size_t &minsup) 
{
	ProductSet* Candidates = allocateAlign<ProductSet>(count);	
	size_t CandidatesCount=0;
	
	size_t* Retired = allocateAlign<size_t>(count);
	size_t RetiredCount=0;
	
	for(size_t i=0; i<DashedCircleCount; i++)
	{
			if(Products[DashedCircle[i]].Support>=minsup)
			{
				for(size_t j=0; j<DashedBoxCount; j++)
				{
					if(Products[DashedCircle[i]].K==Products[DashedBox[j]].K)
					{
						ProductSet candidate;
						candidate.BitMask=Products[DashedCircle[i]].BitMask | Products[DashedBox[j]].BitMask;
						candidate.K=Products[DashedCircle[i]].K+1;
						candidate.Support=0;
						candidate.StopNo=0;
						Candidates[CandidatesCount]=candidate;
						CandidatesCount++;
					}
				}
				for(size_t j=0; j<SolidBoxCount; j++) 
				{
					if(Products[DashedCircle[i]].K==Products[SolidBox[j]].K)
					{
						ProductSet candidate;
						candidate.BitMask=Products[DashedCircle[i]].BitMask | Products[SolidBox[j]].BitMask;
						candidate.K=Products[DashedCircle[i]].K+1;
						candidate.Support=0;
						candidate.StopNo=0;
						Candidates[CandidatesCount]=candidate;
						CandidatesCount++;
					}
				}
				//Retired[RetiredCount]=Products[DashedCircle[i]];
			}
		}
}

inline void CheckPassCompletion(size_t &stopNo) 
{
	size_t* Retired = allocateAlign<size_t>(count);
	size_t RetiredCount=0;
	
	for(size_t j=0; j<DashedCircleCount; j++)
	{
		if(Products[DashedCircle[j]].StopNo==stopNo)
		{
			Retired[RetiredCount]=DashedCircle[j];
			RetiredCount++;
		}
	}
	for(size_t j=0; j<DashedBoxCount; j++)
	{
		if(Products[DashedBox[j]].StopNo==stopNo)
		{
			Retired[RetiredCount]=DashedBox[j];
			RetiredCount++;
		}
	}
	
	for(size_t i=0; i<RetiredCount; i++)
	{
		if(Products[Retired[i]].Type==1) 
		{
			Products[Retired[i]].Type=3;
		}
		if(Products[Retired[i]].Type==2) 
		{
			Products[Retired[i]].Type=4;
		}
	}
	freeAlign(Retired);
}



int main(int argc, char *argv[])
{
	/*
	Init	
	*/
	
	DashedCircle = allocateAlign<size_t>(count);
	DashedBox = allocateAlign<size_t>(count);
	SolidCircle = allocateAlign<size_t>(count);
	SolidBox = allocateAlign<size_t>(count);
	
	Products = allocateAlign<ProductSet>(count);
	/*Finish init*/

	fillDashedCircle();
	
	size_t MPerThread=100;
	size_t C=1;
	size_t h=1;
	size_t n=1000;
	size_t minsup=2;

	size_t stopNo=0;
	size_t M = C*h*MPerThread;
	
	while(!dashedIsEmpty())
	{
		stopNo++;
		if(stopNo>n/M)
		{
			stopNo=1;
		}
		
		
		CountSupport(stopNo, M);
		GenerateCandidates(minsup);
		CheckPassCompletion(stopNo);
		
	}
	
		
	srand(time(nullptr));
	
	return EXIT_SUCCESS;
}


