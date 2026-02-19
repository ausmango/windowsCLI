#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <Psapi.h>

typedef struct {
	char name[256];
	SIZE_T ramMB;
} ProcessInfo;

ProcessInfo list[1024];
int listCount = 0;

int static comp(const void* a, const void* b) {
	return ((ProcessInfo*)a)->ramMB - ((ProcessInfo*)b)->ramMB;
}

int main() {
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

	for (int i = 0; i < listCount; i++) {
		printf("%-30s %llu MB\n", list[i].name, (unsigned long long)list[i].ramMB);
	}
	return 0;
}
