#ifndef SOFTLOQ_CHARSET_ENCODING_ERROR_HPP
#define SOFTLOQ_CHARSET_ENCODING_ERROR_HPP

/**
 * @author Brandon Foster
 * @file error.hpp
 * @version 1.0.0
 * @brief Holds an error that occurs for the charset encoding functions and classes.
 */

#include "softloq-charset-encoding/libmacro.hpp"
#include <string>

namespace Softloq::Charset
{
    /** @brief Unicode error handle. */
    struct Error
    {
        /** @brief The error message. */
        std::string message;
    };
}

#endif