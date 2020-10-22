#include <webkitgtk-4.0/webkit2/webkit2.h>
#include <simplenav.h>


void home_redirect(GtkButton *botao, gpointer null){
  WebKitDownload *download;
  download = webkit_web_view_download_uri(WEBKIT_WEB_VIEW(webview),HOME);

  g_signal_connect(download,"finished",G_CALLBACK(resposta),NULL);
}

void nova_url(GtkEntry *search_entry, gpointer null){
  WebKitDownload *download;
  gchar *url =(gchar*) gtk_entry_get_text(search_entry);
  if(url){
    char *new_url = malloc(g_ref_string_length(url)+10);
    if(!g_strstr_len(url,g_ref_string_length(url),"https://")){
      sprintf(new_url,"https://%s",url);
    }else{
      sprintf(new_url,"%s",url);
    }
    gtk_entry_set_text(search_entry,new_url);
    download = webkit_web_view_download_uri(WEBKIT_WEB_VIEW(webview),new_url);
  }
  g_signal_connect(download,"finished",G_CALLBACK(resposta),NULL);
}

void resposta(WebKitDownload *download){
  WebKitURIRequest *req = webkit_download_get_request(download);
  webkit_web_view_load_request(WEBKIT_WEB_VIEW(webview),req);
}

int main(){
  gtk_init(NULL,NULL);
  webview = webkit_web_view_new();
  GtkWidget *url_entry = gtk_search_entry_new();
  GtkWidget *opcoes_box = gtk_box_new(0,0);
  GtkWidget *home_button = gtk_button_new();
  GtkWidget *view_box = gtk_box_new(1,0);
  GdkDisplay *display = gdk_display_get_default ();
  GdkMonitor *monitor = gdk_display_get_monitor(display,0);
  int x = gdk_monitor_get_width_mm(monitor)*3.779;
  int y = gdk_monitor_get_height_mm(monitor)*3.779;
  gtk_widget_set_size_request(webview,x,y);
  GtkWidget *box = gtk_box_new(1,0);
  GtkWidget *wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  WebKitDownload *download = webkit_web_view_download_uri(WEBKIT_WEB_VIEW(webview),HOME);

  gtk_button_set_image(GTK_BUTTON(home_button),gtk_image_new_from_icon_name("go-home",GTK_ICON_SIZE_SMALL_TOOLBAR));
  gtk_entry_set_width_chars(GTK_ENTRY(url_entry),100);

  gtk_box_pack_start(GTK_BOX(opcoes_box),home_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(opcoes_box),url_entry,0,0,5);

  gtk_box_pack_start(GTK_BOX(view_box),webview,0,0,5);
  gtk_box_pack_start(GTK_BOX(box),opcoes_box,0,0,5);
  gtk_box_pack_start(GTK_BOX(box),view_box,0,0,5);

  gtk_container_add(GTK_CONTAINER(wnd),box);
  gtk_window_maximize(GTK_WINDOW(wnd));
  gtk_widget_show_all(wnd);

  g_signal_connect(wnd,"destroy",G_CALLBACK(gtk_main_quit),NULL);
  g_signal_connect(download,"finished",G_CALLBACK(resposta),NULL);
  g_signal_connect(home_button,"clicked",G_CALLBACK(home_redirect),NULL);
  g_signal_connect(url_entry,"activate",G_CALLBACK(nova_url),NULL);

  gtk_main();
}
