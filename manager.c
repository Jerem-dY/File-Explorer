#include "core.h"



void list_dir(struct FE_Widgets *fe_widgets){


    DIR *folder;
    struct dirent *file;

    if(!isDirExist(".")){
        return;
    }

    folder = opendir(".");

    if(folder == NULL){
        return;
    }

    clear_list(fe_widgets);


    int x = 0;
    int nbr_files = 0;
    int nbr_folders = 0;

    while((file = readdir(folder))){
        if(strcmp(file->d_name, ".") && strcmp(file->d_name, ".."))
            add_to_list(fe_widgets, UTF8(file->d_name)); //Conversion en utf8 pour éviter les bugs d'affichage

            if(isDirExist(file->d_name)){
                nbr_folders++;
            }
            else
                nbr_files++;
        x++;
    }

    char cwd[255];
    getcwd(cwd, 255);

    char nbr[128];
    sprintf(nbr, "Elements : %d ; Files : %d ; Folders : %d", nbr_folders+nbr_files, nbr_files, nbr_folders);

    gtk_entry_set_text(GTK_ENTRY(fe_widgets->entry_path), cwd);
    gtk_statusbar_push(GTK_STATUSBAR(fe_widgets->statusbar), fe_widgets->context_id, nbr);



}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_Bool isDirExist(char *path){

    DIR *folder;

    folder = opendir(path);

    if(folder == NULL){
        return 0;
    }

    return 1;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_Bool isDir(char *path){

    struct stat s_buf;

    if (stat(path, &s_buf))
        return 0;

    return S_ISDIR(s_buf.st_mode);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int open_directory(char *path){

    if(!isDirExist(path)){
        open_file(path);
        return 1;
    }

    if(!chdir(path)){
        return 1;
    }

    return 0;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int get_size(char *path){

    /*struct stat statistic;

    stat(path, &statistic);


    return (unsigned int)statistic.st_size;*/

    FILE *file = fopen(path, "r");
    unsigned int ret;

   if(file == NULL)
   {
      return -1;
   }

   /*On place le curseur à la fin*/
   fseek(file, 0, SEEK_END);
   /*On récupére la position courante*/
   ret = (unsigned int)ftell(file);
   fclose(file);
   return ret;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void open_file(char *filename){

    ShellExecute(NULL, "open", filename, NULL, NULL, SW_SHOWDEFAULT);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int copy_file(char const * const source, char const * const destination)
{
    FILE* fSrc;
    FILE* fDest;
    char buffer[512];
    int NbLus;

    if ((fSrc = fopen(source, "rb")) == NULL)
    {
        return 1;
    }

    if ((fDest = fopen(destination, "wb")) == NULL)
    {
        fclose(fSrc);
        return 2;
    }

    while ((NbLus = fread(buffer, 1, 512, fSrc)) != 0)
        fwrite(buffer, 1, NbLus, fDest);

    fclose(fDest);
    fclose(fSrc);

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int remove_dir(char *path){

    DIR*            dir;
    struct dirent*  ep;
    char            p_buf[512] = {0};


    dir = opendir(path);

    while ((ep = readdir(dir))) {

        sprintf(p_buf, "%s/%s", path, ep->d_name);
        if (isDir(p_buf))
            remove_dir(p_buf); //Problème de récursivité ici
        else
            unlink(p_buf);
    }

    closedir(dir);

    return rmdir(path);
}

