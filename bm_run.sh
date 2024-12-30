cd build
#make clean
cmake -Dtest=OFF -Dbm=ON .. && make && ./benchmark
cd -
