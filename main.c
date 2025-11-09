#include <stdio.h>
#include <gtk/gtk.h>
#include <curl/curl.h>

struct buttons {
    GtkWidget *sweeperButtons;
    int isBomb;
    int isFlag;
}button[9][9];

void declareButtons();
void onClickButton(GtkButton *button,gpointer user_data);


//Globalised variables
GtkWidget *gridMain;
static void activate(GtkApplication *app,gpointer user_data) {

    //Init of windowMain
    GtkWidget *windowMain = gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(windowMain),450,450);
    gtk_window_set_title(GTK_WINDOW(windowMain),"JustaGridSweeper");
    gtk_window_present(GTK_WINDOW(windowMain));

    //init of gridMain
    gridMain = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(windowMain),gridMain);

    //Declare and attach all the buttons
    declareButtons();




}
//for the button number count
int butno;
void declareButtons() {
    for (int i=0;i<9;i++) {
        for (int j = 0;j<9;j++) {

            button[i][j].sweeperButtons = gtk_button_new();
            gtk_grid_attach(GTK_GRID(gridMain),button[i][j].sweeperButtons,j,i,1,1);
            g_signal_connect(button[i][j].sweeperButtons,"clicked",G_CALLBACK(onClickButton),GINT_TO_POINTER(butno));
            //Sets the minimum size of buttons to be 50x50
            gtk_widget_set_size_request(GTK_WIDGET(button[i][j].sweeperButtons),50,50);
            butno++;
        }
    }
}

void onClickButton(GtkButton *button,gpointer user_data) {
    int buttonNo = GPOINTER_TO_INT(user_data);
    printf("Button no=%d",buttonNo);
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

     GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "styles.css");

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );
    return status;
}