#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include <stdlib.h>
#include <gtk/gtk.h>
#include "callbacks.h"


/*Constantes : */

#define M_WINDOW_WIDTH 900
#define M_WINDOW_HEIGHT 600

enum{

    COLUMN_NAME,
    COLUMN_TYPE,
    COLUMN_SIZE,
    N_COLUMNS

};


struct FE_Widgets
{
    /*Main Window : */
    GtkWidget *mainWindow;
    GtkWidget *windowPanel;
    GtkWidget *layout1; //list's layout
    GtkWidget *layout2; //Control's layout
    GtkWidget *layout3; //Additional control's layout
    GtkWidget *fixed;
    GtkWidget *paned;

    /*List widget : */
    GtkListStore *store;
    GtkWidget *view;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeViewColumn *column2;
    GtkTreeViewColumn *column3;
    GtkTreeSelection *selection;

    GtkWidget *scrolledWindow;


    /*Control widgets : */
    GtkWidget *btn_open;
    GtkWidget *btn_return;
    GtkWidget *entry_path;
    GtkWidget *btn_browse;
    GtkWidget *btn_delete;
    GtkWidget *btn_new;

    /*New file control widgets : */
    GtkWidget *new_entry;
    GtkWidget *new_create;
    GtkWidget *new_radio1;
    GtkWidget *new_radio2;


    /*Others : */
    GtkWidget *statusbar;
    guint context_id;


    /*Dialog windows : */
    GtkDialog *dialog_delete;
};

/*Prototypes de fonctions : */


/**
* Init the whole GUI
*/
int init_gui(int *argc, char **argv[], struct FE_Widgets *fe_widgets);


/**
* Init the main window
*/
void init_main_window(struct FE_Widgets *fe_widgets);


/**
* Init the main layout for the main window (grid layout)
*/
void init_main_layout(struct FE_Widgets *fe_widgets);


/**
* Init the second layout, which contains the controls widgets
*/
void init_second_layout(struct FE_Widgets *fe_widgets);


/**
* Init the third layout
*/
void init_third_layout(struct FE_Widgets *fe_widgets);


/**
* Init the paned layout
*/
void init_paned(struct FE_Widgets *fe_widgets);


/**
* Init the list widget
*/
void init_list(struct FE_Widgets *fe_widgets);


/**
* Init the widgets that controls folders and files
*/
void init_control_widgets(struct FE_Widgets *fe_widgets);


/**
* Add the widget to the main window
*/
void add_to_main_window(struct FE_Widgets *fe_widgets, GtkWidget *widget);


/**
* Add to the list widget a row with a string (name)
*/
void add_to_list(struct FE_Widgets *fe_widgets, char *str);


/**
* Clear the list widget
*/
void clear_list(struct FE_Widgets *fe_widgets);


#endif // INTERFACE_H_INCLUDED
