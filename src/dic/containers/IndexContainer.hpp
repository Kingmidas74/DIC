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

		Content & operator[](unsigned long long & index) {
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
			--Size;
			for (unsigned long long i = index;i < Size; ++i)
			{
				content[index] = content[index + 1];
			}
			content[Size] = NULL;
		}

	};

}