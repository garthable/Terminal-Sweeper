// Copyright 2025 Dalton Prokosch

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SVEC_SVECTOR
#define SVEC_SVECTOR

#include <iostream>
#include <type_traits>
#include <cstring>

namespace svec 
{

/**
 * @brief SFINAE check for whether or not object has an operator==(T) (False).
 * If this struct is chosen SVector class will determine if two SVectors are equal by using memcmp instead of operator===(T).
 * 
 * @tparam T type.
 */
template <typename T, typename = void>
struct HasEquals : std::false_type {};

/**
 * @brief SFINAE check for whether or not object has an operator==(T) (True).
 * If this struct is chosen SVector class will determine if two SVectors are equal by using operator==(T).
 * 
 * @tparam T type.
 */
template <typename T>
struct HasEquals<T, std::void_t<decltype(std::declval<T>() == std::declval<T>())>> : std::true_type {};

/**
 * @brief SFINAE check for whether or not object is printable via std::cout << T (False).
 * If this struct is chosen SVector class will not be printable.
 * 
 * @tparam T type.
 */
template <typename T, typename = void>
struct Printable : std::false_type {};

/**
 * @brief SFINAE check for whether or not object is printable via std::cout << T (True).
 * If this struct is chosen SVector class will be printable.
 * 
 * @tparam T type.
 */
template <typename T>
struct Printable<T, std::void_t<decltype(std::cout << std::declval<T>())>> : std::true_type {};

/**
 * @brief Vector like container that is stored on the stack rather than the heap. 
 * 
 * @tparam T type stored in container
 * @tparam CAPACITY size allocated on stack
 */
template<typename T, size_t CAPACITY>
class SVector
{
public:
    /**
     * @brief Forward iterator for SVector container.
     * 
     */
    class Iterator
    {
    public:
        /**
         * @brief Construct a new Iterator object
         * 
         * @param ptr pointer located in SVector container
         */
        Iterator(T* ptr) :
            m_ptr(ptr)
        {}
        /**
         * @brief Iterates pointer forward by one
         * 
         * @return Iterator&
         */
        Iterator& operator++()
        {
            m_ptr++;
            return *this;
        }
        /**
         * @brief Iterates pointer forward by one
         * 
         * @return Iterator
         */
        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++(*this);
            return iterator;
        }
        /**
         * @brief Decrements pointer backwards by one
         * 
         * @return Iterator&
         */
        Iterator& operator--()
        {
            m_ptr--;
            return *this;
        }
        /**
         * @brief Decrements pointer backwards by one
         * 
         * @return Iterator
         */
        Iterator operator--(int)
        {
            Iterator iterator = *this;
            --(*this);
            return iterator;
        }
        /**
         * @brief Increments copy pointer forward by i
         * 
         * @param i amount forward
         * @return Iterator
         */
        Iterator operator+(long i) const
        {
            return Iterator(m_ptr + i);
        }
        /**
         * @brief Increments pointer forward by i
         * 
         * @param i amount forward
         * @return Iterator&
         */
        Iterator& operator+=(long i)
        {
            m_ptr += i;
            return *this;
        }
        /**
         * @brief Decrements copy pointer backwards by i
         * 
         * @param i amount backward
         * @return Iterator
         */
        Iterator operator-(long i) const
        {
            return Iterator(m_ptr - i);
        }
        /**
         * @brief Decrements pointer backwards by i
         * 
         * @param i amount backward
         * @return Iterator&
         */
        Iterator& operator-=(long i)
        {
            m_ptr -= i;
            return *this;
        }
        /**
         * @brief Finds difference between self and other iterator
         * 
         * @param ptr other iterator
         * @return ssize_t
         */
        ssize_t operator-(const Iterator& ptr) const
        {
            return m_ptr - ptr.m_ptr;
        }
        /**
         * @brief Gets T& value an amount forward from iterator
         * 
         * @param index amount forward from pointer
         * @return T&
         */
        T& operator[](size_t index)
        {
            return *(m_ptr + index);
        }
        /**
         * @brief Accesses pointers type internals
         * 
         * @return T*
         */
        T* operator->()
        {
            return m_ptr;
        }
        /**
         * @brief Dereferences pointer
         * 
         * @return T&
         */
        T& operator*()
        {
            return *m_ptr;
        }
        /**
         * @brief Checks if iterators are equal
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        bool operator==(const Iterator& other) const
        {
            return m_ptr == other.m_ptr;
        }
        /**
         * @brief Checks if iterators are not equal
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        bool operator!=(const Iterator& other) const
        {
            return m_ptr != other.m_ptr;
        }
        /**
         * @brief Checks if iterator is less than this iterator
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        bool operator>(const Iterator& other) const
        {
            return m_ptr > other.m_ptr;
        }
        /**
         * @brief Checks if iterator is less than or equal this iterator
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        bool operator>=(const Iterator& other) const
        {
            return m_ptr >= other.m_ptr;
        }
        /**
         * @brief Checks if iterator is greater than this iterator
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        bool operator<(const Iterator& other) const
        {
            return m_ptr > other.m_ptr;
        }
        /**
         * @brief Checks if iterator is greater than or equal to this iterator
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        bool operator<=(const Iterator& other) const
        {
            return m_ptr >= other.m_ptr;
        }
    public:
        typedef T value_type;
        typedef T difference_type;
        typedef T* pointer;
        typedef T& reference;
        typedef std::forward_iterator_tag iterator_category;
    private:
        /**
         * @brief Pointer to where iterator is.
         * 
         */
        T* m_ptr;
    };
    /**
     * @brief Input iterator for SVector container.
     * 
     */
    class ConstIterator
    {
    public:
        /**
         * @brief Construct a new Iterator object
         * 
         * @param ptr pointer located in SVector container
         */
        ConstIterator(const T* ptr) :
            m_ptr(ptr)
        {}
        /**
         * @brief Iterates pointer forward by one
         * 
         * @return ConstIterator&
         */
        ConstIterator& operator++()
        {
            m_ptr++;
            return *this;
        }
        /**
         * @brief Iterates pointer forward by one
         * 
         * @return ConstIterator
         */
        ConstIterator operator++(int)
        {
            ConstIterator iterator = *this;
            ++(*this);
            return iterator;
        }
        /**
         * @brief Decrements pointer backwards by one
         * 
         * @return ConstIterator&
         */
        ConstIterator& operator--()
        {
            m_ptr--;
            return *this;
        }
        /**
         * @brief Decrements pointer backwards by one
         * 
         * @return ConstIterator
         */
        ConstIterator operator--(int)
        {
            ConstIterator iterator = *this;
            --(*this);
            return iterator;
        }
        /**
         * @brief Increments copy pointer forward by i
         * 
         * @param i amount forward
         * @return ConstIterator
         */
        ConstIterator operator+(long i) const
        {
            return ConstIterator(m_ptr + i);
        }
        /**
         * @brief Increments pointer forward by i
         * 
         * @param i amount forward
         * @return ConstIterator&
         */
        ConstIterator& operator+=(long i)
        {
            m_ptr += i;
            return *this;
        }
        /**
         * @brief Decrements copy pointer backwards by i
         * 
         * @param i amount backward
         * @return ConstIterator
         */
        ConstIterator operator-(long i) const
        {
            return ConstIterator(m_ptr - i);
        }
        /**
         * @brief Decrements pointer backwards by i
         * 
         * @param i amount backward
         * @return ConstIterator&
         */
        ConstIterator& operator-=(long i)
        {
            m_ptr -= i;
            return *this;
        }
        /**
         * @brief Finds difference between self and other iterator
         * 
         * @param ptr other iterator
         * @return ssize_t
         */
        ssize_t operator-(const ConstIterator& ptr) const
        {
            return m_ptr - ptr.m_ptr;
        }
        /**
         * @brief Gets T& value an amount forward from iterator
         * 
         * @param index amount forward from pointer
         * @return const T&
         */
        const T& operator[](size_t index)
        {
            return *(m_ptr + index);
        }
        /**
         * @brief Accesses pointers type internals
         * 
         * @return const T*
         */
        const T* operator->()
        {
            return m_ptr;
        }
        /**
         * @brief Dereferences pointer
         * 
         * @return const T&
         */
        const T& operator*()
        {
            return *m_ptr;
        }
        /**
         * @brief Checks if iterators are equal
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        bool operator==(const ConstIterator& other) const
        {
            return m_ptr == other.m_ptr;
        }
        /**
         * @brief Checks if iterators are not equal
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        bool operator!=(const ConstIterator& other) const
        {
            return m_ptr != other.m_ptr;
        }
        /**
         * @brief Checks if iterator is less than this iterator
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        bool operator>(const ConstIterator& other) const
        {
            return m_ptr > other.m_ptr;
        }
        /**
         * @brief Checks if iterator is less than or equal this iterator
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        bool operator>=(const ConstIterator& other) const
        {
            return m_ptr >= other.m_ptr;
        }
        /**
         * @brief Checks if iterator is greater than this iterator
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        bool operator<(const ConstIterator& other) const
        {
            return m_ptr > other.m_ptr;
        }
        /**
         * @brief Checks if iterator is greater than or equal to this iterator
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        bool operator<=(const ConstIterator& other) const
        {
            return m_ptr >= other.m_ptr;
        }
    public:
        typedef const T value_type;
        typedef const T difference_type;
        typedef const T* pointer;
        typedef const T& reference;
        typedef std::input_iterator_tag iterator_category;
    private:
        /**
         * @brief Pointer to where iterator is.
         * 
         */
        const T* m_ptr;
    };
public:
    /**
     * @brief Construct a new SVector object, initializes size to zero
     * 
     */
    SVector() :
        m_size{0}
    {

    }
    /**
     * @brief Construct a new SVector object, initializes size to length of initList, sets array equal to init list
     * 
     * @param initList array of T values
     */
    SVector(std::initializer_list<T>&& initList) :
        m_size{initList.size()}
    {
        std::copy(initList.begin(), initList.end(), m_array);
    }
    /**
     * @brief Deep Copies SVector Object
     * 
     * @param other 
     */
    SVector(const SVector<T, CAPACITY>& other) :
        m_size{other.m_size}
    {
        std::copy(std::begin(other.m_array), std::end(other.m_array), std::begin(m_array));
    }
    /**
     * @brief Moves SVector Object
     * 
     * @param other 
     */
    SVector(SVector<T, CAPACITY>&& other) :
        m_array{*std::move(other.m_array)},
        m_size{std::move(other.m_size)}
    {
        
    }
    /**
     * @brief Sets SVector Object equal to array
     * 
     * @param initList 
     */
    void operator=(const std::initializer_list<T>& initList)
    {
        std::copy(initList.begin(), initList.end(), std::begin(m_array));
        m_size = initList.size();
    }
    /**
     * @brief Moves SVector Object
     * 
     * @param other 
     */
    void operator=(SVector<T, CAPACITY>&& other)
    {
        m_array = std::move(other.m_array);
        m_size = std::move(other.m_size);
    }
    /**
     * @brief Deep Copies SVector Object
     * 
     * @param other 
     */
    void operator=(const SVector<T, CAPACITY>& other)
    {
        std::copy(std::begin(other.m_array), std::end(other.m_array), std::begin(m_array));
        m_size = other.m_size;
    }

