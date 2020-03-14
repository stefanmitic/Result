# Result
Result is a simple, header only (can also be used as a static library), std::optional replacement that works with int values (enums) instead of bool.
It could be extended to work with other types as well.

# How to build tests
Make sure that you have installed gtest through VCPKG (or any other means, as long as find_package(GTest CONFIG REQUIRED) can find it).
If working with VCPKG pass -DCMAKE_TOOLCHAIN_FILE="[[path_to_vcpkg]]/scripts/buildsystems/vcpkg.cmake" to CMake during config.