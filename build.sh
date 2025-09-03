rm -rf ./out
rm -rf ./build
mkdir build
cd build
cmake ..
make VERBOSE=1
make install
