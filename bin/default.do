redo-ifchange "../build/$1.o"
DEPS=$(../odeps "../build/$1.o")
redo-ifchange ../link ${DEPS}
../link "$3" "../build/$1.o" ${DEPS}
