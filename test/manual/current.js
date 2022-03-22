import { current } from "../../lib/index.js";

const { width, height } = current();
console.log(`Current screen resolution is ${width}x${height}`);