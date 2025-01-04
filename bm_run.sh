mkdir -p build-bm
cd build-bm
#make clean
cmake -Dtest=OFF -Dbm=ON .. && make && ./benchmark
cd -
