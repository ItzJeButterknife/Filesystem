#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILDREN 4

typedef struct inode {
    char *name;
    struct inode *parent;
    struct inode *children[MAX_CHILDREN];
} inode;

inode *addInode(inode *fs, char *name) {
    inode *new_inode;
    new_inode = (inode*) malloc(sizeof(inode*));
    new_inode->name = (char*) malloc(sizeof(char*)*20);
    if (fs == NULL) {
        for(int i = 0; i < MAX_CHILDREN; i++) {
            new_inode->children[i] = NULL;
        }
        new_inode->parent = NULL;
        strcpy(new_inode->name, name);
        //new_inode->children[2] = NULL;
        fs = new_inode;
    }
    else {
        for (int i = 0; i < MAX_CHILDREN; i++) {
            if (fs->children[i] == NULL) {
                new_inode->parent = fs;
                for(int j = 0; j < MAX_CHILDREN; j++) {
                    new_inode->children[j] = NULL;
                }
                strcpy(new_inode->name, name);
                
                
                fs->children[i] = new_inode;
                
                break;
            }
            else if(fs->children[i] != NULL && strcmp(fs->children[i]->name,name)==0) {
                printf("File %s already exists in /\n", name);
                break;
            }
            else if (i >= 3) {
                printf("Directory %s is full.\n", fs->name);
                break;
            }
        }
    }
    
    return fs;
}

void printDirectory(inode *fs) {
    for(int i = 0; i < MAX_CHILDREN; i++) {
        if (fs->children[i] != NULL) {
            char array[strlen(fs->children[i]->name)];
            strcpy(array,fs->children[i]->name);
            if (array[strlen(fs->children[i]->name)-1] == '/') {
                printf("Directory: %s\n", fs->children[i]->name);
            }
            else {
                printf("File: %s\n", fs->children[i]->name);
            }
        }
    }
}

void changeDirectory(inode **fs, char *dir) {
    inode *curr = *fs;
    if (curr != NULL) {
        if (strcmp(dir,"..")== 0 && curr->parent != NULL) {
            *fs = curr->parent;
        }
        else {
            for(int i = 0; i < MAX_CHILDREN; i++) {
                if (curr->children[i] != NULL && strcmp(dir,curr->children[i]->name)==0) {
                    
                    *fs = curr->children[i];
                    break;
                }
                else if(i >= 3) {
                    printf("Directory does not exist!\n");
                }
            }
        }
    }
}

void printFullPath(inode *fs) {
    inode *curr = fs;
    while (curr != NULL) {
        curr = curr->parent;
        printf("%s",curr->parent->name);
        
    }
}

int main(void) {
    char cmd;
    char *name = (char*) malloc(sizeof(char*)*20);
    inode *fc = addInode(NULL, "/");
    do {
        printf("Command? ");
        scanf(" %c", &cmd);
        switch(cmd) {
            case 'a':
                printf("Give filename: ");
                scanf("%s", name);
                fc = addInode(fc,name);
                break;
            case 'p':
                printDirectory(fc);
                break;
            case 'c':
                printf("Change path to: ");
                scanf(" %s", name);
                changeDirectory(&fc,name);
                for(int i = 0; i < MAX_CHILDREN; i++) {
                    if (fc->children[i] == NULL) {
                        printf("%d = NULL\n", i);
                    }
                }
                break;
            case 'f':
                printFullPath(fc);
                break;
            case 'q':
                printf("Bye! ");
                break;
            default:
                printf("Unknown command '%c'\n",cmd);
                break;
        }
    } while (cmd != 'q');
}
