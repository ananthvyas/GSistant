#include <gio/gio.h>
#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;

unordered_map <string,string> map;
void indexHome(char* path)
{
	map.reserve(7000);
	GFileEnumerator *enumerator;
	GFileInfo       *info;
	GError			*error;
	GFile*			parent=g_file_new_for_path(path);
	enumerator = g_file_enumerate_children (parent, NULL, G_FILE_QUERY_INFO_NONE,  NULL,	&error);

	if (enumerator == NULL);
  /* Handle error */
					
					
	while ((info = g_file_enumerator_next_file (enumerator,
                                            NULL, &error)) != NULL)
  	{
    	/* Do something with the file info */
    	//printf("%s/%s\n",path,g_file_info_get_name(info));
    	char* newpath=(char*) malloc(sizeof(char)*4096);
    	newpath[0]='\0';
    	strcat(newpath,path);
    	strcat(newpath,"/");
    	strcat(newpath,g_file_info_get_name(info));
    	map[string(g_file_info_get_name(info))]=string(newpath);
    	if(g_file_info_get_file_type(info)==G_FILE_TYPE_DIRECTORY)
    	{
    		
    		indexHome(newpath);
    	}	
    	g_object_unref (info);
  	}
	
	g_file_enumerator_close (enumerator, NULL, NULL);
}

string getPath(char* file)
{
	return map[string(file)];
}