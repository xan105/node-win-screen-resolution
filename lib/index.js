/*
Copyright (c) Anthony Beaumont
This source code is licensed under the MIT License
found in the LICENSE file in the root directory of this source tree.
*/

import { deprecate } from "node:util";
import { dirname, join } from "node:path";
import { fileURLToPath } from "node:url";
import { find, load } from "node-gyp-load";
import { 
  isWin8orLesser, 
  isIntegerPositiveOrZero 
} from "@xan105/is";
import { 
  shouldObjLike,
  shouldArrayOfObjLike
} from "@xan105/is/assert";
import { Failure } from "@xan105/error";

const legacy = {
  is: isWin8orLesser(),
  warning: "Windows 7/8 are EOL; Support for these platforms is pending removal !"
}

const bindings = await find({
  name: legacy.is ? "resolution_legacy" : "resolution",
  dir: join(dirname(fileURLToPath(import.meta.url)), "../"),
  prebuild: true
});

const {
  GetResolutionList, 
  GetCurrentResolution 
} = load(bindings);

function _GetResolutionList(){

  const result = legacy.is ? 
                 deprecate(GetResolutionList, legacy.warning)() :
                 GetResolutionList();
  
  shouldArrayOfObjLike(result,{
    width: isIntegerPositiveOrZero,
    height: isIntegerPositiveOrZero 
  }, new Failure("Unexpected data from the native addon !", { code: 0, info: { 
      bindings,
      type: typeof result,
      value: result
    }})
  );
  
  return result;
}

function _GetCurrentResolution(){

  const result = legacy.is ? 
                 deprecate(GetCurrentResolution, legacy.warning)() :
                 GetCurrentResolution();

  shouldObjLike(result,{
    width: isIntegerPositiveOrZero,
    height: isIntegerPositiveOrZero 
  }, new Failure("Unexpected data from the native addon !", { code: 0, info: { 
      bindings,
      type: typeof result,
      value: result
    }})
  );
  
  return result;
}

function list(){

  const min = { width: 800, height: 600 };
  
  let list = [];

  // Remove duplicate and garbage
  for(const res of _GetResolutionList()){ 
    if (
      res.width >= min.width && res.height >= min.height && 
      !list.some(o => o.width === res.width && o.height === res.height)
    ) {
      list.push(res); 
    }
  }

  // Sort by highest first
  return list.sort((a,b) => (b.width - a.width) == 0 ? b.height - a.height : b.width - a.width );
}

export {
  _GetCurrentResolution as current,
  list
};