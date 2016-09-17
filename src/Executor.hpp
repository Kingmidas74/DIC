#pragma once


/**
Executor.h
Purpose: Incapsulation of workflow.

@author		Suleymanov D.
@version	0.0.0.1 9/17/2016
*/


#include <fstream>
#include <sstream>
#include <ctime>
#include <omp.h>

#include "Consts.hpp"
#include "Parameters.hpp"
#include "Itemsets.hpp"
#include "IndexContainer.hpp"
#include "DICAlgorithm.hpp"

namespace DIC {

	using namespace std;


	class Executor
	{

	public:

		Executor(DIC::Parameters* algorithmParameters)
		{
			AlgorithmParameters = algorithmParameters;
			Runtime = 0;
		}

		void FindResult()
		{
			auto data = IndexContainer<Itemsets>(AlgorithmParameters->CountOfItemsets);

			setDateTime();

			if (tryReadFile(data, AlgorithmParameters))
			{
				int start = omp_get_wtime();
				auto algorithm = DICAlgorithm(data, AlgorithmParameters);
				algorithm.GetResult();
				Runtime = (omp_get_wtime() - start);

				//WriteLog();
				//tryWriteFile(clustering->ResultMatrix);
			}
			else {
				exit(EXIT_FAILURE);
			}
		}

		virtual ~Executor()
		{

		}
	
	private:
		Parameters* AlgorithmParameters;
		double Runtime;
		string DateTimeNow;

		void WriteLog()
		{
			fstream log;
			log.open("log.csv", ios::out | ios::app);
			log <<
				DateTimeNow << ";" <<
				AlgorithmParameters->CountOfItemsets << ";" <<
				AlgorithmParameters->CountOfItems << ";" <<
				AlgorithmParameters->CountOfCores << ";" <<
				AlgorithmParameters->CountOfThreads << ";" <<
				AlgorithmParameters->CountOfTransactions << ";" <<
				AlgorithmParameters->MinimumSupport << ";" <<
				Runtime << endl;
		}

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
				item.K = 0;
				item.StopNo = 0;
				item.Support = 0;
				item.BitMask = bitset<BITSET_SIZE>(0);
				while (ss)
				{

					string str;
					unsigned long long p;
					if (!getline(ss, str, ';')) break;

					istringstream iss(str);


					if (iss >> p)
					{
						item.BitMask[p - 1] = 1;
					}

				}
				cout << "item " << row << "=" << item.BitMask << endl;
				data.Append(item);
				row++;
			}
			return true;
		}

		void tryWriteFile(IndexContainer<Itemsets>* data)
		{
			//fstream outfile(AlgorithmParameters->OutputFilePath, fstream::out);
		}

		void setDateTime()
		{
			/*time_t rawtime;
			struct tm * timeinfo;
			char buffer[80];

			time(&rawtime);
			timeinfo = localtime(&rawtime);

			strftime(buffer, 80, "%d-%m-%Y;%H:%M:%S", timeinfo);
			DateTimeNow = buffer;*/
		}
	};
}
