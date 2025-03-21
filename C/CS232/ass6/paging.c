#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PAGE_SIZE 4096     // 4 KB
#define MEMORY_SIZE 262144 // 256 KB
#define NUM_PAGES 64       // Logical address space / page size
#define NUM_FRAMES 64      // Physical memory / page size

typedef struct
{
    int frame_number;
    bool valid;
} PageTableEntry;

typedef struct
{
    PageTableEntry page_table[NUM_PAGES];
    unsigned char physical_memory[MEMORY_SIZE];
} MemoryManager;

void init_memory_manager(MemoryManager *mm)
{
    for (int i = 0; i < NUM_PAGES; i++)
    {
        mm->page_table[i].valid = false;
        mm->page_table[i].frame_number = -1;
    }
}

void map_page_to_frame(MemoryManager *mm, int page_number, int frame_number)
{
    if (page_number < NUM_PAGES && frame_number < NUM_FRAMES)
    {
        mm->page_table[page_number].valid = true;
        mm->page_table[page_number].frame_number = frame_number;
    }
}

int translate_address(MemoryManager *mm, int logical_address)
{
    int page_number = logical_address / PAGE_SIZE;
    int offset = logical_address % PAGE_SIZE;

    if (page_number >= NUM_PAGES)
    {
        printf("Invalid page number\n");
        return -1;
    }

    if (!mm->page_table[page_number].valid)
    {
        printf("Page fault: Page %d not in memory\n", page_number);
        return -1;
    }

    int frame_number = mm->page_table[page_number].frame_number;
    int physical_address = frame_number * PAGE_SIZE + offset;

    if (physical_address >= MEMORY_SIZE)
    {
        printf("Physical address out of bounds\n");
        return -1;
    }

    return physical_address;
}

int main()
{
    MemoryManager mm;
    init_memory_manager(&mm);

    map_page_to_frame(&mm, 0, 5);  // Page 0, Frame 5
    map_page_to_frame(&mm, 1, 10); // Page 1, Frame 10
    map_page_to_frame(&mm, 2, 15); // Page 2, Frame 15

    int logical_addresses[] = {
        0,    // Start of page 0
        4095, // End of page 0
        4096, // Start of page 1
        8191, // End of page 1
        8192, // Start of page 2
        50000 // Invalid address
    };

    printf("\nAddress Translation Results:\n");
    printf("Logical Address -> Physical Address\n");
    printf("--------------------------------\n");

    for (int i = 0; i < 6; i++)
    {
        int physical_address = translate_address(&mm, logical_addresses[i]);
        if (physical_address != -1)
        {
            printf("%d -> %d\n", logical_addresses[i], physical_address);
        }
    }

    return 0;
}