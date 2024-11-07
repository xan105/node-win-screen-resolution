import test from "node:test";
import assert from "node:assert/strict";
import { getCurrentResolution } from "../../lib/index.js";
import { setDPI } from "../util/setDPI.js";
import { setTimeout } from "node:timers/promises";

test("DPI awareness", async() => {
  await test(" reported resolution shouldn't change", async() => {
    const resolution = getCurrentResolution();
    for (const level of [ 125, 100 ])
    {
      await setDPI({ level });
      await setTimeout(3 * 1000);
      const current = getCurrentResolution();
      assert.deepEqual(current, resolution);
    }
  });
});

