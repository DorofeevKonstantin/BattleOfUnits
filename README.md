# Battle of Units

## C++ task

### Build steps:
mkdir build && cd build
cmake -D CMAKE_CXX_COMPILER=clang++-18 ..
//cmake -D CMAKE_CXX_COMPILER=g++ ..
//cmake -G "Visual Studio 17 2022" ..
make
./sw_battle_test ../commands_example.txt
