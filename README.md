A NAPI Native C++ Addons to get the current and all available screen resolution on Windows.

Example
=======

```js

const resolution = require("win-screen-resolution");

const current = resolution.current(); // {width: 1920, height: 1080}
const available = resolution.list(); // [{width: 1920, height: 1080},...]

```

Installation
============

`npm install win-screen-resolution`

You will need C/C++ build tools and Python 2.7(node-gyp) to build this module.