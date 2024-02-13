#include <random>
#include <vector>

namespace hoare {}

namespace two_way {

template <typename T> int partition(std::vector<T> &a, int lo, int hi) {
  int idx = lo;
  for (int i = lo + 1; i <= hi; ++i) {
    if (a[i] <= a[lo]) {
      std::swap(a[++idx], a[i]);
    }
  }
  std::swap(a[idx], a[lo]);
  return idx;
}

template <typename T>
int randomized_partition(std::vector<T> &a, int lo, int hi) {
  static std::mt19937 rng = std::mt19937{std::random_device{}()};
  int rand = rng() % (hi - lo + 1) + lo;
  std::swap(a[rand], a[lo]);
  return partition(a, lo, hi);
}

template <typename T> void quicksort(std::vector<T> &a, int lo, int hi) {
  if (hi <= lo)
    return;
  int pos = randomized_partition(a, lo, hi);

  quicksort(a, lo, pos - 1);
  quicksort(a, pos + 1, hi);
}

} // namespace two_way

namespace three_way {

template <typename T>
std::pair<int, int> partition(std::vector<T> &a, int lo, int hi) {
  T v = a[lo];
  int lt = lo, gt = hi;
  int i = lo;
  while (i <= gt) {
    if (a[i] < v) {
      std::swap(a[lt++], a[i++]);
    } else if (a[i] > v) {
      std::swap(a[gt--], a[i]);
    } else {
      ++i;
    }
  }

  return {lt, gt};
}

template <typename T>
std::pair<int, int> randomized_partition(std::vector<T> &a, int lo, int hi) {
  static std::mt19937 rng = std::mt19937{std::random_device{}()};
  int rand = rng() % (hi - lo + 1) + lo;
  std::swap(a[rand], a[lo]);
  return partition(a, lo, hi);
}

template <typename T> void quicksort(std::vector<T> &a, int lo, int hi) {
  if (hi <= lo)
    return;
  auto [lt, gt] = randomized_partition(a, lo, hi);

  quicksort(a, lo, lt - 1);
  quicksort(a, gt + 1, hi);
}

} // namespace three_way