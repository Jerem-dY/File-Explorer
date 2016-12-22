#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <windows.h>
#include "interface.h"


#define BASE_DIRECTORY "C:\\Users\\jejeleterrible\\Documents"

#define UTF8(string) g_locale_to_utf8(string, -1, NULL, NULL, NULL)


/*Prototypes de fonctions : */


/**
* List the items of the current working directory
*/
void list_dir(void);


/**
* Check if the directory exist
*/
_Bool isDirExist(char *path);


/**
* Open the given directory
*/
int open_directory(char *path);


/**
* Add each string to the list widget
*/
int string_array_to_list(char **str, int size);


/**
* Get the size of the given file
*/
unsigned int get_size(char *path);


/**
* Open the given file with the default app
*/
void open_file(char *filename);


/**
* Copy the file
*/
int copy_file(char const * const source, char const * const destination);


/**
* Remove a directory
*/
void remove_dir(char *path);


#endif // CORE_H_INCLUDED
