#pragma once

#include <vector>

namespace two_way {

void quicksort(std::vector<int> &a, int lo, int hi);
void quicksort(std::vector<int>::iterator first,
               std::vector<int>::iterator last);

} // namespace two_way

namespace three_way {

void quicksort(std::vector<int> &a, int lo, int hi);
void quicksort(std::vector<int>::iterator first,
               std::vector<int>::iterator last);

} // namespace three_way