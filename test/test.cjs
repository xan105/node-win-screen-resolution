"use strict";

const resolution = require("../index.cjs");

const current = resolution.current();
console.log(`Current screen resolution is ${current.width}x${current.height}`);

const available = resolution.list();
console.log(`Available resolutions (${available.length}):`);
console.log(available);