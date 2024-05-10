/*
Copyright (c) Anthony Beaumont
This source code is licensed under the MIT License
found in the LICENSE file in the root directory of this source tree.
*/

import { join } from "node:path";
import { find, load } from "node-gyp-load";
import { 
  isIntegerPositiveOrZero 
} from "@xan105/is";
import {
  shouldWin10orGreater,
  shouldObjLike,
  shouldArrayOfObjLike
} from "@xan105/is/assert";
import { Failure } from "@xan105/error";

const bindings = await find({
  name: "video",
  dir: join(import.meta.dirname, "../"),
  prebuild: true
});

shouldWin10orGreater();
const module = load(bindings);

function getAvailableDisplayMode(){
  try{
    const result = module.getAvailableDisplayMode();
    shouldArrayOfObjLike(result,{
      width: isIntegerPositiveOrZero,
      height: isIntegerPositiveOrZero,
      hz: isIntegerPositiveOrZero,
      color: isIntegerPositiveOrZero
    }, new Failure("Unexpected result", {code: 2, info: {
      type: typeof result,
      value: result
    }}));
    
    return result;

  }catch(err){
    throw new Failure("An unexpected error occured with the native addon !", { 
      code: 0, 
      cause: err, 
      info: { bindings }
    });
  }
}

function getCurrentDisplayMode(){
  try{
    const result = module.getCurrentDisplayMode();
    shouldObjLike(result,{
      width: isIntegerPositiveOrZero,
      height: isIntegerPositiveOrZero,
      hz: isIntegerPositiveOrZero,
      color: isIntegerPositiveOrZero
    }, new Failure("Unexpected result", {code: 2, info: {
      type: typeof result,
      value: result
    }}));
    
    return result;
    
  }catch(err){
    throw new Failure("An unexpected error occured with the native addon !", { 
      code: 0, 
      cause: err, 
      info: { bindings }
    });
  }
}

function getCurrentResolution(){
  const { width, height } = getCurrentDisplayMode();
  return { width, height };
}

function getAvailableResolution(){

  const min = { width: 800, height: 600 };

  return getAvailableDisplayMode()
  .reduce((accumulator, current) => {

    // Remove duplicate and garbage
    const doublon = ({width, height}) => width === current.width && height === current.height;

    if (!accumulator.find(doublon) && 
        current.width >= min.width && 
        current.height >= min.height) 
    { 
      accumulator.push({
        width: current.width, 
        height: current.height
      });
    }

    return accumulator;
  }, [])
  // Sort by highest first
  .sort((a,b) => b.width - a.width === 0 ? b.height - a.height : b.width - a.width );
}

export {
  getCurrentResolution,
  getCurrentResolution as current, //old api name (compatibility)
  getAvailableResolution,
  getAvailableResolution as list, //old api name (compatibility)
  getAvailableDisplayMode,
  getCurrentDisplayMode
};