
rm -rf build && mkdir build && cd build && cmake .. && make && cd ..

cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
cmake --build .

./bin/starships
