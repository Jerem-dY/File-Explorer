#include "core.h"



void list_dir(void){

    DIR *folder;
    struct dirent *file;

    if(!isDirExist(".")){
        return;
    }

    folder = opendir(".");

    if(folder == NULL){
        return;
    }

    clear_list();


    int x = 0;
    int nbr_files = 0;
    int nbr_folders = 0;

    while((file = readdir(folder))){
        if(strcmp(file->d_name, ".") && strcmp(file->d_name, ".."))
            add_to_list(UTF8(file->d_name)); //Conversion en utf8 pour éviter les bugs d'affichage

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

    gtk_entry_set_text(GTK_ENTRY(entry_path), cwd);
    gtk_statusbar_push(GTK_STATUSBAR(statusbar), context_id, nbr);



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

void remove_dir(char *path){

    DIR *folder;
    struct dirent *file;
    struct stat statistic;

    folder = opendir(path);
    puts(path);

    while((file = readdir(folder))){


    DIR *directory;
    struct dirent *entry;
    struct stat file_stat;


    char buffer[1024] = {0};

    /* On ouvre le dossier. */
    directory = opendir(path);
    if ( directory == NULL ) {
        fprintf(stderr, "cannot open directory %s\n", path);
        return;
    }

    /* On boucle sur les entrées du dossier. */
    while ( (entry = readdir(directory)) != NULL ) {

        /* On "saute" les répertoires "." et "..". */
        if ( strcmp(entry->d_name, ".") == 0 ||
             strcmp(entry->d_name, "..") == 0 ) {
            continue;
        }

        /* On construit le chemin d'accès du fichier en
         * concaténant son nom avec le nom du dossier
         * parent. On intercale "/" entre les deux.
         * NB: '/' est aussi utilisable sous Windows
         * comme séparateur de dossier. */
        snprintf(buffer, 1024, "%s/%s", path, entry->d_name);

        /* On récupère des infos sur le fichier. */
        stat(buffer, &file_stat);
        /* J'ai la flemme de tester la valeur de retour, mais
         * dans un vrai programme il faudrait le faire :D */

        if ( S_ISREG(file_stat.st_mode) ) {
            /* On est sur un fichier, on le supprime. */
            remove(buffer);
        }
        else if ( S_ISDIR(file_stat.st_mode) ) {
            /* On est sur un dossier, on appelle cette fonction. */
            remove_dir(buffer);
        }
    }

    /* On ferme le dossier. */
    closedir(directory);

    /* Maintenant le dossier doit être vide, on le supprime. */
    remove(path);
    /* J'ai toujours la flemme de tester la valeur de retour... */

    return;

    }
}

