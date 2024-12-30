args=("$@")

cd build-driver
cmake -Dtest=OFF -Dbm=OFF .. && make && ./driver 5
cd -
