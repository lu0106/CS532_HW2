#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

typedef int MYFUNC(char *path, int size, char *str, int S, int d, int t, int count, int c);
int test(char *path, int size, char *str, int S, int d, int t, int count, int c);
int get_file_size(char *filename);
int opfunc(char *path, int size, char *str, int S, int d, int t, int count, int c, MYFUNC *function);

// Reference https://www.delftstack.com/zh-tw/howto/c/optind-in-c/
int main(int argc, char *argv[]){

    char str[999];
    memset(str, 0, sizeof(str));

    int S = 0;
    int t = 0; 
    int d = 0;
    int size = 0;
    int count = 1;
    int c = 0;

    char addr[999];
    memset(addr, 0, sizeof(addr));
    getcwd(addr, sizeof(addr));
    strcat(addr, "/");

    int result;
    while((result = getopt(argc, argv, "Ss:f:t:")) != -1){
        switch(result){
            case 'S':
                S = 1;
                break;
            case 's':
                if(atoi(optarg) > size){
                    size = atoi(optarg);
                }
                break;
            case 'f':
                strcpy(str, optarg);
                break;
            case 't':
                if(strcmp(optarg, "f") == 0){
                    t = 1;
                }
                else if (strcmp(optarg, "d") == 0){
                    d = 1;
                }
                else{
                    printf("Error\n");
                    exit(EXIT_SUCCESS);
                }
                break;
        }
    }

    if(argc > optind && argv[optind] != NULL){
        strcat(addr, argv[argc-1]);
    }

    if(argc == 1){
        opfunc(addr, 0, str, 0, 0, 0, count, c, test);
    }
    else{
        opfunc(addr, size, str, S, d, t, count, c, test);
    }
    return 0;
}

// get the type of file
// Reference http://www.gnu.org/software/libc/manual/html_node/Directory-Entries.html
char *type_of_file(unsigned char type){

    char *print;
    switch (type){
        case DT_REG:
            print = "regular file";
            break;
        case DT_DIR:
            print = "directory";
            break;
        case DT_FIFO:
            print = "FIFO";
            break;
        case DT_SOCK:
            print = "local-domain socket";
            break;
        case DT_CHR:
            print = "character device";
            break;
        case DT_BLK:
            print = "block device";
            break;
        case DT_LNK:
            print = "symbolic link";
            break;
        case DT_UNKNOWN:
            print = "unknown file type";
            break;
        default:
            print = "UNKNOWN";
    }
    return print;
}

