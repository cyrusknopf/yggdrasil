args=("$@")

mkdir -p build-driver
cd build-driver
cmake -Dtest=OFF -Dbm=OFF .. && make && ./driver 15
cd -
