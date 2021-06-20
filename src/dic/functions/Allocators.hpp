#pragma once

/**
Allocators.hpp
Purpose: Alignment allocators for XeonPhi.

@author		Suleymanov D.
@version	0.0.0.1 9/17/2016
*/

namespace DIC
{
	using namespace std;

	/**
	Allocate memory align by custom length block.

	@param count	The count of elements in array.
	@param length	Length block (64 by default).
	@return Pointer to type T.
	*/
	template <typename Type>
	Type* allocateAlign(unsigned long long count, int length = 64) {
		Type * result;
		result = static_cast<Type*>(aligned_alloc(length,(count) * sizeof(Type)));
		if (result == nullptr) {
			printf( "\n ERROR: Can't allocate memory for matrices. Aborting... \n\n");
			exit(EXIT_FAILURE);
		}
		return result;
	}

	/**
	Free memory align

	@param pointer The pointer on array of type T.
	*/
	template <typename Type>
	void freeAlign(Type* pointer) {
		if (pointer) {
			free(pointer);
		}
	}
}