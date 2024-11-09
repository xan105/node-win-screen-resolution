declare interface Resolution{
  width: number,
  height: number
}

declare interface Scale{
  x: number,
  y: number
}

declare interface VideoMode{
  width: number,
  height: number,
  hz: number,
  color: number,
  scale?: number|Scale
}

declare interface DisplayInfo{
  id: string,
  adapter: string,
  monitor: string,
  primary: boolean,
  width: number,
  height: number,
  hz: number,
  scale: number|Scale,
  offset: { x: number, y: number }  
}

export function getCurrentResolution(): Resolution;
export function getAvailableResolution(): Resolution[];
export function getAvailableDisplayMode(): VideoMode[];
export function getCurrentDisplayMode(): VideoMode;
export function getActiveDisplays(): DisplayInfo[];
export function setPrimaryDisplay(display: string|number): void;



