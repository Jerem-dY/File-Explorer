#include "callbacks.h"

_Bool isNewShown = FALSE;

void open_selected(GtkWidget *widget, gpointer data){


    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(view));

    GList *list = gtk_tree_selection_get_selected_rows(selection, &model);

    if(list == NULL){
        return;
    }

    GtkTreePath *chemin = list->data;

    GtkTreeIter iter;

    gtk_tree_model_get_iter(model, &iter, chemin);




    GValue *value = (GValue*)g_array_new(FALSE, FALSE, 2048);
    gtk_tree_model_get_value(model, &iter, 0, value);

    char *str = (char *)g_value_get_string(value);


    /*gchar *str = g_char
    gtk_tree_model_get(model, &iter, 0, str, -1);*/


    if(value == NULL){
        return;
    }

    //printf("%s", str);

    open_directory(str);

    list_dir();

}



void open_back(GtkWidget *widget, gpointer data){

    open_directory("..");
    list_dir();

}



void browse(GtkWidget *widget, gpointer data){

    open_directory((char *)gtk_entry_get_text(GTK_ENTRY(entry_path)));
    list_dir();

}


void delete(GtkWidget *widget, gpointer data){

    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(view));

    GList *list = gtk_tree_selection_get_selected_rows(selection, &model);

    if(list == NULL){
        return;
    }

    GtkTreePath *chemin = list->data;

    GtkTreeIter iter;

    gtk_tree_model_get_iter(model, &iter, chemin);


    int error;


    GValue *value = (GValue*)g_array_new(FALSE, FALSE, 2048);
    gtk_tree_model_get_value(model, &iter, 0, value);

    char *str = (char *)g_value_get_string(value);

    if(isDirExist(str)){
        remove_dir(str);
    }
    else{
        error = remove(str);
    }

    if(error==1){
        dialog_delete = gtk_message_dialog_new(GTK_WINDOW(mainWindow), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Error while deleting \"%s\"", str);
        gtk_dialog_run(dialog_delete);
        gtk_widget_destroy(GTK_WIDGET(dialog_delete));
    }
    else{
        dialog_delete = gtk_message_dialog_new(GTK_WINDOW(mainWindow), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Deleting \"%s\" successfull", str);
        gtk_dialog_run(dialog_delete);
        gtk_widget_destroy(GTK_WIDGET(dialog_delete));

    }

    open_directory(".");
    list_dir();

}



void new_click(GtkWidget *widget, gpointer data){

    if(!isNewShown){
        gtk_widget_show(fixed);
        isNewShown = TRUE;
    }
    else{
        gtk_widget_hide(fixed);
        isNewShown = FALSE;
    }

}



void new_create_click(GtkWidget *widget, gpointer data){

    if(!strcmp("", gtk_entry_get_text(GTK_ENTRY(new_entry)))){

        dialog_delete = gtk_message_dialog_new(GTK_WINDOW(mainWindow), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "The name entry is empty !");
        gtk_dialog_run(dialog_delete);
        gtk_widget_destroy(GTK_WIDGET(dialog_delete));


        return;
    }

    char name[255];
    int error = 0;
    strcat(name, gtk_entry_get_text(GTK_ENTRY(new_entry)));


    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(new_radio1))){
        error = mkdir(name);
    }
    else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(new_radio2))){
        FILE *file = fopen(name, "r");

        if(file == NULL){
            fclose(file);
            file = fopen(name, "w");
            fclose(file);
        }
        else{
            dialog_delete = gtk_message_dialog_new(GTK_WINDOW(mainWindow), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Error while creating \"%s\", file exist!", gtk_entry_get_text(GTK_ENTRY(new_entry)));
            gtk_dialog_run(dialog_delete);
            gtk_widget_destroy(GTK_WIDGET(dialog_delete));
        }
    }

    if(error){
        dialog_delete = gtk_message_dialog_new(GTK_WINDOW(mainWindow), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Error while creating \"%s\"", gtk_entry_get_text(GTK_ENTRY(new_entry)));
        gtk_dialog_run(dialog_delete);
        gtk_widget_destroy(GTK_WIDGET(dialog_delete));
    }
    else if(!error){
        dialog_delete = gtk_message_dialog_new(GTK_WINDOW(mainWindow), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Creating \"%s\" successfull", gtk_entry_get_text(GTK_ENTRY(new_entry)));
        gtk_dialog_run(dialog_delete);
        gtk_widget_destroy(GTK_WIDGET(dialog_delete));
    }


    gtk_entry_set_text(GTK_ENTRY(new_entry), " ");
    gtk_widget_hide(fixed);
    isNewShown = FALSE;
    list_dir();


}
