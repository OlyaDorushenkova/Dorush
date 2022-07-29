#ifndef VECTORO__VECTOR_H_
#define VECTORO__VECTOR_H_
#include <iostream>
template <typename T>
class Vector {
 public:
  using ValueType = T;
  using Pointer = T*;
  using ConstPointer = const T*;
  using SizeType = size_t;
  using Reference = T&;
  using ConstReference = T&;
  using Iterator = T*;
  using ConstIterator = const T*;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  SizeType size;
  SizeType capacity;
  Pointer array;
  Vector() {
    size = 0;
    capacity = 0;
    array = nullptr;
  }
  explicit Vector(const SizeType& a) {
    if (a == 0) {
      size = 0;
      capacity = 0;
      array = nullptr;
    } else {
      array = new T[a];
      size = a;
      capacity = a;
    }
  }
  Vector(const SizeType& h, const ValueType& v) {
    if (h == 0) {
      size = 0;
      capacity = 0;
      array = nullptr;
    } else {
      try {
        size = h;
        capacity = size;
        array = new T[size];
        for (SizeType i = 0; i < size; i++) {
          array[i] = v;
        }
      } catch (...) {
        delete[] array;
        size = 0;
        capacity = 0;
        throw;
      }
    }
  }
  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
      std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  Vector(Iterator first, Iterator last) {
    if (first == last) {
      size = 0;
      array = nullptr;
      capacity = 0;
    } else {
      size = 0;
      capacity = 0;
      for (Iterator i = first; i != last; i++) {
        size++;
        capacity++;
      }
      auto v = new T[size];
      try {
        SizeType j = 0;
        for (Iterator i = first; i != last; i++) {
          v[j] = *i;
          j++;
        }
      } catch (...) {
        delete[] v;
        size = 0;
        capacity = 0;
        throw;
      }
      array = v;
      v = nullptr;
    }
  }
  Reference At(const SizeType& i) {
    if (size <= i || i < 0) {
      throw std::out_of_range{"Help_me_please"};
    }
    return array[i];
  }
  ConstReference At(const SizeType& i) const {
    if (size <= i || i < 0) {
      throw std::out_of_range{"Help_me_please"};
    }
    return array[i];
  }
  Vector(std::initializer_list<T> list) {
    if (list.size() == 0) {
      size = 0;
      capacity = 0;
      array = nullptr;
    } else {
      auto v = new T[list.size()];
      try {
        SizeType j = 0;
        for (auto i = list.begin(); i < list.end(); i++) {
          v[j] = *i;
          j++;
        }
      } catch (...) {
        delete[] v;
        throw;
      }
      array = v;
      v = nullptr;
      size = list.size();
      capacity = size;
    }
  }
  ~Vector() {
    delete[] array;
    size = 0;
    capacity = 0;
  }
  Vector(const Vector<ValueType>& v) {
    if (v.capacity == 0) {
      size = 0;
      capacity = 0;
      array = nullptr;
    } else {
      size = v.size;
      capacity = v.capacity;
      array = new ValueType[v.capacity];
      try {
        for (SizeType i = 0; i < v.size; i++) {
          array[i] = v.array[i];
        }
      } catch (...) {
        delete[] array;
        size = 0;
        capacity = 0;
        throw;
      }
    }
  }
  Vector(Vector<ValueType>&& v) noexcept {
    if (v.size == 0) {
      size = 0;
      capacity = 0;
      array = nullptr;
    } else {
      array = v.array;
      size = v.size;
      capacity = v.capacity;
    }
    v.array = nullptr;
    v.size = 0;
    v.capacity = 0;
  }
  Vector<ValueType>& operator=(const Vector<ValueType>& other) {
    if (this != &other) {
      if (other.size == 0) {
        size = 0;
        capacity = 0;
        delete[] array;
        array = nullptr;
      } else {
        delete[] array;
        array = nullptr;
        array = new T[other.capacity];
        size = 0;
        capacity = other.size;
        for (; size < other.size; size++) {
          array[size] = other.array[size];
        }
      }
    }
    return *this;
  }

