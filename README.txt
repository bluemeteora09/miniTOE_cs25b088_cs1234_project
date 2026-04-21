Project : miniTOE

miniTOE stands for mini Terminal Operating Environment

NOTE: For best experience, execute on a 80x24(wxh)terminal.

Code:
Written in C. 
Libraries used are:
1. stdio.h
2. stdlib.h
3. string.h
4. time.h (for one of the features)
5. miniTOE.h (custom library for the project)

Compiling Instructions:
1. make 
2. ./miniTOE
3. make clean (to clear extra files)

Features:
1. Single user.
2. Dashboard: 
    Displays different pages user can visit.
    User can can go to other modes from the Dashboard.
3. File Explorer:
    User can create, edit, rename, delete files.
    Sync option for using files from previou login(consider only the login before)
4. Editor:
    Simple editor, anything we write and press enter/return will show up on the screen.
    It will save the changes as we go back/quit the editor but not when the execution is stopped(ctrl+C)
5. History:
    Shows File history(mosrt recently opened)
    Shows input/command history(anything that we typed in shows up)
6. Help Page:
    Contains all commands and their functions.
7. Login Page:
    Has commands that can be used to logout and log in as different users

Constraints:
1. Input can be atmost 100 characters long.
2. The drive size is currently 15 files(due to screen size constraints)
3. Editor can only save to an exisiting file.
4. Atmost 5 users and default is 'admin'.
5. File names, usernames, passwords are atmost 20 characters long.
6. Currently, we can only add to file, we cant use backspace after pressing 'return/enter'. We can clear to wipe out file contents and start fresh.

Commands:
1. Common Commands:
    back or q  - Return to Dashboard                           
    exit       - Logout/Shutdown

2. Dashboard Commands:
    1    - to go to Editor
    2    - to go to About Page
    3    - to go to File Explorer
    4    - to go to History Page
    5    - to go to Help Page
    exit - to shutdown/logout

3. Editor Commands:
    'back'(quotes) or q - go back to Dashboard/save and exit
    clear               - wipe file's content

4. File Exporer Commands:
    new <file>         - Create file            
    edit <file>        - Open editor         
    del <file>         - Delete file         
    rename <old> <new> - Rename file         
    sync               - Restore from disk

5. History Commands:
    clear - Clears command History

6. Login Page
    adduser - adds user (only when admin)
    deluser - deletes user(only when admin)
    sync    - syncs users only from the one previous login
    logout  - logs out as that user
    login   - for login 

Have Fun !
Comment if you have any feedback.



