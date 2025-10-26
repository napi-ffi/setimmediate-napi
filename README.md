@napi-ffi/setimmediate-napi
===========================
### `setImmediate()` for N-API code

[![CI](https://github.com/napi-ffi/setimmediate-napi/actions/workflows/ci.yml/badge.svg)](https://github.com/napi-ffi/setimmediate-napi/actions/workflows/ci.yml)
[![NPM Version](https://img.shields.io/npm/v/@napi-ffi/setimmediate-napi.svg?style=flat)](https://npmjs.org/package/@napi-ffi/setimmediate-napi)
[![NPM Downloads](https://img.shields.io/npm/dm/@napi-ffi/setimmediate-napi.svg?style=flat)](https://npmjs.org/package/@napi-ffi/setimmediate-napi)

> Forked from [node-ffi-napi/setimmediate-napi](https://github.com/node-ffi-napi/setimmediate-napi) to maintain and modernize the project while preserving the original APIs.

Installation
------------

Install with `npm`:

``` bash
$ npm install @napi-ffi/setimmediate-napi
```

Usage
-----

In your `binding.gyp`:

```python
    'include_dirs': ["<!@(node -p \"require('node-addon-api').include\")",
                     "<!@(node -p \"require('@napi-ffi/setimmediate-napi').include\")"],
```

(Just have `"<!@(node -p \"require('@napi-ffi/setimmediate-napi').include\")"` somewhere in that list, ok?)

In your C++ code:

```c++
#include <setimmediate.h>

int a = 10;
SetImmediate(env, [a]() {
  /* do something with a ... */
});
```

Keep in mind:
- You need to use `Reference`s to keep track of JS objects, since this code runs asynchronously.
- Use `MakeCallback` rather than `Call` to make sure Node.js can track your async context.
- This function can be invoked even when executing JS code itself is not allowed.
