./tools/bins src | xargs redo-ifchange
./tools/exts | xargs redo-ifchange
redo-ifchange build/runtests
