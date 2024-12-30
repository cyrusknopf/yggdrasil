cd build
#make clean
cmake -Dtest=ON -Dbm=OFF .. && make && ./runTests
cd -
