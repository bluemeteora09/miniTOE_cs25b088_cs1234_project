//this is a header file for the functions involved int he miniTOE project
#pragma once
#define WIDTH 80
#define HEIGHT 23
#define MAX_FILES 15
#define MAX_FILE_NAME 20
#define MAX_CONTENT 1100
#define MAX_USERS 5
#define MAX_PASS 20

typedef enum{
	DASHBOARD,
	COMMAND,
	EDIT,
	ABOUT_PAGE, 
	FILE_EXPLORER,
	HISTORY_PAGE,
	HELP_PAGE, 
	LOGIN_PAGE
}state;

typedef struct file_node{
	char name[MAX_FILE_NAME];
	char content[MAX_CONTENT];
	int used;
}file_node;

typedef struct list_node{
	char name[MAX_FILE_NAME];
	char time_acc[10];
	struct list_node *next;
}list_node;

typedef struct user{
    char username[MAX_FILE_NAME];
    char password[MAX_PASS];
    int active;
} user;

extern state curr_st;

extern char screen[HEIGHT][WIDTH];

extern file_node drive[MAX_FILES];

extern list_node *cache_head;

extern char msg_sys[80];
//extern int msg_type;

extern int curr_file_ind;

extern char commd_history[15][40]; 

extern user users[5];

extern int logged_in_user;

void history(char *commd);

void clear_screen();

void draw_box(int x, int y, int w, int h);

void write_text(int x, int y, char *str);

void write_text_with_wrap(int x, int y, char *str, int box_w, int box_h);

void draw_status_bar();

//void draw_status_bar_login();

void init_drive();

int create(char *name);

int delete(char *name);

int search(char *name);

int rename_file(char *old, char *new);

void write_to_file(int ind, char *content);

int count_file_lines(int ind);

void update_cache(char *name);

void free_cache();

void clear_file(int ind);

void save_to_disc();

void load_from_disc();

void history(char *commd);

int get_drive_usage();

void clear_history();

void init_users();

int login(char *user, char *pass);

void save_users();

void load_users();

int add_user();

void del_user();


