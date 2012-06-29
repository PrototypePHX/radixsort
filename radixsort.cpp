#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

template <typename ForwardIterator>
void radixsort(const ForwardIterator first, const ForwardIterator last, int factor = 10)
{
   //partitioning
   std::map<int, std::vector<int> > buckets;
   for (ForwardIterator i = first; i != last; ++i) {
      //'extract' the digit we want from the number and map it in the bucket
      if (factor == 10) buckets[*i%factor].push_back(*i);
      else buckets[(*i/(factor/10)) %10].push_back(*i);
   }

   //collecting
   ForwardIterator copyfirst = first;
   for (int i = 0; i < 10; ++i) {
      for (std::vector<int>::const_iterator it = buckets[i].begin(); it != buckets[i].end(); )
         //collect and apply to range [first, last)
         *copyfirst++ = *it++;
   }

   //we could recurse even more, but then all values will be mapped to zero, hence there wouldn't be
   //any change during the collection
   if (factor > *std::max_element(first, last)) return;
   radixsort(first, last, factor *= 10);
}


int main()
{
  std::vector<int> x = {122, 311, 252, 41, 1, 1921, 12, 1, 92};

  std::cout << "Before sorting: ";
  for (std::vector<int>::iterator it = x.begin(); it != x.end(); ++it)
    std::cout << *it << " ";

  radixsort(x.begin(), x.end());

  std::cout << "\nAfter sorting: ";
  for (std::vector<int>::iterator it = x.begin(); it != x.end(); ++it)
    std::cout << *it << " ";
  std::cout << "\n";
}
