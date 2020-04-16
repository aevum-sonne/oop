#!/bin/sh
clear

currentTest=0
passedTests=0

EXECUTABLE=$1

readonly INPUT_PATH="Tests/Input"
readonly EXPECTED_PATH="Tests/Expected"
readonly OUTPUT_FULL_PATH="output.txt"
FIN1="empty.txt"
FIN2="empty.txt"
EXPECTED_FILE=""

# 1. Without args
((currentTest = currentTest+1))
echo "$currentTest"
if (!(./$EXECUTABLE))
    then
        ((passedTests = passedTests+1))
        echo "TEST $currentTest PASSED. (Without args)\n"
else
    echo "TEST $currentTest FAILED. (Without args)\n"
fi

# 2. One input file
((currentTest = currentTest+1))
if (!(./$EXECUTABLE $INPUT_PATH/$FIN1))
    then
        ((passedTests = passedTests+1))
        echo "TEST $currentTest PASSED. (One input file)\n"
else
    echo "TEST $currentTest FAILED. (One input file)\n"
fi

# 3. If first file is missing
((currentTest = currentTest+1))
FIN1="missing.txt"
if (!(./$EXECUTABLE $INPUT_PATH/$FIN1 $INPUT_PATH/$FIN2))
    then
        ((passedTests = passedTests+1))
        echo "TEST $currentTest PASSED. (First file is missing)\n"
else
    echo "TEST $currentTest FAILED. (First file is missing)\n"
fi

# 4. If second file is missing
((currentTest = currentTest+1))
FIN1="matrix11.txt"
FIN2="missing.txt"
if (!(./$EXECUTABLE $INPUT_PATH/$FIN1 $INPUT_PATH/$FIN2))
    then
        ((passedTests = passedTests+1))
        echo "TEST $currentTest PASSED. (Second file is missing)\n"
else
    echo "TEST $currentTest FAILED. (Second file is missing)\n"
fi

# 5. Empty input
((currentTest = currentTest+1))
FIN1="empty.txt"
if (!(./$EXECUTABLE $INPUT_PATH/$FIN1 $INPUT_PATH/$FIN2))
    then
        ((passedTests = passedTests+1))
        echo "TEST $currentTest PASSED. (Empty input)\n"
else
    echo "TEST $currentTest FAILED.\n"
fi

# 6. Matrix * Zero Matrix
((currentTest = currentTest+1))
FIN1="matrix11.txt"
FIN2="zero.txt"
EXPECTED_FILE="zero.txt"
./$EXECUTABLE $INPUT_PATH/$FIN1 $INPUT_PATH/$FIN2
if (cmp $OUTPUT_FULL_PATH $EXPECTED_PATH/$EXPECTED_FILE)
    then
        ((passedTests = passedTests+1))
        echo "TEST $currentTest PASSED. (Matrix * Zero matrix)\n"
else
    echo "TEST $currentTest FAILED. (Matrix * Zero matrix)\n"
fi

# 7. Matrix * Unit Matrix
((currentTest = currentTest+1))
FIN1="unitmatrix.txt"
FIN2="unit.txt"
EXPECTED_FILE="unit.txt"
./$EXECUTABLE $INPUT_PATH/$FIN1 $INPUT_PATH/$FIN2
if (cmp $OUTPUT_FULL_PATH $EXPECTED_PATH/$EXPECTED_FILE)
    then
        ((passedTests = passedTests+1))
        echo "TEST $currentTest PASSED. (Matrix * Unit Matrix)\n"
else
    echo "TEST $currentTest FAILED. (Matrix * Unit Matrix)\n"
fi

# 8. Matrix11 * Matrix12
((currentTest = currentTest+1))
FIN1="matrix11.txt"
FIN2="matrix12.txt"
EXPECTED_FILE="matrix1.txt"
./$EXECUTABLE $INPUT_PATH/$FIN1 $INPUT_PATH/$FIN2
if (cmp $OUTPUT_FULL_PATH $EXPECTED_PATH/$EXPECTED_FILE)
    then
        ((passedTests = passedTests+1))
        echo "TEST $currentTest PASSED. (Matrix11 * Matrix12)\n"
else
    echo "TEST $currentTest FAILED. (Matrix11 * Matrix12)\n"
fi

# 9. Matrix12 * Matrix11
((currentTest = currentTest+1))
FIN1="matrix12.txt"
FIN2="matrix11.txt"
EXPECTED_FILE="matrix2.txt"
./$EXECUTABLE $INPUT_PATH/$FIN1 $INPUT_PATH/$FIN2
if (cmp $OUTPUT_FULL_PATH $EXPECTED_PATH/$EXPECTED_FILE)
    then
        ((passedTests = passedTests+1))
        echo "TEST $currentTest PASSED. (Matrix12 * Matrix11)\n"
else
    echo "TEST $currentTest FAILED. (Matrix12 * Matrix11)\n"
fi

if (passedTests=overalTests)
    then
        echo "All tests passed. ($passedTests / $currentTest)"
else
    echo "Passed $passedTests / $currentTest tests."
fi
