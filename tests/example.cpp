#include <catch2/catch_test_macros.hpp>
#include <softloq-charset-encoding/utf8.hpp>
#include <softloq-charset-encoding/datatype/datatype.hpp>
#include <softloq-charset-encoding/interface/io_queue.hpp>
#include <softloq-charset-encoding/interface/list.hpp>
#include <iostream>

TEST_CASE("UTF-8 Charset Encoding", "[utf8]")
{
}

TEST_CASE("Charset Encoding Datatypes", "[datatypes]")
{
    using namespace Softloq::Charset;

    Datatype::Codepoint b{0x1A30F};
    b = 0x34;
    std::cout << b << std::endl;
    std::cout << "Size: " << sizeof(const Datatype::Byte) << std::endl;
    // Interface::ImmediateQueue<Datatype::Codepoint> queue;
    // if (queue.eoq())
    // {
    //     std::cout << "HEllo\n";
    // }
}