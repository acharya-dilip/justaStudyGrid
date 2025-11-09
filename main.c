#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <curl/curl.h>

struct buttons {
    GtkWidget *sweeperButtons;
    int isBomb;
    int isFlag;
}button[9][9];
//Stores the values of the buttonNumbers for Mines
int buttonMines[10]={0,1,2,3,4,5,6,7,8};

void declareButtons();
void onClickButton(GtkButton *button,gpointer user_data);
void fetchRandInt();
void setMine();
void setNumbers();


//Globalised variables
GtkWidget *gridMain;
static void activate(GtkApplication *app,gpointer user_data) {

    //Initalizing CSS
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "styles.css");
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );

    //Init of windowMain
    GtkWidget *windowMain = gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(windowMain),450,450);
    gtk_window_set_title(GTK_WINDOW(windowMain),"JustaGridSweeper");
    gtk_window_present(GTK_WINDOW(windowMain));

    //init of gridMain
    gridMain = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(windowMain),gridMain);

    //Sets Random Buttons as mines
    setMine();
    //Declare and attach all the buttons
    declareButtons();




}

void fetchRandInt() {

}



void setMine() {
    fetchRandInt();
    for (int k=0;k<10;k++) {
        int i = buttonMines[k]/10;
        int j = buttonMines[k] % 10;
        button[i][j].isBomb = 1;
    }
}



void setNumbers() {

}

//for the button number count
void declareButtons() {
    for (int i=0;i<9;i++) {
        for (int j = 0;j<9;j++) {

            button[i][j].sweeperButtons = gtk_button_new();
            gtk_grid_attach(GTK_GRID(gridMain),button[i][j].sweeperButtons,j,i,1,1);
            if (button[i][j].isBomb==1) {
                gtk_widget_add_css_class(button[i][j].sweeperButtons,"ButtonBomb");
            }
            g_signal_connect(button[i][j].sweeperButtons,"clicked",G_CALLBACK(onClickButton),GINT_TO_POINTER((i*10)+j));
            //Sets the minimum size of buttons to be 50x50
            gtk_widget_set_size_request(GTK_WIDGET(button[i][j].sweeperButtons),50,50);
        }
    }
}




void onClickButton(GtkButton *button,gpointer user_data) {
    int buttonNo = GPOINTER_TO_INT(user_data);
    int i = buttonNo / 10;
    int j = buttonNo % 10;
    printf("Button no=%d\n",buttonNo);
    printf("i=%d \t j=%d",i,j);
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