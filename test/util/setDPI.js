import { promisify } from "node:util";
import { exec } from "node:child_process";
import { dirname, join } from "node:path";
import { fileURLToPath } from "node:url";

async function setDPI(option = {}){

  const options = {
    level: Number.isInteger(option.level) ? option.level : 100,
    monitor: Number.isInteger(option.monitor) ? option.monitor : 0
  };

  console.warn(`Changing monitor #${options.monitor} to ${options.level}% dpi...`);
  
  const bin = join(dirname(fileURLToPath(import.meta.url)), "bin", "SetDpi.exe");
  const cmd = await promisify(exec)(`${bin} ${options.monitor} ${options.level}`,{ windowsHide: true });
  if (cmd.stderr) throw new Error(cmd.stderr);
}

export { setDPI };