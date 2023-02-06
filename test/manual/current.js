import { getCurrentResolution, getCurrentDisplayMode } from "../../lib/index.js";

const { width, height } = getCurrentResolution();
console.log(`Current screen resolution is ${width}x${height}`);

console.log(getCurrentDisplayMode());

