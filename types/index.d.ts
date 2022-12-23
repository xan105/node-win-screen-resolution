declare interface Resolution{
  width: number,
  height: number
}

declare function _GetCurrentResolution(): Resolution;
export function list(): Resolution[];
export { _GetCurrentResolution as current };
