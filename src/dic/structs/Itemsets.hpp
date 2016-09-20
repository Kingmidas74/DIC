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
	struct Itemsets {
		unsigned long long		 Support;
		unsigned long long		 StopNo;
		unsigned long long		 K;
		bitset<BITSET_SIZE>		 BitMask;
		unsigned long long		 Number;
	};

}