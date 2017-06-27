/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
/* <DESC>
 * HTTP PUT with easy interface and read callback
 * </DESC>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <curl/curl.h>

/*
 * This example shows a HTTP PUT operation. PUTs a file given as a command
 * line argument to the URL also given on the command line.
 *
 * This example also uses its own read callback.
 *
 * Here's an article on how to setup a PUT handler for Apache:
 * http://www.apacheweek.com/features/put
 */
struct MemoryStruct {
  char *memory;
  size_t size;
};

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
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

int main(int argc, char **argv)
{
  CURL *curl;
  CURLcode res;

  char *file;
  char *url = "http://localhost:8088/switchcommand?nodeId=0&requestType=SIGNAL_TIMING_PLAN&signalTimingPlanId=1";
  /* In windows, this will init the winsock stuff */
  curl_global_init(CURL_GLOBAL_ALL);

  /* get a curl handle */
  curl = curl_easy_init();
  if(curl) 
  {
    struct curl_slist *headers = NULL;
    struct MemoryStruct chunk;
 
    chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */ 
    chunk.size = 0;    /* no data at this point */ 
 
    /* Remove a header curl would otherwise add by itself */ 
    // headers = curl_slist_append(headers, "Accept: text/xml");

    /* Add a header with "blank" contents to the right of the colon. Note that
       we're then using a semicolon in the string we pass to curl! */

    headers = curl_slist_append(headers, "Content-Type: text/plain");

    /* set our custom set of headers */ 
    res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    /* we want to use our own read function */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    
    /* HTTP PUT please */
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
    // curl_easy_setopt(curl, CURLOPT_POSTFIELDS, 
    //   "nodeId=0&requestType=SIGNAL_TIMING_PLAN&signalTimingPlanId=2");

    /* specify target URL, and note that this URL should include a file
       name, not only a directory */
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    /* Now run off and do what you've been told! */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
    {
      fprintf(stderr, "curl_easy_perform() failed: %s\n", 
        curl_easy_strerror(res));
    }
    else
    {
      printf("%lu bytes retrieved\n%s", (long)chunk.size, chunk.memory);
    }

    /* always cleanup */
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, NULL);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    free(chunk.memory);
  }

  curl_global_cleanup();
  return 0;
}
