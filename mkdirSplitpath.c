#include "types.h"

#include <stdio.h>

extern struct NODE* root;
extern struct NODE* cwd;

const int pathCharMax=256;
const int levelCharMax=32;
const int pathDepthMax=16;

struct NODE* getChild(struct NODE* parent, char* childName);

//make directory
void mkdir(char pathName[]){

    // TO BE IMPLEMENTED
    //
    // YOUR CODE TO REPLACE THE PRINTF FUNCTION BELOW

    printf("TO BE IMPLEMENTED\n");

    return;
}

//handles tokenizing and absolute/relative pathing options
struct NODE* splitPath(char* pathName, char* baseName, char* dirName){
    
    dirName="";
    baseName="";

    //check path name
    char newPathName[256] = {'\0'};
    if (pathName!=NULL && pathName[0]!='\0'){
        strcpy(newPathName, pathName);
    }
    else{ 
        newPathName[0]='/';
        printf("No path given");
    }


    //edge case where no path is provided
    if (newPathName[1]='\0'){
        dirName[0] = '/\0';
        baseName[0]='\0';
        return root;
    }

    int itemsInPath=0;
    char tokenizedPath[pathDepthMax][pathCharMax]={'\0'};

    char* token = strtok(newPathName, '/');

    while (token!=NULL){
        strcpy(tokenizedPath[itemsInPath], token);
        itemsInPath++;
        if (itemsInPath==pathDepthMax){printf("Path has to many elements to be correctly parsed"); return NULL;}
        token = strtok(NULL, '/');
    }

    struct NODE* currentLocation = NULL;
    int pathLocation=0;


    if (tokenizedPath[0]=='\0'){
        currentLocation=root;
        pathLocation=1;
        strcat(dirName, "/");
    }
    else{
        currentLocation=cwd;
    }

    

    for(;pathLocation<itemsInPath; pathLocation++){
        currentLocation = getChild(currentLocation, tokenizedPath[pathLocation]);
        
        if (pathLocation!=itemsInPath-1){
            strcat(dirName, tokenizedPath[pathLocation]);
            strcat(dirName, "/");
        }
        else {
            strcat(baseName, tokenizedPath[pathLocation]);
            strcat(baseName, "/");
        }
        if (currentLocation==NULL){
            printf("ERROR: directory %s does not exist", dirName);
        }

    }

    
    

    //printf("%s\n", newPathName);

    return currentLocation;
}


struct NODE* getChild(struct NODE* parent, char* childName){
    struct NODE* current = parent->childPtr;
    while(current!=NULL){
        if (strcmp(current->name, childName)){
            return current;
        }
    }
    return NULL;

}

