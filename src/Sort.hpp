#pragma once

#include <vector>
#include <algorithm>

template <typename T>
void BubbleSort(std::vector<T>& array) {
    std::cout << "Bubble Sort" << std::endl;

    const size_t size = array.size();
    for (size_t i = 1; i < size; i++) {
        for (size_t j = 0; j < size - i; j++) {
            if (array[j] > array[j + 1]) {
                array[j].swap(array[j + 1]);
                // std::swap(array[j] , array[j + 1]);
            }
        }
    }
}