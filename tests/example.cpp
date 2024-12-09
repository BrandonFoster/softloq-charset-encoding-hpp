// #include <catch2/catch_test_macros.hpp>
#include <Softloq-Charset-Encoding/DataType/datatype.hpp>
#include <Softloq-Charset-Encoding/ADT/list.hpp>
#include <iostream>

int main()
{
    using namespace Softloq::Charset;

    Codepoint b{0x1A30F};
    b = 0x34;
    std::cout << b << std::endl;
    std::cout << "Size: " << sizeof(const Byte) << std::endl;

    List<Byte> byte_list;
    byte_list.appendItem({0xF3});
    byte_list.appendItem({0x36});
    byte_list.appendItem({0xAE});
    byte_list.appendItem({0x4F});
    List<Byte> byte_list2 = byte_list.sortListAscendingOrder();
    for (auto it = byte_list2.begin(); it != byte_list2.end(); ++it)
    {
        std::cout << "Test1: " << *it << std::endl;
    }
    for (auto it = byte_list.begin(); it != byte_list.end(); ++it)
    {
        std::cout << "Test2: " << *it << std::endl;
    }
}