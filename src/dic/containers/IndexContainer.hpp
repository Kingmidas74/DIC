#pragma once

/**
IndexContainer.hpp
Purpose: Custom container for arrays.

@author		Suleymanov D.
@version	0.0.0.1 9/17/2016
*/

namespace DIC
{
	template<class Content>
	class IndexContainer
	{

	private:

		Content* content;

		unsigned long long my_size;
		unsigned long long my_capacity;

	public:
		
		int Length;

		IndexContainer(): my_size(0), my_capacity(0), Length(0)
		{
			
		}

		IndexContainer(unsigned long long &size)
		{
			content = allocateAlign<Content>(size);			
			my_size = size;
			my_capacity = size;
			Length = 0;
		}

		IndexContainer(unsigned long long &size, const Content &initial)
		{
			content = allocateAlign<Content>(size);
			my_size = size;
			my_capacity = size;
			Length = 0;
			for(unsigned long long i=0; i<size; i++)
			{
				content[i] = initial;
			}
		}

		IndexContainer(unsigned int &size)
		{
			content = allocateAlign<Content>(size);
			my_size = size;
			my_capacity = size;
			Length = 0;
		}

		IndexContainer(unsigned int &size, const Content &initial)
		{
			content = allocateAlign<Content>(size);
			my_size = size;
			my_capacity = size;
			Length = 0;
			for (unsigned int i = 0; i<size; i++)
			{
				content[i] = initial;
			}
		}

		IndexContainer(int &size)
		{
			content = allocateAlign<Content>(size);
			my_size = size;
			my_capacity = size;
			Length = 0;
		}

		IndexContainer(int &size, const Content &initial)
		{
			content = allocateAlign<Content>(size);
			my_size = size;
			my_capacity = size;
			Length = 0;
			for (int i = 0; i<size; i++)
			{
				content[i] = initial;
			}
		}

		~IndexContainer()
		{
			
		}
		
		int * begin()
		{
			return Length>0 ? &content[0] : nullptr;
		}

		int * end()
		{
			return Length>0 ? &content[Length] : nullptr;
		}


		Content & operator[](const unsigned long &index) {
			return content[index];
		}

		void Clear()
		{
			if (sizeof(content) / sizeof(Content) > 0)
			{
				freeAlign<Content>(content);
				my_size = 0;
				Length = 0;
			}
		}


		void ReUse()
		{
			Length = 0;
		}

		void Append(Content &item)
		{
			if (my_size > 0)
			{
				content[Length] = item;
				Length++;
			}
			else
			{
				throw "Memory is not allocated!";
			}
		}

		


		

		void RemoveByIndex(int &index)
		{	
			if (Length == 0 || Length==index) throw "Invalid element index";
			if (Length == 1) 
			{
				ReUse();
				return;
			}
			for (int i = index+1;i < Length; i++)
			{
				content[i-1] = content[i];
			}
			Length--;
		}

	};

}