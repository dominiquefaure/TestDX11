#include "Matrix44.h"
bool Matrix44::s_useCompose=false;


//In debug configuration, the inlline methods need to be include inside a cpp file, to avoid function redefinition errors
#ifdef _DEBUG

#include "Matrix44.inl"

#endif