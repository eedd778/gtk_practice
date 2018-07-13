#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <iostream>
#include <string>
#include </home/eedd778/gladetest/vec.h>
#include <fstream>
#include <pthread.h>
#include <vector>
#include <stdint.h>

enum
{
  MYFILE,
  STATUS
};
GtkBuilder *builder;
GtkWidget *window;
GtkWidget *choose;
GtkWidget *label;
GtkWidget *treev;
GtkWidget *web;
GtkWidget *webwindow;
vec openfile;
dic dictionary;
using namespace std;
void showselect()
{
  char text[10] = {};
  sprintf(text, "%d", openfile.getsize());
  gtk_label_set_text(GTK_LABEL(label), text);

  GtkListStore *store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
  GtkTreeIter iter;
  for (int i = 0; i < openfile.getsize(); i++)
  {
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       MYFILE, openfile.getname(i),
                       STATUS, "wait",
                       -1);
  }
  gtk_tree_view_set_model(GTK_TREE_VIEW(treev), GTK_TREE_MODEL(store));
}
/*void *dothread(void *data)
{
  pthread_detach(pthread_self());
  int i = (intptr_t)data;
  for (int j = i + 1; j < openfile.getsize(); j++)
  {
    // cout << openfile.getname(i) << " compare to " << openfile.getname(j) << " ";
    cout << "file" << i << " compare to "
         << "file " << j << " " << openfile.dolcs(i, j) << endl;
  }
  pthread_exit(NULL);
}

void *thread1(void *data)
{
  int i = (intptr_t)data;
  for (; i < openfile.getsize() / 2; i++)
  {
    for (int j = 0; j < openfile.getsize(); j++)
    {
      cout << "file" << i << " compare to "
           << "file" << j << " ";
      cout << openfile.dolcs(i, j) << endl;
    }
  }
  pthread_exit(NULL);
}

void *thread2(void *data)
{
  int i = (intptr_t)data;
  for (; i < openfile.getsize(); i++)
  {
    for (int j = 0; j < openfile.getsize(); j++)
    {
      cout << "file" << i << " compare to "
           << "file" << j << " ";
      cout << openfile.dolcs(i, j) << endl;
    }
  }
  pthread_exit(NULL);
}*/

int main(int argc, char *argv[])
{
  gtk_init(&argc, &argv);
  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "main.glade", NULL);
  window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
  choose = GTK_WIDGET(gtk_builder_get_object(builder, "fcd1"));
  label = GTK_WIDGET(gtk_builder_get_object(builder, "filecount"));
  treev = GTK_WIDGET(gtk_builder_get_object(builder, "treeview"));
  webwindow = GTK_WIDGET(gtk_builder_get_object(builder, "webwindow"));
  web = webkit_web_view_new();
  gtk_container_add(GTK_CONTAINER(webwindow), web);

  gtk_builder_connect_signals(builder, window);
  g_object_unref(builder);
  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}

extern "C" void window1_destroy()
{
  gtk_main_quit();
}

extern "C" void on_quit_btn_clicked()
{
  gtk_main_quit();
}

extern "C" void on_choose_btn_clicked()
{
  gtk_window_set_transient_for(GTK_WINDOW(choose), GTK_WINDOW(window));
  gtk_dialog_run(GTK_DIALOG(choose));
  gtk_widget_hide(choose);
}

extern "C" void on_close_clicked()
{
  gtk_window_close(GTK_WINDOW(choose));
}

extern "C" void callback(gchar *gc, gpointer user_data)
{
  filename newfile;
  newfile.name = gc;
  openfile.push(newfile);
}

extern "C" void on_ok_clicked()
{
  GSList *list;
  list = gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER(choose));
  g_slist_foreach(list, (GFunc)callback, NULL);
  for (int i = 0; i < openfile.getsize(); i++)
  {
    openfile.readfile(i, dictionary);
    openfile.setname(i);
  }
  showselect();
  gtk_window_close(GTK_WINDOW(choose));
}

extern "C" void on_result_btn_clicked()
{
  if (!openfile.empty())
  {
    webkit_web_view_load_uri(WEBKIT_WEB_VIEW(web), "file:///home/eedd778/gladetest/result.html");
    gtk_widget_show_all(webwindow);
  }
}

extern "C" void on_webwindow_destroy()
{
  gtk_widget_hide(webwindow);
}

extern "C" void on_run_btn_clicked()
{
  if (!openfile.empty())
  {
    u_long *d = new u_long;
    clock_t start = clock();

    /* pthread_t *t = new pthread_t[openfile.getsize()]; //thread n
  int *j = new int[openfile.getsize()];
  for (int i = 0; i < openfile.getsize(); i++)
  {
    j[i] = i;
    pthread_create(&t[i], NULL, dothread, (void *)(intptr_t)j[i]);
  }
  pthread_join(t[0], NULL);*/

    /*  for (int i = 0; i < openfile.getsize(); i++) //n^2
  {
    for (int j = 0; j < openfile.getsize(); j++)
    {
      cout << "file" << i << " compare to "
           << "file" << j << " ";
      cout << openfile.dolcs(i, j) << endl;
    }
  }*/

    for (int i = 0; i < openfile.getsize(); i++) //n!
    {
      openfile.putzero(i);
      for (int j = i + 1; j < openfile.getsize(); j++)
      {
        openfile.dolcs(i, j);
      }
    }

    openfile.print();
    openfile.writeresult();
    /* pthread_t *t = new pthread_t[openfile.getsize()];        //thread n*n!
  int *j = new int[openfile.getsize()];
  for (int i = 0; i < openfile.getsize(); i++)
  {
    j[i] = i;
    pthread_create(&t[i], NULL, dothread, (void *)(intptr_t)j[i]);
  }
  pthread_join(t[0], NULL);*/

    /*pthread_t t1, t2;
  int a = 0;
  cout << a << endl;
  int b = openfile.getsize() / 2;
  pthread_create(&t1, NULL, thread1, (void *)(intptr_t)a);
  pthread_create(&t2, NULL, thread2, (void *)(intptr_t)b);
  pthread_join(t1, NULL);*/
    *d = ((double)(clock() - start));
    cout << *d << endl;
  }
}