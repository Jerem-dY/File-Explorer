#include "interface.h"
#include "core.h"



int main (int argc, char *argv[])
{

    struct FE_Widgets fe_widgets;

    fe_widgets.btn_browse = NULL;
    fe_widgets.btn_delete = NULL;
    fe_widgets.btn_new = NULL;
    fe_widgets.btn_open = NULL;
    fe_widgets.btn_return = NULL;
    fe_widgets.column2 = NULL;
    fe_widgets.column3 = NULL;
    fe_widgets.column = NULL;
    fe_widgets.context_id = NULL;
    fe_widgets.dialog_delete = NULL;
    fe_widgets.entry_path = NULL;
    fe_widgets.fixed = NULL;
    fe_widgets.layout1 = NULL;
    fe_widgets.layout2 = NULL;
    fe_widgets.layout3 = NULL;
    fe_widgets.mainWindow = NULL;
    fe_widgets.new_create = NULL;
    fe_widgets.new_entry = NULL;
    fe_widgets.new_radio1 = NULL;
    fe_widgets.new_radio2 = NULL;
    fe_widgets.paned = NULL;
    fe_widgets.renderer = NULL;
    fe_widgets.scrolledWindow = NULL;
    fe_widgets.selection = NULL;
    fe_widgets.statusbar = NULL;
    fe_widgets.store = NULL;
    fe_widgets.view = NULL;
    fe_widgets.windowPanel = NULL;

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


    /*Launch gtk+'s mainloop*/
    gtk_main();

    return EXIT_SUCCESS;
}

