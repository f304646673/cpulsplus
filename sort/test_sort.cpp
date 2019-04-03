#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <array>
#include <numeric>
#include <set>
#include <chrono>
#include <random>

using duration_mil = std::chrono::duration<double, std::milli>;

class Perform {
public:
    Perform() {
        _start = std::chrono::high_resolution_clock::now();
    }

    ~Perform() {
        _end = std::chrono::high_resolution_clock::now();
        duration_mil ms = _end - _start;
        std::cout << ms.count() << "ms" << std::endl;
    }
private:
    decltype(std::chrono::high_resolution_clock::now()) _start;
    decltype(std::chrono::high_resolution_clock::now()) _end;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template <class ForwardIt>
void quick_sort(ForwardIt first, ForwardIt last) {
    if (first == last) return;
    auto pivot = *std::next(first, std::distance(first, last) / 2);
    ForwardIt middle1 = std::partition(first, last,
        [pivot](const auto& em) { return em < pivot; });
    ForwardIt middle2 = std::partition(middle1, last,
        [pivot](const auto& em) { return !(pivot < em); });
    quick_sort(first, middle1);
    quick_sort(middle2, last);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ForwardIt>
void merge_sort(ForwardIt begin, ForwardIt end)
{
    if (end - begin > 1) {
        ForwardIt middle = begin + (end - begin) / 2;
        merge_sort(begin, middle);
        merge_sort(middle, end);
        std::inplace_merge(begin, middle, end);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ForwardIt>
void heap_sort(ForwardIt first, ForwardIt last) {
    std::make_heap(first, last);
    std::sort_heap(first, last);
}
////////////////////////////////////////////////////////////////////////////////////////////////////

template<class ForwardIt>
void selection_sort(ForwardIt begin, ForwardIt end) {
    for (ForwardIt i = begin; i != end; ++i) {
        std::iter_swap(i, std::min_element(i, end));
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ForwardIt>
void insertion_sort(ForwardIt begin, ForwardIt end) {
    for (ForwardIt i = begin; i != end; ++i) {
        std::rotate(std::upper_bound(begin, i, *i), i, std::next(i));
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////

class UtSort: 
	public ::testing::Test 
{
protected:
	virtual void SetUp() {
		_data.resize(_data_count);
		std::iota(_data.begin(), _data.end(), 1);

		_orded_data.assign(_data.begin(), _data.end());

		std::random_device rd;
	   	std::mt19937 g(rd());
		std::shuffle(_data.begin(), _data.end(), g);
	}

	template<class ForwardIt>
	void test_the_same(ForwardIt begin, ForwardIt end) const {
		auto same_count = std::inner_product(begin, end,
											_orded_data.begin(), 0,
											std::plus<>(), std::equal_to<>());
		ASSERT_EQ(same_count, std::distance(begin, end));
	}

protected:
    std::vector<int> _data;
    decltype(_data) _orded_data;
	size_t _data_count = 1024 * 256;
};

TEST_F(UtSort, quick_sort) {
	{
    	Perform perform;
    	quick_sort(_data.begin(), _data.end());
	}
	test_the_same(_data.begin(), _data.end());
}

TEST_F(UtSort, heap_sort) {
	{
    	Perform perform;
		heap_sort(_data.begin(), _data.end());
	}
	test_the_same(_data.begin(), _data.end());
}

TEST_F(UtSort, insertion_sort) {
	{
    	Perform perform;
		insertion_sort(_data.begin(), _data.end());
	}
	test_the_same(_data.begin(), _data.end());
}

TEST_F(UtSort, merge_sort) {
	{
    	Perform perform;
		merge_sort(_data.begin(), _data.end());
	}
	test_the_same(_data.begin(), _data.end());
}

TEST_F(UtSort, selection_sort) {
	{
    	Perform perform;
		selection_sort(_data.begin(), _data.end());
	}
	test_the_same(_data.begin(), _data.end());
}

TEST_F(UtSort, partial_sort) {
	{
    	Perform perform;
    	std::partial_sort(_data.begin(), _data.end(), _data.end());
	}
	test_the_same(_data.begin(), _data.end());
}

TEST_F(UtSort, stl_sort) {
	{
    	Perform perform;
    	std::sort(_data.begin(), _data.end());
	}
	test_the_same(_data.begin(), _data.end());
}
	

TEST_F(UtSort, set_sort) {
    std::set<int> ordered_data;
	{
    	Perform perform;
    	std::copy(make_move_iterator(_data.begin()), make_move_iterator(_data.end()), std::inserter(ordered_data, ordered_data.begin()));
	}
	test_the_same(ordered_data.begin(), ordered_data.end());
}

TEST_F(UtSort, partial_sort_head_10) {
	{
    	Perform perform;
    	std::partial_sort(_data.begin(), std::next(_data.begin(), 10), _data.end());
	}
	test_the_same(_data.begin(), std::next(_data.begin(), 10));
}

