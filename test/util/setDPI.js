import { promisify } from "node:util";
import { exec } from "node:child_process";
import { join } from "node:path";
import { 
  asIntegerPositive, 
  asIntegerWithinRange 
} from "@xan105/is/opt";
import { shouldObj } from "@xan105/is/assert";
import { Failure, attempt } from "@xan105/error";
import { hashFile } from "@xan105/fs";

async function setDPI(option = {}){
  
  shouldObj(option);
  
  const options = {
    level: asIntegerWithinRange(option.level, 100, 200) ?? 100, //in % scale
    monitor: asIntegerPositive(option.monitor) ?? 1
  };

  console.warn(`Changing monitor #${options.monitor} to ${options.level}% dpi...`);
  
  const bin = join(import.meta.dirname, "bin/SetDpi.exe");
  
  const expected = "eca21767ac80bc5d40ab8e2c52589e7b5f050aa7daef774fa9abb61aefba58ce";
  const hash = await hashFile(bin,"sha256");
  if (hash !== expected)
    throw new Failure("Hash mismatch ! vendor binary was altered ?", { code: 0, info: { expected, hash } });
  
  const [cmd, err] = await attempt(promisify(exec),[
    `${bin} ${options.monitor} ${options.level}`, 
    { windowsHide: true }
  ]);
  if (err || cmd.stderr) throw new Failure(err?.stderr || cmd.stderr, 0);
}

export { setDPI };