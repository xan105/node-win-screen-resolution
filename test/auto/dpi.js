import test from "node:test";
import assert from "node:assert/strict";
import { getCurrentDisplayMode } from "../../lib/index.js";
import { setDPI } from "../util/setDPI.js";
import { setTimeout } from "node:timers/promises";

test("DPI awareness", async() => {
  await test(" reported resolution shouldn't change but scale factor should", async() => {
    const { width, height } = getCurrentDisplayMode();
    for (const scale of [ 125, 100 ])
    {
      await setDPI({ scale });
      await setTimeout(3 * 1000);
      const current = getCurrentDisplayMode();
      assert.deepEqual(current.width, width);
      assert.deepEqual(current.height, height);
      assert.deepEqual(current.scale, scale);
    }
  });
});

