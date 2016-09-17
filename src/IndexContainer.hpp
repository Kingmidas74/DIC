#pragma once

#include "Helper.hpp"

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

		Content & operator[](int & index) {
			if (index < 0) throw "Null index!";
			return content[index];
		}

		void SetValue(Content value, unsigned long long index)
		{
			content[index] = value;
		}

		Content GetValue(unsigned long long index)
		{
			return &content[index];
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