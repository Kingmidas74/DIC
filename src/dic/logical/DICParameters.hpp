#pragma once

/**
DICParameters.hpp
Purpose: Parser of cmd parameters.

@author		Suleymanov D.
@version	0.0.0.1 9/17/2016
*/

#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

namespace DIC {
	using namespace std;

	class DICParameters
	{
	public:

		DICParameters(int argc, char* argv[])
		{
			allParameters.MinimumSupport = 2;
			allParameters.InputFilePath = "input.csv";
			allParameters.OutputFilePath = "output.csv";
			allParameters.CountOfThreads = 1;
			allParameters.CountOfCores = 1;
			allParameters.CountOfItems = 9;
			allParameters.CountOfTransactions = 15;
			allParameters.MPerThread = 5;

			_argc = argc - 1;
			for (auto i = 1; i < argc; i++)
			{
				_argv.push_back(string(argv[i]));
			}
		}

		~DICParameters()
		{

		}

		Parameters GetParameters()
		{
			parse();
			allParameters.CountOfItemsets = 100;//pow(2, allParameters.CountOfItems);
			allParameters.NeedTransactions = 5;//allParameters.CountOfCores*allParameters.CountOfThreads*allParameters.MPerThread;
			return allParameters;
		}

	private:

		int _argc;
		vector<string> _argv;
		Parameters allParameters;


		void parse()
		{
			for (auto i = 0; i < _argc; i = i + 2)
			{
				if (_argv[i].compare("-i") == 0) getInputFilPath(i + 1);
				if (_argv[i].compare("-o") == 0) getOutputFilPath(i + 1);
				if (_argv[i].compare("-c") == 0) getCountOfCores(i + 1);
				if (_argv[i].compare("-d") == 0) getCountOfItemsets(i + 1);
				if (_argv[i].compare("-m") == 0) getCountOfItems(i + 1);
				if (_argv[i].compare("-s") == 0) getMinimumSupport(i + 1);
				if (_argv[i].compare("-t") == 0) getCountOfThreads(i + 1);
			}
		}

		void getInputFilPath(int numberOfparameter)
		{
			if (&_argv[numberOfparameter])
			{
				fstream file;
				file.open(_argv[numberOfparameter]);
				if (!file.fail()) {
					allParameters.InputFilePath = _argv[numberOfparameter];
				}
				file.close();
			}
		}

		void getOutputFilPath(int numberOfparameter)
		{
			if (&_argv[numberOfparameter])
			{
				fstream file;
				file.open(_argv[numberOfparameter], fstream::out);
				if (!file.fail()) {
					allParameters.OutputFilePath = _argv[numberOfparameter];
				}
				file.close();
			}
		}

		void getCountOfItemsets(int numberOfparameter)
		{
			if (&_argv[numberOfparameter])
			{
				int val;
				istringstream iss(_argv[numberOfparameter]);
				if (iss >> val)
				{
					allParameters.CountOfTransactions = val;
				}
			}
		}

		void getCountOfThreads(int numberOfparameter)
		{
			if (&_argv[numberOfparameter])
			{
				int val;
				istringstream iss(_argv[numberOfparameter]);
				if (iss >> val)
				{
					allParameters.CountOfThreads = val;
				}
			}
		}

		void getCountOfCores(int numberOfparameter)
		{
			if (&_argv[numberOfparameter])
			{
				int val;
				istringstream iss(_argv[numberOfparameter]);
				if (iss >> val)
				{
					allParameters.CountOfCores = val;
				}
			}
		}

		void getCountOfItems(int numberOfparameter)
		{
			if (&_argv[numberOfparameter])
			{
				int val;
				istringstream iss(_argv[numberOfparameter]);
				if (iss >> val)
				{
					allParameters.CountOfItems = val;
				}
			}
		}


		void getMinimumSupport(int numberOfparameter)
		{
			if (&_argv[numberOfparameter])
			{
				  int val;
				istringstream iss(_argv[numberOfparameter]);
				if (iss >> val)
				{
					allParameters.MinimumSupport = val;
				}
			}
		}
	};
}
