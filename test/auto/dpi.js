import t from 'tap';
import { current } from "../../lib/esm.js";
import { setDPI } from "../util/setDPI.js";
import { setTimeout } from "node:timers/promises";
import { isWin10orGreater } from "@xan105/is/win";

const monitor = 1; //Change to your setup

if (isWin10orGreater())
{
  t.test('dpi awareness', async t => {
    const start = current();
    await setDPI({level: 125, monitor: monitor});
    await setTimeout(3 * 1000);
    const afterChange = current();
    t.same(afterChange,start,"reported resolution shouldn't change");
    await setDPI({monitor: monitor});
    await setTimeout(3 * 1000);
    const reset = current();
    t.same(reset,start,"reported resolution shouldn't change");
    t.end();
  });
}
/* else...
win8, etc (legacy) dpi change requires session logout/login
*/
