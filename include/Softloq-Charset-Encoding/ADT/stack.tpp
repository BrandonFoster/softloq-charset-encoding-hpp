#include "Softloq-Charset-Encoding/ADT/stack.hpp"

namespace Softloq::Charset
{
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API Stack<T>::Stack() : List<T>() {}

    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API Stack<T>::~Stack() {}
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API Stack<T>::Stack(const Stack<T> &stack) : List<T>(stack) {}
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API Stack<T> &Stack<T>::operator=(const Stack<T> &stack) { *this = List<T>::operator=(stack); }
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API inline Stack<T>::Stack(Stack<T> &&stack) : List<T>(std::move(stack)) {}
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API inline Stack<T> &Stack<T>::operator=(Stack<T> &&stack) { *this = List<T>::operator=(std::move(stack)); }

    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API Stack<T>::Stack(const List<T> &list) : List<T>(list) {}
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API Stack<T> &Stack<T>::operator=(const List<T> &list) { *this = List<T>::operator=(list); }
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API inline Stack<T>::Stack(List<T> &&list) : List<T>(std::move(list)) {}
    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API inline Stack<T> &Stack<T>::operator=(List<T> &&list) { *this = List<T>::operator=(std::move(list)); }

    template <class T>
    SOFTLOQ_CHARSET_ENCODING_API std::optional<T> Stack<T>::popItem()
    {
        if (List<T>::isEmpty())
            return {};
        typename List<T>::Node *back = List<T>::back;
        T item = back->item;
        List<T>::back = List<T>::back->prev;
        delete back;
        if (List<T>::back)
            List<T>::back->next = nullptr;
        else
            List<T>::front = nullptr;
        List<T>::size--;
        return item;
    }
}