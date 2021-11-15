/*
MIT License

Copyright (c) 2020-2021 Anthony Beaumont

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

import { find, load } from "node-gyp-load";
import { dirname, join } from "node:path";
import { fileURLToPath } from "node:url";
import { isWin10orGreater } from "@xan105/is/win";

const bindings = await find({
  name: isWin10orGreater() ? "resolution" : "resolution_legacy",
  dir: join(dirname(fileURLToPath(import.meta.url)), "../"),
  prebuild: true
});

const {
  GetResolutionList, 
  GetCurrentResolution 
} = load(bindings);

function list(){

  const min = { width: 800, height: 600 };
  
  let list = [];
  
  // Remove duplicate and garbage
  for(const i of GetResolutionList()) 
    if (i.width >= min.width && i.height >= min.height && !list.some(j => j.width === i.width && j.height === i.height)) 
      list.push(i); 

  // Sort by highest first  
  return list.sort((a,b) => ( b.width - a.width == 0 ) ? b.height - a.height : b.width - a.width );
}

export {
  list,
  GetCurrentResolution as current 
};