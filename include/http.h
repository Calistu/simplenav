#include <webkitgtk-4.0/webkit2/webkit2.h>

extern GtkWidget *webview;

extern GtkWidget *url_entry;

void resposta(WebKitDownload *download);

void nova_url(GtkEntry *search_entry, gpointer null);
