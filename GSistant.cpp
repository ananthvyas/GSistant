#include <gtk/gtk.h>
#include <gio/gio.h>
#include "TextInterpretor.h"
#include <iostream>
#include <vector>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>


static void activate(GtkApplication* app, gpointer user_data)
{
	GtkWidget* window;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window),"Desktop Genie");
	gtk_window_set_default_size(GTK_WINDOW(window),200,400);
	gtk_widget_show_all(window);
}
void interpret(char* str)
{
	vector<string> strs;
	string line(str);
	boost::split(strs,line,boost::is_any_of(" "));
	if(strs[0]=="open")
	{
		if(boost::starts_with(strs[1],"http://") || boost::starts_with(strs[1],"www") || boost::ends_with(strs[1],".com"))
			urlopen(strs[1].c_str());
		else
			fileopen((char*)strs[1].c_str());
	}else if(strs[0]=="search")
	{
		string term(strs[1]);
		for(int i=2;i<strs.size();i++)
		{
			term+=string(" ");
			term+=string(strs[i]);
		}
		websearch(term.c_str());
	}
}
static void print_hello(GtkWidget* widget, gpointer user_data)
{
	g_print("Hello World\n");
}
static void aloha(GtkWidget* widget, GtkWidget* entry)
{
	const gchar* entry_text;
	entry_text=gtk_entry_get_text(GTK_ENTRY(entry));
	
	interpret((char*) entry_text);
	//indexHome((char*)"/home/ananth/Downloads");
	//cout<<getPath((char*)"theme-118.xml")<<"\n";
}
static void button_activate(GtkApplication* app, gpointer user_data)
{
	GtkWidget* window;
	GtkWidget* entry;

	window=gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window),"Gsistant");
	gtk_window_set_default_size(GTK_WINDOW(window),200,100);

	//entry_box=gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	//gtk_container_add(GTK_CONTAINER(window),button_box);

	//button=gtk_button_new_with_label("Hello World");
	entry=gtk_entry_new();
	g_signal_connect(entry,"activate",G_CALLBACK(aloha),entry);
	//g_signal_connect(button,"clicked",G_CALLBACK(print_hello),NULL);
	//g_signal_connect_swapped(button,"clicked",G_CALLBACK(gtk_widget_destroy),window);
	gtk_container_add(GTK_CONTAINER(window),entry);

	gtk_widget_show_all(window);
}

int main(int argc, char** argv)
{
	GtkApplication* app;
	int status;
	indexHome((char*)"/home/ananth");
	app=gtk_application_new("com.gmail.ananth1987.test",G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app,"activate",G_CALLBACK(button_activate),NULL);
	status=g_application_run(G_APPLICATION(app),argc,argv);
	g_object_unref(app);

	return status;
}