[![Unit-Testing](https://github.com/BrandonFoster/softloq-charset-encoding-hpp/actions/workflows/tests.yml/badge.svg)](https://github.com/BrandonFoster/softloq-charset-encoding-hpp/actions/workflows/tests.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

### Version 1.0.0
# About
[Documentation](https://brandonfoster.github.io/softloq-charset-encoding-hpp/)

Softloq Software C++ headers for standard character set encodings. Provide a decoder and encoder for the character sets describe here: https://encoding.spec.whatwg.org/

# Usage Example
W.i.P.

# CMake Build
## Options
* BUILD_SHARED_LIBS [ON/OFF]:

    Controls building source as shared or static library files.
    
    Default: OFF.
* SOFTLOQ_CHARSET_ENCODING_BUILD_TESTING [ON/OFF]:

    Controls building unit-testing.
    
    Default: OFF.

## Shared Library
When using the shared library, add compiler definition: SOFTLOQ_CHARSET_ENCODING_USE_API or SOFTLOQ_USE_API.

SOFTLOQ_USE_API is recommended when using multiple shared Softloq libraries.

Handled when added via CMake target_link_libraries().

# Running Tests
## Targets
W.i.P.
## Building
Set the CMake option SOFTLOQ_CHARSET_ENCODING_BUILD_TESTING to ON.

The targets will be built to their respective output folder.
