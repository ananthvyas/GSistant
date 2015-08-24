#include <gio/gio.h>
#include <string.h>
#include <stdlib.h>
#include <webkit2/webkit2.h>
#include "WebLibs.h"
#include "FileIndexer.h"
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>

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
	if(boost::starts_with(str,"/"))
		strcat(str,file);
	else
		strcat(str,getPath(file).c_str());
	launchapp(str);
	free(str);
}

void urlopen(const char* url)
{
	char* str = (char*) malloc(4096*sizeof(char));
	str[0]='\0';
	if(!boost::starts_with(str,"http:"))
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
	openurl(str);
	free(str);
}
