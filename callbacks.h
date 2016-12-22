#ifndef CALLBACKS_H_INCLUDED
#define CALLBACKS_H_INCLUDED

#include "interface.h"
#include "core.h"

void open_selected(GtkWidget *widget, gpointer data);
void open_back(GtkWidget *widget, gpointer data);
void browse(GtkWidget *widget, gpointer data);
void rm(GtkWidget *widget, gpointer data);
void new_click(GtkWidget *widget, gpointer data);
void new_create_click(GtkWidget *widget, gpointer data);

#endif // CALLBACKS_H_INCLUDED
