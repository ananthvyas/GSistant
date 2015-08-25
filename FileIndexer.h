#include <gio/gio.h>
#include <unordered_map>
#include <string>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <boost/regex.hpp>

using namespace std;

std::unordered_map <std::string, vector<std::string>> cmap;
bool isValidFile(GFileInfo* file);
void indexHome(char* path)
{
    cmap.reserve(7000);
    GFileEnumerator *enumerator;
    GFileInfo       *info;
    GError          *error;
    GFile*          parent = g_file_new_for_path(path);
    enumerator = g_file_enumerate_children (parent, NULL, G_FILE_QUERY_INFO_NONE,  NULL,    &error);

    if (enumerator == NULL) return;
    /* Handle error */


    while ((info = g_file_enumerator_next_file (enumerator,
                   NULL, &error)) != NULL)
    {
        /* Do something with the file info */
        const char* filename=(g_file_info_get_name(info));
        if (filename == NULL) continue;
        //printf("%s/%s\n",path,g_file_info_get_name(info));
        char* newpath = (char*) malloc(sizeof(char) * 4096);
        newpath[0] = '\0';
        strcat(newpath, path);
        strcat(newpath, "/");
        strcat(newpath, filename);
        if (isValidFile(info))
        {
            boost::regex re(",|:|-|_|\\.|\\s+");        // Create the reg exp
            std::string s=string(filename);
            boost::sregex_token_iterator         // Create an iterator using a
                p(s.begin(), s.end(), re, -1);  // sequence and that reg exp
            boost::sregex_token_iterator end;    // Create an end-of-reg-exp
            // marker
            while (p != end)
            {
                if (cmap.find(string(*p)) == cmap.end()) {
                    vector<string> vs;
                    cmap[string(*p)] = vs;
                }
                vector<string> ss = cmap[string(*p)];
                ss.push_back(string(newpath));
                cmap[string(*p++)]=ss;
            }
            if(cmap.find(string(filename))==cmap.end()){
                vector<string> vs;
                cmap[string(filename)]=vs;
            }
            vector<string> ss = cmap[string(filename)];
            ss.push_back(string(newpath));
            cmap[string(filename)]=ss;
            if (g_file_info_get_file_type(info) == G_FILE_TYPE_DIRECTORY)
            {
                indexHome(newpath);
            }
        }
        g_object_unref (info);
    }
    g_file_enumerator_close (enumerator, NULL, NULL);
}

bool isValidFile(GFileInfo* file)
{
    const char* name = g_file_info_get_name(file);
    gboolean is_certain = FALSE;

    char *content_type = g_content_type_guess (name, NULL, 0, &is_certain);


    if (boost::starts_with(name, ".") ||
            (g_file_info_get_file_type(file) != G_FILE_TYPE_DIRECTORY &&
             g_file_info_get_file_type(file) != G_FILE_TYPE_REGULAR)) return false;
    if (content_type == NULL) return false;
    if (g_file_info_get_file_type(file) == G_FILE_TYPE_DIRECTORY) return true;
    if (!boost::starts_with(content_type, "video") && !boost::starts_with(content_type, "audio")
            && !boost::ends_with(content_type, "pdf") && content_type != "text/html") return false;
    return true;
}

string getPath(char* file)
{
    if(cmap.find(string(file))==cmap.end()) return "";
    return cmap[string(file)][0];
}