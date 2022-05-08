#include "_test.h"

#define SparseArray_Test
#include "../SparseArray.h"

struct X {
	int a;
	float b;
};

bool x_equal(X x1, X x2) {
	return x1.a == x2.a && x1.b == x2.b;
}

template<class T>
void sparsearray__print_free_space(SparseArray<T> &v) {
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
	p_header("SparseArray: construct");
	SparseArray<X> arr(4);
	p_assert(arr.v.size() == 0);
	p_assert(arr.v.capacity() == 4);
	p_assert(arr.free_list.size() == 0);

	p_header("push items when free list empty");
	X x0{0,  0.0};
	X x1{10, 100.0};
	X x2{20, 200.0};
	X x3{30, 300.0};
	arr.push(x0);
	arr.push(x1);;
	arr.push(x2);
	arr.push(x3);
	p_assert(arr.v.size() == 4);
	p_assert(arr.free_list.size() == 0);
	p_assert(x_equal(x0, arr.v[0]));
	p_assert(x_equal(x1, arr.v[1]));
	p_assert(x_equal(x2, arr.v[2]));
	p_assert(x_equal(x3, arr.v[3]));

	p_header("remove from middle");
	arr.remove(1);
	p_assert(arr.v.size() == 4);
	p_assert(arr.free_list.size() == 1);

	p_header("remove from end");
	arr.remove(3);
	p_assert(arr.v.size() == 3);
	p_assert(arr.free_list.size() == 1);
	arr.remove(2);
	p_assert(arr.v.size() == 2);
	p_assert(arr.free_list.size() == 1);

	p_header("push uses free list when present");
	arr.push(x2);
	p_assert(arr.v.size() == 2);
	p_assert(arr.free_list.size() == 0);

	p_header("contains expected items");
	p_assert(x_equal(x0, arr.v[0]));
	p_assert(x_equal(x2, arr.v[1]));

  p_header("n() -> total number of items");
  p_assert(arr.n() == arr.v.size() - arr.free_list.size());
}


int main() {
	test_SparseArray();
	return 0;
}

