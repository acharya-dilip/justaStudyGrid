#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gtk/gtk.h>
#include <curl/curl.h>


struct buttons {
    GtkWidget *sweeperButtons;
    int isBomb;
    int isFlag;
    int proximalMines;
}buttons[9][9];
//Stores the values of the buttonNumbers for Mines
int buttonMines[10];//={00,11,22,33,44,55,66,77,88,23};

void mainWindow();
void declareButtons();
void onClickButton(GtkButton *button,gpointer user_data);
void fetchRandInt();
void setMine();
void setProximalMines();
void expandClick();
void gameOver();
void restartGame();
void clearMines();


//Globalized Variables
GtkWidget *windowGameOver;
static void activate(GtkApplication *app,gpointer user_data) {
    //Activates the Program
    mainWindow();

    //Init of windowGameOver
    windowGameOver = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(windowGameOver),"GAME OVER!");
    gtk_window_set_default_size(GTK_WINDOW(windowGameOver),200,85);

    //Init of buttonRestart
    GtkWidget *buttonRestart = gtk_button_new_with_label("Restart🔃");
    gtk_window_set_child(GTK_WINDOW(windowGameOver),buttonRestart);
    gtk_widget_add_css_class(buttonRestart,"ButtonRestart");
    g_signal_connect(buttonRestart,"clicked",G_CALLBACK(restartGame),NULL);

}



//Globalized Variables
GtkWidget *gridMain;
GtkWidget *windowMain;
void mainWindow() {
    //Initalizing CSS
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "styles.css");
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );

    //Init of windowMain
    windowMain = gtk_window_new();
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
    //Sets the value for proximalMines for buttons near mines
}

void restartGame() {
    gtk_widget_set_visible(GTK_WIDGET(windowGameOver),FALSE);
    gtk_window_destroy(GTK_WINDOW(windowMain));
    clearMines();
    mainWindow();
}
void clearMines() {
    for (int i =0 ; i < 9;i++) {
        for (int j = 0 ; j<9;j++) {
            buttons[i][j].isBomb=0;
            buttons[i][j].proximalMines=0;
        }
    }
    for (int i = 0 ; i < 10; i++) {
        buttonMines[i]= 0 ;
    }
}
//Fetches 10 random integers and stores in buttonMines
void fetchRandInt() {
     srand(time(NULL));
    int repeated = 0;
    int cycle=0;
    while (cycle!=10) {
        int a = rand() % 8;
        int b = rand() % 8;
        int num = (a*10)+b;
        for (int i=0;i<10;i++) {
            if (buttonMines[i]==num) {
                repeated++;
            }
        }
        if (repeated==0) {
           buttonMines[cycle]=num;
            cycle++;
        }
    }
}



void setMine() {
    fetchRandInt();
    for (int k=0;k<10;k++) {
        int i = buttonMines[k]/10;
        int j = buttonMines[k] % 10;
        buttons[i][j].isBomb = 1;
    }
    setProximalMines();
}



void setProximalMines() {
    for (int k=0;k<10;k++) {
        int i = buttonMines[k]/10;
        int j = buttonMines[k]%10;

        if (i==0) {
            buttons[i+1][j].proximalMines = buttons[i+1][j].proximalMines+1;
            buttons[i][j+1].proximalMines = buttons[i][j+1].proximalMines+1;
            buttons[i][j-1].proximalMines = buttons[i][j-1].proximalMines+1;
            buttons[i+1][j+1].proximalMines = buttons[i+1][j+1].proximalMines+1;
            buttons[i+1][j-1].proximalMines = buttons[i+1][j-1].proximalMines+1;
        }else if (i==8) {
            buttons[i-1][j].proximalMines = buttons[i-1][j].proximalMines+1;
            buttons[i][j+1].proximalMines = buttons[i][j+1].proximalMines+1;
            buttons[i][j-1].proximalMines = buttons[i][j-1].proximalMines+1;
            buttons[i-1][j-1].proximalMines = buttons[i-1][j-1].proximalMines+1;
            buttons[i-1][j+1].proximalMines = buttons[i-1][j+1].proximalMines+1;
        }else if (j==0) {
            buttons[i+1][j].proximalMines = buttons[i+1][j].proximalMines+1;
            buttons[i-1][j].proximalMines = buttons[i-1][j].proximalMines+1;
            buttons[i][j+1].proximalMines = buttons[i][j+1].proximalMines+1;
            buttons[i+1][j+1].proximalMines = buttons[i+1][j+1].proximalMines+1;
            buttons[i-1][j+1].proximalMines = buttons[i-1][j+1].proximalMines+1;
        }else if (j==8) {
            buttons[i+1][j].proximalMines = buttons[i+1][j].proximalMines+1;
            buttons[i-1][j].proximalMines = buttons[i-1][j].proximalMines+1;
            buttons[i][j-1].proximalMines = buttons[i][j-1].proximalMines+1;
            buttons[i-1][j-1].proximalMines = buttons[i-1][j-1].proximalMines+1;
            buttons[i+1][j-1].proximalMines = buttons[i+1][j-1].proximalMines+1;
        }
        else {
            buttons[i+1][j].proximalMines = buttons[i+1][j].proximalMines+1;
            buttons[i-1][j].proximalMines = buttons[i-1][j].proximalMines+1;
            buttons[i][j+1].proximalMines = buttons[i][j+1].proximalMines+1;
            buttons[i][j-1].proximalMines = buttons[i][j-1].proximalMines+1;
            buttons[i+1][j+1].proximalMines = buttons[i+1][j+1].proximalMines+1;
            buttons[i-1][j-1].proximalMines = buttons[i-1][j-1].proximalMines+1;
            buttons[i+1][j-1].proximalMines = buttons[i+1][j-1].proximalMines+1;
            buttons[i-1][j+1].proximalMines = buttons[i-1][j+1].proximalMines+1;
        }

    }
}

