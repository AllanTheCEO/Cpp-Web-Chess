#ifndef _WASM_API_I
#define _WASM_API_I

%module WASM_API

%{
#include "wasm_api.h"
%}

%feature("shared_ptr");
%feature("polymorphic_shared_ptr");

%include "wasm_api.h"

#endif
