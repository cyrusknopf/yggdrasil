args=("$@")

cd build
cmake -Dtest=OFF -Dbm=OFF .. && make && ./driver 5
cd -