int test(char *path, int size, char *str, int S, int d, int t, int count, int c){

    struct dirent *ptr;
    int file_size = 2147483647; //max int

    char directory_name[999];
    memset(directory_name, 0,sizeof(directory_name));
    int i;

    DIR *Dir = opendir(path);
    if (Dir == NULL){
        printf("Error\n");
        exit(EXIT_FAILURE);
    }

    while ((ptr = readdir(Dir)) != NULL){
        if ((*ptr).d_type == DT_REG){
            file_size = get_file_size((*ptr).d_name);
        }

        //null 0 0
        if((str == NULL) && (t == 0) && (d == 0)){
            if(file_size >= size){
                for (i = 0; i < c; ++i){
                    printf("     ");
                }
                printf("%s (File Type: %s)", (*ptr).d_name, type_of_file((*ptr).d_type));
                if( (S == 1) && ((*ptr).d_type == DT_REG) ) //regular file
                {
                    printf("\t(File Size: %d)", file_size);
                }
                printf("\n");


                if ((*ptr).d_type != DT_DIR) //directory
                {
                    continue; // run next loop
                }
                else if (!(strcmp((*ptr).d_name, ".") == 0 || strcmp((*ptr).d_name, "..") == 0)){
                    sprintf(directory_name, "%s/%s", path, (*ptr).d_name); // directory_name = path, ptr.d_name
                    test(directory_name, size, str, S, d, t, count, c + 1); //c+1
                }
                count++;
            }

        }

        //null 0 1
        if((str == NULL) && (t == 0) && (d == 1)){
            if(strcmp( type_of_file((*ptr).d_type), "directory") == 0){
                if(file_size >= size){
                    for (i = 0; i < c; ++i){
                        printf("     ");
                    }
                    printf("%s (File Type: %s)", (*ptr).d_name, type_of_file((*ptr).d_type));
                    if( (S == 1) && ((*ptr).d_type == DT_REG) ) //regular file
                    {
                        printf("\t(File Size: %d)", file_size);
                    }
                    printf("\n");


                    if ((*ptr).d_type != DT_DIR) //directory
                    {
                        continue; // run next loop
                    }
                    else if (!(strcmp((*ptr).d_name, ".") == 0 || strcmp((*ptr).d_name, "..") == 0)){
                        sprintf(directory_name, "%s/%s", path, (*ptr).d_name); // directory_name = path, ptr.d_name
                        test(directory_name, size, str, S, d, t, count, c+1); //c+1
                    }
                    count++;
                }
            }
        }


        //null 1 0
        if((str == NULL) && (t == 1) && (d == 0) ){
            if(strcmp( type_of_file((*ptr).d_type), "regular file") == 0){
                if(file_size >= size){
                    for (i = 0; i < c; ++i){
                        printf("     ");
                    }
                    printf("%s (File Type: %s)", (*ptr).d_name, type_of_file((*ptr).d_type));
                    if( (S == 1) && ((*ptr).d_type == DT_REG) ) //regular file
                    {
                        printf("\t(File Size: %d)", file_size);
                    }
                    printf("\n");


                    if ((*ptr).d_type != DT_DIR) //directory
                    {
                        continue; // run next loop
                    }
                    else if (!(strcmp((*ptr).d_name, ".") == 0 || strcmp((*ptr).d_name, "..") == 0)){
                        sprintf(directory_name, "%s/%s", path, (*ptr).d_name); // directory_name = path, ptr.d_name
                        test(directory_name, size, str, S, d, t, count, c+1); //c+1
                    }
                    count++;
                }
            }
        }

        // V 0 0
        if((str != NULL) && (t == 0) && (d == 0)){
            if(strstr((*ptr).d_name, str) != NULL){
                if(file_size >= size){
                    for (i = 0; i < c; ++i){
                        printf("     ");
                    }
                    printf("%s (File Type: %s)", (*ptr).d_name, type_of_file((*ptr).d_type));
                    if( (S == 1) && ((*ptr).d_type == DT_REG) ) //regular file
                    {
                        printf("\t(File Size: %d)", file_size);
                    }
                    printf("\n");


                    if ((*ptr).d_type != DT_DIR) //directory
                    {
                        continue; // run next loop
                    }
                    else if (!(strcmp((*ptr).d_name, ".") == 0 || strcmp((*ptr).d_name, "..") == 0)){
                        sprintf(directory_name, "%s/%s", path, (*ptr).d_name); // directory_name = path, ptr.d_name
                        test(directory_name, size, str, S, d, t, count, c+1); //c+1
                    }
                    count++;
                }
            }
        }

        // V 0 1
        if((str != NULL) && (t == 0) && (d == 1)){
            if((strstr((*ptr).d_name, str) != NULL) && (strcmp( type_of_file((*ptr).d_type), "directory") == 0)){
                if(file_size >= size){
                    for (i = 0; i < c; ++i){
                        printf("     ");
                    }
                    printf("%s (File Type: %s)", (*ptr).d_name, type_of_file((*ptr).d_type));
                    if( (S == 1) && ((*ptr).d_type == DT_REG) ) //regular file
                    {
                        printf("\t(File Size: %d)", file_size);
                    }
                    printf("\n");


                    if ((*ptr).d_type != DT_DIR) //directory
                    {
                        continue; // run next loop
                    }
                    else if (!(strcmp((*ptr).d_name, ".") == 0 || strcmp((*ptr).d_name, "..") == 0)){
                        sprintf(directory_name, "%s/%s", path, (*ptr).d_name); // directory_name = path, ptr.d_name
                        test(directory_name, size, str, S, d, t, count, c+1); //c+1
                    }
                    count++;
                }
            }
        }

        // V 1 0
        if((str != NULL) && (t == 1) && (d == 0) ){
            if((strstr((*ptr).d_name, str) != NULL) && (strcmp(type_of_file((*ptr).d_type), "regular file") == 0)){
                if( file_size >= size){
                    for (i = 0; i < c; ++i){
                        printf("     ");
                    }
                    printf("%s (File Type: %s)", (*ptr).d_name, type_of_file((*ptr).d_type));
                    if( (S == 1) && ((*ptr).d_type == DT_REG) ) //regular file
                    {
                        printf("\t(File Size: %d)", file_size);
                    }
                    printf("\n");


                    if ((*ptr).d_type != DT_DIR) //directory
                    {
                        continue; // run next loop
                    }
                    else if (!(strcmp((*ptr).d_name, ".") == 0 || strcmp((*ptr).d_name, "..") == 0)){
                        sprintf(directory_name, "%s/%s", path, (*ptr).d_name); // directory_name = path, ptr.d_name
                        test(directory_name, size, str, S, d, t, count, c+1); //c+1
                    }
                    count++;
                }
            }
        }

        //Error
        if((t == 1) && (d == 1)){
            printf("Error\n");
            exit(EXIT_FAILURE);
        }
    }
    closedir(Dir);
    return 1;
}

int opfunc(char *path, int size, char *str, int S, int d, int t, int count, int c, MYFUNC *function){
    return function(path, size, str, S, d, t, count, c);
}

// get file size
// Reference https://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c
int get_file_size(char *file_name){

    struct stat st;
    stat(file_name, &st);
    int size = st.st_size;

    return size;
}