//for the button number count
void declareButtons(){
    for (int i=0;i<9;i++) {
        for (int j = 0;j<9;j++) {

            buttons[i][j].sweeperButtons = gtk_button_new();
            gtk_grid_attach(GTK_GRID(gridMain),buttons[i][j].sweeperButtons,j,i,1,1);
            g_signal_connect(buttons[i][j].sweeperButtons,"clicked",G_CALLBACK(onClickButton),GINT_TO_POINTER((i*10)+j));
            //Sets the minimum size of buttons to be 50x50
            gtk_widget_set_size_request(GTK_WIDGET(buttons[i][j].sweeperButtons),50,50);
        }
    }
}




void onClickButton(GtkButton *button,gpointer user_data){
    system("gst-play-1.0 ./src/sounds/click.mp3 >/dev/null 2>&1 &");
    int buttonNo = GPOINTER_TO_INT(user_data);
    int i = buttonNo / 10;
    int j = buttonNo % 10;
    if (buttons[i][j].isBomb==1) {
        gtk_widget_add_css_class(buttons[i][j].sweeperButtons,"ButtonBomb");
        gameOver();
    }else if(buttons[i][j].proximalMines!=0) {
        switch (buttons[i][j].proximalMines) {
            case 1:
                gtk_widget_add_css_class(buttons[i][j].sweeperButtons,"mineProximal1");
                break;
            case 2:
                gtk_widget_add_css_class(buttons[i][j].sweeperButtons,"mineProximal2");
                break;
            case 3:
                gtk_widget_add_css_class(buttons[i][j].sweeperButtons,"mineProximal3");
                break;
            case 4:
                gtk_widget_add_css_class(buttons[i][j].sweeperButtons,"mineProximal4");
                break;
            case 5:
                gtk_widget_add_css_class(buttons[i][j].sweeperButtons,"mineProximal5");
                break;
            case 6:
                gtk_widget_add_css_class(buttons[i][j].sweeperButtons,"mineProximal6");
                break;
            case 7:
                gtk_widget_add_css_class(buttons[i][j].sweeperButtons,"mineProximal7");
                break;
            case 8:
                gtk_widget_add_css_class(buttons[i][j].sweeperButtons,"mineProximal8");
                break;
            default:
                printf("Nothing found");
        }
    }else {
        gtk_widget_add_css_class(buttons[i][j].sweeperButtons,"ButtonInvisible");
    }

}

void gameOver() {
    system("gst-play-1.0 ./src/sounds/explosion.mp3 >/dev/null 2>&1 &");
    for (int i=0;i<9;i++) {
        for (int j=0;j<9;j++) {
            if (buttons[i][j].isBomb==1) {
                gtk_widget_add_css_class(buttons[i][j].sweeperButtons,"ButtonBomb");
            }else if(buttons[i][j].proximalMines!=0) {
                switch (buttons[i][j].proximalMines) {
                    case 1:
                        gtk_widget_add_css_class(buttons[i][j].sweeperButtons,"mineProximal1");
                        break;
                    case 2:
                        gtk_widget_add_css_class(buttons[i][j].sweeperButtons,"mineProximal2");
                        break;
                    case 3:
                        gtk_widget_add_css_class(buttons[i][j].sweeperButtons,"mineProximal3");
                        break;
                    case 4:
                        gtk_widget_add_css_class(buttons[i][j].sweeperButtons,"mineProximal4");
                        break;
                    case 5:
                        gtk_widget_add_css_class(buttons[i][j].sweeperButtons,"mineProximal5");
                        break;
                    case 6:
                        gtk_widget_add_css_class(buttons[i][j].sweeperButtons,"mineProximal6");
                        break;
                    case 7:
                        gtk_widget_add_css_class(buttons[i][j].sweeperButtons,"mineProximal7");
                        break;
                    case 8:
                        gtk_widget_add_css_class(buttons[i][j].sweeperButtons,"mineProximal8");
                        break;
                    default:
                        printf("Nothing found");
                }
            }else {
                gtk_widget_add_css_class(buttons[i][j].sweeperButtons,"ButtonInvisible");
            }
        }
    }
    gtk_window_present(GTK_WINDOW(windowGameOver));


}



int main(int argc, char **argv){
    GtkApplication *app;
    int status;
    app= gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);
    return status;
}