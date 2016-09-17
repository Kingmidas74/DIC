#pragma once

/**
IndexContainer.hpp
Purpose: Custom container for arrays.

@author		Suleymanov D.
@version	0.0.0.1 9/17/2016
*/

#include "Allocators.hpp"

namespace DIC
{
	template<typename Content>
	class IndexContainer
	{

	private:

		Content* content;

	public:
		
		unsigned long long Size;

		IndexContainer()
		{
			Size = 0;
		}

		IndexContainer(unsigned long long &size)
		{
			content = allocateAlign<Content>(size);			
			Size = 0;
		}

		~IndexContainer()
		{
			freeAlign(content);
		}

		Content & operator[](unsigned long long & index) {
			return content[index];
		}

		void Append(Content &item)
		{
			content[Size] = item;
			Size++;
		}
		
		void RemoveByIndex(unsigned long long index)
		{
			
			content[index] = NULL;
		}

	};

}