import t from 'tap';
import { getCurrentResolution } from "../../lib/index.js";
import { setDPI } from "../util/setDPI.js";
import { setTimeout } from "node:timers/promises";

const monitor = 1; //Change to your setup

t.test("dpi awareness", async t => {
  const start = getCurrentResolution();
  await setDPI({level: 125, monitor: monitor});
  await setTimeout(3 * 1000);
  const afterChange = getCurrentResolution();
  t.same(afterChange,start,"reported resolution shouldn't change");
  await setDPI({monitor: monitor});
  await setTimeout(3 * 1000);
  const reset = getCurrentResolution();
  t.same(reset,start,"reported resolution shouldn't change");
  t.end();
});

