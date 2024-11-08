/*
Copyright (c) Anthony Beaumont
This source code is licensed under the MIT License
found in the LICENSE file in the root directory of this source tree.
*/

import { join } from "node:path";
import { dlopen } from "node-gyp-load";
import { 
  isStringNotEmpty,
  isIntegerPositiveOrZero 
} from "@xan105/is";
import { shouldWin10orGreater } from "@xan105/is/assert";
import { attemptify, errorLookup, Failure } from "@xan105/error";

//Load bindings
const NAPI = await dlopen({
  name: "video",
  cwd: join(import.meta.dirname, "../")
});

function getAvailableDisplayMode(){
  shouldWin10orGreater();
  return NAPI.getAvailableDisplayMode();
}
function getCurrentDisplayMode(){
  shouldWin10orGreater();
  return NAPI.getCurrentDisplayMode();
}

function getCurrentResolution(){
  shouldWin10orGreater();
  
  const { width, height } = NAPI.getCurrentDisplayMode();
  return { width, height };
}

function getAvailableResolution(){
  shouldWin10orGreater();
  
  const min = { width: 800, height: 600 };

  return NAPI.getAvailableDisplayMode()
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

function getActiveDisplays(){
  shouldWin10orGreater();
  return NAPI.getActiveDisplays();
}

function setPrimaryDisplay(display){
  shouldWin10orGreater();
  
  if (!(isStringNotEmpty(display) || isIntegerPositiveOrZero(display))){
    throw new Failure("Target display should be either a string (target name) or a number (target index) !", 1);
  };

  const [ code, err ] = attemptify(NAPI.changePrimaryDisplay)(display);
  if(err) throw new Failure(err.message, "ERR_WRONG_USAGE");
  if(code !== 0) throw new Failure(...errorLookup(code));
}

export {
  getAvailableDisplayMode,
  getCurrentDisplayMode,
  getCurrentResolution,
  getAvailableResolution,
  getActiveDisplays,
  setPrimaryDisplay
};