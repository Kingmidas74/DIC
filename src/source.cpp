#include <iostream>
#include <omp.h>
#include <ctime>
#include <bitset> 

using namespace std;

template <typename Type>
Type* allocateAlign(long long count, int length = 64) {
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
};

ProductSet* DashedCircle;
ProductSet* DashedBox;
ProductSet* SolidCircle;
ProductSet* SolidBox;

size_t DashedCircleCount=0;
size_t DashedBoxCount=0;
size_t SolidCircleCount=0;
size_t SolidBoxCount=0;

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

int main(int argc, char *argv[])
{
	/*
	Init	
	*/
	long long count=1000;
	DashedCircle = allocateAlign<ProductSet>(count);
	DashedBox = allocateAlign<ProductSet>(count);
	SolidCircle = allocateAlign<ProductSet>(count);
	SolidBox = allocateAlign<ProductSet>(count);
	/*Finish init*/

	fillDashedCircle();
	
	size_t MPerThread=100;
	size_t C=1;
	size_t h=1;
	size_t n=1000;
	size_t minsup=2;

	size_t stopNo=0;
	size_t M = C*h*MPerThread;
	
	while(!dashedIsEmpty)
	{
		stopNo++;
		if(stopNo>n/M)
		{
			stopNo=1;
		}

		size_t first=M*(stopNo-1);
		size_t last=M*stopNo-1;
		
		for(size_t i=first; i<=last;i++)
		{
			for(size_t j=0; j<DashedCircleCount; j++)
			{
				DashedCircle[i].StopNo++;
				if(checkBitMask(DashedCircle[i].BitMask, DashedCircle[i].BitMask))
				{
					DashedCircle[i].Support++;
				}
			}
			for(size_t j=0; j<DashedBoxCount; j++)
			{
				DashedBox[i].StopNo++;
				if(checkBitMask(DashedBox[i].BitMask, DashedBox[i].BitMask))
				{
					DashedBox[i].Support++;
				}
			}
		}

	
		ProductSet* candidate = allocateAlign<ProductSet>(1);

		for(size_t i=0; i<DashedCircleCount; i++)
		{
			if(DashedCircle[i].Support>minsup)
			{
				for(size_t j=0; j<DashedBoxCount; j++)
				{
					if(DashedCircle[i].K==DashedBox[j].K)
					{
						candidate[0].BitMask=DashedCircle[i].BitMask | DashedBox[j].BitMask;
						candidate[0].K=DashedCircle[i].K;
						candidate[0].Support=0;
						//DashedCircle.insert(candidate);
					}
				}
			}

		}
		
		
	}
	
		
	srand(time(nullptr));
	
	return EXIT_SUCCESS;
}


