import { getCurrentDisplayMode } from "../../lib/index.js";

console.log(getCurrentDisplayMode());

const { width, height, hz, dpi } = getCurrentDisplayMode();
console.log(`Primary screen is ${width}x${height}@${hz}hz (${dpi}%)`);
