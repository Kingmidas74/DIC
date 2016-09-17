#pragma once

#include "Parameters.hpp"


namespace DIC
{
	class DICAlgorithm
	{

	private:

		IndexContainer<unsigned long long> dashedCircle;
		IndexContainer<unsigned long long> dashedBox;
		IndexContainer<unsigned long long> solidCircle;
		IndexContainer<unsigned long long> solidBox;

		IndexContainer<Itemsets> AllItems;

		Parameters* DICparameters;

		inline void fillDashedCircle()
		{
			for (unsigned long long i = 1; i<=DICparameters->CountOfItems; i++)
			{
				dashedCircle.Append(i);
			}
		}

		inline bool dashedIsEmpty()
		{
			return (dashedBox.Size + dashedCircle.Size) == 0;
		}

		inline bool checkBitMask(bitset<12> &ItemBitMask, bitset<12> &NoItemBitMask) const
		{
			return (ItemBitMask&NoItemBitMask) == ItemBitMask;
		}

		inline void CountSupport(unsigned long long &stopNo, unsigned long long &M)
		{
			auto first = M*(stopNo - 1);
			auto last = M*stopNo - 1;

			for (auto i = first; i <= last;i++)
			{
				CountSupportInContainer(dashedCircle);
				CountSupportInContainer(dashedBox);
			}
		}

		inline void CountSupportInContainer(IndexContainer<unsigned long long>& container)
		{
			for (unsigned long long j = 0; j<container.Size; j++)
			{
				if(container[j] != NULL) continue;				
				auto currentItem = AllItems[container[j]];
				currentItem.StopNo++;
				if (checkBitMask(currentItem.BitMask, currentItem.BitMask))
				{
					currentItem.Support++;
				}
			}
		}

		inline void GenerateCandidates()
		{
			auto retired = IndexContainer<unsigned long long>(DICparameters->CountOfItemsets);
			auto PreviousItemsetSize = AllItems.Size;

			for (unsigned long long i = 0; i<dashedCircle.Size; i++)
			{
				if (AllItems[dashedCircle[i]].Support >= DICparameters->MinimumSupport)
				{
					retired.Append(dashedCircle[i]);

					for (unsigned long long j = 0; j<dashedBox.Size; j++)
					{
						if (AllItems[dashedCircle[i]].K == AllItems[dashedBox[j]].K)
						{
							Itemsets candidate;
							candidate.BitMask = AllItems[dashedCircle[i]].BitMask | AllItems[dashedBox[i]].BitMask;
							candidate.K = AllItems[dashedCircle[i]].K + 1;
							candidate.Support = 0;
							candidate.StopNo = 0;
							AllItems.Append(candidate);
						}
					}

					for (unsigned long long j = 0; j<solidBox.Size; j++)
					{
						if (AllItems[dashedCircle[i]].K == AllItems[solidBox[j]].K)
						{
							Itemsets candidate;
							candidate.BitMask = AllItems[dashedCircle[i]].BitMask | AllItems[solidBox[i]].BitMask;
							candidate.K = AllItems[dashedCircle[i]].K + 1;
							candidate.Support = 0;
							candidate.StopNo = 0;
							AllItems.Append(candidate);
						}
					}

					dashedCircle.RemoveByIndex(i);
				}
			}

			for (unsigned long long i = PreviousItemsetSize; i<AllItems.Size; i++)
			{
				dashedCircle.Append(i);
			}

			for (unsigned long long i = 0; i<retired.Size; i++)
			{
				dashedBox.Append(retired[i]);
			}

		}

		inline void CheckPassCompletion(unsigned long long &stopNo)
		{

			for (unsigned long long j = 0; j<dashedCircle.Size; j++)
			{
				if (AllItems[dashedCircle[j]].StopNo == stopNo)
				{
					solidCircle.Append(dashedCircle[j]);
					dashedCircle.RemoveByIndex(j);
				}
			}
			for (unsigned long long j = 0; j<dashedBox.Size; j++)
			{
				if (AllItems[dashedBox[j]].StopNo == stopNo)
				{
					solidBox.Append(dashedBox[j]);
					dashedBox.RemoveByIndex(j);
				}
			}

		}

	public:

		DICAlgorithm(IndexContainer<Itemsets> &items, Parameters* parameters)
		{
			DICparameters	= parameters;
			AllItems		= items;
			
			dashedCircle	=  IndexContainer<unsigned long long>(DICparameters->CountOfItemsets);
			dashedBox		=  IndexContainer<unsigned long long>(DICparameters->CountOfItemsets);
			solidCircle		=  IndexContainer<unsigned long long>(DICparameters->CountOfItemsets);
			solidBox		=  IndexContainer<unsigned long long>(DICparameters->CountOfItemsets);			
		}

		~DICAlgorithm()
		{
		}

		void GetResult()
		{
			
			unsigned long long stopNo = 0;
			
			fillDashedCircle();
			cout << "DCS=" << dashedCircle.Size << endl; //А вот тут ничего!
			unsigned long long step = 0;
			while (!dashedIsEmpty() && step<15)
			{
				cout << "step: " << step << endl;
				step++;
				stopNo++;
				if (stopNo>DICparameters->CountOfTransactions / DICparameters->CountOfItems)
				{
					stopNo = 1;
				}
				cout << "stopNo: " << stopNo << endl;
				unsigned long long a = 1;
				cout << AllItems[a].BitMask[1];
				/*
				CountSupport(stopNo, DICparameters->CountOfItems);
				GenerateCandidates();
				CheckPassCompletion(stopNo);
				*/

			}
		}
	};
}
