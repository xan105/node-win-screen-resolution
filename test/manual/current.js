import { current } from "../../lib/esm.js";

const { width, height } = current();
console.log(`Current screen resolution is ${width}x${height}`);