%module nk

%warnfilter(SWIGWARN_PARSE_NAMED_NESTED_CLASS) nk::Landscape::InvalidGenomeSize;
%warnfilter(SWIGWARN_PARSE_NAMED_NESTED_CLASS) nk::Landscape::InvalidPosition;

%{
#define SWIG_FILE_WITH_INIT
#include "landscape.h"
%}

%copyctor nk::Landscape;

%include "landscape.h"