  Vector<ValueType>& operator=(Vector<ValueType>&& other) noexcept {
    if (this != &other) {
      delete[] array;
      array = other.array;
      other.array = nullptr;
      std::swap(size, other.size);
      std::swap(capacity, other.capacity);
      other.size = 0;
      other.capacity = 0;
    }
    return *this;
  }
  SizeType Size() const {
    return size;
  }
  SizeType Capacity() const {
    return capacity;
  }
  bool Empty() const {
    return !size;
  }
  ConstReference operator[](const SizeType& i) const {
    return array[i];
  }
  Reference operator[](const SizeType& i) {
    return array[i];
  }
  Reference Front() {
    return *array;
  }
  ConstReference Front() const {
    return *array;
  }
  Reference Back() {
    return array[size - 1];
  }
  ConstReference Back() const {
    return array[size - 1];
  }
  Pointer Data() {
    return array;
  }
  ConstPointer Data() const {
    return array;
  }
  void Swap(Vector<ValueType>& other) {
    if (this != &other) {
      auto i = array;
      array = nullptr;
      array = other.array;
      other.array = nullptr;
      other.array = i;
      i = nullptr;
      std::swap(size, other.size);
      std::swap(capacity, other.capacity);
    }
  }
  void Resize(const SizeType& ns) {
    if (ns > capacity) {
      auto v = new ValueType[ns];
      try {
        for (SizeType i = 0; i < size; i++) {
          v[i] = std::move(array[i]);
        }
      } catch (...) {
        delete[] v;
        throw;
      }
      delete[] array;
      array = v;
      v = nullptr;
      capacity = ns;
      size = ns;
    } else if (ns == 0) {
      delete[] array;
      array = nullptr;
      size = 0;
    } else {
      size = ns;
    }
  }
  void Resize(const SizeType& ns, const T& value) {
    if (ns == 0) {
      delete[] array;
      array = nullptr;
      size = 0;
      capacity = 0;
    } else if (ns > capacity) {
      auto v = new ValueType[ns];
      try {
        for (SizeType i = 0; i < ns; i++) {
          if (i < size) {
            v[i] = std::move(array[i]);
          } else {
            v[i] = value;
          }
        }
      } catch (...) {
        delete[] v;
        throw;
      }
      delete[] array;
      array = v;
      capacity = ns;
      size = ns;
    } else if (capacity >= ns && ns > size) {
      for (SizeType i = size; i < ns; i++) {
        array[i] = value;
      }
      size = ns;
    } else {
      size = ns;
    }
  }
  void Reserve(const SizeType& new_cap) {
    if (new_cap > capacity) {
      auto buf = new ValueType[new_cap];
      try {
        for (SizeType i = 0; i < size; i++) {
          buf[i] = std::move(array[i]);
        }
      } catch (...) {
        delete[] buf;
        throw;
      }
      capacity = new_cap;
      delete[] array;
      array = buf;
    }
  }
  void ShrinkToFit() {
    if (capacity > size && size != 0) {
      auto v = new ValueType[size];
      try {
        for (SizeType i = 0; i < size; i++) {
          v[i] = std::move(array[i]);
        }
      } catch (...) {
        delete[] v;
        throw;
      }
      capacity = size;
      delete[] array;
      array = v;
    } else if (capacity > size && size == 0) {
      delete[] array;
      array = nullptr;
      capacity = 0;
    }
  }
  void Clear() {
    size = 0;
  }
  void PushBack(const T& data) {
    if (size == capacity && capacity != 0) {
      auto temp = new ValueType[2 * capacity];
      try {
        for (SizeType i = 0; i < capacity; i++) {
          temp[i] = array[i];
        }
        temp[size] = data;
      } catch (...) {
        delete[] temp;
        throw;
      }
      size++;
      delete[] array;
      capacity *= 2;
      array = temp;
    } else if (capacity == 0) {
      auto v = new ValueType[1];
      try {
        v[0] = data;
      } catch (...) {
        delete[] v;
        throw;
      }
      delete[] array;
      array = v;
      size = 1;
      capacity = 1;
    } else {
      array[size] = data;
      size++;
    }
  }
  void PushBack(T&& data) {
    if (size == capacity && capacity != 0) {
      auto temp = new ValueType[2 * capacity];
      try {
        for (SizeType i = 0; i < capacity; i++) {
          temp[i] = std::move(array[i]);
        }
        temp[size] = std::move(data);
      } catch (...) {
        delete[] temp;
        throw;
      }
      size++;
      delete[] array;
      capacity *= 2;
      array = temp;
    } else if (capacity == 0) {
      auto v = new ValueType[1];
      try {
        v[0] = std::move(data);
      } catch (...) {
        delete[] v;
        throw;
      }
      array = v;
      size = 1;
      capacity = 1;
    } else {
      array[size] = std::move(data);
      size++;
    }
  }
  void PopBack() {
    size--;
  }
  friend bool operator<(const Vector<ValueType>& v, const Vector<ValueType>& q) {
    SizeType a = 0;
    while (a < q.size && a < v.size) {
      if (v.array[a] < q.array[a]) {
        return true;
      }
      if (v.array[a] > q.array[a]) {
        return false;
      }
      a++;
    }
    return (v.size < q.size);
  }
  friend bool operator>(const Vector<ValueType>& v, const Vector<ValueType>& q) {
    SizeType a = 0;
    while (a < q.size && a < v.size) {
      if (v.array[a] > q.array[a]) {
        return true;
      }
      if (v.array[a] < q.array[a]) {
        return false;
      }
      a++;
    }
    return (v.size > q.size);
  }
  friend bool operator==(const Vector<ValueType>& v, const Vector<ValueType>& q) {
    SizeType a = 0;
    if (q.size != v.size) {
      return false;
    }
    while (a < q.size && q.array[a] == v.array[a]) {
      a++;
    }
    return (q.size == a);
  }
  friend bool operator<=(const Vector<ValueType>& v, const Vector<ValueType>& q) {
    return !(v > q);
  }
  friend bool operator>=(const Vector<ValueType>& v, const Vector<ValueType>& q) {
    return !(v < q);
  }
  friend bool operator!=(const Vector<ValueType>& v, const Vector<ValueType>& q) {
    return !(q == v);
  }
  Iterator begin() {  //  NOLINT
    return array;
  }
  ConstIterator begin() const {  //  NOLINT
    return array;
  }
  ConstIterator cbegin() const {  //  NOLINT
    return array;
  }
  ConstIterator end() const {  //  NOLINT
    return array + size;
  }
  Iterator end() {  //  NOLINT
    return array + size;
  }
  ConstIterator cend() const {  //  NOLINT
    return array + size;
  }
  ReverseIterator rbegin() {  //  NOLINT
    return std::reverse_iterator(end());
  }
  ConstReverseIterator rbegin() const {  //  NOLINT
    return ConstReverseIterator(end());
  }
  ReverseIterator rend() {  //  NOLINT
    return std::reverse_iterator(begin());
  }
  ConstReverseIterator rend() const {  //  NOLINT
    return ConstReverseIterator(begin());
  }
  ConstReverseIterator crbegin() const {  //  NOLINT
    return ConstReverseIterator(end());
  }
  ConstReverseIterator crend() const {  //  NOLINT
    return ConstReverseIterator(begin());
  }
};
#endif