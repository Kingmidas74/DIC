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
		
		IndexContainer<unsigned long long>	 dashedCircle;
		IndexContainer<unsigned long long>	 dashedBox;
		IndexContainer<unsigned long long>	 solidCircle;
		IndexContainer<unsigned long long>	 solidBox;
		IndexContainer<Itemsets>			 AllItems;

		IndexContainer<bitset<BITSET_SIZE>> Transactions;

		Parameters* DICparameters;

#pragma endregion

#pragma region AncillaryFunction
		
		inline void fillDashedCircle()
		{
			Itemsets zero_itemset;
			zero_itemset.K = 0;
			zero_itemset.Number = 0;
			zero_itemset.StopNo = 0;
			zero_itemset.Support = 0;
			zero_itemset.BitMask = bitset<BITSET_SIZE>(0);
			zero_itemset.BitMask[0] = 1;
			AllItems.Append(zero_itemset);
			unsigned long long zero = 0;
			dashedCircle.Append(zero);
			
			for (unsigned long long i = 0; i<=DICparameters->CountOfItems; i++)
			{
				Itemsets itemset;
				itemset.K = 0;
				itemset.Number = i;
				itemset.StopNo = 0;
				itemset.Support = 0;
				itemset.BitMask = bitset<BITSET_SIZE>(0);
				itemset.BitMask[i] = 1;
				if (i > 0) {
					AllItems.Append(itemset);
					dashedCircle.Append(i);
				}
			}
			
			/*dashedCircle.RemoveByIndex(zero);
			AllItems.RemoveByIndex(zero);*/

		}

		inline bool dashedIsNotEmpty()
		{
			return (dashedBox.Size + dashedCircle.Size) > 1;
		}

		inline bool checkBitMask(bitset<BITSET_SIZE> &ItemsetsBitMask, bitset<BITSET_SIZE> &TransactionBitMask) const
		{	
			return (ItemsetsBitMask&TransactionBitMask) == ItemsetsBitMask;
		}

		inline void transferBetweenContainers(IndexContainer<unsigned long long> &FromContainer, IndexContainer<unsigned long long> &ToContainer, IndexContainer<unsigned long long> &WhichContainer)
		{
			if(WhichContainer.Size==0) return;
			//printContainerElements(FromContainer, "from");
			//printContainerElements(ToContainer, "to");
			//printContainerElements(WhichContainer, "which");
			for(unsigned long long i=0; i<WhichContainer.Size; i++)
			{
				//cout << "transfer " << WhichContainer[i] << " element" <<"___"<<i<<"___"<< endl;
				ToContainer.Append(FromContainer[WhichContainer[i]]);
			}
			//printContainerElements(FromContainer, "from");
			//printContainerElements(ToContainer, "to");
			//printContainerElements(WhichContainer, "which");
			
			bool flag=false;
			for (unsigned long long i = WhichContainer.Size-1; (i>=0 && flag==false); i--)
			{
				//cout << "remove " << WhichContainer[i] << " element" << "___" << i << "___" << endl;
				FromContainer.RemoveByIndex(WhichContainer[i]);
				//printContainerElements(FromContainer, "from");
				//printContainerElements(WhichContainer, "which");
				flag = i == 0;
			}
			//FromContainer.RemoveByIndex(FromContainer.Size - 1);
			//printContainerElements(FromContainer, "from");
			//FromContainer.RemoveByIndex(FromContainer.Size - 1);
		}

		inline void printContainerElements(IndexContainer<unsigned long long> &container, char* title)
		{
			cout << "PRINT CONTAINER " << title<<" with size="<<container.Size<<endl;
			if(container.Size==0) return;
			for(unsigned long long i=0; i<container.Size; i++)
			{
				cout << title << "[" << i << "]=" << container[i] <<" and AI[" << container[i] <<"]="<<AllItems[container[i]].Number<< endl;
			}
		}

		unsigned long long BitsetToNumber(bitset<BITSET_SIZE> & bitset)
		{
			unsigned long long restult = 0;
			for(unsigned long long i=0; i<BITSET_SIZE; i++)
			{
				if(bitset[i]==1)
				{
					restult = (restult * 10) + i;
				}
			}
			return restult;
		}

