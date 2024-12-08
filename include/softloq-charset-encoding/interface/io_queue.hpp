#ifndef SOFTLOQ_CHARSET_INTERFACE_IO_QUEUE_HPP
#define SOFTLOQ_CHARSET_INTERFACE_IO_QUEUE_HPP

#include "softloq-charset-encoding/error.hpp"
#include "softloq-charset-encoding/datatype/datatype.hpp"

namespace Softloq::Charset::Interface
{
    // template <class T>
    // class IOQueue
    // {
    // public:
    //     class Item
    //     {
    //     public:

    //     protected:
    //         bool eoq_toggle;
    //     };

    //     SOFTLOQ_CHARSET_ENCODING_API virtual void readItem() = 0;
    //     SOFTLOQ_CHARSET_ENCODING_API virtual void readItems() = 0;
    //     SOFTLOQ_CHARSET_ENCODING_API virtual void peekItems() = 0;
    //     SOFTLOQ_CHARSET_ENCODING_API virtual void pushItem() = 0;
    //     SOFTLOQ_CHARSET_ENCODING_API virtual void pushItems() = 0;

    // protected:
    //     class Node
    //     {
    //     };

    //     SOFTLOQ_CHARSET_ENCODING_API void enableEOQ() {}
    // };

    // template <class T>
    // class ImmediateQueue final : public IOQueue<T>
    // {
    // public:
    //     SOFTLOQ_CHARSET_ENCODING_API inline ImmediateQueue()
    //     {
    //         typename IOQueue<T>::Item item;
    //         item.eoq_toggle = true;
    //     }

    //     SOFTLOQ_CHARSET_ENCODING_API inline void readItem() override {}
    //     SOFTLOQ_CHARSET_ENCODING_API inline void readItems() override {}
    //     SOFTLOQ_CHARSET_ENCODING_API inline void peekItems() override {}
    //     SOFTLOQ_CHARSET_ENCODING_API inline void pushItem() override {}
    //     SOFTLOQ_CHARSET_ENCODING_API inline void pushItems() override {}

    // private:
    // };
    // template class ImmediateQueue<Datatype::Byte>;
    // template class ImmediateQueue<Datatype::Codepoint>;

    // template <class T>
    // class StreamingQueue final : public IOQueue<T>
    // {
    // public:
    //     // SOFTLOQ_CHARSET_ENCODING_API inline StreamingQueue()
    //     // {
    //     //     IOQueue<T>::head = nullptr;
    //     //     IOQueue<T>::size = 0;
    //     // }

    //     SOFTLOQ_CHARSET_ENCODING_API inline void readItem() override {}
    //     SOFTLOQ_CHARSET_ENCODING_API inline void readItems() override {}
    //     SOFTLOQ_CHARSET_ENCODING_API inline void peekItems() override {}
    //     SOFTLOQ_CHARSET_ENCODING_API inline void pushItem() override {}
    //     SOFTLOQ_CHARSET_ENCODING_API inline void pushItems() override {}

    // private:
    // };
    // template class StreamingQueue<Datatype::Byte>;
    // template class StreamingQueue<Datatype::Codepoint>;
}

#endif