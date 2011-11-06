TEST_FILES=$(find src/test -name \*.cpp)
redo-ifchange ${TEST_FILES}

TEST_OFILES=$(for t in $TEST_FILES; do
  echo "build/$(echo "${t%.cpp}" | sed 's/src\///').o"
done)
redo-ifchange $TEST_OFILES

ALL_OFILES=$(for of in $TEST_OFILES; do
  echo "$of"
  ./odeps "$of"
done |
sort |
uniq)

redo-ifchange link ${ALL_OFILES}

clang++ -lc++ -lboost_unit_test_framework-mt -o"$3" ${ALL_OFILES}