//ES Module Wrapper
//https://nodejs.org/api/esm.html#esm_dual_commonjs_es_module_packages

import module from './index.cjs';
export const list = module.list;
export const current = module.current;