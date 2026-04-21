#include <stdio.h>
#include <string.h>
#include "miniTOE.h"

user users[MAX_USERS];

int logged_in_user = -1;

void init_users(){
    for(int i=0; i<MAX_USERS; i++){
        users[i].active = 0;
    }
    strcpy(users[0].username, "admin");
    strcpy(users[0].password, "admin@1234");
    users[0].active = 1;
}

int login(char *user, char *pass){
    for(int i=0; i<MAX_USERS; i++) {
        if(users[i].active && strcmp(users[i].username, user) == 0) {
            if(strcmp(users[i].password, pass) == 0) {
                logged_in_user = i;
                return 1;
            }
        }
    }
    return 0;
}

void save_users(){
    FILE *fp = fopen("users.bin", "wb");
    if(fp == NULL){
        strcpy(msg_sys, "Save User failed");
    }
    else{
        fwrite(users, sizeof(user), MAX_USERS, fp);
        fclose(fp);
        strcpy(msg_sys, "Users saved successfully");
    }
}

void load_users(){
    FILE *fp = fopen("users.bin", "wb");
    if(fp == NULL){
        strcpy(msg_sys, "Save User failed");
    }
    fread(users, sizeof(user), MAX_USERS, fp);
    fclose(fp);
    strcpy(msg_sys, "Users data restored");
}

int add_user(){
    int empty = -1;
    for(int i=0; i<MAX_USERS; i++){
        if(users[i].active == 0){
            empty = i;
            break;
        }
    }
    if(empty == -1){
        strcpy(msg_sys, "CRITICAL : At the Maximum User limit !");
        return 0;
    }
    char new_user[50];
    char new_pass[50];
    printf("Enter Username : ");
    fgets(new_user, sizeof(new_user), stdin);
    new_user[strcspn(new_user, "\n")] = 0;
    printf("Enter Password : ");
    fgets(new_pass, sizeof(new_user), stdin);
    new_pass[strcspn(new_pass, "\n")] = 0;

    strncpy(users[empty].username, new_user, MAX_PASS);
    strncpy(users[empty].password, new_pass, MAX_PASS);
    users[empty].active = 1;

    save_users();
    strcpy(msg_sys, "New User Successfully added!");
    return 1;
}

void del_user(){
    int ind = -1;
    char user[50];
    printf("Enter Username : ");
    fgets(user, sizeof(user), stdin);
    user[strcspn(user, "\n")] = 0;
    
    if(strcmp(user, "admin") == 0) {
        strcpy(msg_sys, "ERROR: Cannot delete admin account");
        return;
    }

    for(int i=0; i<MAX_USERS; i++){
        if(strcmp(users[i].username, user) == 0){
            ind = i;
            strcpy(users[i].username, "");
            strcpy(users[i].password, "");
            users[i].active = 0;
            strcpy(msg_sys, "User deleted Successfully");
            return;
        }
    }
    if(ind == -1){
        strcpy(msg_sys, "User not Found");
    }
}

