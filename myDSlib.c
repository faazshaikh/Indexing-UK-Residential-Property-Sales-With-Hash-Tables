#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myDSlib.h"

// -----------------
Record *table = NULL;  // DO NOT CHANGE: A global pointer to save the read data from csv files (a pointer to array of Records)
size_t table_size = 0; // DO NOT CHANGE: A global variable showing the number of rows (number of Records) read from csv files (rows in table)
// -----------------

// CODE 2: ADD more global variables if you need

#define MAX_LENOF_LINE 1024

// CODE 3: Implement all the functions here

unsigned int hash_string(const char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return (unsigned int)(hash % INDEX_SIZE);
}

void read_file(const char *filename)
{

    // Open the respective CVS file
    FILE *openFile = fopen(filename, "r");

    // Check if memory allocation failed
    if (openFile == NULL)
    {
        printf("Error opening file");
        return;
    }

    // Length needed to hold one line in the CVS file
    char line[MAX_LENOF_LINE];

    // Read and assign each line of the CVS
    while (fgets(line, sizeof(line), openFile))
    {
        // When data is added, allocate more memory for it
        Record *tableAdd = realloc(table, (table_size + 1) * sizeof(Record));

        // Check if memory allocation failed
        if (tableAdd == NULL)
        {
            printf("Failed to Memory Allocate");
            fclose(openFile);
            return;
        }

        // The temp table needs to be sent to the global table
        table = tableAdd;

        Record *recordNEW = &table[table_size];

        // Split the lines in the CVS files based on its data
        char *seperateFEILDS = strtok(line, ",");
        int indexofCOL = 0;

        // As defined, there are 16 feilds
        while (seperateFEILDS != NULL && indexofCOL < 16)
        {
            // Ensure quotes are gone
            seperateFEILDS = removeQUOTESS(seperateFEILDS);

            // Data is in a case format for the correct index
            switch (indexofCOL)
            {
            case 0:
            {
                strcpy(recordNEW->transaction_id, seperateFEILDS);
                break;
            }
            case 1:
            {
                recordNEW->price = atoi(seperateFEILDS);
                break;
            }
            case 2:
            {
                int cvsYEAR = 0;
                int cvsMONTH = 0;
                int cvsDAY = 0;
                sscanf(seperateFEILDS, "%d-%d-%d", &cvsYEAR, &cvsMONTH, &cvsDAY);
                recordNEW->date.year = cvsYEAR;
                recordNEW->date.month = cvsMONTH;
                recordNEW->date.day = cvsDAY;
                break;
            }
            case 3:
            {
                strcpy(recordNEW->postcode, seperateFEILDS);
                break;
            }
            case 4:
            {
                recordNEW->property_type = seperateFEILDS[0];
                break;
            }
            case 5:
            {
                recordNEW->old_new = seperateFEILDS[0];
                break;
            }
            case 6:
            {
                recordNEW->duration = seperateFEILDS[0];
                break;
            }
            case 7:
            {
                strcpy(recordNEW->paon, seperateFEILDS);
                break;
            }
            case 8:
            {
                strcpy(recordNEW->saon, seperateFEILDS);
                break;
            }
            case 9:
            {
                strcpy(recordNEW->street, seperateFEILDS);
                break;
            }
            case 10:
            {
                strcpy(recordNEW->locality, seperateFEILDS);
                break;
            }
            case 11:
            {
                strcpy(recordNEW->town, seperateFEILDS);
                break;
            }
            case 12:
            {
                recordNEW->district = malloc(strlen(seperateFEILDS) + 1);
                strcpy(recordNEW->district, seperateFEILDS);
                break;
            }
            case 13:
            {
                strcpy(recordNEW->county, seperateFEILDS);
                break;
            }
            case 14:
            {
                recordNEW->record_status = seperateFEILDS[0];
                break;
            }
            case 15:
            {
                recordNEW->blank_col = seperateFEILDS[0];
                break;
            }
            }

            // Go to the the next feilds in the CVS file
            seperateFEILDS = strtok(NULL, ",");
            indexofCOL++;
        }

        // Add a row after the data is filled in
        table_size++;
    }

    // Ensure file is correctly closed
    fclose(openFile);
}

