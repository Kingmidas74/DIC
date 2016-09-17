#pragma once

/**
Parameters.hpp
Purpose: Struct for save parameters.

@author		Suleymanov D.
@version	0.0.0.1 9/17/2016
*/

#include <iostream>

namespace DIC
{
	using namespace std;

	struct Parameters
	{
		unsigned long long	CountOfTransactions;
		unsigned long long	CountOfCores;
		unsigned long long	CountOfThreads;
		unsigned long long	CountOfItems;
		unsigned long long	CountOfItemsets;
		unsigned long long	MinimumSupport;
		string				InputFilePath;
		string				OutputFilePath;
	};
}