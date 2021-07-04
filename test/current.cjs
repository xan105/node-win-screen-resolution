"use strict";

const resolution = require("../lib/index.cjs");

const current = resolution.current();
console.log(`Current screen resolution is ${current.width}x${current.height}`);

setTimeout( ()=>{

const current = resolution.current();
console.log(`Current screen resolution is ${current.width}x${current.height}`);

}, 10 * 1000);