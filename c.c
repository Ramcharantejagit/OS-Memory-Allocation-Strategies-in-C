#include <stdio.h>
#include <limits.h>
typedef struct {
int size;
int isAllocated;
} MemoryBlock;
typedef struct {
int size;
int allocatedBlock;
} Process;
void firstFit(MemoryBlock blocks[], int m, Process processes[], int p) {
for (int i = 0; i < p; i++) {
for (int j = 0; j < m; j++) {
if (!blocks[j].isAllocated && blocks[j].size >= processes[i].size) {
processes[i].allocatedBlock = j;
blocks[j].size -= processes[i].size;
blocks[j].isAllocated = 1;
break;
}
}
}
}
void bestFit(MemoryBlock blocks[], int m, Process processes[], int p) {
for (int i = 0; i < p; i++) {
int bestIndex = -1;
for (int j = 0; j < m; j++) {
if (!blocks[j].isAllocated && blocks[j].size >= processes[i].size) {
if (bestIndex == -1 || blocks[j].size < blocks[bestIndex].size) {
bestIndex = j;
}
}
}
if (bestIndex != -1) {
processes[i].allocatedBlock = bestIndex;
blocks[bestIndex].size -= processes[i].size;
blocks[bestIndex].isAllocated = 1;
}
}
}
void worstFit(MemoryBlock blocks[], int m, Process processes[], int p) {
for (int i = 0; i < p; i++) {
int worstIndex = -1;
for (int j = 0; j < m; j++) {
if (!blocks[j].isAllocated && blocks[j].size >= processes[i].size) {
if (worstIndex == -1 || blocks[j].size > blocks[worstIndex].size) {
worstIndex = j;
}
}
}
if (worstIndex != -1) {
processes[i].allocatedBlock = worstIndex;
blocks[worstIndex].size -= processes[i].size;
blocks[worstIndex].isAllocated = 1;
}
}
}
void displayResults(Process processes[], int p, MemoryBlock blocks[], int m) {
printf("\nProcess Allocation Results:\n");
for (int i = 0; i < p; i++) {
if (processes[i].allocatedBlock != -1) {
printf("Process %d of size %d allocated to block %d\n", i + 1, processes[i].size,
processes[i].allocatedBlock + 1);
} else {
printf("Process %d of size %d not allocated\n", i + 1, processes[i].size);
}
}
printf("\nRemaining Memory in Blocks:\n");
for (int i = 0; i < m; i++) {
printf("Block %d: %d\n", i + 1, blocks[i].size);
}
}
int main() {
int m, p;
printf("Enter the number of memory blocks: ");
scanf("%d", &m);
MemoryBlock blocks[m];
printf("Enter the sizes of memory blocks:\n");
for (int i = 0; i < m; i++) {
scanf("%d", &blocks[i].size);
blocks[i].isAllocated = 0;
}
printf("Enter the number of processes: ");
scanf("%d", &p);
Process processes[p];
printf("Enter the sizes of processes:\n");
for (int i = 0; i < p; i++) {
scanf("%d", &processes[i].size);
processes[i].allocatedBlock = -1;
}
printf("Choose Allocation Method: 1. First Fit 2. Best Fit 3. Worst Fit\n");
int choice;
scanf("%d", &choice);
switch (choice) {
case 1:
firstFit(blocks, m, processes, p);
break;
case 2:
bestFit(blocks, m, processes, p);
break;
case 3:
worstFit(blocks, m, processes, p);
break;
default:
printf("Invalid choice!\n");
return 1;
}
displayResults(processes, p, blocks, m);
return 0;
}