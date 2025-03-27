#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define PAGE_SIZE 1024     // 1 KB
#define NUM_PAGES 256      // Virtual address space
#define VIRTUAL_MEM_SIZE (NUM_PAGES * PAGE_SIZE)
#define NUM_FRAMES 128     // Physical memory
#define PHYSICAL_MEM_SIZE (NUM_FRAMES * PAGE_SIZE)
#define TLB_SIZE 16        // TLB entries

typedef struct {
    int frame_number;
    bool valid;
    bool modified;
    bool referenced;
} PageTableEntry;

typedef struct {
    int virtual_page;
    int frame_number;
    bool valid;
    int time_of_use; // For LRU 
} TLBEntry;

PageTableEntry page_table[NUM_PAGES];
TLBEntry tlb[TLB_SIZE];
unsigned char physical_memory[PHYSICAL_MEM_SIZE];
int tlb_hits = 0, tlb_misses = 0, page_faults = 0, total_accesses = 0;
int next_frame = 0;  // Next available frame in physical memory
int time_counter = 0; // For LRU

void init_memory() {
    for (int i = 0; i < NUM_PAGES; i++) {
        page_table[i].valid = false;
        page_table[i].frame_number = -1;
        page_table[i].modified = false;
        page_table[i].referenced = false;
    }
    for (int i = 0; i < TLB_SIZE; i++) {
        tlb[i].valid = false;
    }
}

int extract_page_number(int virtual_address) {
    return virtual_address / PAGE_SIZE;
}

int extract_offset(int virtual_address) {
    return virtual_address % PAGE_SIZE;
}

int check_tlb(int page_number) {
    for (int i = 0; i < TLB_SIZE; i++) {
        if (tlb[i].valid && tlb[i].virtual_page == page_number) {
            tlb[i].time_of_use = time_counter++;
            tlb_hits++;
            return tlb[i].frame_number;
        }
    }
    tlb_misses++;
    return -1;
}

void update_tlb(int page_number, int frame_number) {
    int lru_index = 0;
    int min_time = tlb[0].time_of_use;

    for (int i = 1; i < TLB_SIZE; i++) {
        if (!tlb[i].valid) {
            lru_index = i;
            break;
        }
        if (tlb[i].time_of_use < min_time) {
            min_time = tlb[i].time_of_use;
            lru_index = i;
        }
    }

    tlb[lru_index].virtual_page = page_number;
    tlb[lru_index].frame_number = frame_number;
    tlb[lru_index].valid = true;
    tlb[lru_index].time_of_use = time_counter++;
}

int handle_page_fault(int page_number) {
    if (next_frame >= NUM_FRAMES) {
        printf("No available frames\n");
        // Page replacement logic
        exit(1);
    }
    page_table[page_number].valid = true;
    page_table[page_number].frame_number = next_frame;
    page_table[page_number].referenced = true;
    page_faults++;
    return next_frame++;
}

int translate_address(int virtual_address) {
    int page_number = extract_page_number(virtual_address);
    int offset = extract_offset(virtual_address);

    if (page_number >= NUM_PAGES) {
        printf("Invalid virtual address\n");
        return -1;
    }

    int frame_number = check_tlb(page_number);
    if (frame_number == -1) {
        if (!page_table[page_number].valid) {
            frame_number = handle_page_fault(page_number);
        } else {
            frame_number = page_table[page_number].frame_number;
        }
        update_tlb(page_number, frame_number);
    }
    return frame_number * PAGE_SIZE + offset;
}

void generate_memory_accesses() {
    srand(time(NULL));
    for (int i = 0; i < 1000; i++) {
        int virtual_address;
        if (rand() % 2) {
            virtual_address = (rand() % 10) * PAGE_SIZE + (rand() % PAGE_SIZE); // Locality-based
        } else {
            virtual_address = rand() % VIRTUAL_MEM_SIZE; // Random access
        }
        translate_address(virtual_address);
        total_accesses++;
    }
}

void print_statistics() {
    printf("\nResults:\n");
    printf("Total memory accesses: %d\n", total_accesses);
    printf("TLB Hits: %d\n", tlb_hits);
    printf("TLB Misses: %d\n", tlb_misses);
    printf("Page Faults: %d\n", page_faults);
    printf("TLB Hit Rate: %.2f%%\n", (tlb_hits / (double)total_accesses) * 100);
    printf("Average Memory Access Time: %.2f ns\n", 100 + (tlb_misses * 20) + (page_faults * 5000));
}

int main() {
    init_memory();
    generate_memory_accesses();
    print_statistics();
    return 0;
}