#pragma endregion

#pragma region CountSupport

		inline void CountSupport(unsigned long long &stopNo)
		{
			auto first = DICparameters->NeedTransactions*(stopNo - 1);
			auto last = DICparameters->NeedTransactions*stopNo - 1;
			cout << first << ":" << last << endl;
			for (unsigned long long i = first; i <= last;i++)
			{
				cout << "Current transaction is = " << Transactions[i].to_string() << endl;
				CountSupportInContainer(dashedCircle, i);
				CountSupportInContainer(dashedBox, i);
			}

			for(unsigned long long i=0; i<AllItems.Size;i++)
			{
				cout << "AllItems[" << i << "]=" << AllItems[i].Number << " and support=" << AllItems[i].Support<<endl;
			}
		}

		inline void CountSupportInContainer(IndexContainer<unsigned long long>& container, unsigned long long itemInTransaction)
		{
			cout << "I am here " << itemInTransaction << endl;
			for (unsigned long long j = 0; j<container.Size; j++)
			{
				AllItems[container[j]].StopNo++;
				cout << "Check BM for " << Transactions[itemInTransaction].to_string() << " and " << AllItems[container[j]].BitMask << endl;
				if (checkBitMask(AllItems[container[j]].BitMask, Transactions[itemInTransaction]) && AllItems[container[j]].Number>0)
				{
					AllItems[container[j]].Support++;
					cout << "itemset " << AllItems[container[j]].Number << " will support" << endl;
				}
			}
		}

#pragma endregion

#pragma region GenerateCandidates

		void GenerateCandidatesFromContainer(unsigned long long itemInTransaction, IndexContainer<unsigned long long> &container)
		{
			//cout << "container size = " << container.Size << endl;
			for (unsigned long long j = 0; j<container.Size; j++)
			{
				if (AllItems[itemInTransaction].K == AllItems[container[j]].K && AllItems[container[j]].Number>0)
				{
					cout << "GENERATE CANDIBOBR!" << endl;
					Itemsets candidate;
					candidate.BitMask = AllItems[itemInTransaction].BitMask | AllItems[container[j]].BitMask;
					candidate.K = AllItems[itemInTransaction].K + 1;
					candidate.Support = 0;
					candidate.StopNo = 0;
					candidate.Number = BitsetToNumber(candidate.BitMask);
					cout << "CANDIBOBR IS " << candidate.Number << " and " << candidate.BitMask.to_string() << endl;
					AllItems.Append(candidate);
				//	cout << "candidate " << candidate.Number << " with bitmask " << candidate.BitMask.to_string() << " was added" << endl;
				}
			}
		}

		inline void GenerateCandidates()
		{
			auto transfer = IndexContainer<unsigned long long>(DICparameters->CountOfItemsets);
			auto PreviousItemsetSize = AllItems.Size;
			
			//printContainerElements(dashedCircle, "dashedCircle");
			
			for (unsigned long long i = 0; i<dashedCircle.Size; i++)
			{
				/*cout << "DC[" << i << "]="
					<< dashedCircle[i]
					<< " and AI["
					<< dashedCircle[i]
					<< "]="
					<< AllItems[dashedCircle[i]].BitMask.to_string()
					<< " and support=" 
					<< AllItems[dashedCircle[i]].Support << endl;*/
				if (AllItems[dashedCircle[i]].Support >= DICparameters->MinimumSupport)
				{
					transfer.Append(i);
					//cout << "add to retired " << dashedCircle[i] << endl;
					GenerateCandidatesFromContainer(dashedCircle[i], solidBox);
					GenerateCandidatesFromContainer(dashedCircle[i], dashedBox);					
					
				}
			}
			//printContainerElements(transfer, "transfer");
			transferBetweenContainers(dashedCircle, dashedBox, transfer);
			
			for (unsigned long long i = PreviousItemsetSize; i<AllItems.Size; i++)
			{
				//cout << "added to DC" << endl;
				if (AllItems[i].Number > 0)
				{
					dashedCircle.Append(i);
				}
			}
			transfer.Clean();
		}

