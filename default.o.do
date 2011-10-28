if [ -e $1.cpp ]; then
  redo-ifchange $1.cpp
  ./cc $1 $2 $3
  read DEPS < $1.d
  redo-ifchange ${DEPS#*:}
fi

