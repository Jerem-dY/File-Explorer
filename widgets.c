#include "interface.h"


/*Main Window : */
GtkWidget *mainWindow = NULL;
GtkWidget *windowPanel = NULL;
GtkWidget *layout1 = NULL; //list's layout
GtkWidget *layout2 = NULL; //Control's layout
GtkWidget *layout3 = NULL; //Additional control's layout
GtkWidget *fixed = NULL;
GtkWidget *paned = NULL;

/*List widget : */
GtkListStore *store = NULL;
GtkWidget *view = NULL;
GtkCellRenderer *renderer = NULL;
GtkTreeViewColumn *column = NULL;
GtkTreeViewColumn *column2 = NULL;
GtkTreeViewColumn *column3 = NULL;
GtkTreeSelection *selection = NULL;

GtkWidget *scrolledWindow = NULL;


/*Control widgets : */
GtkWidget *btn_open = NULL;
GtkWidget *btn_return = NULL;
GtkWidget *entry_path = NULL;
GtkWidget *btn_browse = NULL;
GtkWidget *btn_delete = NULL;
GtkWidget *btn_new = NULL;

/*New file control widgets : */
GtkWidget *new_entry = NULL;
GtkWidget *new_create = NULL;
GtkWidget *new_radio1 = NULL;
GtkWidget *new_radio2 = NULL;


/*Others : */
GtkWidget *statusbar = NULL;
guint context_id;


/*Dialog windows : */
GtkDialog *dialog_delete = NULL;

