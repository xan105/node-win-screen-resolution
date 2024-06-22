/*
Copyright (c) Anthony Beaumont
This source code is licensed under the MIT License
found in the LICENSE file in the root directory of this source tree.
*/

import { join } from "node:path";
import { dlopen } from "node-gyp-load";
import { 
  isIntegerPositiveOrZero 
} from "@xan105/is";
import {
  shouldWin10orGreater,
  shouldObjLike,
  shouldArrayOfObjLike
} from "@xan105/is/assert";
import { Failure } from "@xan105/error";

shouldWin10orGreater();

//Load bindings
const module = await dlopen({
  name: "video",
  cwd: join(import.meta.dirname, "../")
});

function getAvailableDisplayMode(){
  const result = module.getAvailableDisplayMode();
  
  //Better safe than sorry
  shouldArrayOfObjLike(result,{
    width: isIntegerPositiveOrZero,
    height: isIntegerPositiveOrZero,
    hz: isIntegerPositiveOrZero,
    color: isIntegerPositiveOrZero
  }, new Failure("Unexpected result", {code: 2, info: {
    type: typeof result,
    tag: Object.prototype.toString.call(result),
    value: result
  }}));
    
  return result;
}

function getCurrentDisplayMode(){

  const result = module.getCurrentDisplayMode();
    
  //Better safe than sorry
  shouldObjLike(result,{
    width: isIntegerPositiveOrZero,
    height: isIntegerPositiveOrZero,
    hz: isIntegerPositiveOrZero,
    color: isIntegerPositiveOrZero
  }, new Failure("Unexpected result", {code: 2, info: {
    type: typeof result,
    tag: Object.prototype.toString.call(result),
    value: result
  }}));
    
  return result;
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