#ifndef SOFTLOQ_CHARSET_ENCODING_DATATYPE_HPP
#define SOFTLOQ_CHARSET_ENCODING_DATATYPE_HPP

#include "Softloq-Charset-Encoding/error.hpp"
#include <cstdint>

namespace Softloq::Charset
{
    /**
     * @brief Follows the behavior stated here: (https://infra.spec.whatwg.org/#byte).
     * A byte is a sequence of eight bits and is represented as "0x" followed by two ASCII upper hex digits, in the range 0x00 to 0xFF, inclusive. A byte’s value is its underlying number.
     */
    struct Byte
    {
        using value_type = uint8_t;
        value_type value = {};

        SOFTLOQ_CHARSET_ENCODING_API Byte();

        // The rule of five

        SOFTLOQ_CHARSET_ENCODING_API ~Byte();
        SOFTLOQ_CHARSET_ENCODING_API Byte(const Byte &byte);
        SOFTLOQ_CHARSET_ENCODING_API Byte &operator=(const Byte &byte);
        SOFTLOQ_CHARSET_ENCODING_API Byte(Byte &&byte);
        SOFTLOQ_CHARSET_ENCODING_API Byte &operator=(Byte &&byte);

        // Value type constructor/assigment

        SOFTLOQ_CHARSET_ENCODING_API Byte(const value_type value);
        SOFTLOQ_CHARSET_ENCODING_API Byte &operator=(const value_type value);

        SOFTLOQ_CHARSET_ENCODING_API inline operator value_type() const { return value; }

        // Output

        SOFTLOQ_CHARSET_ENCODING_API friend std::ostream &operator<<(std::ostream &out, const Byte c);
    };
    static_assert(sizeof(Byte) == 1, "Size of a Byte in the Character Set Encoding Standards must be 8-bits.");

    /**
     * @brief Follows the behavior stated here: (https://infra.spec.whatwg.org/#code-points).
     * A code point is a Unicode code point and is represented as "U+" followed by four-to-six ASCII upper hex digits, in the range U+0000 to U+10FFFF, inclusive.
     * A code point’s value is its underlying number.
     */
    struct Codepoint
    {
        using value_type = uint32_t;
        value_type value;

        SOFTLOQ_CHARSET_ENCODING_API Codepoint();

        // The rule of five

        SOFTLOQ_CHARSET_ENCODING_API ~Codepoint();
        SOFTLOQ_CHARSET_ENCODING_API Codepoint(const Codepoint &codepoint);
        SOFTLOQ_CHARSET_ENCODING_API Codepoint &operator=(const Codepoint &codepoint);
        SOFTLOQ_CHARSET_ENCODING_API Codepoint(Codepoint &&codepoint);
        SOFTLOQ_CHARSET_ENCODING_API Codepoint &operator=(Codepoint &&codepoint);

        // Value type constructor/assigment

        SOFTLOQ_CHARSET_ENCODING_API Codepoint(const value_type value);
        SOFTLOQ_CHARSET_ENCODING_API Codepoint &operator=(const value_type value);

        SOFTLOQ_CHARSET_ENCODING_API inline operator value_type() const { return value; }
        SOFTLOQ_CHARSET_ENCODING_API inline explicit operator char32_t() const { return static_cast<char32_t>(value); }

        // Output

        SOFTLOQ_CHARSET_ENCODING_API friend std::ostream &operator<<(std::ostream &out, const Codepoint &c);

        // Intra codepoint member functions

        SOFTLOQ_CHARSET_ENCODING_API inline constexpr bool isValid() const { return value <= 0x10FFFF; }
        SOFTLOQ_CHARSET_ENCODING_API inline constexpr bool isLeadingSurrogate() const { return 0xD800 <= value && value <= 0xD8FF; }
        SOFTLOQ_CHARSET_ENCODING_API inline constexpr bool isTrailingSurrogate() const { return 0xDC00 <= value && value <= 0xDFFF; }
        SOFTLOQ_CHARSET_ENCODING_API inline constexpr bool isSurrogate() const { return isLeadingSurrogate() || isTrailingSurrogate(); }
        SOFTLOQ_CHARSET_ENCODING_API inline constexpr bool isScalar() const { return !isSurrogate(); }
        SOFTLOQ_CHARSET_ENCODING_API inline constexpr bool isNoncharacter() const
        {
            switch (value)
            {
            case 0xFFFE:
            case 0xFFFF:
            case 0x1FFFE:
            case 0x1FFFF:
            case 0x2FFFE:
            case 0x2FFFF:
            case 0x3FFFE:
            case 0x3FFFF:
            case 0x4FFFE:
            case 0x4FFFF:
            case 0x5FFFE:
            case 0x5FFFF:
            case 0x6FFFE:
            case 0x6FFFF:
            case 0x7FFFE:
            case 0x7FFFF:
            case 0x8FFFE:
            case 0x8FFFF:
            case 0x9FFFE:
            case 0x9FFFF:
            case 0xAFFFE:
            case 0xAFFFF:
            case 0xBFFFE:
            case 0xBFFFF:
            case 0xCFFFE:
            case 0xCFFFF:
            case 0xDFFFE:
            case 0xDFFFF:
            case 0xEFFFE:
            case 0xEFFFF:
            case 0xFFFFE:
            case 0xFFFFF:
            case 0x10FFFE:
            case 0x10FFFF:
                return true;
            default:
                return 0xFDD0 <= value && value <= 0xFDEF;
            }
        }
        SOFTLOQ_CHARSET_ENCODING_API inline constexpr bool isASCII() const { return value <= 0x7F; }
        /** Note: This is the Infra's ASCII whitespace definition. */
        SOFTLOQ_CHARSET_ENCODING_API inline constexpr bool isWhitespace() const
        {
            switch (value)
            {
            case 0x9:
            case 0xA:
            case 0xC:
            case 0xD:
            case 0x20:
                return true;
            default:
                return false;
            }
        }
        SOFTLOQ_CHARSET_ENCODING_API inline constexpr bool isC0Control() const { return value <= 0x1F; }
        SOFTLOQ_CHARSET_ENCODING_API inline constexpr bool isControl() const { return isC0Control() || (0x7F <= value && value <= 0x9F); }
        SOFTLOQ_CHARSET_ENCODING_API inline constexpr bool isDigit() const { return 0x30 <= value && value <= 0x39; }
        SOFTLOQ_CHARSET_ENCODING_API inline constexpr bool isUpperHex() const { return isDigit() || (0x41 <= value && value <= 0x46); }
        SOFTLOQ_CHARSET_ENCODING_API inline constexpr bool isLowerHex() const { return isDigit() || (0x61 <= value && value <= 0x66); }
        SOFTLOQ_CHARSET_ENCODING_API inline constexpr bool isHex() const { return isDigit() || (0x41 <= value && value <= 0x46) || (0x61 <= value && value <= 0x66); }
        SOFTLOQ_CHARSET_ENCODING_API inline constexpr bool isUpper() const { return 0x41 <= value && value <= 0x5A; }
        SOFTLOQ_CHARSET_ENCODING_API inline constexpr bool isLower() const { return 0x61 <= value && value <= 0x7A; }
        SOFTLOQ_CHARSET_ENCODING_API inline constexpr bool isAlpha() const { return isLower() || isAlpha(); }
        SOFTLOQ_CHARSET_ENCODING_API inline constexpr bool isAlnum() const { return isDigit() || isAlpha(); }
    };
}

#endif