#include "Softloq-Charset-Encoding/DataType/datatype.hpp"
#include <iostream>
#include <iomanip>

namespace Softloq::Charset
{
    SOFTLOQ_CHARSET_ENCODING_API Byte::Byte() : value(0) {}

    SOFTLOQ_CHARSET_ENCODING_API Byte::~Byte() {}
    SOFTLOQ_CHARSET_ENCODING_API Byte::Byte(const Byte &byte) : value(byte.value) {}
    SOFTLOQ_CHARSET_ENCODING_API Byte &Byte::operator=(const Byte &byte)
    {
        value = byte.value;
        return *this;
    }
    SOFTLOQ_CHARSET_ENCODING_API Byte::Byte(Byte &&byte) : value(std::move(byte.value)) {}
    SOFTLOQ_CHARSET_ENCODING_API Byte &Byte::operator=(Byte &&byte)
    {
        value = std::move(byte.value);
        return *this;
    }

    SOFTLOQ_CHARSET_ENCODING_API Byte::Byte(const value_type value) : value(value) {}
    SOFTLOQ_CHARSET_ENCODING_API Byte &Byte::operator=(const value_type value)
    {
        Byte::value = value;
        return *this;
    }

    SOFTLOQ_CHARSET_ENCODING_API std::ostream &operator<<(std::ostream &out, const Byte c)
    {
        out << "0x" << std::hex << std::uppercase << static_cast<int_fast16_t>(c);
        return out;
    }

    SOFTLOQ_CHARSET_ENCODING_API Codepoint::Codepoint() : value(0) {}

    SOFTLOQ_CHARSET_ENCODING_API Codepoint::~Codepoint() {}
    SOFTLOQ_CHARSET_ENCODING_API Codepoint::Codepoint(const Codepoint &codepoint) : value(codepoint.value) {}
    SOFTLOQ_CHARSET_ENCODING_API Codepoint &Codepoint::operator=(const Codepoint &codepoint)
    {
        value = codepoint.value;
        return *this;
    }
    SOFTLOQ_CHARSET_ENCODING_API Codepoint::Codepoint(Codepoint &&codepoint) : value(std::move(codepoint.value)) {}
    SOFTLOQ_CHARSET_ENCODING_API Codepoint &Codepoint::operator=(Codepoint &&codepoint)
    {
        value = std::move(codepoint.value);
        return *this;
    }

    SOFTLOQ_CHARSET_ENCODING_API Codepoint::Codepoint(const value_type value) : value(value) {}
    SOFTLOQ_CHARSET_ENCODING_API Codepoint &Codepoint::operator=(const value_type value)
    {
        Codepoint::value = value;
        return *this;
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