import { getActiveDisplays, setPrimaryDisplay } from "../../lib/index.js";
import { stdin, stdout } from "node:process";
import { createInterface } from "node:readline/promises";

const displays = getActiveDisplays();
console.log(displays);

const rl = createInterface({ input: stdin, output: stdout }); 
const index = await rl.question("New primary display index: ");
rl.close();

setPrimaryDisplay(displays[+index].id);
//setPrimaryDisplay(+index);
