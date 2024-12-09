#ifndef SOFTLOQ_CHARSET_ENCODING_ADT_LIST_HPP
#define SOFTLOQ_CHARSET_ENCODING_ADT_LIST_HPP

#include "Softloq-Charset-Encoding/error.hpp"
#include <functional>
#include <iterator>
#include <list>
#include <iostream>

namespace Softloq::Charset
{
    template <class T>
    class List
    {
    private:
        struct Node
        {
            T item;
            Node *prev, *next;
        };

    public:
        // Iterators

        class BaseIterator
        {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type = T;
            using difference_type = ptrdiff_t;
            using pointer = Node *;
            using reference = T &;

            SOFTLOQ_CHARSET_ENCODING_API BaseIterator();
            SOFTLOQ_CHARSET_ENCODING_API BaseIterator(Node *prev, Node *curr);
            SOFTLOQ_CHARSET_ENCODING_API BaseIterator(const BaseIterator &it);
            SOFTLOQ_CHARSET_ENCODING_API virtual ~BaseIterator() = 0;
            SOFTLOQ_CHARSET_ENCODING_API inline constexpr bool operator==(const BaseIterator &rhs) const { return prev == rhs.prev && curr == rhs.curr; }
            SOFTLOQ_CHARSET_ENCODING_API inline constexpr bool operator!=(const BaseIterator &rhs) const { return prev != rhs.prev || curr != rhs.curr; }

        protected:
            Node *prev, *curr;
        };

        class Iterator final : public BaseIterator
        {
        public:
            using iterator_category = BaseIterator::iterator_category;
            using value_type = BaseIterator::value_type;
            using difference_type = BaseIterator::difference_type;
            using pointer = BaseIterator::pointer;
            using reference = BaseIterator::reference;

            SOFTLOQ_CHARSET_ENCODING_API inline Iterator();
            SOFTLOQ_CHARSET_ENCODING_API inline Iterator(Node *prev, Node *curr);
            SOFTLOQ_CHARSET_ENCODING_API inline Iterator(const Iterator &it);

            SOFTLOQ_CHARSET_ENCODING_API inline Iterator &operator++()
            {
                if (BaseIterator::curr)
                {
                    BaseIterator::prev = BaseIterator::curr;
                    BaseIterator::curr = BaseIterator::curr->next;
                }
                return *this;
            }
            SOFTLOQ_CHARSET_ENCODING_API inline Iterator operator++(int)
            {
                Iterator tmp(*this);
                operator++();
                return tmp;
            }
            SOFTLOQ_CHARSET_ENCODING_API inline Iterator &operator--()
            {
                if (BaseIterator::prev)
                {
                    BaseIterator::curr = BaseIterator::prev;
                    BaseIterator::prev = BaseIterator::prev->prev;
                }
                return *this;
            }
            SOFTLOQ_CHARSET_ENCODING_API inline Iterator operator--(int)
            {
                Iterator tmp(*this);
                operator--();
                return tmp;
            }
            SOFTLOQ_CHARSET_ENCODING_API inline reference operator*() { return BaseIterator::curr->item; }

            SOFTLOQ_CHARSET_ENCODING_API inline friend void swap(Iterator &lhs, Iterator &rhs)
            {
                using std::swap;
                swap(lhs.prev, rhs.prev);
                swap(lhs.curr, rhs.curr);
            }
        };

        class ReverseIterator final : public BaseIterator
        {
        public:
            using iterator_category = BaseIterator::iterator_category;
            using value_type = BaseIterator::value_type;
            using difference_type = BaseIterator::difference_type;
            using pointer = BaseIterator::pointer;
            using reference = BaseIterator::reference;

            SOFTLOQ_CHARSET_ENCODING_API inline ReverseIterator();
            SOFTLOQ_CHARSET_ENCODING_API inline ReverseIterator(Node *prev, Node *curr);
            SOFTLOQ_CHARSET_ENCODING_API inline ReverseIterator(const ReverseIterator &it);

            SOFTLOQ_CHARSET_ENCODING_API inline ReverseIterator &operator++()
            {
                if (BaseIterator::prev)
                {
                    BaseIterator::curr = BaseIterator::prev;
                    BaseIterator::prev = BaseIterator::prev->prev;
                }
                return *this;
            }
            SOFTLOQ_CHARSET_ENCODING_API inline ReverseIterator operator++(int)
            {
                ReverseIterator tmp(*this);
                operator++();
                return tmp;
            }
            SOFTLOQ_CHARSET_ENCODING_API inline ReverseIterator &operator--()
            {
                if (BaseIterator::curr)
                {
                    BaseIterator::prev = BaseIterator::curr;
                    BaseIterator::curr = BaseIterator::curr->next;
                }
                return *this;
            }
            SOFTLOQ_CHARSET_ENCODING_API inline ReverseIterator operator--(int)
            {
                ReverseIterator tmp(*this);
                operator--();
                return tmp;
            }
            SOFTLOQ_CHARSET_ENCODING_API inline reference operator*() { return BaseIterator::prev->item; }

