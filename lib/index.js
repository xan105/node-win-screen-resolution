/*
Copyright (c) Anthony Beaumont
This source code is licensed under the MIT License
found in the LICENSE file in the root directory of this source tree.
*/

import { find, load } from "node-gyp-load";
import { dirname, join } from "node:path";
import { fileURLToPath } from "node:url";
import { isWin10orGreater } from "@xan105/is";

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