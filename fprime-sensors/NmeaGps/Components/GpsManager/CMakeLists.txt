####
# FPrime CMakeLists.txt:
#
# More information in the F´ CMake API documentation:
# https://fprime.jpl.nasa.gov/latest/docs/user-manual/build-system/cmake-api/
#
####

register_fprime_module(
    AUTOCODER_INPUTS
	"${CMAKE_CURRENT_LIST_DIR}/GpsManager.fpp"
    SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/GpsManager.cpp"
)

### Unit Tests ###
register_fprime_ut(
    AUTOCODER_INPUTS
        "${CMAKE_CURRENT_LIST_DIR}/GpsManager.fpp"
    SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/GpsManagerTestMain.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/GpsManagerTester.cpp"
    UT_AUTO_HELPERS
)
