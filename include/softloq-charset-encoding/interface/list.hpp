#ifndef SOFTLOQ_CHARSET_INTERFACE_LIST_HPP
#define SOFTLOQ_CHARSET_INTERFACE_LIST_HPP

#include "softloq-charset-encoding/error.hpp"
#include "softloq-charset-encoding/datatype/datatype.hpp"
#include <functional>
#include <list>

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
        class Iterator
        {
        public:
        private:
            Node *node;
        };

    public:
        using size_type = size_t;
        SOFTLOQ_CHARSET_ENCODING_API inline List() : size(0), front(nullptr), back(nullptr) {}
        SOFTLOQ_CHARSET_ENCODING_API inline ~List()
        {
            while (front)
            {
                Node *node = front;
                front = front->next;
                delete node;
            }
        }
        SOFTLOQ_CHARSET_ENCODING_API inline void appendItem(const T &item)
        {
            Node *node = new Node;
            node->next = nullptr;
            node->item = item;
            if (!front)
                front = back = node;
            else
            {
                back->next = node;
                back = node->next;
            }
            size++;
        }
        SOFTLOQ_CHARSET_ENCODING_API inline void prependItem(const T &item)
        {
            Node *node = new Node;
            node->next = front;
            node->item = item;
            front = node;
            size++;
        }
        SOFTLOQ_CHARSET_ENCODING_API inline void extendList(const List<T> &list)
        {
            Node *item_node = list.front;
            while (item_node)
            {
                appendItem(item_node->item);
                item_node = item_node->next;
            }
        }
        SOFTLOQ_CHARSET_ENCODING_API inline void replaceItems(const std::function<bool(const T &)> &cond, const T &item)
        {

            Node *item_node = front;
            while (item_node)
            {
                if (cond(item_node->item))
                    item_node->item = item;
                item_node = item_node->next;
            }
        }
        SOFTLOQ_CHARSET_ENCODING_API inline void insertItem(const size_type index, const T &item)
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
            insert_node->next = next_node;
            size++;
        }
        SOFTLOQ_CHARSET_ENCODING_API inline void removeItems(const std::function<bool(const T &)> &cond)
        {

            Node *prev_node = nullptr;
            Node *next_node = front;
            while (next_node)
            {
                if (cond(next_node->item))
                {
                    if (next_node == front)
                    {
                        front = front->next;
                        delete next_node;
                        next_node = front;
                    }
                    else
                    {
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
        SOFTLOQ_CHARSET_ENCODING_API inline void emptyList()
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
        SOFTLOQ_CHARSET_ENCODING_API inline constexpr bool containsItem(const T &item) const
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
        SOFTLOQ_CHARSET_ENCODING_API inline constexpr size_type getSize() const { return size; }
        SOFTLOQ_CHARSET_ENCODING_API inline constexpr size_type isEmpty() const { return size == 0; }
        SOFTLOQ_CHARSET_ENCODING_API inline T &operator[](const size_type index) const
        {
            Node *iter_node = front;
            for (size_type i = 0; i < index; ++i)
            {
                iter_node = iter_node->next;
            }
            return iter_node->item;
        }
        SOFTLOQ_CHARSET_ENCODING_API inline List<T> cloneList()
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

    private:
        Node *front, *back;
        size_type size;
    };
    template class List<Datatype::Byte>;
}

#endif