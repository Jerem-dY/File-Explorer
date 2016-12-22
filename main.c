#include "interface.h"
#include "core.h"



int main (int argc, char *argv[])
{

    struct FE_Widgets fe_widgets;


    int error = init_gui(&argc, &argv, &fe_widgets);

    if(error == 1){
        exit(EXIT_FAILURE);
    }

    if(argc == 2 && isDirExist(argv[1])){
        open_directory(argv[1]);
    }
    else{
        open_directory(BASE_DIRECTORY);
    }

    list_dir(&fe_widgets);

    /*Launch gtk+'s mainloop*/
    gtk_main();

    return EXIT_SUCCESS;
}

