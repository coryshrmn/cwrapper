# CWrapper [![Build Status](https://travis-ci.org/coryshrmn/cwrapper.svg?branch=master)](https://travis-ci.org/coryshrmn/cwrapper)

Header-only C++14 utilities for wrapping C libraries.

## Features

* Enable bitwise operations on type-safe `enum class`es, for wrapping C bit flags.
* Manage C resources with movable `cwrapper::Resource` class.

### Tested compilers

* g++ 6
* clang++ 4.0

## Using CWrapper

### Including CWrapper

Include the [include](include) directory to your project,
and add `#include "cwrapper.hpp"` in your code.

### Examples

* [glwrapper](https://www.github.com/coryshrmn/glwrapper)
* [sdlwrapper](https://www.github.com/coryshrmn/sdlwrapper)
* [test](test) files

## License

Apache License 2.0, see [LICENSE.txt](LICENSE.txt)
