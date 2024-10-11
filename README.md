# Requirements
A CURL library exposed to your CMAKE toolchain. Easily done using vcpkg and changing the `CMAKE_TOOLCHAIN_FILE` in the `CMakeLists.txt`.

# How to build
Use CMAKE with your build tool of choice. Personally, I use `ninja`. An example run would be:
```
cmake -B build -G Ninja
```
```
cd build
```
```
./CurlHelper.exe
```
