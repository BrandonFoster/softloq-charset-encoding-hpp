// #include <catch2/catch_test_macros.hpp>
#include <Softloq-Charset-Encoding/DataType/datatype.hpp>
#include <Softloq-Charset-Encoding/ADT/list.hpp>
#include <Softloq-Charset-Encoding/ADT/stack.hpp>
#include <Softloq-Charset-Encoding/ADT/queue.hpp>
#include <iostream>

int main()
{
    using namespace Softloq::Charset;

    Codepoint b{0x1A30F};
    b = 0x34;
    std::cout << b << std::endl;
    std::cout << "Size: " << sizeof(const Byte) << std::endl;

    Queue<Byte> byte_list;
    byte_list.enqueueItem({0xF3});
    byte_list.enqueueItem({0x36});
    byte_list.enqueueItem({0xAE});
    byte_list.enqueueItem({0x4F});
    std::cout << "Last Value: " << byte_list.peekQueue().value() << std::endl;
    Queue<Byte> byte_list2 = byte_list.sortListAscendingOrder();
    while (!byte_list.isEmpty())
        std::cout << "Test1: " << byte_list.dequeueItem().value() << std::endl;
    while (!byte_list2.isEmpty())
        std::cout << "Test2: " << byte_list2.dequeueItem().value() << std::endl;
    Stack<Byte> stack;
}