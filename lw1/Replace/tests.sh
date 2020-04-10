#!/bin/sh
clear

currentTest=0
passedTests=0

RUN_PATH=$1
readonly OUTPUT_FILE="output.txt"
readonly INPUT_PATH="Input"
readonly EXPECTED_PATH="Expected"

# 1. Without args
((currentTest = currentTest+1))
if (!(./$RUN_PATH))
    then
        echo "TEST $currentTest PASSED. (Without args).\n"
        ((passedTests = passedTests+1))
else
    echo "TEST $currentTest FAILED.\n"
fi

# 2. Empty input
((currentTest = currentTest+1))
INPUT_FILE="empty.txt"
if (!(./$RUN_PATH $INPUT_PATH/$INPUT_FILE $OUTPUT_FILE the 123))
    then
        echo "TEST $currentTest PASSED. (Empty input).\n"
        ((passedTests = passedTests+1))
else
    echo "TEST $currentTest FAILED.\n"
fi

# 3. If input file name is empty
((currentTest = currentTest+1))
INPUT_FILE=""

if (!(./$RUN_PATH "" $OUTPUT_FILE "$searchArg" "$replaceArg"))
    then
        echo "TEST $currentTest PASSED. (Input file name is empty).\n"
        ((passedTests = passedTests+1))
else
    echo "TEST $currentTest FAILED.\n"
fi

# 4. If path to input file is empty or incorrect
((currentTest = currentTest+1))
INPUT_FILE="non-existing.file"

if (!(./$RUN_PATH $INPUT_PATH/$INPUT_FILE $OUTPUT_FILE "$searchArg" "$replaceArg"))
    then
        echo "TEST $currentTest PASSED. (Path to input file is empty or incorrect).\n"
        ((passedTests = passedTests+1))
else
    echo "TEST $currentTest FAILED.\n"
fi

# 5. If output file name is empty
((currentTest = currentTest+1))
INPUT_FILE="long.txt"

if (!(./$RUN_PATH $INPUT_PATH/$INPUT_FILE "Replace/" "$searchArg" "$replaceArg"))
    then
        echo "TEST $currentTest PASSED. (Output file name is empty).\n"
        ((passedTests = passedTests+1))
else
    echo "TEST $currentTest FAILED.\n"
fi

# 6. If path to output file is empty or incorrect
((currentTest = currentTest+1))
if (!(./$RUN_PATH $INPUT_PATH/$INPUT_FILE "" "$searchArg" "$replaceArg"))
    then
        echo "TEST $currentTest PASSED. (Path to input file is empty or incorrect).\n"
        ((passedTests = passedTests+1))
else
    echo "TEST $currentTest FAILED.\n"
fi

# 7. If both files are empty
((currentTest = currentTest+1))
if (!(./$RUN_PATH "" "" "$searchArg" "$replaceArg"))
    then
        echo "TEST $currentTest PASSED. (Both files are empty).\n"
        ((passedTests = passedTests+1))
else
    echo "TEST $currentTest FAILED.\n"
fi

# 8. Search substring is empty
((currentTest = currentTest+1))
INPUT_FILE="long.txt"
searchArg=""
replaceArg="1"

if (!(./$RUN_PATH $INPUT_PATH/$INPUT_FILE $OUTPUT_FILE "$searchArg" "$replaceArg"))
    then
        echo "TEST $currentTest PASSED. [REPLACE \"$searchArg\" TO \"$replaceArg\"] (Search substring is empty).\n"
        ((passedTests = passedTests+1))
else
    echo "TEST $currentTest FAILED.\n"
fi


# 9. Replace char
((currentTest = currentTest+1))
INPUT_FILE="char_replace.txt"
searchArg="e"
replaceArg="1"

./$RUN_PATH $INPUT_PATH/$INPUT_FILE $OUTPUT_FILE "$searchArg" "$replaceArg"
if (cmp $OUTPUT_FILE $EXPECTED_PATH/$INPUT_FILE)
    then
        echo "TEST $currentTest PASSED. [REPLACE \"$searchArg\" TO \"$replaceArg\"] (Replace char).\n"
        ((passedTests = passedTests+1))
else
    echo "TEST $currentTest FAILED.\n"
fi

# 10. One row input
((currentTest = currentTest+1))
INPUT_FILE="one_row.txt"
searchArg="the"
replaceArg="123"

./$RUN_PATH $INPUT_PATH/$INPUT_FILE $OUTPUT_FILE "$searchArg" "$replaceArg"
if (cmp $OUTPUT_FILE $EXPECTED_PATH/$INPUT_FILE)
    then
        echo "TEST $currentTest PASSED. [REPLACE \"$searchArg\" TO \"$replaceArg\"] (One row input file).\n"
        ((passedTests = passedTests+1))