#pragma endregion 

#pragma region CheckPassCompletion

		inline void CheckPassCompletion(unsigned long long &stopNo)
		{
			//cout << "GLOBAL STOP NO = " << stopNo<<endl;
			CheckPassCompletionInContainer(dashedCircle, solidCircle, stopNo, true);
			CheckPassCompletionInContainer(dashedBox, solidBox, stopNo);
		}

		inline void CheckPassCompletionInContainer(IndexContainer<unsigned long long> & SourceContainer, IndexContainer<unsigned long long> & TargetContainer, unsigned long long &stopNo, bool fakeElement=false)
		{
			auto transfer = IndexContainer<unsigned long long>(DICparameters->CountOfItemsets);
			for (unsigned long long j = (0+fakeElement); j<SourceContainer.Size; j++)
			{
				if (AllItems[SourceContainer[j]].StopNo == stopNo)
				{
					//cout << "added to transfer " << AllItems[SourceContainer[j]].Number << endl;
					transfer.Append(j);
				}
			}
			//cout << "Start transfer " << endl;
			transferBetweenContainers(SourceContainer, TargetContainer, transfer);
			transfer.Clean();
		}

#pragma endregion 

	public:

		DICAlgorithm(IndexContainer<bitset<BITSET_SIZE>> &transactions, Parameters* parameters)
		{
			DICparameters	= parameters;
			Transactions	= transactions;
			
			AllItems		=  IndexContainer<Itemsets>(DICparameters->CountOfItems);
			dashedCircle	=  IndexContainer<unsigned long long>(DICparameters->CountOfItemsets);
			dashedBox		=  IndexContainer<unsigned long long>(DICparameters->CountOfItemsets);
			solidCircle		=  IndexContainer<unsigned long long>(DICparameters->CountOfItemsets);
			solidBox		=  IndexContainer<unsigned long long>(DICparameters->CountOfItemsets);			
		}

		~DICAlgorithm()
		{
			dashedBox.Clean();
			dashedCircle.Clean();
			solidBox.Clean();
			solidCircle.Clean();
			AllItems.Clean();
		}

		void GetResult()
		{
			
			unsigned long long stopNo = 0;
			
			fillDashedCircle();
			printContainerElements(dashedCircle, "dashedCircle");
			

			unsigned long long step = 0;
			
			while (dashedIsNotEmpty() && step<2)
			{
				cout << endl<<endl << "*****************STEP "<<step<<"************" << endl<<endl;
				
				step++;
				stopNo++;
				if (stopNo>DICparameters->CountOfTransactions / DICparameters->NeedTransactions)
				{
					stopNo = 1;
				}
				cout << "StopNo=" << stopNo << endl;
				
				cout << "#############COUNT SUPPORT###########" << endl << endl;
				CountSupport(stopNo);
				/*printContainerElements(dashedCircle, "dashedCircle");
				printContainerElements(dashedBox, "dashedBox");
				printContainerElements(solidCircle, "solidCircle");
				printContainerElements(solidBox, "solidBox");*/
				cout << "#############END COUNT SUPPORT###########" << endl << endl;
				
				cout << "#############GENERATE CANDIDATES###########" << endl << endl;
				GenerateCandidates();
				/*printContainerElements(dashedCircle, "dashedCircle");
				printContainerElements(dashedBox, "dashedBox");
				printContainerElements(solidCircle, "solidCircle");
				printContainerElements(solidBox, "solidBox");*/
				cout << "#############END GENERATE CANDIDATES###########" << endl << endl;
				
				
				cout << "#############CHECK PASS COMPLITION###########" << endl << endl;
				CheckPassCompletion(stopNo);
				printContainerElements(dashedCircle, "dashedCircle");
				printContainerElements(dashedBox, "dashedBox");
				printContainerElements(solidCircle, "solidCircle");
				printContainerElements(solidBox, "solidBox");
				cout << "#############END CHECK PASS COMPLITION###########" << endl << endl;

				
				
				
			}
			cout << "SBS=" << solidBox.Size << endl;
			cout << "step is " << step << endl;
		}
	};
}
