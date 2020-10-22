#include <home.h>

void home_redirect(GtkButton *botao, gpointer null){
  WebKitDownload *download;
  download = webkit_web_view_download_uri(WEBKIT_WEB_VIEW(webview),HOME);

  g_signal_connect(download,"finished",G_CALLBACK(resposta),NULL);
}