else
    echo "TEST $currentTest FAILED.\n"
fi

# 11. Several rows input
((currentTest = currentTest+1))
INPUT_FILE="several_rows.txt"
searchArg="the"
replaceArg="123"

./$RUN_PATH $INPUT_PATH/$INPUT_FILE $OUTPUT_FILE "$searchArg" "$replaceArg"
if (cmp $OUTPUT_FILE $EXPECTED_PATH/$INPUT_FILE)
    then
        echo "TEST $currentTest PASSED. [REPLACE \"$searchArg\" TO \"$replaceArg\"] (Several rows input file).\n"
        ((passedTests = passedTests+1))
else
    echo "TEST $currentTest FAILED.\n"
fi

# 12. Replace in long text
((currentTest = currentTest+1))
INPUT_FILE="long.txt"
searchArg="Brothers Karamazov"
replaceArg="B. K."

./$RUN_PATH $INPUT_PATH/$INPUT_FILE $OUTPUT_FILE "$searchArg" "$replaceArg"
if (cmp $OUTPUT_FILE $EXPECTED_PATH/$INPUT_FILE)
    then
        echo "TEST $currentTest PASSED. [REPLACE \"$searchArg\" TO \"$replaceArg\"] (Long text).\n"
        ((passedTests = passedTests+1))
else
    echo "TEST $currentTest FAILED.\n"
fi

# 13. If replace subword is bigger then input file
((currentTest = currentTest+1))
INPUT_FILE="small.txt"
searchArg="the"
replaceArg="123"

if (!(./$RUN_PATH $INPUT_PATH/$INPUT_FILE $OUTPUT_FILE "$searchArg" "$replaceArg"))
    then
        echo "TEST $currentTest PASSED. [REPLACE \"$searchArg\" TO \"$replaceArg\"] (Replace subword is bigger then input file).\n"
        ((passedTests = passedTests+1))
else
    echo "TEST $currentTest FAILED.\n"
fi

# 14. Replace sentence to word
((currentTest = currentTest+1))
INPUT_FILE="sentence_to_word.txt"
searchArg="Sentence that must be replaced to one word."
replaceArg="Hello"

./$RUN_PATH $INPUT_PATH/$INPUT_FILE $OUTPUT_FILE "$searchArg" "$replaceArg"
if (cmp $OUTPUT_FILE $EXPECTED_PATH/$INPUT_FILE)
    then
        echo "TEST $currentTest PASSED. [REPLACE \"$searchArg\" TO \"$replaceArg\"] (Replace sentence to word).\n"
        ((passedTests = passedTests+1))
else
    echo "TEST $currentTest FAILED.\n"
fi

# 15.1 Replace word with multiple occurence of one syllable
((currentTest = currentTest+1))
INPUT_FILE="multiple_occurrence.txt"
EXPECTED_FILE="multiple_occurrence81.txt"
searchArg="мама"
replaceArg="м"

./$RUN_PATH $INPUT_PATH/$INPUT_FILE $OUTPUT_FILE "$searchArg" "$replaceArg"
if (cmp $OUTPUT_FILE $EXPECTED_PATH/$EXPECTED_FILE)
    then
        echo "TEST $currentTest.1 PASSED. [REPLACE \"$searchArg\" TO \"$replaceArg\"] (Replace word with multiple occurence of one syllable).\n"
        ((passedTests = passedTests+1))
else
    echo "TEST $currentTest.1 FAILED.\n"
fi

# 15.2 Replace word with multiple occurence of one syllable
INPUT_FILE="multiple_occurrence.txt"
EXPECTED_FILE="multiple_occurrence82.txt"
searchArg="12312312345"
replaceArg="1231234"

./$RUN_PATH $INPUT_PATH/$INPUT_FILE $OUTPUT_FILE "$searchArg" "$replaceArg"
if (cmp $OUTPUT_FILE $EXPECTED_PATH/$EXPECTED_FILE)
    then
        echo "TEST $currentTest.2 PASSED. [REPLACE \"$searchArg\" TO \"$replaceArg\"] (Replace word with multiple occurence of one syllable).\n"
        ((passedTests = passedTests+1))
        ((currentTest = currentTest+1))
else
    echo "TEST $currentTest.2 FAILED.\n"
fi

if (passedTests=overalTests)
    then
        echo "All tests passed. ($passedTests / $currentTest)"
else
    echo "Passed $passedTests / $currentTest tests."
fi
