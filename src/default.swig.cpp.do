redo-ifchange "$1.i" "$1.cpp"
swig -python -c++ -builtin -outdir "../npx/$(dirname "$1")" -o "$3" "$1.i"