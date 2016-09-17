#pragma once

#include <bitset>

namespace DIC
{

	struct Itemsets {
		unsigned long long		 Support;
		unsigned long long		 StopNo;
		unsigned long long		 K;
		bitset<12>	 BitMask;
	};

}