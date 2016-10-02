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
		  int	CountOfTransactions;	//�� ������� �����
		  int	CountOfCores;
		  int	CountOfThreads;
		  int	CountOfItems;   //����� �������
		  int	CountOfItemsets;  //2^����
		  int	MinimumSupport;
		string				InputFilePath;
		string				OutputFilePath;
		  int	NeedTransactions;
		  int	MPerThread;
	};
}