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
//{ width: 1920, height: 1080, hz: 60, scale: 100, color: 32 }

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

Multi-monitor

```js
import { 
  getActiveDisplays, 
  setPrimaryDisplay 
} from "win-screen-resolution";

const displays = getActiveDisplays();
console.log(displays);
/*
[{
    id: '\\\\.\\DISPLAY1',
    adapter: 'NVIDIA GeForce GTX 1060 6GB',
    monitor: 'LG ULTRAGEAR(DisplayPort)',
    primary: true,
    width: 2560,
    height: 1440,
    hz: 165,
    scale: 100,
    offset: { x: 0, y: 0 }
  },
  {
    id: '\\\\.\\DISPLAY5',
    adapter: 'Intel(R) HD Graphics 530',
    monitor: 'Dell U2417H (HDMI)',
    primary: false,
    width: 1920,
    height: 1080,
    hz: 59,
    scale: 100,
    offset: { x: 2560, y: 0 }
  }]
*/

//Change primary display
setPrimaryDisplay(displays[1].id); //by identifier
//OR
setPrimaryDisplay(1); //by index
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

### `getCurrentDisplayMode(): object`

Get the current **primary display** video mode as follows:

```ts
{
  width: number, //Horizontal resolution
  height: number, //Vertical resolution
  hz: number, //Refresh rate
  color: number //Color depth in bits/pixel
  scale: number //DPI scale factor in %
}
```

❌ Will throw on unexpected error.

### `getAvailableDisplayMode(): object[]`

Get all available video modes from the **primary display** as follows: 

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

### `getCurrentResolution(): object`

Get the current **primary display** screen resolution as follows:

```ts
{
  width: number,
  height: number
}
```

This is a short hand to `getCurrentDisplayMode()`

❌ Will throw on unexpected error.

### `getAvailableResolution(): object[]`

Get all available screen resolutions from the **primary display** as follows sorted _from highest to lowest_ as follows:

```ts
[
  {
    width: number,
    height: number
  }
]
```

💡 Available screen resolution below _800x600_ are ignored because of Windows 10 min display resolution requirement.

This is a short hand to `getAvailableDisplayMode()`

❌ Will throw on unexpected error.

### `getActiveDisplays(): object[]`

List the current settings of every display devices attached to the desktop as follows:

```ts
[
  {
    id: string, //Device id
    adapter: string, //Adapter name
    monitor: string, //Monitor name
    primary: boolean,
    width: number, //Pixels X
    height: number, //Pixels Y
    hz: number, //Frequency
    scale: number, //DPI scale factor
    offset: { x: number, y: number } //Position in the [Windows virtual screen](https://learn.microsoft.com/en-us/windows/win32/gdi/the-virtual-screen)
  }
]
```

❌ Will throw on unexpected error.

### `setPrimaryDisplay(display: string|number): void`

Switch the primary display to specified display.

If display is a `string` then the device id is assumed;<br />
If it's a `number` then the array index is used.

Call `getActiveDisplays()` to list available displays.

⚠️ Please be carefull that the list of displays might have changed between the time you called `getActiveDisplays()` and `setPrimaryDisplay()`.
Depending on your use case you might be better of using the device id to avoid this problem.

❌ Will throw on error.<br />
❌ Will throw on unexpected error.