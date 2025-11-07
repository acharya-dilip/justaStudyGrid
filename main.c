#include <stdio.h>
#include <gtk/gtk.h>
#include <curl/curl.h>



static void activate(GtkApplication *app,gpointer user_data) {

}



int main(int argc, char **argv){
    FILE *file = fopen("filePath.txt","a");
    fclose(file);
    GtkApplication *app;
    int status;
    app= gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}