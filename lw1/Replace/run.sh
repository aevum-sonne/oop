EXECUTABLE=main.out
g++ -std=c++17 main.cpp -o $EXECUTABLE && sh tests.sh $EXECUTABLE