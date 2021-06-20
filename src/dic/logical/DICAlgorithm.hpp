#pragma once

/**
DICAlgorithm.hpp
Purpose: Base class for algorithm.

@author		Suleymanov D.
@version	0.0.0.1 9/17/2016
*/


namespace DIC
{
	class DICAlgorithm
	{

	private:

#pragma region Fields

		IndexContainer<int>	 dashedCircle;
		IndexContainer<int>	 dashedBox;
		IndexContainer<int>	 solidCircle;
		IndexContainer<int>	 solidBox;
		IndexContainer<int>	 transferIndexes;
		IndexContainer<Itemsets> AllItems;


		IndexContainer<bitset<BITSET_SIZE>> Transactions;
		Parameters* DICparameters;

#pragma endregion

#pragma region AncillaryFunction

		inline void fillDashedCircle()
		{
			for (int i = 0; i<=DICparameters->CountOfItems; i++)
			{
				dashedCircle.Append(i);
			}
		}

		inline void initFirstItemsets()
		{
			for(int i=0; i<=DICparameters->CountOfItems; i++)
			{
				Itemsets item = Itemsets(i);
				AllItems.Append(item);
			}
		}

		inline bool dashedIsNotEmpty()
		{
			return (dashedBox.Length + dashedCircle.Length) > 0;
		}

		inline void transferBetweenContainers(IndexContainer<int> &FromContainer, IndexContainer<int> &ToContainer, IndexContainer<int> &WhichContainer)
		{
			if (WhichContainer.Length == 0) return;
			int zero = 0;

			printContainerElements(FromContainer, "from");
			printContainerElements(ToContainer, "to");
			printContainerElements(WhichContainer, "which");

			for (auto &index:WhichContainer)
			{
				ToContainer.Append(FromContainer[index]);
			}

			for (int i = WhichContainer.Length - 1; i>0; i--)
			{
				FromContainer.RemoveByIndex(WhichContainer[i]);
			}
			FromContainer.RemoveByIndex(WhichContainer[zero]);
		}

		void printAllElements()
		{
			cout << "PRINT ALL ITEMS" << endl;
			for(int i=0; i<AllItems.Length;i++)
			{
				cout << "A[" << i << "]=" << AllItems[i].BitMask.to_string() << " and K=" << AllItems[i].K << " and Support=" << AllItems[i].Support << endl;

			}
		}

		inline void printContainerElements(IndexContainer<int> &container, string title)
		{
			cout << "PRINT CONTAINER " << title << " with size=" << container.Length << endl;
			if (container.Length == 0)
			{
				return;
			}
			for (auto &index:container)
			{
				cout << title << "[" << index << "]=" << index << " and AI[" << index << "]=" << AllItems[index].BitMask.to_string() << " and support=" << AllItems[index].Support << " and stopNo=" << AllItems[index].StopNo << " and K=" << AllItems[index].K << endl;
			}
		}



#pragma endregion

#pragma region CountSupport

		inline void CountSupport(int &stopNo)
		{
			IncrementStopNoInContainer(dashedCircle);
			IncrementStopNoInContainer(dashedBox);

			int first = DICparameters->NeedTransactions*(stopNo - 1);
			int last = DICparameters->NeedTransactions*stopNo - 1;

			for (int i = first; i <= last;i++)
			{
				CountSupportInContainer(dashedCircle, Transactions[i]);
				CountSupportInContainer(dashedBox, Transactions[i]);
			}
		}

		inline void IncrementStopNoInContainer(IndexContainer<int> &container)
		{
			for (auto &index:container)
			{
				AllItems[index].StopNo++;
			}
		}

		inline void CountSupportInContainer(IndexContainer<int> & container, bitset<BITSET_SIZE> & transaction)
		{
			for(auto &index:container)
			{
				AllItems[index].CountNewSupport(transaction);
			}
		}

#pragma endregion

#pragma region GenerateCandidates

		void GenerateCandidatesFromContainer(Itemsets & item, IndexContainer<int> &container)
		{
			for (auto &index:container)
			{
				auto currentItem = AllItems[index];
				if (item.K == currentItem.K)
				{
					auto candidate = Itemsets(item, currentItem);
					AllItems.Append(candidate);
				}
			}
		}

