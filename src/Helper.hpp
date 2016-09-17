#pragma once

namespace DIC
{
	using namespace std;

	/*Allocators*/
	template <typename Type>
	Type* allocateAlign(unsigned long long count, int length = 64) {
		return static_cast<Type*>(_mm_malloc(count * sizeof(Type), length));
	}

	template <typename Type>
	void freeAlign(Type* pointer) {
		if (pointer) {
			_mm_free(pointer);
		}
	}
}