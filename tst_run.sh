mkdir -p build-test
cd build-test
#make clean
cmake -Dtest=ON -Dbm=OFF .. && make && ./runTests
cd -