		inline void GenerateCandidates()
		{
			transferIndexes.ReUse();
			int PreviousAllItemsSize = AllItems.Length;
			for (int i = 0; i<dashedCircle.Length; i++)
			{
				if (AllItems[dashedCircle[i]].Support >= DICparameters->MinimumSupport)
				{
					transferIndexes.Append(i);
					GenerateCandidatesFromContainer(AllItems[dashedCircle[i]], dashedBox);
					GenerateCandidatesFromContainer(AllItems[dashedCircle[i]], solidBox);

				}
			}

			transferBetweenContainers(dashedCircle, dashedBox, transferIndexes);

			for (int i = PreviousAllItemsSize; i<AllItems.Length;i++)
			{
				dashedCircle.Append(i);
			}
		}

#pragma endregion

#pragma region CheckPassCompletion

		inline void CheckPassCompletion(  int &stopNo)
		{
			CheckPassCompletionInContainer(dashedCircle, solidCircle, stopNo);
			CheckPassCompletionInContainer(dashedBox, solidBox, stopNo);
		}

		inline void CheckPassCompletionInContainer(IndexContainer<  int> & SourceContainer, IndexContainer<  int> & TargetContainer,   int &stopNo)
		{
			transferIndexes.ReUse();
			for (int j = 0; j<SourceContainer.Length; j++)
			{
				if (AllItems[SourceContainer[j]].StopNo == stopNo)
				{
					transferIndexes.Append(j);
				}
			}
			transferBetweenContainers(SourceContainer, TargetContainer, transferIndexes);
		}

#pragma endregion

	public:

		DICAlgorithm(IndexContainer<bitset<BITSET_SIZE>> &transactions, Parameters* parameters)
		{
			DICparameters	= parameters;
			Transactions	= transactions;

			AllItems		=  IndexContainer<Itemsets>(DICparameters->CountOfItems);
			dashedCircle	=  IndexContainer<int>(DICparameters->CountOfItemsets);
			dashedBox		=  IndexContainer<int>(DICparameters->CountOfItemsets);
			solidCircle		=  IndexContainer<int>(DICparameters->CountOfItemsets);
			solidBox		=  IndexContainer<int>(DICparameters->CountOfItemsets);

			transferIndexes =  IndexContainer<int>(DICparameters->CountOfItemsets);
		}

		~DICAlgorithm()
		{
			dashedBox.Clear();
			dashedCircle.Clear();
			solidBox.Clear();
			solidCircle.Clear();
			AllItems.Clear();
			transferIndexes.Clear();
		}

		void GetResult()
		{
			initFirstItemsets();

			fillDashedCircle();

			int stopNo = 0;
			int step = 0;

			while(dashedIsNotEmpty() && step<=1)
			{
				stopNo++;
				step++;
				if (stopNo>DICparameters->CountOfTransactions / DICparameters->NeedTransactions)
				{
					stopNo = 1;
				}

				cout << "#############COUNT SUPPORT###########" << endl << endl;
				CountSupport(stopNo);
				printContainerElements(dashedCircle, "dashedCircle");
				printContainerElements(dashedBox, "dashedBox");
				printContainerElements(solidCircle, "solidCircle");
				printContainerElements(solidBox, "solidBox");
				cout << "#############END COUNT SUPPORT###########" << endl << endl;

				cout << "#############GENERATE CANDIDATES###########" << endl << endl;
				GenerateCandidates();
				printContainerElements(dashedCircle, "dashedCircle");
				printContainerElements(dashedBox, "dashedBox");
				printContainerElements(solidCircle, "solidCircle");
				printContainerElements(solidBox, "solidBox");
				cout << "#############END GENERATE CANDIDATES###########" << endl << endl;


				cout << "#############CHECK PASS COMPLITION###########" << endl << endl;
				CheckPassCompletion(stopNo);
				printContainerElements(dashedCircle, "dashedCircle");
				printContainerElements(dashedBox, "dashedBox");
				printContainerElements(solidCircle, "solidCircle");
				printContainerElements(solidBox, "solidBox");
				cout << "#############END CHECK PASS COMPLITION###########" << endl << endl;
			}
			cout << "all" << endl;
		}

	};
}