#include "Softloq-Charset-Encoding/ADT/queue.hpp"

namespace Softloq::Charset
{
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API Queue<T>::Queue() : List<T>() {}

    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API Queue<T>::~Queue() {}
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API Queue<T>::Queue(const Queue<T> &queue) : List<T>(queue) {}
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API Queue<T> &Queue<T>::operator=(const Queue<T> &queue) { *this = List<T>::operator=(queue); }
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API inline Queue<T>::Queue(Queue<T> &&queue) : List<T>(std::move(queue)) {}
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API inline Queue<T> &Queue<T>::operator=(Queue<T> &&queue) { *this = List<T>::operator=(std::move(queue)); }

    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API Queue<T>::Queue(const List<T> &list) : List<T>(list) {}
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API Queue<T> &Queue<T>::operator=(const List<T> &list) { *this = List<T>::operator=(list); }
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API inline Queue<T>::Queue(List<T> &&list) : List<T>(std::move(list)) {}
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API inline Queue<T> &Queue<T>::operator=(List<T> &&list) { *this = List<T>::operator=(std::move(list)); }

    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API std::optional<T> Queue<T>::dequeueItem()
    {
        if (List<T>::isEmpty())
            return {};
        typename List<T>::Node *front = List<T>::front;
        T item = front->item;
        List<T>::front = List<T>::front->next;
        delete front;
        if (List<T>::front)
            List<T>::front->prev = nullptr;
        else
            List<T>::back = nullptr;
        List<T>::size--;
        return item;
    }
}