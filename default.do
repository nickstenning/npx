if [ ! -e "src/$1.d" ]; then
  redo-ifchange src/$1.o
fi

read DEPS < src/$1.d
O_FILES=$(for d in ${DEPS#*:}; do echo ${d%.*}.o; done)

redo-ifchange ${O_FILES}       
clang++ -lc++ -o $3 ${O_FILES}
