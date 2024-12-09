#include "Softloq-Charset-Encoding/DataType/datatype.hpp"
#include <iostream>
#include <iomanip>

namespace Softloq::Charset
{
    SOFTLOQ_CHARSET_ENCODING_API std::ostream &operator<<(std::ostream &out, const Byte c)
    {
        out << "0x" << std::hex << std::uppercase << static_cast<int_fast16_t>(c);
        return out;
    }

    SOFTLOQ_CHARSET_ENCODING_API std::ostream &operator<<(std::ostream &out, const Codepoint &c)
    {
        if (c <= 0xFFFF)
            out << "U+" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << static_cast<int_fast16_t>(c);
        else if (c <= 0x10FFFF)
            out << "U+" << std::hex << std::uppercase << static_cast<int_fast32_t>(c);
        else
            out << "invalid codepoint value(" << c << ")";
        return out;
    }
}