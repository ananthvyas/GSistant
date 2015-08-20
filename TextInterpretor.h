#include <gio/gio.h>
#include <string.h>
#include <stdlib.h>


void launchapp(const char* path)
{
	gboolean ret;
	GError* error=NULL;
	ret=g_app_info_launch_default_for_uri(path,NULL,&error);
	if(ret)
	{
		g_print("Worked !");
	}else
	{
		g_print("Problem :( --> %s",error->message);
	}
}

void fileopen(char* file)
{
	char* str = (char*) malloc(4096*sizeof(char));
	str[0]='\0';
	strcat(str,"file://");
	strcat(str,file);
	launchapp(str);
	free(str);
}

void urlopen(char* url)
{
	char* str = (char*) malloc(4096*sizeof(char));
	str[0]='\0';
	strcat(str,"http://");
	strcat(str,url);
	launchapp(str);
	free(str);
}

void websearch(const char* text)
{
	char* str = (char*) malloc(4096*sizeof(char));
	str[0]='\0';
	strcat(str,
		"http://www.google.com/search?sourceid=navclient&gfns=1&q=");
	strcat(str,text);
	launchapp(str);
	free(str);
}
