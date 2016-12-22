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


/*Widgets : */

extern GtkWidget *mainWindow;
extern GtkWidget *windowPanel;
extern GtkWidget *layout1;
extern GtkWidget *layout2;
extern GtkWidget *layout3;
extern GtkWidget *fixed;
extern GtkWidget *paned;

extern GtkListStore *store;
extern GtkWidget *view;
extern GtkCellRenderer *renderer;
extern GtkTreeViewColumn *column;
extern GtkTreeViewColumn *column2;
extern GtkTreeViewColumn *column3;
extern GtkWidget *scrolledWindow;
extern GtkTreeSelection *selection;

extern GtkWidget *btn_open;
extern GtkWidget *btn_return;
extern GtkWidget *entry_path;
extern GtkWidget *btn_browse;
extern GtkWidget *btn_delete;
extern GtkWidget *btn_new;

extern GtkWidget *new_entry;
extern GtkWidget *new_create;
extern GtkWidget *new_radio1;
extern GtkWidget *new_radio2;

extern GtkWidget *statusbar;
extern guint context_id;

extern GtkDialog *dialog_delete;

/*Prototypes de fonctions : */


/**
* Init the whole GUI
*/
int init_gui(int *argc, char **argv[]);


/**
* Init the main window
*/
void init_main_window(void);


/**
* Init the main layout for the main window (grid layout)
*/
void init_main_layout(void);


/**
* Init the second layout, which contains the controls widgets
*/
void init_second_layout(void);


/**
* Init the third layout
*/
void init_third_layout(void);


/**
* Init the paned layout
*/
void init_paned(void);


/**
* Init the list widget
*/
void init_list(void);


/**
* Init the widgets that controls folders and files
*/
void init_control_widgets(void);


/**
* Add the widget to the main window
*/
void add_to_main_window(GtkWidget *widget);


/**
* Add to the list widget a row with a string (name)
*/
void add_to_list(char *str);


/**
* Clear the list widget
*/
void clear_list(void);


#endif // INTERFACE_H_INCLUDED
