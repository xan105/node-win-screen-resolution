declare interface Resolution{
  width: number,
  height: number
}

declare interface VideoMode{
  width: number,
  height: number,
  hz: number,
  color: number
}

export function getCurrentResolution(): Resolution;
export function getAvailableResolution(): Resolution[];
export function getAvailableDisplayMode(): VideoMode[];
export function getCurrentDisplayMode(): VideoMode;
export { getCurrentResolution as current, getAvailableResolution as list };
