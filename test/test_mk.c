
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <curl/curl.h>

#include <string.h>

#include <sys/time.h>
#include <time.h>

int get_current_utc_second()
{
  struct timeval tv;
  time_t raw_time;

  gettimeofday(&tv, NULL);
  
  raw_time = tv.tv_sec;

  return raw_time;
}

struct MemoryStruct {
  char *memory;
  size_t size;
};

static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t retcode;
  curl_off_t nread;
 
  /* in real-world cases, this would probably get this data differently
     as this fread() stuff is exactly what the library already would do
     by default internally */ 
  // retcode = fread(ptr, size, nmemb, stream);
 
  // nread = (curl_off_t)retcode;
  printf("read_callback: \n");
 
  // fprintf(stderr, "*** We read %" CURL_FORMAT_CURL_OFF_T
  //         " bytes from file\n", nread);
 
  return retcode;
}

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  // fprintf(stderr, "write_callback\n");
 
  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}

int call_curl(int request_type, char* url_str)
{
  /* CURL */
  CURL *curl;
  CURLcode res; 
  /* In windows, this will init the winsock stuff */
  if (request_type > 2)
  {
    fprintf(stderr, "Invalid request_type: %d\n", request_type);
    return 0;
  }

  curl_global_init(CURL_GLOBAL_ALL);

  /* get a curl handle */
  curl = curl_easy_init();
  if(curl) 
  {
    struct MemoryStruct chunk;
    struct curl_slist *headers = NULL;
 
    chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */ 
    chunk.size = 0;    /* no data at this point */

    headers = curl_slist_append(headers, "Content-Type: text/plain");

    /* set our custom set of headers */ 
    res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_URL, url_str);

    switch(request_type) 
    {
      case 0:
        // printf("GET\n");
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
      break;
      case 1:
        // printf("PUT\n");
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT"); /* PUT request */
      break;
      case 2:
        // printf("HEAD\n");
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L); /* HEAD request */
      break;
      default:
        
      break;
    }
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    /* we want to use our own write function */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
    {
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    else
    {
      fprintf(stderr, "%lu bytes retrieved\n", (long)chunk.size);
    }
    /* always cleanup */
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    free(chunk.memory);
  }
  else 
  {
    fprintf(stderr, "curl_easy_init() failed\n");
  }
  curl_global_cleanup();
  return (res == CURLE_OK);
}

int print_usage(void)
{
  fprintf(stderr, "Usage:\n"
    "\ttest_mk.exe\n"
    "\tOR\n"
    "\ttest_mk.exe <test_file>\n"
    "\tOR\n"
    "\ttest_mk.exe <start_pos> <start_time>\n"
    "\tOR\n"
    "\ttest_mk <test_file> <start_pos> <start_time>\n");
}

int main(int argc, char* args[])
{
  /* libevent http */
  
  /* Working with input file */
  FILE* url_file;
  char file_name[100];
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  int res = 0;
  int start_pos = 0;
  int start_time = get_current_utc_second() - 1800;

  print_usage();

  if (argc < 2) 
  {
    strcpy(file_name, "default.test");
  }
  else if (argc == 2)
  {
    strcpy(file_name, args[1]);
  }

  url_file = fopen(file_name, "r");

  if (NULL == url_file) //failed to open file: return
  {
    fprintf(stderr, "Failed to open file\n");
    return -1;
  }

  /* Read URL format from file, perform GET/PUT request */
  // while ((read = getline(&line, &len, url_file)) != -1)
  while (!feof(url_file))
  {
    /**
     * request_type: 0 = GET; 1 = PUT; 2 = HEAD;
     */
    int request_type = 0;
    char url_format_str[120];
    char url_type[4];
    char url_str[120];
    
    // printf("Retrieved line of length %zu:\n", read);
    // line[read-1] = '\0';
    // printf("(%zu): %s", read, line);
    fscanf(url_file, "%s", url_type);
    fscanf(url_file, "%s", url_format_str);

    //printf("_%s: %s_\n", url_type, url_format_str);
    

    /* Split <code>line</code> for method and URL */
    /* HTTP GET/PUT/HEAD based on option */
    if (strncmp(url_type, "GET", 3)==0)
    {
      request_type = 0;
    }
    else if (strncmp(url_type, "PUT", 3)==0)
    {
      request_type = 1;
    }
    else if (strncmp(url_type, "HEAD", 4)==0)
    {
      request_type = 2;
    }
    else 
    {
      request_type = 3;
    }

    if (0 == request_type) 
    {
      sprintf(url_str, url_format_str, start_pos, start_time);
    }
    else if (1 == request_type || 2 == request_type)
    {
      sprintf(url_str, url_format_str);
    }
    
    if (3 != request_type)
    {
      fprintf(stderr, "URL: %s\n", url_str);
      res = call_curl(request_type, url_str);
      fprintf(stderr, "Return: %d\n", res);
    }
  }
  
  /* always cleanup */
  res = fclose(url_file);
  return 0;
}