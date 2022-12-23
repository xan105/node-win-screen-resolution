About
=====

A NAPI Native C++ Addons to get the current and all available screen resolution on Windows.

Example
=======

```js

import { current, list } from "win-screen-resolution";

console.log(current()); //{ width: 1920, height: 1080 }
console.log(list());
/*
[
  { width: 1920, height: 1080 },
  { width: 1768, height: 992 },
  { width: 1680, height: 1050 },
  { width: 1600, height: 1024 },
  { width: 1600, height: 900 },
  { width: 1366, height: 768 },
  { width: 1360, height: 768 },
  { width: 1280, height: 1024 },
  { width: 1280, height: 960 },
  { width: 1280, height: 800 },
  { width: 1280, height: 768 },
  { width: 1280, height: 720 },
  { width: 1176, height: 664 },
  { width: 1152, height: 864 },
  { width: 1024, height: 768 },
  { width: 800, height: 600 }
]
*/
```

Installation
============

```
npm install win-screen-resolution
```

Force compiling:
```
npm install win-screen-resolution --build-from-source
```

You will need C/C++ build tools and Python 3.x (node-gyp) to build this module.<br />
🚀 x64 prebuilt binary provided.

API
===

⚠️ This module is only available as an ECMAScript module (ESM) starting with version 2.0.0.<br />
Previous version(s) are CommonJS (CJS) with an ESM wrapper.

## Named export

#### `list(): object[]`

List all available screen resolution. HighDPI supported (DPI Aware).

```ts
[
  {
    width: number,
    height: number
  }
]
```

NB: Available screen resolution below 800x600 are ignored because of Windows 10 min display resolution requirement.

#### `current(): object`

Get current screen resolution (primary display). HighDPI supported (DPI Aware).

```ts
{
  width: number,
  height: number
}
```