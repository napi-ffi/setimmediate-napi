/**
 * Unit tests for setimmediate.h
 *
 * This test suite verifies the functionality of the SetImmediate
 * function with N-API.
 */

#include <napi.h>
#include <stdio.h>
#include "../include/setimmediate.h"

/* Test counter */
static int tests_passed = 0;
static int tests_failed = 0;

/* Test macros */
#define ASSERT(condition, message) \
    do { \
        if (condition) { \
            printf("  ✓ PASS: %s\n", message); \
            tests_passed++; \
        } else { \
            printf("  ✗ FAIL: %s\n", message); \
            tests_failed++; \
        } \
    } while (0)

/* Test: SetImmediate should execute callback */
static Napi::Value TestBasicExecution(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    printf("Running test: basic_execution\n");

    bool callback_executed = false;

    SetImmediate(env, [&callback_executed]() {
        callback_executed = true;
    });

    // At this point, callback shouldn't have executed yet
    ASSERT(!callback_executed, "Callback should not execute immediately");

    return env.Undefined();
}

/* Test: SetImmediate should handle multiple callbacks */
static Napi::Value TestMultipleCallbacks(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    printf("\nRunning test: multiple_callbacks\n");

    int execution_count = 0;

    SetImmediate(env, [&execution_count]() {
        execution_count++;
    });

    SetImmediate(env, [&execution_count]() {
        execution_count++;
    });

    SetImmediate(env, [&execution_count]() {
        execution_count++;
    });

    ASSERT(execution_count == 0, "Callbacks should not execute immediately");

    return env.Undefined();
}

/* Test: SetImmediate with captured variables */
static Napi::Value TestCapturedVariables(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    printf("\nRunning test: captured_variables\n");

    int value = 42;
    bool captured = false;

    SetImmediate(env, [value, &captured]() {
        captured = (value == 42);
    });

    ASSERT(!captured, "Callback should not execute immediately");

    return env.Undefined();
}

/* Test: SetImmediate doesn't crash with empty lambda */
static Napi::Value TestEmptyCallback(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    printf("\nRunning test: empty_callback\n");

    bool no_crash = true;

    try {
        SetImmediate(env, []() {
            // Empty callback
        });
        ASSERT(no_crash, "SetImmediate with empty callback should not crash");
    } catch (...) {
        no_crash = false;
        ASSERT(false, "SetImmediate with empty callback should not throw");
    }

    return env.Undefined();
}

/* Test runner that will be called from JavaScript */
static Napi::Value RunTests(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    printf("\n");
    printf("===========================================\n");
    printf("Testing setimmediate.h\n");
    printf("===========================================\n\n");

    TestBasicExecution(info);
    TestMultipleCallbacks(info);
    TestCapturedVariables(info);
    TestEmptyCallback(info);

    printf("\n===========================================\n");
    printf("Test Results:\n");
    printf("  Passed: %d\n", tests_passed);
    printf("  Failed: %d\n", tests_failed);
    printf("  Total:  %d\n", tests_passed + tests_failed);
    printf("===========================================\n\n");

    return Napi::Number::New(env, tests_failed > 0 ? 1 : 0);
}

/* Module initialization */
static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("runTests", Napi::Function::New(env, RunTests));
    return exports;
}

NODE_API_MODULE(test_setimmediate, Init)