IndexEntry **createIndexOnStreet(Record *table, int table_size)
{

    // Memory allocation for the table on the respected hash index
    IndexEntry **hashIndex = calloc(INDEX_SIZE, sizeof(IndexEntry *));

    // Check if memory allocation has failed
    if (hashIndex == NULL)
    {
        printf("Index Memory Allocation Failed\n");
        return NULL;
    }

    // Go through each record, set of data
    for (int i = 0; i < table_size; i++)
    {

        // Get the street name
        char *streetNameCVS = table[i].street;

        // Street name hash value
        int hashValueofStreet = hash_string(streetNameCVS);

        // Memory allocation for the new node
        IndexEntry *addNode = malloc(sizeof(IndexEntry));

        // Check if the memory allocation has failed
        if (addNode == NULL)
        {
            printf("Entry Memory Allocation Failed\n");
            continue;
        }

        // Memory allocation to make key have the street name value
        addNode->key = malloc(strlen(streetNameCVS) + 1);

        // Check if memory allocation has failed
        if (addNode->key == NULL)
        {
            printf("Key Memory Allocation Failed\n");
            free(addNode);
            continue;
        }

        // Safely copy the name of the street into the key value, using strcpy
        strcpy(addNode->key, streetNameCVS);

        // This points to the current dataset in the table
        addNode->record_ptr = &table[i];

        addNode->next = NULL;

        // If the head of the hastable is empty, then just simply add it, or add it at the front
        if (hashIndex[hashValueofStreet] == NULL)
        {
            hashIndex[hashValueofStreet] = addNode;
        }
        else
        {
            addNode->next = hashIndex[hashValueofStreet];
            hashIndex[hashValueofStreet] = addNode;
        }
    }

    return hashIndex;
}

void searchStreetLinear(Record *table, size_t table_size, const char *target, bool printFlagLinearSearch)
{

    // Loop through all the datasets in the CVS file
    for (size_t indexes = 0; indexes < table_size; indexes++)
    {

        // Use strcmp, to see if string is identical
        if (strcmp(table[indexes].street, target) == 0)
        {

            // See if print is true or false
            if (printFlagLinearSearch != false)
            {

                Record *line = &table[indexes];
                printf("Match found: Street = %s | Price = %u | Postcode = %s | Date = %04d-%02d-%02d\n", line->street, line->price, line->postcode, line->date.year, line->date.month, line->date.day);
            }
        }
    }
}

void searchStreet(IndexEntry **index_on_street, const char *target, bool printFlagHashIndexSearch)
{
    // Use hash function for the street name
    int hashFuncFind = hash_string(target);

    // Assign a temp variable to go through the index
    IndexEntry *tempIndex = index_on_street[hashFuncFind];

    // Go through the lists at the specific index
    while (tempIndex != NULL)
    {
        // Compare if the key and street name are identical
        if (strcmp(tempIndex->key, target) == 0)
        {
            // If print is true, print
            if (printFlagHashIndexSearch)
            {
                printf("Match found: Street = %s | Price = %u | Postcode = %s | Date = %04d-%02d-%02d\n", tempIndex->key, tempIndex->record_ptr->price, tempIndex->record_ptr->postcode, tempIndex->record_ptr->date.year, tempIndex->record_ptr->date.month, tempIndex->record_ptr->date.day);
            }
        }

        // Go to the next list
        tempIndex = tempIndex->next;
    }
}

int count_unused_slots(IndexEntry **index_on_street)
{

    // Variable for amount of free not used indexes
    int free = 0;

    // Loop through each index
    for (int i = 0; i < INDEX_SIZE; i++)
    {

        // If such index is NULL, update the counter
        if (index_on_street[i] == NULL)
        {

            free++;
        }
    }
    return free;
}

void free_index(IndexEntry **index_on_street)
{

    // Go through the data sets in index
    for (int i = 0; i < INDEX_SIZE; i++)
    {

        // Assign a variable for each line
        IndexEntry *temp = index_on_street[i];

        // Free all structures in the index
        while (temp != NULL)
        {
            IndexEntry *ahead = temp->next;
            free(temp->key);
            free(temp);
            temp = ahead;
        }
    }

    free(index_on_street);
}

void free_table()
{
    // Go through each data set in the table
    for (size_t i = 0; i < table_size; i++)
    {

        // Freeing the district set
        free(table[i].district);
    }

    free(table);
}

char *removeQUOTESS(char *seperateFEILDS)
{
    if (seperateFEILDS[0] == '\"')
        seperateFEILDS++;
    int totalLENGTH = strlen(seperateFEILDS);
    if (totalLENGTH > 0 && seperateFEILDS[totalLENGTH - 1] == '\"')
        seperateFEILDS[totalLENGTH - 1] = '\0';
    return seperateFEILDS;
}
