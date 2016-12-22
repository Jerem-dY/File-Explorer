#include "callbacks.h"

_Bool isNewShown = FALSE;

void open_selected(GtkWidget *widget, gpointer data){

    /*Get the structure where fe widgets are*/
    struct FE_Widgets *fe_widgets = (struct FE_Widgets*)data;

    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(fe_widgets->view));

    GList *list = gtk_tree_selection_get_selected_rows(fe_widgets->selection, &model);

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

    list_dir(fe_widgets);

}



void open_back(GtkWidget *widget, gpointer data){

    /*Get the structure where fe widgets are*/
    struct FE_Widgets *fe_widgets = (struct FE_Widgets*)data;

    open_directory("..");
    list_dir(fe_widgets);

}



void browse(GtkWidget *widget, gpointer data){

    /*Get the structure where fe widgets are*/
    struct FE_Widgets *fe_widgets = (struct FE_Widgets*)data;

    open_directory((char *)gtk_entry_get_text(GTK_ENTRY(fe_widgets->entry_path)));
    list_dir(fe_widgets);

}


void rm(GtkWidget *widget, gpointer data){

    /*Get the structure where fe widgets are*/
    struct FE_Widgets *fe_widgets = (struct FE_Widgets*)data;

    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(fe_widgets->view));

    GList *list = gtk_tree_selection_get_selected_rows(fe_widgets->selection, &model);

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

    if(isDir(str)){
        error = remove_dir(str);
    }
    else{
        error = remove(str);
    }

    if(error==1){
        fe_widgets->dialog_delete = GTK_DIALOG(gtk_message_dialog_new(GTK_WINDOW(fe_widgets->mainWindow), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Error while deleting \"%s\"", str));
        gtk_dialog_run(fe_widgets->dialog_delete);
        gtk_widget_destroy(GTK_WIDGET(fe_widgets->dialog_delete));
    }
    else{
        fe_widgets->dialog_delete = GTK_DIALOG(gtk_message_dialog_new(GTK_WINDOW(fe_widgets->mainWindow), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Deleting \"%s\" successfull", str));
        gtk_dialog_run(fe_widgets->dialog_delete);
        gtk_widget_destroy(GTK_WIDGET(fe_widgets->dialog_delete));

    }

    open_directory(".");
    list_dir(fe_widgets);

}



void new_click(GtkWidget *widget, gpointer data){

    /*Get the structure where fe widgets are*/
    struct FE_Widgets *fe_widgets = (struct FE_Widgets*)data;

    if(!isNewShown){
        gtk_widget_show(fe_widgets->fixed);
        isNewShown = TRUE;
    }
    else{
        gtk_widget_hide(fe_widgets->fixed);
        isNewShown = FALSE;
    }

}



void new_create_click(GtkWidget *widget, gpointer data){

    /*Get the structure where fe widgets are*/
    struct FE_Widgets *fe_widgets = (struct FE_Widgets*)data;

    if(!strcmp("", gtk_entry_get_text(GTK_ENTRY(fe_widgets->new_entry)))){

        fe_widgets->dialog_delete = GTK_DIALOG(gtk_message_dialog_new(GTK_WINDOW(fe_widgets->mainWindow), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "The name entry is empty !"));
        gtk_dialog_run(fe_widgets->dialog_delete);
        gtk_widget_destroy(GTK_WIDGET(fe_widgets->dialog_delete));


        return;
    }

    char name[255];
    int error = 0;
    strcat(name, gtk_entry_get_text(GTK_ENTRY(fe_widgets->new_entry)));


    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(fe_widgets->new_radio1))){
        error = mkdir(name);
    }
    else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(fe_widgets->new_radio2))){
        FILE *file = fopen(name, "r");

        if(file == NULL){
            fclose(file);
            file = fopen(name, "w");
            fclose(file);
        }
        else{
            fe_widgets->dialog_delete = GTK_DIALOG(gtk_message_dialog_new(GTK_WINDOW(fe_widgets->mainWindow), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Error while creating \"%s\", file exist!", gtk_entry_get_text(GTK_ENTRY(fe_widgets->new_entry))));
            gtk_dialog_run(fe_widgets->dialog_delete);
            gtk_widget_destroy(GTK_WIDGET(fe_widgets->dialog_delete));
        }
    }

    if(error){
        fe_widgets->dialog_delete = GTK_DIALOG(gtk_message_dialog_new(GTK_WINDOW(fe_widgets->mainWindow), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Error while creating \"%s\"", gtk_entry_get_text(GTK_ENTRY(fe_widgets->new_entry))));
        gtk_dialog_run(fe_widgets->dialog_delete);
        gtk_widget_destroy(GTK_WIDGET(fe_widgets->dialog_delete));
    }
    else if(!error){
        fe_widgets->dialog_delete = GTK_DIALOG(gtk_message_dialog_new(GTK_WINDOW(fe_widgets->mainWindow), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Creating \"%s\" successfull", gtk_entry_get_text(GTK_ENTRY(fe_widgets->new_entry))));
        gtk_dialog_run(fe_widgets->dialog_delete);
        gtk_widget_destroy(GTK_WIDGET(fe_widgets->dialog_delete));
    }


    gtk_entry_set_text(GTK_ENTRY(fe_widgets->new_entry), " ");
    gtk_widget_hide(fe_widgets->fixed);
    isNewShown = FALSE;
    list_dir(fe_widgets);


}
