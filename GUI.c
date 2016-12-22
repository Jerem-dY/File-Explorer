#include "interface.h"



int init_gui(int *argc, char **argv[]){

    /*Initialize GTK+*/
    gtk_init(argc, argv);


    /*mainWindow : */
    init_main_window();


    /*Init widgets */
    init_paned();
    init_main_layout();
    init_third_layout();
    init_second_layout();
    init_list();
    init_control_widgets();



    /*Connect widgets : */
    g_signal_connect(G_OBJECT(mainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(btn_open), "clicked", G_CALLBACK(open_selected), NULL);
    g_signal_connect(G_OBJECT(btn_return), "clicked", G_CALLBACK(open_back), NULL);
    g_signal_connect(G_OBJECT(btn_browse), "clicked", G_CALLBACK(browse), NULL);
    g_signal_connect(G_OBJECT(btn_delete), "clicked", G_CALLBACK(delete), NULL);
    g_signal_connect(G_OBJECT(btn_new), "clicked", G_CALLBACK(new_click), NULL);
    g_signal_connect(G_OBJECT(new_create), "clicked", G_CALLBACK(new_create_click), NULL);


    /*Display widgets : */
    gtk_widget_show_all(mainWindow);
    gtk_widget_hide(fixed);


    return 0;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void init_main_window(void){

    mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(mainWindow), "File Explorer");
    gtk_window_set_default_size(GTK_WINDOW(mainWindow), (gint)M_WINDOW_WIDTH, (gint)M_WINDOW_HEIGHT);

    windowPanel = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(mainWindow), windowPanel);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void init_paned(void){

    paned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    add_to_main_window(paned);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void init_main_layout(void){

    layout1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    gtk_paned_add2(GTK_PANED(paned), layout1);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void init_second_layout(void){

    layout2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    gtk_box_pack_start(GTK_BOX(layout3), layout2, TRUE, TRUE, 5);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void init_third_layout(void){

    layout3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    gtk_paned_add1(GTK_PANED(paned), layout3);

    fixed = gtk_fixed_new();

    gtk_box_pack_end(GTK_BOX(layout3), fixed, TRUE, TRUE, 5);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void init_control_widgets(void){

    btn_open = gtk_button_new_from_stock(GTK_STOCK_OPEN);
    btn_return = gtk_button_new_from_stock(GTK_STOCK_GO_UP);
    entry_path = gtk_entry_new();
    btn_browse = gtk_button_new_from_stock(GTK_STOCK_APPLY);
    btn_delete = gtk_button_new_from_stock(GTK_STOCK_DELETE);
    btn_new = gtk_button_new_from_stock(GTK_STOCK_NEW);

    new_entry = gtk_entry_new();
    new_create = gtk_button_new_from_stock(GTK_STOCK_OK);

    new_radio1 = gtk_radio_button_new_with_label(NULL, "Folder");
    new_radio2 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(new_radio1), "File");

    statusbar = gtk_statusbar_new();

    gtk_box_pack_start(GTK_BOX(layout2), btn_open, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(layout2), btn_return, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(layout2), btn_delete, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(layout2), btn_new, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(layout2), entry_path, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(layout2), btn_browse, FALSE, FALSE, 5);
    gtk_box_pack_end(GTK_BOX(windowPanel), statusbar, FALSE, FALSE, 0);

    gtk_fixed_put(GTK_FIXED(fixed), new_entry, 250, 5);
    gtk_fixed_put(GTK_FIXED(fixed), new_create, 425, 0);
    gtk_fixed_put(GTK_FIXED(fixed), new_radio1, 490, 0);
    gtk_fixed_put(GTK_FIXED(fixed), new_radio2, 490, 15);

    context_id = gtk_statusbar_get_context_id(GTK_STATUSBAR(statusbar), "Number");

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_to_main_window(GtkWidget *widget){

    gtk_box_pack_start(GTK_BOX(windowPanel), widget, TRUE, TRUE, 5);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void init_list(void){


    store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);



    view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));

    scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrolledWindow), view);

    gtk_box_pack_start(GTK_BOX(layout1), scrolledWindow, TRUE, TRUE, 1);

    renderer = gtk_cell_renderer_text_new();

    column = gtk_tree_view_column_new_with_attributes("Element", renderer, "text", COLUMN_NAME, NULL);
    column2 = gtk_tree_view_column_new_with_attributes("Type", renderer, "text", COLUMN_TYPE, NULL);
    column3 = gtk_tree_view_column_new_with_attributes("Size", renderer, "text", COLUMN_SIZE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column2);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column3);
    gtk_tree_view_column_set_min_width(GTK_TREE_VIEW_COLUMN(column), 350);

    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_to_list(char *str){

    GtkTreeIter iter;

    gtk_list_store_append(store, &iter);

    char c_size[128] = {0};
    unsigned long int size = 0;


    if(isDirExist(str)){
        size = 0;
        sprintf(c_size, "%lu", size);

        gtk_list_store_set(store, &iter, COLUMN_NAME, str, COLUMN_TYPE, "", COLUMN_SIZE, "", -1);
    }
    else{
        size = get_size(str)/1024;
        sprintf(c_size, "%lu Ko", size);

        gtk_list_store_set(store, &iter, COLUMN_NAME, str, COLUMN_TYPE, "file", COLUMN_SIZE, c_size, -1);
    }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clear_list(void){

    gtk_list_store_clear(GTK_LIST_STORE(store));

}

