#pragma once

/**
IndexContainer.hpp
Purpose: Custom container for arrays.

@author		Suleymanov D.
@version	0.0.0.1 9/17/2016
*/

namespace DIC
{
	template<typename Content>
	class IndexContainer
	{

	private:

		Content* content;

	public:
		
		unsigned long long Size;
		unsigned long long Length;

		IndexContainer()
		{
			Size = 0;
			Length = 0;
		}

		IndexContainer(unsigned long long &size)
		{
			content = allocateAlign<Content>(size);			
			Size = 0;
			Length = size;
		}

		~IndexContainer()
		{
			
		}

		void Clean()
		{
			if (sizeof(content) / sizeof(Content) > 0)
			{
				freeAlign<Content>(content);
				Size = 0;
				Length = 0;
			}
		}

		void Clear()
		{
				Size = 0;
			
		}

		Content & operator[](unsigned long long & index) {
			return content[index];
		}

		Content & operator[](unsigned int & index) {
			return content[index];
		}

		void Append(Content &item)
		{
			if (Length > 0)
			{
				content[Size] = item;
				Size++;
			}
			else
			{
				throw "Memory is not allocated!";
			}
		}
		
		void RemoveByIndex(unsigned long long index)
		{	

			//cout << "REMOVE BY INDEX " << index << endl;
			for (unsigned long long i = index;i < Size-1; ++i)
			{
				//cout << "AND " << (i + 1) << " BECAME A " << i << endl;
				//cout << "AND content[" << i << " WAS A " << content[i] << endl;
				content[i] = content[i + 1];
				//cout << "AND content[" << i << " BECAME A " << content[i] << endl;
			}
			--Size;
			content[Size] = NULL;
		}

	};

}