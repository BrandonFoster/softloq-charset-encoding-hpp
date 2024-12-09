#ifndef SOFTLOQ_CHARSET_ENCODING_ADT_STACK_HPP
#define SOFTLOQ_CHARSET_ENCODING_ADT_STACK_HPP

#include "Softloq-Charset-Encoding/ADT/list.hpp"

#include <optional>

namespace Softloq::Charset
{
    template <class T>
    class Stack : public List<T>
    {
    public:
        // Standard iterator support

        using size_type = List<T>::size_type;
        using iterator = List<T>::iterator;
        using const_iterator = List<T>::const_iterator;
        using reverse_iterator = List<T>::reverse_iterator;
        using const_reverse_iterator = List<T>::const_reverse_iterator;

        SOFTLOQ_CHARSET_ENCODING_API Stack();

        // The rule of five

        SOFTLOQ_CHARSET_ENCODING_API ~Stack();
        SOFTLOQ_CHARSET_ENCODING_API Stack(const Stack<T> &stack);
        SOFTLOQ_CHARSET_ENCODING_API Stack<T> &operator=(const Stack<T> &stack);
        SOFTLOQ_CHARSET_ENCODING_API Stack(Stack<T> &&stack);
        SOFTLOQ_CHARSET_ENCODING_API Stack<T> &operator=(Stack<T> &&stack);

        // Although stacks are lists, for each must not be used with them; instead, a combination of while and pop is more appropriate.

        SOFTLOQ_CHARSET_ENCODING_API iterator begin() = delete;
        SOFTLOQ_CHARSET_ENCODING_API const_iterator begin() const = delete;
        SOFTLOQ_CHARSET_ENCODING_API const_iterator cbegin() const noexcept = delete;

        SOFTLOQ_CHARSET_ENCODING_API reverse_iterator rbegin() = delete;
        SOFTLOQ_CHARSET_ENCODING_API const_reverse_iterator rbegin() const = delete;
        SOFTLOQ_CHARSET_ENCODING_API const_reverse_iterator crbegin() const noexcept = delete;

        SOFTLOQ_CHARSET_ENCODING_API iterator end() = delete;
        SOFTLOQ_CHARSET_ENCODING_API const_iterator end() const = delete;
        SOFTLOQ_CHARSET_ENCODING_API const_iterator cend() const noexcept = delete;

        SOFTLOQ_CHARSET_ENCODING_API reverse_iterator rend() = delete;
        SOFTLOQ_CHARSET_ENCODING_API const_reverse_iterator rend() const = delete;
        SOFTLOQ_CHARSET_ENCODING_API const_reverse_iterator crend() const noexcept = delete;

        // Inherited constructors/assignments

        SOFTLOQ_CHARSET_ENCODING_API Stack(const List<T> &list);
        SOFTLOQ_CHARSET_ENCODING_API Stack<T> &operator=(const List<T> &list);
        SOFTLOQ_CHARSET_ENCODING_API Stack(List<T> &&list);
        SOFTLOQ_CHARSET_ENCODING_API Stack<T> &operator=(List<T> &&list);

        // Intra stack member functions

        SOFTLOQ_CHARSET_ENCODING_API void appendItem(const T &item) = delete;
        SOFTLOQ_CHARSET_ENCODING_API void prependItem(const T &item) = delete;
        SOFTLOQ_CHARSET_ENCODING_API void removeItems(const std::function<bool(const T &)> &cond) = delete;

        SOFTLOQ_CHARSET_ENCODING_API inline void pushItem(const T &item) { List<T>::appendItem(item); }
        SOFTLOQ_CHARSET_ENCODING_API std::optional<T> popItem();
        SOFTLOQ_CHARSET_ENCODING_API inline std::optional<T> peekStack() { return List<T>::isEmpty() ? std::optional<T>() : *List<T>::rbegin(); }

    private:
    };
}
#include "Softloq-Charset-Encoding/ADT/stack.tpp"

#endif