            SOFTLOQ_CHARSET_ENCODING_API inline friend void swap(ReverseIterator &lhs, ReverseIterator &rhs)
            {
                using std::swap;
                swap(lhs.prev, rhs.prev);
                swap(lhs.curr, rhs.curr);
            }
        };

    public:
        // Standard iterator support

        using size_type = size_t;
        using iterator = Iterator;
        using const_iterator = const Iterator;
        using reverse_iterator = ReverseIterator;
        using const_reverse_iterator = const ReverseIterator;

        SOFTLOQ_CHARSET_ENCODING_API List();

        // The rule of five

        SOFTLOQ_CHARSET_ENCODING_API ~List();
        SOFTLOQ_CHARSET_ENCODING_API List(const List<T> &list);
        SOFTLOQ_CHARSET_ENCODING_API List<T> &operator=(const List<T> &list);
        SOFTLOQ_CHARSET_ENCODING_API inline List(List<T> &&list);
        SOFTLOQ_CHARSET_ENCODING_API inline List<T> &operator=(List<T> &&list);

        // Range-based for loop support

        SOFTLOQ_CHARSET_ENCODING_API inline iterator begin() { return iterator(nullptr, front); }
        SOFTLOQ_CHARSET_ENCODING_API inline const_iterator begin() const { return const_iterator(nullptr, front); }
        SOFTLOQ_CHARSET_ENCODING_API inline const_iterator cbegin() const noexcept { return const_iterator(nullptr, front); }

        SOFTLOQ_CHARSET_ENCODING_API inline reverse_iterator rbegin() { return reverse_iterator(back, nullptr); }
        SOFTLOQ_CHARSET_ENCODING_API inline const_reverse_iterator rbegin() const { return const_reverse_iterator(back, nullptr); }
        SOFTLOQ_CHARSET_ENCODING_API inline const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(back, nullptr); }

        SOFTLOQ_CHARSET_ENCODING_API inline iterator end() { return Iterator(back, nullptr); }
        SOFTLOQ_CHARSET_ENCODING_API inline const_iterator end() const { return const_iterator(back, nullptr); }
        SOFTLOQ_CHARSET_ENCODING_API inline const_iterator cend() const noexcept { return const_iterator(back, nullptr); }

        SOFTLOQ_CHARSET_ENCODING_API inline reverse_iterator rend() { return reverse_iterator(nullptr, front); }
        SOFTLOQ_CHARSET_ENCODING_API inline const_reverse_iterator rend() const { return const_reverse_iterator(nullptr, front); }
        SOFTLOQ_CHARSET_ENCODING_API inline const_reverse_iterator crend() const noexcept { return const_reverse_iterator(nullptr, front); }

        // Intra list member functions

        SOFTLOQ_CHARSET_ENCODING_API void appendItem(const T &item);
        SOFTLOQ_CHARSET_ENCODING_API void prependItem(const T &item);
        SOFTLOQ_CHARSET_ENCODING_API void extendList(const List<T> &list);
        SOFTLOQ_CHARSET_ENCODING_API void replaceItems(const std::function<bool(const T &)> &cond, const T &item);
        SOFTLOQ_CHARSET_ENCODING_API void insertItem(const size_type index, const T &item);
        SOFTLOQ_CHARSET_ENCODING_API void removeItems(const std::function<bool(const T &)> &cond);
        SOFTLOQ_CHARSET_ENCODING_API void emptyList();
        SOFTLOQ_CHARSET_ENCODING_API const bool containsItem(const T &item) const;

        SOFTLOQ_CHARSET_ENCODING_API inline constexpr size_type getSize() const { return size; }
        SOFTLOQ_CHARSET_ENCODING_API inline constexpr size_type isEmpty() const { return size == 0; }
        SOFTLOQ_CHARSET_ENCODING_API T &operator[](const size_type index) const;
        SOFTLOQ_CHARSET_ENCODING_API List<T> cloneList();
        SOFTLOQ_CHARSET_ENCODING_API List<T> sortListAscending();
        SOFTLOQ_CHARSET_ENCODING_API List<T> sortListDescending();

    private:
        Node *front, *back;
        size_type size;

        // Auxiliary member functions

        SOFTLOQ_CHARSET_ENCODING_API void mergeSort(
            Node **left_node_ptr, Node **right_node_ptr, const size_type size,
            const std::function<const bool(const T &, const T &)> &cond);

        SOFTLOQ_CHARSET_ENCODING_API void merge(
            Node **left_node_ptr, const size_type mid_size, Node **right_node_ptr,
            const std::function<const bool(const T &, const T &)> &cond);
    };
}
#include "Softloq-Charset-Encoding/ADT/list.tpp"
#endif