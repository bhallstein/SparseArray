/*
 * Some tests for SparseArray
 *   compile: clang++ -std=c++11 test.cpp
 *
 */

#include "../../_test.h"

#define __SparseArray_Test
#include "SparseArray.h"

struct X {
	int a;
	float b;
};

template<class T>
void print_VSA_freeSpace(SparseArray<T> &v) {
	printf("free list: ");
	if (v.free_list.size() == 0) {
		printf("none\n");
	}
	else {
		for (int i=0; i < v.free_list.size(); ++i) {
			printf("%d ", i);
		}
		printf("\n");
	}
}

void test_SparseArray() {
	p_header("SparseArray: construction");
	SparseArray<X> vsa_defsize(12);
	p_assert(vsa_defsize.v.capacity() == 12);
	
	SparseArray<X> vsa(4);
	p_assert(vsa.v.size() == 0);
	p_assert(vsa.v.capacity() == 4);
	p_assert(vsa.free_list.size() == 0);
	
	p_header("SparseArray: get_slot() at end");
	int ind = vsa.get_slot();
	p_assert(ind == 0);
	p_assert(vsa.v.size() == 1);
	p_assert(vsa.free_list.size() == 0);
	
	for (int i=0; i < 3; ++i) {
		vsa.get_slot();
	}
	p_assert(vsa.v.size() == 4);
	p_assert(vsa.free_list.size() == 0);
	
	p_header("SparseArray: remove() at end");
	vsa.remove(3);
	p_assert(vsa.v.size() == 3);
	p_assert(vsa.free_list.size() == 0);
	print_VSA_freeSpace(vsa);
	
	p_header("SparseArray: remove() from middle");
	vsa.remove(1);
	p_assert(vsa.v.size() == 3);
	p_assert(vsa.free_list.size() == 1);
	print_VSA_freeSpace(vsa);
	
	vsa.remove(0);
	p_assert(vsa.v.size() == 3);
	p_assert(vsa.free_list.size() == 2);
	print_VSA_freeSpace(vsa);
	
	p_header("SparseArray: get_slot() from free list");
	ind = vsa.get_slot();
	p_assert(ind == 0);
	p_assert(vsa.v.size() == 3);
	p_assert(vsa.free_list.size() == 1);
	print_VSA_freeSpace(vsa);
	
	ind = vsa.get_slot();
	p_assert(ind == 1);
	p_assert(vsa.v.size() == 3);
	p_assert(vsa.free_list.size() == 0);
	print_VSA_freeSpace(vsa);
	
	ind = vsa.get_slot();
	p_assert(ind == 3);
	p_assert(vsa.v.size() == 4);
	p_assert(vsa.free_list.size() == 0);
	print_VSA_freeSpace(vsa);
}


int main() {
	test_SparseArray();
	return 0;
}

