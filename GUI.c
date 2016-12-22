#include "interface.h"



int init_gui(int *argc, char **argv[], struct FE_Widgets *fe_widgets){

    /*Initialize GTK+*/
    gtk_init(argc, argv);


    /*mainWindow : */
    init_main_window(fe_widgets);


    /*Init widgets */
    init_paned(fe_widgets);
    init_main_layout(fe_widgets);
    init_third_layout(fe_widgets);
    init_second_layout(fe_widgets);
    init_list(fe_widgets);
    init_control_widgets(fe_widgets);



    /*Connect widgets : */
    g_signal_connect(G_OBJECT(fe_widgets->mainWindow), "delete-event", G_CALLBACK(gtk_main_quit), fe_widgets);
    g_signal_connect(G_OBJECT(fe_widgets->btn_open), "clicked", G_CALLBACK(open_selected), fe_widgets);
    g_signal_connect(G_OBJECT(fe_widgets->btn_return), "clicked", G_CALLBACK(open_back), fe_widgets);
    g_signal_connect(G_OBJECT(fe_widgets->btn_browse), "clicked", G_CALLBACK(browse), fe_widgets);
    g_signal_connect(G_OBJECT(fe_widgets->btn_delete), "clicked", G_CALLBACK(rm), fe_widgets);
    g_signal_connect(G_OBJECT(fe_widgets->btn_new), "clicked", G_CALLBACK(new_click), fe_widgets);
    g_signal_connect(G_OBJECT(fe_widgets->new_create), "clicked", G_CALLBACK(new_create_click), fe_widgets);


    /*Display widgets : */
    gtk_widget_show_all(fe_widgets->mainWindow);
    gtk_widget_hide(fe_widgets->fixed);


    return 0;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void init_main_window(struct FE_Widgets *fe_widgets){

    fe_widgets->mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(fe_widgets->mainWindow), "File Explorer");
    gtk_window_set_default_size(GTK_WINDOW(fe_widgets->mainWindow), (gint)M_WINDOW_WIDTH, (gint)M_WINDOW_HEIGHT);

    fe_widgets->windowPanel = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(fe_widgets->mainWindow), fe_widgets->windowPanel);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void init_paned(struct FE_Widgets *fe_widgets){

    fe_widgets->paned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    add_to_main_window(fe_widgets, fe_widgets->paned);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void init_main_layout(struct FE_Widgets *fe_widgets){

    fe_widgets->layout1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    gtk_paned_add2(GTK_PANED(fe_widgets->paned), fe_widgets->layout1);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void init_second_layout(struct FE_Widgets *fe_widgets){

    fe_widgets->layout2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    gtk_box_pack_start(GTK_BOX(fe_widgets->layout3), fe_widgets->layout2, TRUE, TRUE, 5);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void init_third_layout(struct FE_Widgets *fe_widgets){

    fe_widgets->layout3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    gtk_paned_add1(GTK_PANED(fe_widgets->paned), fe_widgets->layout3);

    fe_widgets->fixed = gtk_fixed_new();

    gtk_box_pack_end(GTK_BOX(fe_widgets->layout3), fe_widgets->fixed, TRUE, TRUE, 5);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void init_control_widgets(struct FE_Widgets *fe_widgets){

    fe_widgets->btn_open = gtk_button_new_from_stock(GTK_STOCK_OPEN);
    fe_widgets->btn_return = gtk_button_new_from_stock(GTK_STOCK_GO_UP);
    fe_widgets->entry_path = gtk_entry_new();
    fe_widgets->btn_browse = gtk_button_new_from_stock(GTK_STOCK_APPLY);
    fe_widgets->btn_delete = gtk_button_new_from_stock(GTK_STOCK_DELETE);
    fe_widgets->btn_new = gtk_button_new_from_stock(GTK_STOCK_NEW);

    fe_widgets->new_entry = gtk_entry_new();
    fe_widgets->new_create = gtk_button_new_from_stock(GTK_STOCK_OK);

    fe_widgets->new_radio1 = gtk_radio_button_new_with_label(NULL, "Folder");
    fe_widgets->new_radio2 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(fe_widgets->new_radio1), "File");

    fe_widgets->statusbar = gtk_statusbar_new();

    gtk_box_pack_start(GTK_BOX(fe_widgets->layout2), fe_widgets->btn_open, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(fe_widgets->layout2), fe_widgets->btn_return, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(fe_widgets->layout2), fe_widgets->btn_delete, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(fe_widgets->layout2), fe_widgets->btn_new, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(fe_widgets->layout2), fe_widgets->entry_path, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(fe_widgets->layout2),fe_widgets-> btn_browse, FALSE, FALSE, 5);
    gtk_box_pack_end(GTK_BOX(fe_widgets->windowPanel), fe_widgets->statusbar, FALSE, FALSE, 0);

    gtk_fixed_put(GTK_FIXED(fe_widgets->fixed), fe_widgets->new_entry, 250, 5);
    gtk_fixed_put(GTK_FIXED(fe_widgets->fixed), fe_widgets->new_create, 425, 0);
    gtk_fixed_put(GTK_FIXED(fe_widgets->fixed), fe_widgets->new_radio1, 490, 0);
    gtk_fixed_put(GTK_FIXED(fe_widgets->fixed), fe_widgets->new_radio2, 490, 15);

    fe_widgets->context_id = gtk_statusbar_get_context_id(GTK_STATUSBAR(fe_widgets->statusbar), "Number");

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_to_main_window(struct FE_Widgets *fe_widgets, GtkWidget *widget){

    gtk_box_pack_start(GTK_BOX(fe_widgets->windowPanel), widget, TRUE, TRUE, 5);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void init_list(struct FE_Widgets *fe_widgets){


    fe_widgets->store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);



    fe_widgets->view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(fe_widgets->store));

    fe_widgets->scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(fe_widgets->scrolledWindow), fe_widgets->view);

    gtk_box_pack_start(GTK_BOX(fe_widgets->layout1), fe_widgets->scrolledWindow, TRUE, TRUE, 1);

    fe_widgets->renderer = gtk_cell_renderer_text_new();

    fe_widgets->column = gtk_tree_view_column_new_with_attributes("Element", fe_widgets->renderer, "text", COLUMN_NAME, NULL);
    fe_widgets->column2 = gtk_tree_view_column_new_with_attributes("Type", fe_widgets->renderer, "text", COLUMN_TYPE, NULL);
    fe_widgets->column3 = gtk_tree_view_column_new_with_attributes("Size", fe_widgets->renderer, "text", COLUMN_SIZE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(fe_widgets->view), fe_widgets->column);
    gtk_tree_view_append_column(GTK_TREE_VIEW(fe_widgets->view), fe_widgets->column2);
    gtk_tree_view_append_column(GTK_TREE_VIEW(fe_widgets->view), fe_widgets->column3);
    gtk_tree_view_column_set_min_width(GTK_TREE_VIEW_COLUMN(fe_widgets->column), 350);

    fe_widgets->selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(fe_widgets->view));

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_to_list(struct FE_Widgets *fe_widgets, char *str){

    GtkTreeIter iter;

    gtk_list_store_append(fe_widgets->store, &iter);

    char c_size[128] = {0};
    unsigned long int size = 0;


    if(isDirExist(str)){
        size = 0;
        sprintf(c_size, "%lu", size);

        gtk_list_store_set(fe_widgets->store, &iter, COLUMN_NAME, str, COLUMN_TYPE, "", COLUMN_SIZE, "", -1);
    }
    else{
        size = get_size(str)/1024;
        sprintf(c_size, "%lu Ko", size);

        gtk_list_store_set(fe_widgets->store, &iter, COLUMN_NAME, str, COLUMN_TYPE, "file", COLUMN_SIZE, c_size, -1);
    }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clear_list(struct FE_Widgets *fe_widgets){

    gtk_list_store_clear(GTK_LIST_STORE(fe_widgets->store));

}

