#include <init.h>

int nav_init(){
  gtk_init(NULL,NULL);
  webview = webkit_web_view_new();
  url_entry = gtk_search_entry_new();
  GtkWidget *opcoes_box = gtk_box_new(0,0);
  GtkWidget *home_button = gtk_button_new();
  GtkWidget *voltar_button = gtk_button_new();
  GtkWidget *frente_button = gtk_button_new();
  GtkWidget *view_box = gtk_box_new(1,0);
  GdkDisplay *display = gdk_display_get_default ();
  GdkMonitor *monitor = gdk_display_get_monitor(display,0);
  GtkWidget *box = gtk_box_new(1,0);
  GtkWidget *wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  WebKitDownload *download = webkit_web_view_download_uri(WEBKIT_WEB_VIEW(webview),HOME);

  int x = gdk_monitor_get_width_mm(monitor)*3;
  int y = gdk_monitor_get_height_mm(monitor)*3;
  gtk_widget_set_size_request(webview,x,y);

  gtk_button_set_image(GTK_BUTTON(home_button),gtk_image_new_from_icon_name("go-home",GTK_ICON_SIZE_SMALL_TOOLBAR));
  gtk_button_set_image(GTK_BUTTON(voltar_button),gtk_image_new_from_icon_name("go-previous",GTK_ICON_SIZE_SMALL_TOOLBAR));
  gtk_button_set_image(GTK_BUTTON(frente_button),gtk_image_new_from_icon_name("go-next",GTK_ICON_SIZE_SMALL_TOOLBAR));

  gtk_entry_set_width_chars(GTK_ENTRY(url_entry),100);

  gtk_box_pack_start(GTK_BOX(opcoes_box),voltar_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(opcoes_box),frente_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(opcoes_box),home_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(opcoes_box),url_entry,0,0,5);
  gtk_window_set_icon_name(GTK_WINDOW(wnd),"emblem-web");

  gtk_box_pack_start(GTK_BOX(view_box),webview,0,0,5);
  gtk_box_pack_start(GTK_BOX(box),opcoes_box,0,0,5);
  gtk_box_pack_start(GTK_BOX(box),view_box,0,0,5);

  gtk_container_add(GTK_CONTAINER(wnd),box);
  gtk_window_maximize(GTK_WINDOW(wnd));
  gtk_widget_show_all(wnd);

  g_signal_connect(wnd,"destroy",G_CALLBACK(gtk_main_quit),NULL);
  g_signal_connect(download,"finished",G_CALLBACK(resposta),NULL);

  g_signal_connect(frente_button,"clicked",G_CALLBACK(frente_web),NULL);
  g_signal_connect(voltar_button,"clicked",G_CALLBACK(voltar_web),NULL);

  g_signal_connect(home_button,"clicked",G_CALLBACK(home_redirect),NULL);
  g_signal_connect(url_entry,"activate",G_CALLBACK(nova_url),NULL);

  gtk_main();
}
