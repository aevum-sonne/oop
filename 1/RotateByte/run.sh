EXECUTABLE=RotateByte.out
g++ -std=c++17 RotateByte.cpp -o $EXECUTABLE && sh tests.sh $EXECUTABLE && rm RotateByte.out