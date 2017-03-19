//
// SparseArray.h
//
// An array with free list.
//  - When an object is removed, if it's the last (active) in the array, it's
//    simply popped off the end
//  - If not, it is added to the free list
//
// Ways in which this is OK:
//  - Indices of elements do not change in the array
//  - Slots for elements *may* be reused promptly
//  - Potentially decent cache locality, depending on usage pattern
//
// Ways in which this is suboptimal:
//  - Not good for traversal, if holes cannot be ruled out
//  - Holes may be randomly distributed -- inserting new elements from free list
//    may display poor cache locality
//  - Potentially limited opportunities for compaction
//


#ifndef __SparseArray_h
#define __SparseArray_h

#include <vector>

// Forward declarations
// --------------------------------------

template<class T>
class SparseArray;

template<class T>
void print_VSA_freeSpace(SparseArray<T> &);


// SparseArray
// --------------------------------------

template<class T>
class SparseArray {
public:
	SparseArray(int initial_size)
	{
		v.reserve(initial_size);
	}
	SparseArray() = delete;

	typedef T value_type;

	int add_entry(const T &t) {
		int i;
		if (free_list.size() == 0) {
			i = (int) v.size();
			v.push_back(t);
		}
		else {
			i = free_list.back();
			free_list.pop_back();
		}
		return i;
	}

	int get_slot() {
		return add_entry(T());
	}

	void remove(int i) {
		if (i == v.size() - 1) {
			v.pop_back();
		}
		else {
			free_list.push_back(i);
		}
	}
	// NB: removeEntry() doesn't check if entry in was already in the
	// free list -- if so, bad things will happen

	T operator[](int i) const {
		return v[i];
	}

private:
	std::vector<T> v;
	std::vector<int> free_list;

#ifdef __SparseArray_Test
	friend void test_SparseArray();
	friend void print_VSA_freeSpace<T>(SparseArray<T> &);
#endif

};


#endif

// LICENSE
// Copyright (c) 2017 Ben Hallstein
// -------------------------------------------
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
//   The above copyright notice and this permission notice shall be included in all
//   copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
