import { current } from "../lib/esm.js";

const { width, height } = current();
console.log(`Current screen resolution is ${width}x${height}`);

//Timeout to change DPI settings manually
setTimeout( ()=>{
  const { width, height } = current();
  console.log(`Current screen resolution is ${width}x${height}`);
}, 10 * 1000);