#pragma once

/**
Itemsets.hpp
Purpose: Struct for save itemsets.

@author		Suleymanov D.
@version	0.0.0.1 9/17/2016
*/

#include <bitset>

namespace DIC
{
	class Itemsets {
		public:
			int					Support;
			int					StopNo;
			int					K;
			bitset<BITSET_SIZE>	BitMask;

			Itemsets()
			{
				this->BitMask = bitset<BITSET_SIZE>(0);
				this->BitMask[0] = 1;
				this->K = 1;
				this->Support = 0;
				this->StopNo = 0;
			}

			Itemsets(int & number)
			{
				this->BitMask = bitset<BITSET_SIZE>(0);
				this->BitMask[number] = 1;
				this->K = 1;
				this->Support = 0;
				this->StopNo = 0;
			}

			Itemsets(const Itemsets & daddy, const Itemsets & mother)
			{
				this->BitMask = (daddy.BitMask | mother.BitMask);
				this->K = daddy.K + 1;
				this->Support = 0;
				this->StopNo = 0;
				cout << "Create new candidate: " << BitMask.to_string() << " with k=" << K << endl;
			}

			bool CheckBitmask(const bitset<BITSET_SIZE> & bitmask)
			{
				return ((BitMask&bitmask) == BitMask);
			}

			void CountNewSupport(const bitset<BITSET_SIZE> & bitmask)
			{
				StopNo++;
				if(CheckBitmask(bitmask))
				{
					Support++;
				}
			}
	};

}