#include<stdio.h>
#include<stdlib.h>
#include "miniTOE.h"
#include<string.h>
#include<time.h>

file_node drive[MAX_FILES];

list_node *cache_head;

int curr_file_ind;

char msg_sys[80] = "";

char commd_history[15][40];

void init_drive(){
    for(int i=0; i<MAX_FILES; i++){
        drive[i].used = 0;
        strcpy(drive[i].name, "");
        strcpy(drive[i].content, "");
    }
}

int create(char *name){
    for(int i=0; i<MAX_FILES; i++){
        if(drive[i].used && strcmp(drive[i].name, name) == 0){
            return -2;
        }
    }
    for(int i=0; i<MAX_FILES; i++){
        if(drive[i].used == 0){
            strncpy(drive[i].name, name, MAX_FILE_NAME);
            drive[i].used = 1;
            return i;
        }
    }
    return -1;
}

int search(char *name){
    for(int i=0; i<MAX_FILES; i++){
        if(strcmp(drive[i].name, name) == 0){
            return i;
        }
    }
    return -1;
}

int delete(char *name){
    if(search(name) == -1){
        strcpy(msg_sys, "File does not exist");
    }
    for(int i=0; i<MAX_FILES; i++){
        if(drive[i].used && strcmp(drive[i].name, name) == 0){
            drive[i].used= 0;
            return 1;
        }
    }
    return 0;
}

void write_to_file(int ind, char *content){
    if(ind < 0 || ind >= MAX_FILES || drive[ind].used == 0){
        return;
    }
    int size_cont = strlen(drive[ind].content);
    int size_input = strlen(content);

    if(size_cont + size_input + 2 < MAX_CONTENT){
       if (size_cont > 0) {
            strcat(drive[ind].content, " ");
        }
        strcat(drive[ind].content, content);
    }
    else{
        strcpy(msg_sys, "CRITICAL: File buffer overflow! Cannot add more text.");
    }
}

void update_cache(char *name){
    list_node *prev =NULL;
    list_node *curr = cache_head;
    int flag = 0;
    while(curr != NULL){
        if(strcmp(curr->name, name) == 0){
            if(curr == cache_head && prev == NULL){
                break;
            }
            if(prev != NULL){
                prev->next = curr->next;
            }
            curr->next = cache_head;
            cache_head = curr;
            flag = 1;
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    if(flag == 0){
        list_node *newnode = (list_node *)malloc(sizeof(list_node));
        if(newnode == NULL){
            printf("malloc failed\nexiting function\n");
            return;
        }
        strncpy(newnode->name, name, MAX_FILE_NAME);
        newnode->next = cache_head;
        cache_head = newnode;
        time_t rawtime;
        struct tm *info;
        time(&rawtime);
        info = localtime(&rawtime);
        strftime(newnode->time_acc, 10, "%H:%M", info);
    }
    
}

int rename_file(char *old, char *new){
    int ind = search(old);
    if(ind == -1){
        strcpy(msg_sys, "ErROR : Original file not found");
    }
    if(search(new) != -1){
        strcpy(msg_sys, "ERROR : New fileaname already in use");
    }
    strncpy(drive[ind].name, new, MAX_FILE_NAME);
    update_cache(new);
    strcpy(msg_sys, "File rename success");
    return 1;

}

void clear_file(int ind){
    if(ind <0 || ind >= MAX_FILES || drive[ind].used == 0){
        strcpy(msg_sys, "ERROR : Invalid file");
        return;
    }
    drive[ind].content[0] = '\0';
    //strcpy(msg_sys, "File cleared");
    update_cache(drive[ind].name);
    strcpy(msg_sys, "File cleared");
}

// int count_file_lines(int ind){
//     int num_lines;
//     num_lines = strlen(drive[ind].content)/76 + 1;
//     return num_lines;
// }

void save_to_disc(){
    FILE *fp = fopen("filesys_data.bin", "wb");
    if(fp == NULL){
        strcpy(msg_sys, "DISK ERROR : Could not open save file");
        return;
    }
    fwrite(drive, sizeof(file_node), MAX_FILES, fp);
    fclose(fp);
    strcpy(msg_sys, "System state saved to filesys_data.bin");
}

void load_from_disc(){
    strcpy(msg_sys, "Sync will erase all existing files");
    FILE *fp =fopen("filesys_data.bin", "rb");
    if(fp == NULL){
        strcpy(msg_sys, "Drive not found. Initialising New Drive");
        return;
    }
    fread(drive, sizeof(file_node), MAX_FILES, fp);
    fclose(fp);
    strcpy(msg_sys, "Drive data restored");
}

void rebuild_cache_on_boot() {
    for(int i = 0; i < MAX_FILES; i++) {
        if(drive[i].used) {
            update_cache(drive[i].name);
        }
    }
}

void free_cache(){
    list_node *curr = cache_head;
    list_node *temp = NULL;
    while(curr != NULL){
        temp = curr;
        curr = curr->next;
        cache_head = curr;
        free(temp);
    }
    cache_head = NULL;
}

void history(char *commd){
    if(commd == NULL || strlen(commd) == 0){
        return;
    }

    for(int i=14; i>0; i--){
        strcpy(commd_history[i], commd_history[i-1]);
    }
    strncpy(commd_history[0], commd, 39);
    commd_history[0][39] = '\0';

}

int get_drive_usage(){
    int total = 0;
    for(int i = 0; i < MAX_FILES; i++) {
        if(drive[i].used) total += strlen(drive[i].content);
    }
    return total;
}

void clear_history() {
    for(int i = 0; i < 15; i++) {
        strcpy(commd_history[i], "");
    }
    strcpy(msg_sys, "Command history cleared");
}