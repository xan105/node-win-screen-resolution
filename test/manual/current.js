import { getCurrentDisplayMode } from "../../lib/index.js";

console.log(getCurrentDisplayMode());

const { width, height, hz, scale } = getCurrentDisplayMode();
console.log(`Primary screen is ${width}x${height}@${hz}hz (${scale}%)`);
