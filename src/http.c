#include <http.h>

void resposta(WebKitDownload *download){
  WebKitURIRequest *req = webkit_download_get_request(download);
  webkit_web_view_load_request(WEBKIT_WEB_VIEW(webview),req);
}

void voltar_web(GtkButton *button, gpointer null){
  WebKitBackForwardList *list_item = webkit_web_view_get_back_forward_list(WEBKIT_WEB_VIEW(webview));
  WebKitBackForwardListItem *item = webkit_back_forward_list_get_back_item(list_item);
  webkit_web_view_go_to_back_forward_list_item(WEBKIT_WEB_VIEW(webview),item);
  gtk_entry_set_text(GTK_ENTRY(url_entry),webkit_back_forward_list_item_get_uri(item));
}

void frente_web(GtkButton *button, gpointer null){
  WebKitBackForwardList *list_item = webkit_web_view_get_back_forward_list(WEBKIT_WEB_VIEW(webview));
  WebKitBackForwardListItem *item = webkit_back_forward_list_get_forward_item(list_item);
  webkit_web_view_go_to_back_forward_list_item(WEBKIT_WEB_VIEW(webview),item);
  gtk_entry_set_text(GTK_ENTRY(url_entry),webkit_back_forward_list_item_get_uri(item));
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
