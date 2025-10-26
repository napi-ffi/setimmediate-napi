/**
 * JavaScript test runner for setimmediate.h
 */

const addon = require('../build/Release/test_setimmediate.node');

console.log('Running setimmediate-napi tests...\n');
const exitCode = addon.runTests();

// Give SetImmediate callbacks a chance to execute
setImmediate(() => {
    console.log('All deferred callbacks have executed.');
    process.exit(exitCode);
});
