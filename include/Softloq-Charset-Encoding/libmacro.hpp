#ifndef SOFTLOQ_CHARSET_ENCODING_LIBMACRO_HPP
#define SOFTLOQ_CHARSET_ENCODING_LIBMACRO_HPP

/**
 * @author Brandon Foster
 * @file libmacro.hpp
 * @version 1.0.0
 * @brief Shared/Static Library Macro.
 */

// Static/Shared Build Macros

#if defined(_MSC_VER)
#define SOFTLOQ_CHARSET_ENCODING_EXPORT __declspec(dllexport)
#define SOFTLOQ_CHARSET_ENCODING_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
#define SOFTLOQ_CHARSET_ENCODING_EXPORT __attribute__((visibility("default")))
#define SOFTLOQ_CHARSET_ENCODING_IMPORT
#endif

// For Standalone Builds

#if defined(SOFTLOQ_CHARSET_ENCODING_NO_API)
#define SOFTLOQ_CHARSET_ENCODING_API
#elif defined(SOFTLOQ_CHARSET_ENCODING_BUILD_API)
#define SOFTLOQ_CHARSET_ENCODING_API SOFTLOQ_CHARSET_ENCODING_EXPORT
#elif defined(SOFTLOQ_CHARSET_ENCODING_USE_API)
#define SOFTLOQ_CHARSET_ENCODING_API SOFTLOQ_CHARSET_ENCODING_IMPORT
#endif

// For Monolithic Builds

#ifndef SOFTLOQ_CHARSET_ENCODING_API
#if defined(SOFTLOQ_NO_API)
#define SOFTLOQ_CHARSET_ENCODING_API
#elif defined(SOFTLOQ_BUILD_API)
#define SOFTLOQ_CHARSET_ENCODING_API SOFTLOQ_CHARSET_ENCODING_EXPORT
#elif defined(SOFTLOQ_USE_API)
#define SOFTLOQ_CHARSET_ENCODING_API SOFTLOQ_CHARSET_ENCODING_IMPORT
#endif
#endif

// Static Build By Default

#ifndef SOFTLOQ_CHARSET_ENCODING_API
/** @brief Static/Shared Build Macro. */
#define SOFTLOQ_CHARSET_ENCODING_API
#endif

#endif