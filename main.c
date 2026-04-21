#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "miniTOE.h"

#define HEIGHT 23
#define WIDTH 80

void printscreen(){
    int i, j;
    int height;
    if(curr_st == LOGIN_PAGE){
        height = 21;
    }
    else{
        height = HEIGHT;
    }
    for(i=0; i<height; i++){
        for(j=0; j<WIDTH; j++){
            printf("%c", screen[i][j]);
        }
        //if(i < HEIGHT-1){
            printf("\n");
        //}
    }
    fflush(stdout);
}

state curr_st = DASHBOARD;

int main(){
    char input[100];
    int running = 1;
    
    init_drive();
    init_users();
    logged_in_user = 0;
    //load_from_disc();

    while(running){
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
            clear_screen();

        if(curr_st == LOGIN_PAGE){
            draw_box(0, 0, 80, 19);
            //draw_box(18, 5, 44, 12);
            write_text(28, 4, "--- miniTOE LOGIN ---");
            write_text(7, 6, "-----------------------------------------------------------------");
            write_text(7, 7, "Commands: adduser | deluser | sync | exit | logout | login | home");
            draw_box(26, 11, 26, 5);
            char curr_user[20];
            strcpy(curr_user, users[logged_in_user].username);
            write_text(34, 12, "Current User");
            write_text(34, 14, curr_user);

            draw_status_bar();
            printscreen();

            printf("login page > ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;

            if(strcmp(input, "exit") == 0){
                running = 0;
                continue;
            }
            else if(strcmp(input, "home") == 0){
                if(logged_in_user != -1){
                    curr_st = DASHBOARD;
                    strcpy(msg_sys, "Returning to Dashboard");
                    continue;
                }
                else{
                    strcpy(msg_sys, "ERROR: Must login before accessing Dashboard");
                }
                continue;
            }
            else if(strcmp(input, "adduser") == 0){
                if(strcmp(users[logged_in_user].username, "admin") == 0){
                    add_user();
                }
                else{
                    strcpy(msg_sys, "ERROR: Login in as admin to add/delete user");
                }
                continue;
            }
            else if(strcmp(input, "deluser") == 0){
                if(strcmp(users[logged_in_user].username, "admin") == 0){
                    del_user();
                }
                else{
                    strcpy(msg_sys, "ERROR: Login in as admin to add/delete user");
                }
                continue;
            }
            else if(strcmp(input, "sync") == 0){
                load_users();
                printf("\n\n");
                continue;
            }
            else if(strcmp(input, "logout") == 0){
                logged_in_user = -1;
                strcpy(curr_user, "");
                strcpy(msg_sys, "Logged out safely");
                continue;
            }
            else if(strcmp(input, "login") == 0){
                if(logged_in_user != -1){
                    strcpy(msg_sys, "Logout first to login as other user");
                    continue;
                }
                char username[50];
                char password[50];
                printf("Enter Username : ");
                fgets(username, sizeof(username), stdin);
                username[strcspn(username, "\n")] = 0;
                printf("Enter Password : ");
                fgets(password, sizeof(password), stdin);
                password[strcspn(password, "\n")] = 0;

                if(login(username, password)){
                    curr_st = DASHBOARD;
                    strcpy(msg_sys, "Welcome Back !");
                    continue;
                }
                else{
                    strcpy(msg_sys, "Invalid Credentials");
                }
                continue;
            }

        }

        else if(curr_st == DASHBOARD){
            time_t rawtime;
            struct tm *timeinfo;
            char time_str[20];
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            strftime(time_str, sizeof(time_str), "%H:%M", timeinfo);

            draw_box(0, 0, 80, 23);
            draw_box(0, 0, 80, 3);
            draw_box(20, 5, 40, 14);
            write_text(5, 1, "miniTOE v1.0.2");
            write_text(30, 3, "WELCOME TO miniTOE");
            write_text(31, 6, "SYSTEM MENU");      // Title of the box
            write_text(21, 7, "--------------------------------------"); // Divider
    
            write_text(23, 9, "1. Type '1' open Text Editor");
            write_text(23, 10, "2. Type '2' to view System About");
            write_text(23, 11, "3. Type '3' to open File Explorer");
            write_text(23, 12, "4. Type '4' to view History");
            write_text(23, 13, "5. Type '5' to open Help Page");
            write_text(23, 14, "6. Type '6' to go to login page");
            write_text(23, 15, "7. Type 'logout' to logout");
            write_text(23, 16, "8. Type 'exit' to shutdown");
            write_text(65, 1, time_str);

            // draw_box(45, 17, 33, 5); 
            // write_text(46, 17, " RECENT CMDs ");
            // for(int i=0; i<5; i++) {
            // write_text(47, 18+i, commd_history[i]);
        }
        
        if(curr_st == ABOUT_PAGE){
            draw_box(0, 0, 80, 23);
            write_text(30, 5, "--- ABOUT miniTOE ---");
            write_text(15, 8, "This is a custom TUI OE written in C.");
            write_text(15, 10, "Made by: Tvisha CS25B088");
            write_text(15, 12, "Version: 1.0.2");
            write_text(22, 20, "Type 'back' or 'q' to return to Menu");
        }

        if(curr_st== FILE_EXPLORER){
            draw_box(0, 0, 80, 23);
            write_text(22, 1, "--- WELCOME TO FILE EXPLORER ---");
            write_text(10, 3, "ID   FILENAME             SIZE");
            write_text(10, 4, "------------------------------------");

            int row = 5;
            for(int i = 0; i < MAX_FILES; i++) {
                if(drive[i].used == 1) {
                    char file_info[50];
                    sprintf(file_info, "[%d]  %-20s %lu bytes", i, drive[i].name, strlen(drive[i].content));
                    write_text(10, row++, file_info);
                }

            }
            draw_box(54, 4, 24, 10);
            write_text(62, 5, "COMMANDS");
            write_text(56, 7, "- new <file>");
            write_text(56, 8, "- del <file>");
            write_text(56, 9, "- edit <file>");
            write_text(56, 10, "- rename <old> <new>");
            write_text(56, 11, "- q or back");
            write_text(56, 12, "- sync");
            //write_text(56, 11, "- csync'");

            draw_box(54, 15, 24, 4);
            write_text(62, 16, "DISK USAGE");
            char disc_usage[10];
            sprintf(disc_usage, "%d Bytes", get_drive_usage());
            write_text(62, 17, disc_usage);
            //write_text(1, 19, "Commands: 'new <filename>', 'del <filename>', 'edit <filename>', 'back'");
        }

        if(curr_st == EDIT){
            draw_box(0, 0, 80, 23);
            draw_box(0, 0, 80, 3);
            strcpy(msg_sys, "type q or 'back' in quotes to exit");
            char heading[50];
            //int num_lines = count_file_lines(curr_file_ind);
            sprintf(heading, "EDITOR : Editing: %s (%lu bytes)", drive[curr_file_ind].name, strlen(drive[curr_file_ind].content));
            write_text(2, 1, heading);
            //char lines[15];
            //int num_lines = count_file_lines(curr_file_ind);
            //sprintf(lines, "Lines: %d/15", num_lines);
            //write_text(65, 22, lines);
            write_text(47, 1, "Type 'q' or 'back' to save/exit");
            write_text_with_wrap(2, 4, drive[curr_file_ind].content, 75, 15);
            //write_text(5, 20, "Commands: Type text to add, 'back' to save/exit, 'clear' to wipe.");
            draw_status_bar();

        }

        if(curr_st == HISTORY_PAGE) {
            draw_box(0, 0, 80, 23);
            draw_box(40, 0, 40, 23);
            write_text(14, 2, "CACHE HISTORY");
            write_text(7, 4, "Most Recently Accessed Files");
            write_text(7, 5, "----------------------------");

            write_text(53, 2, "COMMAND HISTORY");
            write_text(45, 4, "Most Recent Command/Inputs");
            write_text(45, 5, "--------------------------");

            list_node *curr = cache_head;
            int row = 6;
            while(curr != NULL && row < 20) {
                char history_file[40];
                int ind = search(curr->name);
                // int size = 0;
                // if(ind != -1){
                //     size = strlen(drive[ind].content);
                // }
                sprintf(history_file, "%-20s %lu Bytes %s",  curr->name, strlen(drive[ind].content), curr->time_acc);
                write_text(3, row++, history_file);
                curr = curr->next;
            }

            for(int i=0; i<15; i++){
                if(strlen(commd_history[i]) > 0){
                    write_text_with_wrap(44, 6+i, commd_history[i], 40, 1);
                }
            }
            draw_box(21, 18, 37, 3);
            write_text(22, 19, "Type 'back' to return to Dashboard");
        }

        if(curr_st == HELP_PAGE){
            draw_box(0, 0, 80, 23);
            draw_box(0, 0, 80, 3);
            write_text(32, 1, "HELP PAGE");
            draw_box(40, 2, 41, 10);
            draw_box(40, 9, 41, 10);
            draw_box(0, 2, 41, 10);
            draw_box(0, 9, 41, 10);
            draw_box(40, 12, 41, 10);
            draw_box(0, 13, 41, 10);

            write_text(3, 3, "Dashboard Comamnds");
            write_text(3, 4, "1 - Edit");
            write_text(3, 5, "2 - About Page");
            write_text(3, 6, "3 - File Explorer");
            write_text(3, 7, "4 - History and Cache");
            write_text(3, 8, "5 - Help Page");

            write_text(3, 10, "Editor Commands");
            write_text(3, 11, "clear           - Wipe File Content");
            write_text(3, 12, "'back'(quotes)  - Save and Exit");
            
            write_text(42, 3, "File Explorer Comamnds");
            write_text(42, 4, "new <file>     - Create file");
            write_text(42, 5, "edit <file>    - Open editor");
            write_text(42, 6, "del <file>     - Delete file");
            write_text(42, 7, "rename <o> <n> - Rename file");
            write_text(42, 8, "sync           - Restore from disk");

            write_text(42, 10, "History Commands");
            write_text(42, 11, "clear - Clears Command History");

            write_text(3, 14, "Common Commands");
            write_text(3, 15, "back or q  - Return to Dashboard");
            write_text(3, 16, "exit       - Logout/Shutdown");

            write_text(42, 13, "Login Page Commands");
            write_text(42, 14, "adduser  - adds user");
            write_text(42, 15, "deluser  - deletes user");
            write_text(42, 16, "sync     - loads previous users");
            write_text(42, 17, "logout   - logs out");
            write_text(42, 18, "login    - to log in");
            write_text(42, 19, "home     - to go to Dashboard");
        }

        draw_status_bar();
 
        printscreen();
        if(curr_st !=LOGIN_PAGE){
            printf("miniTOE > ");
        }
        else{
            printf("login page > ");
        }
        

        if(strlen(msg_sys) > 0){
            static int timer = 0;
            timer++;
            if(timer > 15){
                strcpy(msg_sys, "");
                timer = 0;
            }
        }

        fgets(input, sizeof(input), stdin);
        if(curr_st != EDIT){
            input[strcspn(input, "\n")] = 0;
        }  
        history(input);

        char temp[100];
        strcpy(temp, input);
        char *commd = strtok(temp, " ");
        char *arg1 = strtok(NULL, " ");
        char *arg2 = strtok(NULL, "");
        //printf("%s %s\n", commd, arg);

        if(curr_st == DASHBOARD){
            if (strcmp(input, "1") == 0){
                if(curr_file_ind < 0 || curr_file_ind >= MAX_FILES || drive[curr_file_ind].used == 0){
                    strcpy(msg_sys, "ERROR : No file selected. Go to explorer first!");
                }
                else{
                    curr_st = EDIT;
                    strcpy(msg_sys, "Resuming edit Session");
                }
            } 
            else if (strcmp(input, "2") == 0){
                curr_st = ABOUT_PAGE;
            } 
            else if (strcmp(input, "3") == 0){
               curr_st = FILE_EXPLORER;
                
            }
            else if (strcmp(input, "4") == 0){
                curr_st = HISTORY_PAGE;
            }
            else if (strcmp(input, "5") == 0){
                curr_st = HELP_PAGE;
            }
            else if (strcmp(input, "6") == 0){
                curr_st = LOGIN_PAGE;
            }
            else if (strcmp(input, "logout") ==0){
                curr_st = LOGIN_PAGE;
                logged_in_user = -1;
                strcpy(msg_sys, "Logged out successfully");
                continue;
            }
        }

        else if (curr_st == ABOUT_PAGE) {
            if (strcmp(input, "back") == 0 || strcmp(input, "q") == 0) {
                curr_st = DASHBOARD; 
            }
        }

        else if (curr_st == EDIT) {
            if (strcmp(input, "q\n") == 0 || strcmp(input, "'back'\n") == 0) {
                update_cache(drive[curr_file_ind].name);
                curr_st = DASHBOARD;
                save_to_disc();
                strcpy(msg_sys, "File saved succesfully");
            }

            else if(strcmp(input, "clear") == 0){
                clear_file(curr_file_ind);
            }

            else{
                write_to_file(curr_file_ind, input);
            }
        }

        else if (curr_st == FILE_EXPLORER) {
            if (strcmp(input, "q") == 0 || strcmp(input, "back") == 0) {
                curr_st = DASHBOARD;
            }

            else if(strcmp(input, "sync") == 0){
                load_from_disc();
                strcpy(msg_sys, "Syncing Complete");
            }

            else if(commd != NULL && strcmp(commd, "new") == 0 && arg1 != NULL){
                create(arg1);
                strcpy(msg_sys, "File Created");
            }

            else if(commd != NULL && strcmp(commd, "del") == 0 && arg1 != NULL){
                delete(arg1);
                //strcpy(msg_sys, "File Deleted");
            }

            else if(commd != NULL && strcmp(commd, "edit") == 0 && arg1 != NULL){
                int temp_ind  = search(arg1);
                if(temp_ind != -1){
                    curr_file_ind = temp_ind;
                    curr_st = EDIT;
                    strcpy(msg_sys, "Entering Edit...");
                }
                else{
                    strcpy(msg_sys, "ERROR : File Does Not Exsist");
                }

            }

            else if(commd != NULL && strcmp(commd, "rename") == 0){
                if(arg1 != NULL && arg2 != NULL && strlen(arg1) > 0 && strlen(arg2) > 0){
                    rename_file(arg1, arg2);
                }
                else{
                    strcpy(msg_sys, "Usage : rename <old> <new>");
                }
            }
        }

        if(curr_st == HISTORY_PAGE){
            if (strcmp(input, "q") == 0 || strcmp(input, "back") == 0) {
                curr_st = DASHBOARD;
            }
            if(strcmp(input, "clear") == 0){
                clear_history();
            }
        }

        if(curr_st == HELP_PAGE){
            if (strcmp(input, "q") == 0 || strcmp(input, "back") == 0) {
                curr_st = DASHBOARD;
            }
        }

        if(strcmp(input, "exit") == 0){
            running = 0;
        }
    }
    
    free_cache();
    return 0;
}
