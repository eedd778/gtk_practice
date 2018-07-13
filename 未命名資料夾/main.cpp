#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <iostream>
GtkBuilder *builder;
GtkWidget *box;
GtkWidget *window;
GtkWidget *window1;
GtkWidget *web;
int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "main.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "webwindow"));
    window1 = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
    box = GTK_WIDGET(gtk_builder_get_object(builder, "box3"));
    web = webkit_web_view_new();
    gtk_container_add(GTK_CONTAINER(window1), web);

    // gtk_box_pack_start(GTK_BOX(box), web, 1, 1, 0);
    gtk_builder_connect_signals(builder, window);
    g_object_unref(builder);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
extern "C" void on_button1_clicked()
{
    webkit_web_view_load_uri(WEBKIT_WEB_VIEW(web), "file:///home/eedd778/gladetest/haha.html");
    gtk_widget_show_all(window1);
}