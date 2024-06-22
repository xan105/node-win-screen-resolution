About
=====

A NAPI Native C++ addon to get the current and all available screen resolution on Windows (DPI Aware).

Example
=======

```js
import { 
  getCurrentResolution, 
  getAvailableResolution 
} from "win-screen-resolution";

console.log(getCurrentResolution()); 
//{ width: 1920, height: 1080 }

console.log(getAvailableResolution());
/*
[
  { width: 1920, height: 1080 },
  { width: 1768, height: 992 },
  { width: 1680, height: 1050 },
  { width: 1600, height: 1024 },
  ...
]
*/
```

You may want the raw data which has more information such as the refresh rate:

```js
import { 
  getCurrentDisplayMode, 
  getAvailableDisplayMode 
} from "win-screen-resolution";

console.log(getCurrentDisplayMode()); 
//{ width: 1920, height: 1080, hz: 60, color: 32 }

console.log(getAvailableDisplayMode());
/*
[
  { width: 640, height: 480, hz: 59, color: 32 },
  { width: 640, height: 480, hz: 60, color: 32 },
  { width: 640, height: 480, hz: 75, color: 32 },
  { width: 720, height: 480, hz: 60, color: 32 },
  ...
]
*/

```

Installation
============

```
npm install win-screen-resolution
```

🚀 x86, x64 and arm64 prebuilt binary provided.

Force compiling:
```
npm install win-screen-resolution --build-from-source
```

You will need C/C++ build tools and Python 3.x (node-gyp) to build this module.

API
===

⚠️ This module is only available as an ECMAScript module (ESM) starting with version 2.0.0.<br />
Previous version(s) are CommonJS (CJS) with an ESM wrapper.

**DPI Awareness**

The following exports are DPI aware meaning that their results won't change with different DPI scalor factor.
Please note that support for DPI awareness on Windows 7/8 was removed in 3.x. If you need it use previous version.

## Named export

#### `getCurrentDisplayMode(): object`

Get the current **primary display** video mode as follows:

```ts
{
  width: number, //Horizontal resolution
  height: number, //Vertical resolution
  hz: number, //Refresh rate
  color: number //Color depth in bits/pixel
}
```

❌ Will throw on unexpected error.

#### `getAvailableDisplayMode(): object[]`

Get all available display video mode from the current display device on which the calling thread is running as follows: 

```ts
[
  {
    width: number, //Horizontal resolution
    height: number, //Vertical resolution
    hz: number, //Refresh rate
    color: number //Color depth in bits/pixel
  }
]
```

❌ Will throw on unexpected error.

#### `getCurrentResolution(): object`

alias: `current()` _backward compatibility_

Get the current **primary display** screen resolution as follows:

```ts
{
  width: number,
  height: number
}
```

This is a short hand to `getCurrentDisplayMode()`

❌ Will throw on unexpected error.

#### `getAvailableResolution(): object[]`

alias: `list()` _backward compatibility_

Get all available screen resolution from the current display device on which the calling thread is running sorted _from highest to lowest_ as follows:

```ts
[
  {
    width: number,
    height: number
  }
]
```

💡 Available screen resolution below 800x600 are ignored because of Windows 10 min display resolution requirement.

This is a short hand to `getAvailableDisplayMode()`

❌ Will throw on unexpected error.