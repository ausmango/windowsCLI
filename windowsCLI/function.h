#ifndef function_h
#define function_h

#include <windows.h>
#include <Psapi.h>

typedef struct {
	char name[256];
	SIZE_T ramMB;
} ProcessInfo;

ProcessInfo* gatherRam(int* outCount);

#endif