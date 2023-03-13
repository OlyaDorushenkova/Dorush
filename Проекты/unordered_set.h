#ifndef UNORDERED_SETO__UNORDERED_SET_H_
#define UNORDERED_SETO__UNORDERED_SET_H_
#include<vector>
#include<list>
template<typename KeyT>
class UnorderedSet {
 public:
  std::vector<std::list<KeyT>> table;
  size_t elements;
  size_t buckets;
  UnorderedSet() {
    elements = 0;
    buckets = 0;
    std::vector<std::list<KeyT>> v;
    table = v;
  }
  explicit UnorderedSet(const size_t &count) {
    elements = 0;
    buckets = count;
    table = std::vector<std::list<KeyT>> (buckets);
  }
  using Iterator = KeyT*;
  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<std::forward_iterator_tag,
                                                                       typename std::iterator_traits<Iterator>::iterator_category>>>
  UnorderedSet(Iterator first, Iterator second) {
    auto i = first;
    buckets = 0;
    while(i != second) {
      buckets++;
      i++;
    }
    elements = buckets;
    auto p = first;
    table = std::vector<std::list<KeyT>> (buckets);
    while (p != second) {
      if (!Find(*p)) {
        table[std::hash<KeyT>()(*p) % buckets].push_back(*p);
        p++;
      }
    }
  }
  UnorderedSet(const UnorderedSet<KeyT>& other) { /
    elements = other.elements;
    buckets = other.buckets;
    table = other.table;
  }
  UnorderedSet<KeyT>& operator=(const UnorderedSet<KeyT>& other) {
    if (this != &other) {
      table.clear();
      elements = other.elements;
      buckets = other.buckets;
      table = std::vector<std::list<KeyT>>(buckets);
      for (size_t i = 0; i < buckets; i++) {
        auto j = other.table[i].begin();
        while (j != other.table[i].end()) {
          table[i].push_back(*j);
          j++;
        }
      }
    }
    return *this;
  }
  UnorderedSet(UnorderedSet<KeyT>&& other) noexcept {
    elements = other.elements;
    buckets = other.buckets;
    table = other.table;
    other.table.clear();
    other.elements = 0;
    other.buckets = 0;
  }
  UnorderedSet<KeyT>& operator=(UnorderedSet<KeyT>&& other) noexcept {
    if (this != &other) {
      table.clear();
      elements = other.elements;
      buckets = other.buckets;
      table = std::vector<std::list<KeyT>>(buckets);
      for (size_t i = 0; i < buckets; i++) {
        auto j = other.table[i].begin();
        while (j != other.table[i].end()) {
          table[i].push_back(*j);
          j++;
        }
      }
    }
    other.table.clear();
    other.elements = 0;
    other.buckets = 0;
    return *this;
  }
  size_t Size() const{
    return elements;
  }
  bool Empty() const{
    return !elements;
  }
  void Clear() {
    elements = 0;
    buckets = 0;
    table.clear();
  }
  bool Find(const KeyT& element) const{
    if (buckets == 0) {
      return false;
    }
    size_t i = std::hash<KeyT>()(element) % buckets;
    auto j = table[i].begin();
    while (j != table[i].end()) {
      if (*j == element){
        return true;
      }
      j++;
    }
    return false;
  }
  void Rehash(const size_t new_bucket_count) {
    if (new_bucket_count == buckets) {
      return;
    }
    if (new_bucket_count < elements) {
      return;
    }
    std::vector<std::list<KeyT>> other = table;
    table.clear();
    table = std::vector<std::list<KeyT>> (new_bucket_count);
    for (size_t i = 0; i < buckets; i++) {
      auto j = other[i].begin();
      while (j != other[i].end()) {
        table[std::hash<KeyT>()(*j) % new_bucket_count].push_back(*j);
        j++;
      }
    }
    other.clear();
    buckets = new_bucket_count;
  }
  void Insert(const KeyT& element) {
    if (Find(element)) {
      return;
    }
    if (buckets == 0) {
      buckets = 1;
      elements = 1;
      table = std::vector<std::list<KeyT>> (buckets);
      table[0].push_back(element);
    } else if (buckets <= elements) {
      Rehash(2 * buckets);
      table[std::hash<KeyT>()(element) % buckets].push_back(element);
      elements++;
    } else {
      table[std::hash<KeyT>()(element) % buckets].push_back(element);
      elements++;
    }
  }
  void Insert(KeyT&& element) {
    if (Find(element)) {
      return;
    }
    if (buckets == 0) {
      buckets = 1;
      elements = 1;
      table = std::vector<std::list<KeyT>> (buckets);
      table[0].push_back(element);
    } else if (buckets == elements) {
      Rehash(2 * buckets);
      table[std::hash<KeyT>()(element) % buckets].push_back(element);
      elements++;
    } else {
      table[std::hash<KeyT>()(element) % buckets].push_back(element);
      elements++;
    }
  }
  void Erase (const KeyT& element) {
    if (!Find(element)) {
      return;
    }
    elements--;
    size_t i = std::hash<KeyT>()(element) % buckets;
    auto j = table[i].begin();
    while (j != table[i].end()) {
      if (*j == element){
        table[i].erase(j);
        return ;
      }
      j++;
    }
  }
  void Reserve(const size_t new_bucket_count) {
    if (buckets < new_bucket_count) {
      Rehash(new_bucket_count);
    }
  }
  size_t BucketCount() const {
    return buckets;
  }
  size_t BucketSize(const size_t i) const {
    if (i >= buckets) {
      return 0;
    }
    return table[i].size();
  }
  size_t Bucket(const KeyT key) const {
    if (buckets == 0) {
      return 0;
    }
    return std::hash<KeyT>()(key) % buckets;
  }
  double LoadFactor() const {
    if (buckets == 0) {
      return 0.0;
    }
    double lf = elements * 1.0 / (buckets * 1.0);
    return lf;
  }
};
#endif

