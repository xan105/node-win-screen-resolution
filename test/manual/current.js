import { getCurrentDisplayMode } from "../../lib/index.js";

const { width, height, hz } = getCurrentDisplayMode();
console.log(`Primary screen is ${width}x${height}@${hz}hz`);
