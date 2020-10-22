#include <webkitgtk-4.0/webkit2/webkit2.h>

#define HOME "http://www.google.com"

extern GtkWidget *webview;

void home_redirect(GtkButton *botao, gpointer null);

extern void resposta(WebKitDownload *download);
