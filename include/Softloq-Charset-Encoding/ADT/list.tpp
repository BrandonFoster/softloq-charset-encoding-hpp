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
    SOFTLOQ_CHARSET_ENCODING_API List<T> List<T>::sortListAscendingOrder()
    {
        List<T> sorted{*this};
        static constexpr auto cond = std::less_equal<T>();
        sorted.front = mergeSort(sorted.front, cond);
        Node *back = sorted.front;
        while (back && back->next)
            back = back->next;
        sorted.back = back;
        return sorted;
    }
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API List<T> List<T>::sortListDescendingOrder()
    {
        List<T> sorted{*this};
        static constexpr auto cond = std::greater<T>();
        sorted.front = mergeSort(sorted.front, cond);
        Node *back = sorted.front;
        while (back && back->next)
            back = back->next;
        sorted.back = back;
        return sorted;
    }

    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API List<T>::Node *List<T>::mergeSort(Node *head, const std::function<const bool(const T &, const T &)> &cond)
    {
        // Base case: if the list is empty or has only one node, it is already sorted.
        if (!head || !head->next)
            return head;

        // Split into two halves.
        Node *second = mergeSplit(head);

        // Recursively sort each half.
        head = mergeSort(head, cond);
        second = mergeSort(second, cond);

        // Merge the two sorted halves.
        return merge(head, second, cond);
    }
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API List<T>::Node *List<T>::mergeSplit(Node *head)
    {
        Node *fast = head;
        Node *slow = head;

        // Move fast pointer two steps and slow pointer one step until fast reaches the end.
        while (fast && fast->next && fast->next->next)
        {
            fast = fast->next->next;
            slow = slow->next;
        }

        // Split the list into two halves.
        Node *temp = slow->next;
        slow->next = nullptr;
        if (temp)
            temp->prev = nullptr;

        return temp;
    }
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API List<T>::Node *List<T>::merge(Node *first, Node *second, const std::function<const bool(const T &, const T &)> &cond)
    {
        // If either list is empty, return the other list.
        if (!first)
            return second;
        if (!second)
            return first;

        // Pick the conditional value between first and second nodes.
        if (cond(first->item, second->item))
        {
            // Recursively merge the rest of the lists and link the result to the current node.
            first->next = merge(first->next, second, cond);
            if (first->next)
                first->next->prev = first;
            first->prev = nullptr;
            return first;
        }
        else
        {
            // Recursively merge the rest of the lists and link the result to the current node.
            second->next = merge(first, second->next, cond);
            if (second->next)
                second->next->prev = second;
            second->prev = nullptr;
            return second;
        }
    }
}