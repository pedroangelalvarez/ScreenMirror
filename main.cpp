#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <X11/Xlib.h>
#include "gtk/gtk.h"
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <unistd.h>
#include <cairo.h>

using namespace std;

int main(int argc, char* argv[])
{
        gtk_init(&argc, &argv);
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(window), "WELCOME");

        gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
        gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

        //gtk_window_set_default_size(GTK_WINDOW(window), 700, 550);
        //char *file = ;
        icono = gdk_pixbuf_new_from_file_at_scale("./src/icono.png", 80, 80, TRUE, NULL);

        //gtk_image_set_from_file(GTK_IMAGE(image),file);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image), pixbuf);
        gtk_window_set_icon(GTK_WINDOW(window), icono);
        gtk_widget_set_size_request(GTK_WIDGET(window), ancho, alto);
        //gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
        //gtk_container_set_border_width(GTK_CONTAINER(window), 10);

        vbox = gtk_vbox_new(FALSE, 5);

        hbox = gtk_hbox_new(TRUE, 3);

        /*GtkWidget *load_button = gtk_button_new_with_label("Load");
        GtkWidget *run_button = gtk_button_new_with_label("Run");
        gtk_widget_set_size_request(load_button, 70, 30);
        gtk_widget_set_size_request(run_button, 70, 30);

        gtk_container_add(GTK_CONTAINER(hbox), load_button);
        gtk_container_add(GTK_CONTAINER(hbox), run_button);*/

        menu_bar = gtk_menu_bar_new();
        gtk_container_add(GTK_CONTAINER (hbox), menu_bar);
        gtk_widget_show(menu_bar);


        //MENU ARCHIVO
        file_menu = gtk_menu_new();
        open_item = gtk_menu_item_new_with_label("Abrir");
        quit_item = gtk_menu_item_new_with_label("Salir");
        gtk_menu_shell_append(GTK_MENU_SHELL (file_menu), open_item);
        gtk_menu_shell_append(GTK_MENU_SHELL (file_menu), quit_item);

        g_signal_connect(G_OBJECT(open_item), "activate",
                         G_CALLBACK(load_file),
                         (gpointer) "file.open");

        g_signal_connect(G_OBJECT(quit_item), "activate",
                         G_CALLBACK(destroy),
                         (gpointer) "file.quit");
        gtk_widget_show(open_item);
        gtk_widget_show(quit_item);

        file_item = gtk_menu_item_new_with_label("Archivo");
        gtk_widget_show(file_item);
        gtk_menu_item_set_submenu(GTK_MENU_ITEM (file_item), file_menu);

        //MENU PREPROCESAMIENTO

        prepro_menu = gtk_menu_new();
        //GtkWidget *gray_item = gtk_menu_item_new_with_label ("Escala de Grises");//SACA ESCALA DE GRISES
        GtkWidget *filtrado_item = gtk_menu_item_new_with_label("Filtrado");
        GtkWidget *pseudocolor_item = gtk_menu_item_new_with_label("Pseudocolor");
        GtkWidget *erosion_item = gtk_menu_item_new_with_label("Erosión"); //ESCALAR +100
        //gtk_menu_shell_append(GTK_MENU_SHELL (prepro_menu), gray_item);//SACA ESCALA DE GRISES
        gtk_menu_shell_append(GTK_MENU_SHELL (prepro_menu), filtrado_item);
        gtk_menu_shell_append(GTK_MENU_SHELL (prepro_menu), pseudocolor_item);
        gtk_menu_shell_append(GTK_MENU_SHELL (prepro_menu), erosion_item);


        /*g_signal_connect(G_OBJECT(gray_item), "activate",
                                   G_CALLBACK (escalaDeGrises),
                                   (gpointer) "prepro.grises"); SACA ESCALA DE GRISES*/

        g_signal_connect(G_OBJECT(pseudocolor_item), "activate",
                         G_CALLBACK(pseudocolor),
                         (gpointer) "prepro.pseudocolor");

        g_signal_connect(G_OBJECT(filtrado_item), "activate",
                         G_CALLBACK(filtrado),
                         (gpointer) "prepro.filtrado");

        g_signal_connect(G_OBJECT(erosion_item), "activate",
                         G_CALLBACK(erosion),
                         (gpointer) "prepro.escalar");
        //gtk_widget_show (gray_item); ///SACA A ESCALA DE GRISES
        gtk_widget_show(filtrado_item);
        gtk_widget_show(pseudocolor_item);
        //gtk_widget_show(escalar_item);


        prepro_item = gtk_menu_item_new_with_label("Preprocesamiento");
        gtk_widget_show(prepro_item);
        gtk_menu_item_set_submenu(GTK_MENU_ITEM (prepro_item), prepro_menu);
        //gtk_menu_bar_append(GTK_MENU_BAR



        //MENU PROCESAMIENTO
        pro_menu = gtk_menu_new();


        GtkWidget *recorte_item = gtk_menu_item_new_with_label("Recorte");
        GtkWidget *gray_item = gtk_menu_item_new_with_label("Escala de Grises");
        GtkWidget *borde_item = gtk_menu_item_new_with_label("Deteccion de Bordes Sobel");

        gtk_menu_shell_append(GTK_MENU_SHELL (pro_menu), recorte_item);
        gtk_menu_shell_append(GTK_MENU_SHELL (pro_menu), gray_item);
        gtk_menu_shell_append(GTK_MENU_SHELL (pro_menu), borde_item);


        g_signal_connect(G_OBJECT(recorte_item), "activate",
                         G_CALLBACK(recorte),
                         (gpointer) "pro.recorte");

        g_signal_connect(G_OBJECT(gray_item), "activate",
                         G_CALLBACK(escalaDeGrises),
                         (gpointer) "prepro.grises");

        g_signal_connect(G_OBJECT(borde_item), "activate",
                         G_CALLBACK(deteccionBordes),
                         (gpointer) "pro.borde");

        gtk_widget_show(recorte_item);
        gtk_widget_show(gray_item);
        gtk_widget_show(borde_item);

        pro_item = gtk_menu_item_new_with_label("Segmentacion");
        gtk_widget_show(pro_item);
        gtk_menu_item_set_submenu(GTK_MENU_ITEM (pro_item), pro_menu);

        //MENU INTERPRETACION
        inter_menu = gtk_menu_new();
        GtkWidget *svm_item = gtk_menu_item_new_with_label("SVM");
        gtk_menu_shell_append(GTK_MENU_SHELL (inter_menu), svm_item);
        g_signal_connect(G_OBJECT(svm_item), "activate",
                         G_CALLBACK(recorte),
                         (gpointer) "inter.svm");
        gtk_widget_show(svm_item);


        inter_item = gtk_menu_item_new_with_label("Reconocimiento");
        gtk_widget_show(inter_item);
        gtk_menu_item_set_submenu(GTK_MENU_ITEM (inter_item), inter_menu);

        gtk_menu_shell_append(GTK_MENU_SHELL (menu_bar), file_item);
        gtk_menu_shell_append(GTK_MENU_SHELL (menu_bar), prepro_item);
        gtk_menu_shell_append(GTK_MENU_SHELL (menu_bar), pro_item);
        gtk_menu_shell_append(GTK_MENU_SHELL (menu_bar), inter_item);
        gtk_widget_set_sensitive(prepro_item, FALSE);
        gtk_widget_set_sensitive(pro_item, FALSE);
        gtk_widget_set_sensitive(inter_item, FALSE);
        //expression_label = gtk_label_new("Expression");

        //image = gtk_image_new();

        //Display placeholder image
        image = gtk_image_new_from_file(NULL);
        /*static GtkTargetEntry entries[] = {
       { "GTK_LIST_BOX_ROW", GTK_TARGET_SAME_APP, 0 }
    };
    gtk_drag_dest_set(DEST_DEFAULT_ALL , entries, GDK_ACTION_COPY);
    g_signal_connect_swapped(G_OBJECT(image), "drag-data-received", G_CALLBACK(on_drop), NULL);
    */
        liststore = gtk_list_store_new(NUM_COLS, G_TYPE_STRING);

        //lblPath.DragDataReceived += new Gtk.DragDataReceivedHandler(OnLabelDragDataReceived)
        //gtk_drag_dest_set(Gtk.DestDefaults.ALL, [enforce_target], Gdk.DragAction.COPY);

        //img->connect('drag-data-received', on_drop, image);
        //list<GtkTargetEntry> listTargets;
        //listTargets.push_back(GtkTargetEntry("text/uri-list"));
        //gtk_drag_dest_set(window,GTK_DEST_DEFAULT_ALL, listTargets,1, GDK_ACTION_COPY);
        //g_drag_dest_set(listTargets, GTK_DEST_DEFAULT_MOTION | GTK_DEST_DEFAULT_DROP, GDK_ACTION_COPY | GDK_ACTION_MOVE);

        gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

        //gtk_container_add(GTK_CONTAINER(window),vbox);
        //gtk_box_pack_start(GTK_BOX(vbox), image, FALSE, FALSE, 0);
        contenedor = gtk_grid_new();


        darea = gtk_drawing_area_new();
        gtk_widget_set_size_request (darea, 350, 450);
        //gtk_box_pack_end(GTK_BOX(vbox), darea, FALSE, FALSE, 0);

        //gtk_box_pack_end(GTK_BOX(vbox), expression_label, FALSE, FALSE, 0);
        gtk_grid_attach (GTK_GRID(contenedor), image, 0, 0, 1, 1);
        gtk_grid_attach (GTK_GRID(contenedor), darea, 1, 0, 1, 1);
        gtk_grid_set_row_homogeneous(GTK_GRID(contenedor),true);
        gtk_grid_set_column_homogeneous(GTK_GRID(contenedor),true);
        gtk_box_pack_start(GTK_BOX(vbox), contenedor, FALSE, FALSE, 0);

        GdkRGBA color = {.75, .75, .75, 1.0};
        gtk_widget_override_background_color(GTK_WIDGET(vbox), GTK_STATE_FLAG_NORMAL, &color );
        gtk_container_add(GTK_CONTAINER(window), vbox);

        gtk_widget_set_size_request(GTK_WIDGET(window), ancho, alto);
        //int load_handler_id = g_signal_connect(G_OBJECT(load_button), "clicked", G_CALLBACK(load_file), NULL);

        //g_signal_connect(G_OBJECT(run_button), "clicked", G_CALLBACK(get_expression), NULL);

        enum {
            TARGET_STRING,
            TARGET_URL
        };

        static GtkTargetEntry targetentries[] =
                {
                        {"STRING",        0, TARGET_STRING},
                        {"text/plain",    0, TARGET_STRING},
                        {"text/uri-list", 0, TARGET_URL},
                };

        gtk_drag_dest_set(window, GTK_DEST_DEFAULT_ALL, targetentries, 3, GDK_ACTION_COPY);


        //data = malloc(sizeof(*data));
        //image
        g_signal_connect(window, "drag_data_received", G_CALLBACK(on_drop), liststore);


        g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

        gtk_widget_show_all(window);

        gtk_main();
    }

    return 0;
}
