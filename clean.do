rm -rf .redo

if [ -e .do_built ]; then
  while read x; do
    [ -d "$x" ] || rm -f "$x"
  done <.do_built

fi
[ -z "$DO_BUILT" ] && rm -rf .do_built .do_built.dir

./bins | xargs rm -f

find . -name '*.tmp' -exec rm -fv {} \;
find . -name '*.o' -exec rm -fv {} \;
find . -name '*.d' -exec rm -fv {} \;
