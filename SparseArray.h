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
// MIT licensed: http://opensource.org/licenses/MIT
//

#ifndef __SparseArray_h
#define __SparseArray_h

#include <vector>


// SparseArray
// --------------------------------------

template<class T>
struct SparseArray {
	std::vector<T> v;
	std::vector<size_t> free_list;
	typedef T value_type;


	SparseArray(size_t initial_size) {
		v.reserve(initial_size);
	}
	SparseArray() = delete;


	T& operator[](size_t i) {
		return v[i];
	}


	size_t push(const T &t) {
		size_t i;
		if (free_list.size() > 0) {
			i = free_list.back();
			free_list.pop_back();
			v[i] = t;
		}
		else {
			i = v.size();
			v.push_back(t);
		}
		return i;
	}


	void remove(size_t i) {
		if (i == v.size() - 1) {
			v.pop_back();
		}
		else {
			free_list.push_back(i);
		}
	}
		// NB: remove() doesn't check if entry in was already in the
		// free list -- if so, bad things will happen


	size_t n() {
		return v.size() - free_list.size();
	}
};

#endif

