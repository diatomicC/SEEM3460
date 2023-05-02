#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gui.h"

int add_new_card(int container_id, int step);
char *get_prompt();
void new_game();
void card_shuffle();
void end_game();
void higher_lower(int is_higher);
void close_cheat(GtkWindow *window);

static int status[3]; // step, North's score, South's score
static int card_deck[52];
const int rounds = 19;
char prompt[100];
char debug[100]; // to print to console

// container_id = 0 for North, 1 for South
int add_new_card(int container_id, int step) {
  int card = card_deck[step];
  add_image(container_id, card);
  return card;
}

char *get_prompt() {
  char north[] = "North";
  char south[] = "South";
  sprintf(prompt, "%s's turn\nNorth's score : %d\n South's score: %d",
          (status[0] % 2 == 0 ? north : south), status[1], status[2]);
  return prompt;
}

void new_game() {
  // starts a new game,
  // all initialization useful for resetting should be done here
  // Start from scratch or
  // finished one game and start another one.

  int i;
  for (i = 0; i < 3; i++) {
    status[i] = 0; // reset status to zero
  }
  clear_container(0); // reset North
  clear_container(1); // reset South

  char *new_prompt = get_prompt();
  set_prompt(new_prompt); // clear existing and set a blank new prompt

  card_shuffle(); // shuffle the card deck

  // 2. initialize two cards to be pre-shown at the start of the game
  add_new_card(0, 0); // Add card to North player
  add_new_card(1, 1); // Add card to South player
  status[0] =
      2; // After two initial cards given, increment initial steps by two

  show_ingame_buttons(); // show higher, lower, pass, etc. buttons

  sprintf(debug, "New game initialized.\n");
  g_print(debug); // debug to console
}

void card_shuffle() {
  // this method prepares all cards in card_deck
  // this is the ONLY function that should apply RANDOMNESS
  int i, irandom, temp;
  for (i = 0; i < 52; i++) {
    card_deck[i] = i;
    irandom = rand() % (i + 1);
    if (irandom != i) {
      temp = card_deck[i];
      card_deck[i] = card_deck[irandom];
      card_deck[irandom] = temp;
    }
  }
}

void end_game() {
  // 1. Hide the higher and lower button
  hide_ingame_buttons();

  // 2. show match results in buffer_prompt. If North wins, Please show
  // "North wins.\nNorth's score : %d, South's score: %d"
  int score = status[1] -
              status[2]; // positive if North has higher score or tie with South

  char *results = malloc(60);

  switch (score) {
  case 0:
    sprintf(results, "Draw.\nNorth's score : %d, South's score: %d", status[1],
            status[2]);
    break;
  case 1:
    sprintf(results, "North wins.\nNorth's score : %d, South's score: %d",
            status[1], status[2]);
    break;
  default:
    sprintf(results, "South wins.\nNorth's score : %d, South's score: %d",
            status[1], status[2]);
    break;
  }

  set_prompt(results); // update prompt with message in `results` array

  if (score == 0) {
    g_print("Game ended with a tie!\n"); // debug to console
  } else if (score > 0) {
    g_print("Game ended. North wins.\n"); // debug to console
  } else {
    g_print("Game ended. South wins.\n"); // debug to console
  }
}

void higher_lower(int is_higher) {
  int step = status[0];
  int current_container = step % 2;
  int card = add_new_card(current_container, step);

  // If current player predict correct card, he get 10 points. Otherwise,
  // he loss 5 points.
  int last_card = card_deck[step - 1];
  int card_diff =
      card - last_card; // negative only if current card is lower than last card
  int player = step % 2; // 0 for North, 1 for South

  char *player_name = (player == 0 ? "North" : "South");

  if (is_higher ? card_diff > 0 : card_diff < 0) {
    status[player + 1] += 10;
    g_print("%s chose \"%s\" and gained 10 points.\n", player_name,
            is_higher ? "Higher" : "Lower");
  } else {
    status[player + 1] -= 5;
    g_print("%s chose \"%s\" and lost 5 points.\n", player_name,
            is_higher ? "Higher" : "Lower");
  }

  if (status[0] == rounds) {
    end_game();
    return;
  } else {
    status[0]++;
    char *prompt = get_prompt();
    set_prompt(prompt);
  }
}
void on_click_higher() { higher_lower(1); }

void on_click_lower() { higher_lower(0); }

void on_click_pass() { higher_lower(-1); }

void on_click_hint(GtkWidget *widget, gpointer window) {
  char north[] = "North";
  char south[] = "South";
  sprintf(debug, "%s peeked a hint.\n", (status[0] % 2 == 0 ? north : south));
  g_print(debug); // debug to console

  GtkDialogFlags flags =
      GTK_DIALOG_MODAL |
      GTK_DIALOG_DESTROY_WITH_PARENT; // modal to force user attention
  GtkWidget *dialog;
  char *buffer = malloc(200);

  int step = status[0];
  int last_card = card_deck[step - 1];
  int remaining = 52 - step;
  int higher = 0;
  int lower = 0;

  int i;
  // compare all remaining cards with the last card
  for (i = step; i < 52; i++) {
    if (card_deck[i] > last_card)
      higher++;
    if (card_deck[i] < last_card)
      lower++;
  }

  sprintf(buffer,
          "Remaining cards: %d\n"
          "No. of cards higher than %s\'s last card: %d\n"
          "No. of cards lower than %s\'s last card: %d",
          remaining, ((step - 1) % 2 == 0 ? north : south), higher,
          ((step - 1) % 2 == 0 ? north : south), lower);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), flags, GTK_MESSAGE_INFO,
                                  GTK_BUTTONS_OK, buffer);
  gtk_window_set_title(GTK_WINDOW(dialog), "Information");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog); // destroy when closed
}

void on_click_cheat() {
  char north[] = "North";
  char south[] = "South";
  sprintf(debug, "%s gave up and cheated.\n",
          (status[0] % 2 == 0 ? north : south));
  g_print(debug);

  GtkWidget *cheat, *image, *label, *vbox, *close;

  cheat = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(cheat), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(cheat), 230, 150);
  gtk_window_set_decorated(GTK_WINDOW(cheat), FALSE);
  gtk_window_set_modal(GTK_WINDOW(cheat), TRUE);
  gtk_window_set_resizable(GTK_WINDOW(cheat), FALSE);
  gtk_container_set_border_width(GTK_CONTAINER(cheat), 0);

  char *cheat_description = malloc(30);
  sprintf(cheat_description, "The next card will be:\n");
  label = gtk_label_new(cheat_description); // label component

  int next_card =
      card_deck[status[0]]; // the current step is "to be revealed" card
  char *imagepath = get_image_path(next_card); // use function declared in gui.h
  image = gtk_image_new_from_file(imagepath);

  close = gtk_button_new_with_label("Close");
  g_signal_connect_swapped(close, "clicked", G_CALLBACK(close_cheat), cheat);

  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE,
                     0); // add label to collection vbox
  gtk_box_pack_start(GTK_BOX(vbox), image, FALSE, FALSE,
                     1); // add cheat card to collection vbox
  gtk_box_pack_start(GTK_BOX(vbox), close, FALSE, FALSE,
                     1); // add close button to collection vbox
  gtk_container_add(GTK_CONTAINER(cheat),
                    vbox); // show the collection container

  gtk_widget_show_all(cheat);
}

void close_cheat(GtkWindow *window) {
  gtk_widget_destroy(GTK_WIDGET(window));
} // close cheat window



