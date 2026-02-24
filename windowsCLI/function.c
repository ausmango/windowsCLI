#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <Psapi.h>
#include "function.h"

ProcessInfo list[1024];

int static comp(const void* a, const void* b) {
	return ((ProcessInfo*)a)->ramMB - ((ProcessInfo*)b)->ramMB;
}

ProcessInfo* gatherRam(int*outCount) {
	int listCount = 0;

	DWORD processes[1024];
	DWORD bytesNeeded;
	unsigned int count;

	EnumProcesses(processes, sizeof(processes), &bytesNeeded);
	count = bytesNeeded / sizeof(DWORD);

	for (unsigned int i = 0; i < count; i++) {
		if (processes[i] == 0) continue;

		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processes[i]);
		if (hProcess == NULL) continue;

		char name[256];
		GetModuleBaseNameA(hProcess, NULL, name, sizeof(name));

		PROCESS_MEMORY_COUNTERS pmc;
		if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
			list[listCount].ramMB = pmc.WorkingSetSize / (1024 * 1024);
			strcpy_s(list[listCount].name, sizeof(list[listCount].name), name);
			listCount++;
		}
		CloseHandle(hProcess);

	}

	qsort(list, listCount, sizeof(ProcessInfo), comp);
	*outCount = listCount;
	return list;
}
