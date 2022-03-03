declare interface IRes{
  width: number,
  height: number
}

export function list(): IRes[];
export function current(): IRes;