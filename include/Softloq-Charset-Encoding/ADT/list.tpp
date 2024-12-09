#include "Softloq-Charset-Encoding/ADT/list.hpp"

namespace Softloq::Charset
{
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API List<T>::BaseIterator::BaseIterator() : prev(nullptr), curr(nullptr) {}
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API List<T>::BaseIterator::BaseIterator(Node *prev, Node *curr) : prev(prev), curr(curr) {}
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API List<T>::BaseIterator::BaseIterator(const BaseIterator &it) : prev(it.prev), curr(it.curr) {}
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API List<T>::BaseIterator::~BaseIterator() {}

    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API List<T>::Iterator::Iterator() : BaseIterator() {}
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API List<T>::Iterator::Iterator(Node *prev, Node *curr) : BaseIterator(prev, curr) {}
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API List<T>::Iterator::Iterator(const Iterator &it) : BaseIterator(it.prev, it.curr) {}

    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API List<T>::ReverseIterator::ReverseIterator() : BaseIterator() {}
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API List<T>::ReverseIterator::ReverseIterator(Node *prev, Node *curr) : BaseIterator(prev, curr) {}
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API List<T>::ReverseIterator::ReverseIterator(const ReverseIterator &it) : BaseIterator(it.prev, it.curr) {}

    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API List<T>::List() : size(0), front(nullptr), back(nullptr) {}
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API List<T>::~List()
    {
        while (front)
        {
            Node *node = front;
            front = front->next;
            delete node;
        }
    }
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API List<T>::List(const List<T> &list) : size(0), front(nullptr), back(nullptr)
    {
        Node *item_node = list.front;
        while (item_node)
        {
            appendItem(item_node->item);
            item_node = item_node->next;
        }
    }
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API List<T> &List<T>::operator=(const List<T> &list)
    {
        if (this != &list)
        {
            emptyList();

            Node *item_node = list.front;
            while (item_node)
            {
                appendItem(item_node->item);
                item_node = item_node->next;
            }
        }
        return *this;
    }
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API List<T>::List(List<T> &&list) : size(std::move(list.size)), front(std::move(list.front)), back(std::move(list.back))
    {
        list.front = nullptr;
        list.back = nullptr;
        list.size = 0;
    }
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API List<T> &List<T>::operator=(List<T> &&list)
    {
        front = std::move(list.front);
        back = std::move(list.back);
        size = std::move(list.size);
        list.front = nullptr;
        list.back = nullptr;
        list.size = 0;
        return *this;
    }

    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API void List<T>::appendItem(const T &item)
    {
        Node *node = new Node;
        node->next = nullptr;
        node->item = item;
        if (!front)
        {
            node->prev = nullptr;
            front = back = node;
        }
        else
        {
            node->prev = back;
            back->next = node;
            back = node;
        }
        size++;
    }
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API void List<T>::prependItem(const T &item)
    {
        Node *node = new Node;
        node->prev = nullptr;
        node->next = front;
        node->item = item;
        front->prev = node;
        front = node;
        size++;
    }
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API void List<T>::extendList(const List<T> &list)
    {
        Node *item_node = list.front;
        while (item_node)
        {
            appendItem(item_node->item);
            item_node = item_node->next;
        }
    }
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API void List<T>::replaceItems(const std::function<bool(const T &)> &cond, const T &item)
    {

        Node *item_node = front;
        while (item_node)
        {
            if (cond(item_node->item))
                item_node->item = item;
            item_node = item_node->next;
        }
    }
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API void List<T>::insertItem(const size_type index, const T &item)
    {
        if (!index)
        {
            prependItem(item);
            return;
        }

        Node *insert_node = new Node;
        insert_node->item = item;

        Node *prev_node = nullptr;
        Node *next_node = front;
        for (size_type i = 0; i < index; ++i)
        {
            prev_node = next_node;
            next_node = next_node->next;
        }
        prev_node->next = insert_node;
        insert_node->prev = prev_node;
        insert_node->next = next_node;
        if (next_node)
            next_node->prev = insert_node;
        size++;
    }
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API void List<T>::removeItems(const std::function<bool(const T &)> &cond)
    {
        Node *prev_node = nullptr;
        Node *next_node = front;
        while (next_node)
        {
            if (cond(next_node->item))
            {
                if (next_node == front)
                {
                    if (front->next)
                        front->next->prev = nullptr;
                    front = front->next;
                    delete next_node;
                    next_node = front;
                }
                else
                {
                    if (next_node->next)
                        next_node->next->prev = prev_node;
                    prev_node->next = next_node->next;
                    delete next_node;
                    next_node = prev_node->next;
                }
                size--;
            }
            else
            {
                prev_node = next_node;
                next_node = next_node->next;
            }
        }
    }
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API void List<T>::emptyList()
    {
        while (front)
        {
            Node *node = front;
            front = front->next;
            delete node;
        }
        front = back = nullptr;
        size = 0;
    }
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API const bool List<T>::containsItem(const T &item) const
    {
        Node *item_node = front;
        while (item_node)
        {
            if (item_node->item == item)
                return true;
            item_node = item_node->next;
        }
        return false;
    }
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API T &List<T>::operator[](const size_type index) const
    {
        Node *iter_node = front;
        for (size_type i = 0; i < index; ++i)
        {
            iter_node = iter_node->next;
        }
        return iter_node->item;
    }
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API List<T> List<T>::cloneList()
    {
        List<T> clone;
        Node *iter_node = front;
        while (iter_node)
        {
            clone.appendItem(iter_node->item);
            iter_node = iter_node->next;
        }
        return clone;
    }
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API List<T> List<T>::sortListAscending()
    {
        List<T> sorted = cloneList();
        static const auto ascending_cond = [](const T &item1, const T &item2) -> const bool
        { return item1 <= item2; };
        if (sorted.getSize())
            mergeSort(&sorted.front, &sorted.back, size, ascending_cond);
        return sorted;
    }
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API List<T> List<T>::sortListDescending()
    {
        List<T> sorted;
        static const auto descending_cond = [](const T &item1, const T &item2) -> const bool
        { return item1 > item2; };
        if (sorted.getSize())
            mergeSort(&sorted.front, &sorted.back, size, descending_cond);
        return sorted;
    }

    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API void List<T>::mergeSort(
        Node **left_node_ptr, Node **right_node_ptr, const size_type size,
        const std::function<const bool(const T &, const T &)> &cond)
    {
        if (size <= 1)
            return;
        const size_type mid_size = size / 2;
        Node *mid_node = *left_node_ptr;
        for (size_type i = 0; i < mid_size - 1; ++i)
            mid_node = mid_node->next;
        if (size % 2)
        {
            // Divide
            mergeSort(&mid_node->next, right_node_ptr, mid_size + 1, cond);
            mergeSort(left_node_ptr, &mid_node, mid_size, cond);

            // Conquer
            merge(left_node_ptr, mid_size, right_node_ptr, cond);
        }
        else
        {
            // Divide
            mergeSort(&mid_node->next, right_node_ptr, mid_size, cond);
            mergeSort(left_node_ptr, &mid_node, mid_size, cond);

            // Conquer
            merge(left_node_ptr, mid_size, right_node_ptr, cond);
        }
    }
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API void List<T>::merge(
        Node **left_node_ptr, const size_type mid_size, Node **right_node_ptr,
        const std::function<const bool(const T &, const T &)> &cond)
    {
    }
}