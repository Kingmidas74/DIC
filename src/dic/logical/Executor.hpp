#pragma once


/**
Executor.h
Purpose: Incapsulation of workflow.

@author		Suleymanov D.
@version	0.0.0.1 9/17/2016
*/

namespace DIC {

	using namespace std;


	class Executor
	{

	public:

		Executor(Parameters* algorithmParameters)
		{
			AlgorithmParameters = algorithmParameters;
			Runtime = 0;
		}

		void FindResult()
		{
			auto transactions = IndexContainer<bitset<BITSET_SIZE>>(AlgorithmParameters->CountOfItemsets);

			setDateTime();

			if (tryReadFile(transactions, AlgorithmParameters))
			{
				auto start = omp_get_wtime();
				auto algorithm = DICAlgorithm(transactions, AlgorithmParameters);
				algorithm.GetResult();

				Runtime = (omp_get_wtime() - start);

				//WriteLog();
				//tryWriteFile(clustering->ResultMatrix);
			}
			else {
				transactions.Clear();
				exit(EXIT_FAILURE);
			}
			transactions.Clear();
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

		bool tryReadFile(IndexContainer<bitset<BITSET_SIZE>> &data, Parameters* parameters)
		{
			fstream infile(parameters->InputFilePath);
			  int row = 0;
			while (row<parameters->CountOfTransactions && infile)
			{
				string s;
				if (!getline(infile, s)) break;

				istringstream ss(s);

				auto bitmask = bitset<BITSET_SIZE>();

				while (ss)
				{

					string str;
					  int p;
					if (!getline(ss, str, ';')) break;

					istringstream iss(str);

					if (iss >> p)
					{
						bitmask[p] = 1;
					}

				}
				data.Append(bitmask);
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
