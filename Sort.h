#ifndef SORT_H_
#define SORT_H_

#include <iostream>
#include <vector>

void bubble_sort(std::vector<int>& values) {
	const size_t size = values.size();
	for (size_t sorted_index = 1; sorted_index < size; ++sorted_index) {
		for (size_t bubble_index = sorted_index; bubble_index > 0; --bubble_index) {
			int& bubble_element = values[bubble_index], & previous_element = values[bubble_index - 1];
			if (bubble_element < previous_element) {
				std::swap(bubble_element, previous_element);
			}
			else break;
		}
	}
}

#endif /* SORT_H_ */
