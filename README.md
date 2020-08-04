A NAPI Native C++ Addons to get the current and all available screen resolution on Windows.

Example
=======

```js

const resolution = require("win-screen-resolution");

const current = resolution.current(); // {width: i, height: i}
const available = resolution.list(); // [{width: i, height: i}, ... ]

console.log(current); // { width: 1920, height: 1080 }
console.log(available);
/*
[
  { width: 1920, height: 1080 },
  { width: 1768, height: 992 },
  { width: 1680, height: 1050 },
  { width: 1600, height: 900 },
  { width: 1360, height: 768 },
  { width: 1280, height: 720 },
  { width: 1176, height: 664 },
  { width: 1152, height: 864 },
  { width: 1024, height: 768 },
  { width: 800, height: 600 },
  { width: 640, height: 480 }
]
*/

```

Installation
============

`npm install win-screen-resolution`

You will need C/C++ build tools and Python 2.7(node-gyp) to build this module.