####
# FPrime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
# More information in the F´ CMake API documentation:
# https://fprime.jpl.nasa.gov/latest/docs/user-manual/build-system/cmake-api/
#
####

register_fprime_module(
    AUTOCODER_INPUTS
        "${CMAKE_CURRENT_LIST_DIR}/AccumulatorAdapter.fpp"
    SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/AccumulatorAdapter.cpp"
)

register_fprime_ut(
    AUTOCODER_INPUTS
        "${CMAKE_CURRENT_LIST_DIR}/AccumulatorAdapter.fpp"
    SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/AccumulatorAdapterTestMain.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/AccumulatorAdapterTester.cpp"
    UT_AUTO_HELPERS
)

