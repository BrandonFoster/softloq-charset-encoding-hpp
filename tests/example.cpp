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
    byte_list = byte_list.cloneList();
    for (auto it = byte_list.begin(); it != byte_list.end(); ++it)
    {
        std::cout << "Forward: " << *it << std::endl;
    }
    for (auto it = byte_list.rbegin(); it != byte_list.rend(); ++it)
    {
        std::cout << "Backward: " << *it << std::endl;
    }
}