#include "types.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern struct NODE* root;
extern struct NODE* cwd;

const int pathCharMax=256;
const int levelCharMax=64;


struct NODE* getChild(struct NODE* parent, char* childName);

//make directory
void mkdir(char pathName[]){

    if (strcmp(pathName, "/")==0){
        printf("MKDIR ERROR: no path provided\n");
    }

    char* baseName = malloc(sizeof(char)*64);
    memset(baseName, '\0', 64);

    char* temp = malloc(strlen(pathName)+1);
    
    struct NODE* head = splitPath(pathName, baseName, temp);
    free(temp);

    //printf("head: %p\n", head);
    //printf("head %p\n", head);

    if (head==NULL){
        return;
    }

    if (getChild(head, baseName)!=NULL){
        printf("MKDIR ERROR: directory %s already exists\n", pathName);
        return;
    }

    printf("MKDIR SUCCESS: node %s successfully created\n", pathName);

    struct NODE* newDir = malloc(sizeof(struct NODE));
    
    //printf("newDir %s \n", baseName);
    strcpy(newDir->name, baseName);
    //printf("newDir %s \n", newDir->name);

    newDir->parentPtr = head;
    newDir->fileType='D';

    if (head->childPtr==NULL){
        head->childPtr=newDir;
        return;
    }
    head=head->childPtr;

    while (1){
        if (head->siblingPtr==NULL){
            head->siblingPtr=newDir;
            return;
        }
        else{
            head=head->siblingPtr;
        }
    }


    
    //newDir->name=baseName;




    // TO BE IMPLEMENTED
    //
    // YOUR CODE TO REPLACE THE PRINTF FUNCTION BELOW

    //printf("TO BE IMPLEMENTED\n");

    return;
}

//handles tokenizing and absolute/relative pathing options
struct NODE* splitPath(char* pathName, char* baseName, char* dirName){
    //printf("BaseNane %s\n", baseName);
    strcpy(baseName, "");
    strcpy(dirName, "");
    //printf("test1\n");
    dirName[0]='\0';

    //check path name
    char newPathName[256] = {'\0'};
    if (pathName!=NULL && pathName[0]!='\0'){
        strcpy(newPathName, pathName);

    }
    else{ 
        newPathName[0]='/';
        //printf("No path given\n");
    }

    //printf("%s\n",newPathName);


    //edge case where no path is provided
    if (newPathName[0]=='/'&&newPathName[1]=='\0'){
        //printf(":3%s\n", dirName);
        strcat(dirName, "/");
        //printf("test2\n");

        baseName[0]='\0';

        // printf("newPathName[1]\n");
        // printf("PathName%s\n", pathName);
        // printf("baseName%s\n", baseName);
        // printf("dirName%s\n", dirName);

        return root;
    }



    //printf("path: %s\n", newPathName);

    char* token=NULL;
    struct NODE* currentLocation = NULL;
    int charsLeft = strlen(pathName);



    if (pathName[0]=='/'){
        currentLocation=root;
        strcat(dirName, "/");
        charsLeft--;
        printf("root\n");
    }
    else{
        currentLocation=cwd;
        //printf("cwd: %p\n", cwd);

    }

    while (1){

        if (token == NULL)  {token= strtok(newPathName, "/");}
        else {token = strtok(NULL, "/");}
        charsLeft-=(strlen(token)+1);
        // printf("token: %s\n", token);
        // printf("Chars left: %d\n", charsLeft);
        if (charsLeft<=0){
            strcat(baseName, token);
            //printf("token: %s", token);
            break;
        }






        currentLocation = getChild(currentLocation, token);

        //printf("directory %p\n", currentLocation);
        if (currentLocation==NULL){
            printf("ERROR: directory %s does not exist\n", dirName);
            return NULL;
        }


        if (strlen(dirName)!=0&&dirName[strlen(dirName)-1]!='/') strcat(dirName, "/");
        strcat(dirName, currentLocation->name);
        //printf("CurrentLocation.name: %s\n", currentLocation->name);
        


                
 


    }


    // printf("PathName: %s\n", pathName);
    // printf("baseName: %s\n", baseName);
    // printf("dirName: %s\n", dirName);
    // printf("returnNodeName: %s\n", currentLocation->name);


    return currentLocation;
}


struct NODE* getChild(struct NODE* parent, char* childName){
    struct NODE* current = parent->childPtr;
    while(current!=NULL){
        if (strcmp(current->name, childName)==0){
            return current;
        }
        current=current->childPtr;
    }
    return NULL;

}

