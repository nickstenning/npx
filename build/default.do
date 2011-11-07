redo-ifchange "$1.o"
DEPS=$(../tools/odeps "$1.o")
redo-ifchange link ${DEPS}
./link "$3" "$1.o" ${DEPS}
