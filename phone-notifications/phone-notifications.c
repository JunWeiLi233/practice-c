#include <stdio.h>
#include <curl/curl.h>

int main()
{
    CURL * curl;
    printf("Hello World!\n");

    CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
    if (result != CURLE_OK){
        return (int) result;
    }

    curl = curl_easy_init();

    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, "ntfy.sh/task-notification");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "dsjdkasdasdasdasdsaa");
        result = curl_easy_perform(curl);
    }
}