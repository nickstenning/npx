TEST_FILES=$(find ../src/test -name \*.cpp)
redo-ifchange ${TEST_FILES}

TEST_OFILES=$(for t in $TEST_FILES; do
  echo "${t%.cpp}.o" | cut -d/ -f3-
done)
redo-ifchange $TEST_OFILES

ALL_OFILES=$(for of in $TEST_OFILES; do
  echo "$of"
  ../tools/odeps "$of"
done |
sort |
uniq)

redo-ifchange ${ALL_OFILES}

clang++ -lc++ -o"$3" ${ALL_OFILES}