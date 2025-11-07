#include <stdio.h>
#include <gtk/gtk.h>
#include <curl/curl.h>

struct buttons {
    GtkWidget *sweeperButtons;
}button[81];

void declareButtons();


static void activate(GtkApplication *app,gpointer user_data) {

    //Init of windowMain
    GtkWidget *windowMain = gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(windowMain),500,500);
    gtk_window_set_title(GTK_WINDOW(windowMain),"justaGridSweeper");
    gtk_window_present(GTK_WINDOW(windowMain));





}
//for the button number count
int butno;
void declareButtons() {
    for (int i=0;i<9;i++) {
        for (int j = 0;j<9;j++) {

            button[butno].sweeperButtons = gtk_button_new();


            butno++;
        }
    }
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