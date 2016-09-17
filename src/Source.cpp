#include <iostream>
#include <omp.h>
#include <ctime>

#include "DIC.h"
#include "DICParameters.hpp"

using namespace std;


bool tryReadFile(IndexContainer<Itemsets> &data, Parameters* parameters)
{
	fstream infile(parameters->InputFilePath);
	unsigned long long row = 0;
	while (row<parameters->CountOfTransactions && infile)
	{
		string s;
		if (!getline(infile, s)) break;

		istringstream ss(s);
		
		unsigned long long total = 0;
		Itemsets item;
		item.BitMask = bitset<12>(0);
		item.K = 0;
		item.StopNo = 0;
		item.Support = 0;
		item.BitMask = bitset<12>(0);
		while (ss)
		{

			string str;
			unsigned long long p;
			if (!getline(ss, str, ';')) break;

			istringstream iss(str);


			if (iss >> p)
			{
				item.BitMask[p-1]=1;
			}
						
		}
		cout << "item " << row << "="  << item.BitMask<<endl;
		data.Append(item);
		row++;
	}
	return true;
}

void execute(Parameters* parameters)
{
	auto data = IndexContainer<Itemsets>(parameters->CountOfItemsets);

	//setDateTime();

	if (tryReadFile(data, parameters))
	{
		int start = omp_get_wtime();
		auto algorithm = DICAlgorithm(data, parameters);
		algorithm.GetResult();
		//Runtime = (omp_get_wtime() - start);

		//WriteLog();
		//tryWriteFile(clustering->ResultMatrix);
	}
	else {
		exit(EXIT_FAILURE);
	}
}




int main(int argc, char *argv[])
{
	srand(time(nullptr));
	Parameters parameters;
	DICParameters parser = DICParameters(argc, argv);
	parameters = parser.GetParameters();
	execute(&parameters);
	return EXIT_SUCCESS;
}