    /**
     * @brief Checks if two SVectors are equal. Compares values using T::operator==(T)
     * 
     * @tparam U T
     * @tparam C capacity of other SVector 
     * @param other
     * @return bool 
     */
    template<typename U = T, size_t C>
    std::enable_if<HasEquals<U>::value, 
            bool>::type
    operator==(const SVector<U, C>& other) const
    {
        if (other.size() != m_size) 
        {
            return false;
        }
        for (size_t i = 0; i < m_size; i++)
        {
            if (!(m_array[i] == other[i]))
            {
                return false;
            }
        }
        return true;
    }
    /**
     * @brief Checks if two SVectors are equal. Compares values using T::operator==(T)
     * 
     * @tparam U T
     * @tparam C capacity of other SVector 
     * @param other 
     * @return bool
     */
    template<typename U = T, size_t C>
    std::enable_if<HasEquals<U>::value, 
            bool>::type
    operator==(const SVector<U, C>& other)
    {
        if (other.size() != m_size) 
        {
            return false;
        }
        for (size_t i = 0; i < m_size; i++)
        {
            if (!(m_array[i] == other[i]))
            {
                return false;
            }
        }
        return true;
    }
    /**
     * @brief Checks if two SVectors are equal. Compares values using memcmp
     * 
     * @tparam U 
     * @tparam C 
     * @param other 
     * @return bool
     */
    template<typename U = T, size_t C>
    std::enable_if<!HasEquals<U>::value, 
            bool>::type
    operator==(const SVector<U, C>& other) const
    {
        if (other.size() != m_size) 
        {
            return false;
        }
        for (size_t i = 0; i < m_size; i++)
        {
            if (!(memcmp(&m_array[i], &other[i], sizeof(U)) == 0))
            {
                return false;
            }
        }
        return true;
    }
    /**
     * @brief Checks if a SVector is equal to an array. Compares values using T::operator==(T)
     * 
     * @tparam U T
     * @param initList 
     * @return bool
     */
    template<typename U = T>
    std::enable_if<HasEquals<U>::value, 
            bool>::type
    operator==(const std::initializer_list<U>& initList) const
    {
        if (initList.size() != m_size) 
        {
            return false;
        }
        for (size_t i = 0; i < m_size; i++)
        {
            if (!(m_array[i] == *(initList.begin() + i)))
            {
                return false;
            }
        }
        return true;
    }
    /**
     * @brief Checks if a SVector is equal to an array. Compares values using T::operator==(T)
     * 
     * @tparam U T
     * @param initList 
     * @return bool
     */
    template<typename U = T>
    std::enable_if<HasEquals<U>::value, 
            bool>::type
    operator==(const std::initializer_list<U>& initList)
    {
        if (initList.size() != m_size) 
        {
            return false;
        }
        for (size_t i = 0; i < m_size; i++)
        {
            if (!(m_array[i] == *(initList.begin() + i)))
            {
                return false;
            }
        }
        return true;
    }
    /**
     * @brief Checks if a SVector is equal to a RHV array. Compares values using memcmp
     * 
     * @tparam U T
     * @param initList 
     * @return bool
     */
    template<typename U = T>
    std::enable_if<!HasEquals<U>::value, 
            bool>::type
    operator==(const std::initializer_list<U>& initList) const
    {
        if (initList.size() != m_size) 
        {
            return false;
        }
        for (size_t i = 0; i < m_size; i++)
        {
            if (!(memcmp(&m_array[i], (initList.begin() + i), sizeof(U)) == 0))
            {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Returns iterator at start of array
     * 
     * @return Iterator 
     */
    inline Iterator begin()
    {
        return Iterator(static_cast<T*>(m_array));
    } 
    /**
     * @brief Returns iterator at start of array
     * 
     * @return ConstIterator 
     */
    inline ConstIterator begin() const
    {
        return ConstIterator(static_cast<const T*>(m_array));
    } 
    /**
     * @brief Returns iterator at end of array
     * 
     * @return Iterator 
     */
    inline Iterator end()
    {
        return Iterator(static_cast<T*>(m_array) + m_size);
    } 
    /**
     * @brief Returns iterator at end of array
     * 
     * @return ConstIterator 
     */
    inline ConstIterator end() const
    {
        return ConstIterator(static_cast<const T*>(m_array) + m_size);
    } 

    /**
     * @brief Accesses element of array
     * 
     * @param index
     * @return T& 
     */
    inline T& operator[](size_t i)
    {
    #ifdef _DEBUG
        if (i >= m_size)
        {
            throw std::out_of_range("ERROR: index " + std::to_string(i) + " is larger than size " + std::to_string(m_size));
        }
    #endif // _DEBUG end
        return m_array[i];
    }
    /** 
     * @brief Accesses element of array
     * 
     * @param index
     * @return const T&
     */
    inline const T& operator[](size_t i) const
    {
    #ifdef _DEBUG
        if (i >= m_size)
        {
            throw std::out_of_range("ERROR: index " + std::to_string(i) + " is larger than size " + std::to_string(m_size));
        }
    #endif // _DEBUG end
        return m_array[i];
    }
    /**
     * @brief Returns size of SVector
     * 
     * @return size_t 
     */
    inline size_t size() const
    {
        return m_size;
    }
    /**
     * @brief Returns size of array
     * 
     * @return size_t 
     */
    inline size_t capacity() const
    {
        return CAPACITY;
    }
    /**
     * @brief Returns last element
     * 
     * @return T& 
     */
    inline T& back()
    {
        return m_array[m_size-1];
    }
    /**
     * @brief Returns last element
     * 
     * @return const T& 
     */
    inline const T& back() const
    {
        return m_array[m_size-1];
    }
    /**
     * @brief Returns first element
     * 
     * @return T& 
     */
    inline T& front()
    {
        return m_array[0];
    }
    /**
     * @brief Returns first element
     * 
     * @return const T& 
     */
    inline const T& front() const
    {
        return m_array[0];
    }

    /**
     * @brief Adds element to back of SVector and increases size
     * 
     * @param element
     */
    inline void pushBack(const T& element)
    {
        m_array[m_size] = element;
        m_size++;
    }
    /**
     * @brief Adds element to back of SVector and increases size
     * 
     * @param element
     */
    inline void pushBack(T&& element)
    {
        m_array[m_size] = element;
        m_size++;
    }
    /**
     * @brief Adds element to front of SVector and increases size
     * 
     * @param element 
     */
    inline void pushFront(const T& element)
    {
        for (size_t i = m_size-1; i != SIZE_MAX; i--) 
        {
            m_array[i + 1] = m_array[i];
        }
        m_array[0] = element;
        m_size++;
    }
    /**
     * @brief Adds element to front of SVector and increases size
     * 
     * @param element 
     */
    inline void pushFront(T&& element)
    {
        for (size_t i = m_size-1; i != SIZE_MAX; i--) 
        {
            m_array[i + 1] = m_array[i];
        }
        m_array[0] = element;
        m_size++;
    }
    /**
     * @brief Removes element from back
     * 
     */
    inline void popBack()
    {
        m_size--;
    }
    /**
     * @brief Removes element from front
     * 
     */
    inline void popFront()
    {
        m_size--;
        for (size_t i = 0; i < m_size; i++) 
        {
            m_array[i] = m_array[i + 1];
        }
    }
    /**
     * @brief Inserts element into array
     * 
     * @param index 
     * @param element
     */
    inline void insert(size_t index, const T& element)
    {
        for (size_t i = m_size-1; i >= index && i != index-1u; i--) 
        {
            m_array[i + 1] = m_array[i];
        }
        m_array[index] = element;
        m_size++;
    }
    /**
     * @brief Inserts element into array
     * 
     * @param index 
     * @param element
     */
    inline void insert(size_t index, T&& element)
    {
        for (size_t i = m_size-1; i >= index && i != index-1u; i--) 
        {
            m_array[i + 1] = m_array[i];
        }
        m_array[index] = element;
        m_size++;
    }
    /**
     * @brief Removes element from array
     * 
     * @param index 
     */
    inline void erase(size_t index)
    {
        m_size--;
        for (size_t i = index; i < m_size; i++) 
        {
            m_array[i] = m_array[i + 1];
        }
    }
    /**
     * @brief Emplaces element at the back of the SVector
     * 
     * @tparam ARGS 
     * @param args 
     */
    template<typename... ARGS>
    inline void emplaceBack(ARGS&&... args)
    {
        m_array[m_size] = T(std::forward<ARGS>(args)...);
        m_size++;
    }
    /**
     * @brief Emplaces element at the front of the SVector
     * 
     * @tparam ARGS 
     * @param args 
     */
    template<typename... ARGS>
    inline void emplaceFront(ARGS&&... args)
    {
        for (size_t i = m_size-1; i != SIZE_MAX; i--) 
        {
            m_array[i + 1] = m_array[i];
        }
        m_array[0] = T(std::forward<ARGS>(args)...);
        m_size++;
    }
    /**
     * @brief Emplaces element at a specific element of array
     * 
     * @tparam ARGS 
     * @param index 
     * @param args 
     */
    template<typename... ARGS>
    inline void emplace(size_t index, ARGS&&... args)
    {
        for (size_t i = m_size-1; i >= index && i != index-1u; i--) 
        {
            m_array[i + 1] = m_array[i];
        }
        m_array[index] = T(std::forward<ARGS>(args)...);
        m_size++;
    }

    /**
     * @brief Sets size of SVector to 0
     * 
     */
    inline void clear()
    {
        m_size = 0;
    }
private:
    /**
     * @brief Container on stack
     * 
     */
    T m_array[CAPACITY];
    /**
     * @brief Size of container being used
     * 
     */
    size_t m_size;
};

/**
 * @brief Prints SVector
 * 
 * @tparam T 
 * @tparam CAPACITY 
 * @param out 
 * @param obj 
 * @return std::ostream&
 */
template<typename T, size_t CAPACITY>
std::enable_if<Printable<T>::value, 
        std::ostream&>::type
operator<<(std::ostream &out, const SVector<T, CAPACITY>& obj)
{
    out << "{";
    for (size_t i = 0; i < obj.size(); i++)
    {
        out << obj[i];
        if (i != obj.size() - 1)
        {
            out << ", ";
        }
    }
    out << "}";
    return out;
}

}

#endif // SVEC_SVECTOR END