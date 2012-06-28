#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

template <typename RandomAccessIterator>
void radixsort(const RandomAccessIterator first, const RandomAccessIterator last, int factor = 10)
{
   //partitioning
   std::map<int, std::vector<int> > buckets;
   for (RandomAccessIterator i = first; i != last; ++i) {
      if (factor == 10) buckets[*i%factor].push_back(*i);
      else buckets[(*i/(factor/10)) %10].push_back(*i);
   }

   //collecting
   RandomAccessIterator copyfirst = first;
   for (int i = 0; i < 10; ++i) {
      for (std::vector<int>::const_iterator it = buckets[i].begin(); it != buckets[i].end(); )
         *copyfirst++ = *it++;
   }
   if (factor > *std::max_element(first, last)) return;
   radixsort(first, last, factor *= 10);
}


int main()
{
  std::vector<int> x = {122, 311, 252, 41, 1, 1921, 12, 1, 92};
  radixsort(x.begin(), x.end());
  for (std::vector<int>::iterator it = x.begin(); it != x.end(); ++it)
    std::cout << *it << " ";
  std::cout << "\n";
}
