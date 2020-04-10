#!/bin/sh
clear

readonly OUTPUT_FILE="output.txt"
readonly EXPECTED_PATH="Expected"

EXECUTABLE=$1
EXPECTED_FILE=""
currentTest=0
passedTests=0
byte=0
shiftInterval=0
shiftDirection='L'

# 1. Without args
((currentTest = currentTest+1))
if (!(./$EXECUTABLE))
    then
        ((passedTests = passedTests+1))
        echo "TEST $currentTest PASSED (Without args).\n"
else
    echo "TEST $currentTest FAILED (Without args).\n"
fi

# 2. Without argument <byte> or <shiftInterval>
((currentTest = currentTest+1))
if (!(./$EXECUTABLE 1 $shiftDirection))
    then
        ((passedTests = passedTests+1))
        echo "TEST $currentTest PASSED (Without argument <byte> or <shiftInterval>).\n"
else
    echo "TEST $currentTest FAILED (Without argument <byte> or <shiftInterval>).\n"
fi

# 3. If <byte> and <shiftInterval> isn't int
((currentTest = currentTest+1))
byte="byte"
shiftInterval="interval"
if (!(./$EXECUTABLE $byte $shiftInterval $shiftDirection))
    then
        ((passedTests = passedTests+1))
        echo "TEST $currentTest PASSED (<byte> and <shiftInterval> isn't int).\n"
else
    echo "TEST $currentTest FAILED (<byte> and <shiftInterval> isn't int).\n"
fi

# 4. Without argument <shiftDirection>
((currentTest = currentTest+1))
byte=17
shiftInterval=2
if (!(./$EXECUTABLE $byte $shiftInterval))
    then
        ((passedTests = passedTests+1))
        echo "TEST $currentTest PASSED (Without argument <shiftDirection>).\n"
else
    echo "TEST $currentTest FAILED (Without argument <shiftDirection>).\n"
fi

# 5. If <shiftDirection> isn't 'L' or 'R'
((currentTest = currentTest+1))
shiftDirection='M'
if (!(./$EXECUTABLE $byte $shiftInterval $shiftDirection))
    then
        ((passedTests = passedTests+1))
        echo "TEST $currentTest PASSED (<shiftDirection> isn't 'L' or 'R').\n"
else
    echo "TEST $currentTest FAILED (<shiftDirection> isn't 'L' or 'R').\n"
fi

# 6. If byte < 0
((currentTest = currentTest+1))
shiftDirection=L
byte=-1
if (!(./$EXECUTABLE $byte $shiftInterval $shiftDirection))
    then
        ((passedTests = passedTests+1))
        echo "TEST $currentTest PASSED (Byte < 0).\n"
else
    echo "TEST $currentTest FAILED (Byte < 0).\n"
fi


# 7. If byte > INT_SIZE
((currentTest = currentTest+1))
byte=256
if (!(./$EXECUTABLE $byte $shiftInterval $shiftDirection))
    then
        ((passedTests = passedTests+1))
        echo "TEST $currentTest PASSED (Byte > INT_SIZE).\n"
else
    echo "TEST $currentTest FAILED (Byte > INT_SIZE).\n"
fi

# 8. Byte = 0
((currentTest = currentTest+1))
byte=0
shiftInterval=2
shiftDirection=L
EXPECTED_FILE="zerobyte.txt"
./$EXECUTABLE $byte $shiftInterval $shiftDirection
if (cmp $OUTPUT_FILE $EXPECTED_PATH/$EXPECTED_FILE)
    then
        ((passedTests = passedTests+1))
        echo "TEST $currentTest PASSED (Byte = 0).\n"
else
    echo "TEST $currentTest FAILED (Byte = 0).\n"
fi

# 9. ./RotateByte 17 2 L
((currentTest = currentTest+1))
byte=17
shiftInterval=2
shiftDirection='L'
EXPECTED_FILE="9.txt"
./$EXECUTABLE $byte $shiftInterval $shiftDirection
if (cmp $OUTPUT_FILE $EXPECTED_PATH/$EXPECTED_FILE)
    then
        ((passedTests = passedTests+1))
        echo "TEST $currentTest PASSED (./RotateByte 17 2 L).\n"
else
    echo "TEST $currentTest FAILED (./RotateByte 17 2 L).\n"
fi

# 10. ./RotateByte 5 3 R
((currentTest = currentTest+1))
byte=5
shiftInterval=2
shiftDirection=R
EXPECTED_FILE="10.txt"
./$EXECUTABLE $byte $shiftInterval $shiftDirection
if (cmp $OUTPUT_FILE $EXPECTED_PATH/$EXPECTED_FILE)
    then
        ((passedTests = passedTests+1))
        echo "TEST $currentTest PASSED (./RotateByte 5 3 R).\n"
else
    echo "TEST $currentTest FAILED (./RotateByte 5 3 R).\n"
fi

# 11. Byte = 255
((currentTest = currentTest+1))
byte=255
shiftInterval=3
shiftDirection=L
EXPECTED_FILE="255byte.txt"
./$EXECUTABLE $byte $shiftInterval $shiftDirection
if (cmp $OUTPUT_FILE $EXPECTED_PATH/$EXPECTED_FILE)
    then
        ((passedTests = passedTests+1))
        echo "TEST $currentTest PASSED (Byte = 255).\n"
else
    echo "TEST $currentTest FAILED (Byte = 255).\n"
fi

if (passedTests=overalTests)
    then
        echo "All tests passed. ($passedTests / $currentTest)"
else
    echo "Passed $passedTests / $currentTest tests."
fi
