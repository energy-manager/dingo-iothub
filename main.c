// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// CAVEAT: This sample is to demonstrate azure IoT client concepts only and is not a guide design principles or style
// Checking of return codes and error values shall be omitted for brevity.  Please practice sound engineering practices
// when writing production code.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cJSON.h"
#include "iothub.h"
#include "iothub_device_client_ll.h"
#include "iothub_client_options.h"
#include "iothub_message.h"
#include "azure_c_shared_utility/threadapi.h"
#include "azure_c_shared_utility/shared_util_options.h"

// The protocol you wish to use should be uncommented
//
#define SAMPLE_MQTT
//#define SAMPLE_MQTT_OVER_WEBSOCKETS
//#define SAMPLE_AMQP
//#define SAMPLE_AMQP_OVER_WEBSOCKETS
//#define SAMPLE_HTTP

#ifdef SAMPLE_MQTT
#include "iothubtransportmqtt.h"
#endif // SAMPLE_MQTT
#ifdef SAMPLE_MQTT_OVER_WEBSOCKETS
#include "iothubtransportmqtt_websockets.h"
#endif // SAMPLE_MQTT_OVER_WEBSOCKETS
#ifdef SAMPLE_AMQP
#include "iothubtransportamqp.h"
#endif // SAMPLE_AMQP
#ifdef SAMPLE_AMQP_OVER_WEBSOCKETS
#include "iothubtransportamqp_websockets.h"
#endif // SAMPLE_AMQP_OVER_WEBSOCKETS
#ifdef SAMPLE_HTTP
#include "iothubtransporthttp.h"
#endif // SAMPLE_HTTP

#ifdef SET_TRUSTED_CERT_IN_SAMPLES
#include "certs.h"
#endif // SET_TRUSTED_CERT_IN_SAMPLES

/* Paste in the your iothub connection string  */

static bool g_continueRunning = true;
static size_t g_message_recv_count = 0;
static int closeAfter = 3600; //3600
static time_t seconds;
static time_t startSeconds;

#include <curl/curl.h>

struct memory
{
    char *memory;
    size_t size;
};

static size_t
writecallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct memory *mem = (struct memory *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL)
    {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

void sendReq()
{

    CURL *curl;
    CURLcode res;
    struct memory chunk;

    chunk.memory = NULL; /* will be grown as needed by the realloc above */
    chunk.size = 0;      /* no data at this point */
                         // struct curl_slist* headers = NULL;
    curl_global_init(CURL_GLOBAL_ALL);

    /* init the curl session */
    curl = curl_easy_init();

    /* specify URL to get */
    curl_easy_setopt(curl, CURLOPT_URL, "URL_TO_GET");

    // headers = curl_slist_append(headers, "Content-Type: application/json");
    // headers = curl_slist_append(headers, "Authorization: Bearer <my_token>");

    //  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    /* send all data to this function  */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writecallback);

    /* we pass our 'chunk' struct to the callback function */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);

    /* get it! */
    res = curl_easy_perform(curl);

    /* check for errors */
    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }
    else
    {
        /*
     * Now, our chunk.memory points to a memory block that is chunk.size
     * bytes big and contains the remote file.
     *
     * Do something nice with it!
     */

        printf("%s bytes retrieved\n", chunk.memory);
    }

    /* cleanup curl stuff */
    curl_easy_cleanup(curl);

    free(chunk.memory);

    /* we're done with libcurl, so clean it up */
    curl_global_cleanup();
}

void sendCommand(char *commandToSend)
{
    system(commandToSend);
}

static IOTHUBMESSAGE_DISPOSITION_RESULT receive_msg_callback(IOTHUB_MESSAGE_HANDLE message, void *user_context)
{
    (void)user_context;
    const char *messageId;
    const char *correlationId;

    // Message properties
    if ((messageId = IoTHubMessage_GetMessageId(message)) == NULL)
    {
        messageId = "<unavailable>";
    }

    if ((correlationId = IoTHubMessage_GetCorrelationId(message)) == NULL)
    {
        correlationId = "<unavailable>";
    }

    IOTHUBMESSAGE_CONTENT_TYPE content_type = IoTHubMessage_GetContentType(message);
    if (content_type == IOTHUBMESSAGE_BYTEARRAY)
    {
        const unsigned char *buff_msg;
        size_t buff_len;

        if (IoTHubMessage_GetByteArray(message, &buff_msg, &buff_len) != IOTHUB_MESSAGE_OK)
        {
            (void)printf("Failure retrieving byte array message\r\n");
        }
        else
        {
            const cJSON *resolution = NULL;

            cJSON *json = cJSON_Parse(buff_msg);
            //char *string = cJSON_Print(json);
            //(void)printf(string);
            cJSON_ArrayForEach(resolution, json)
            {
                cJSON *type = cJSON_GetObjectItemCaseSensitive(resolution, "Type");
                cJSON *data = cJSON_GetObjectItemCaseSensitive(resolution, "Data");

                if (cJSON_IsString(type) && (type->valuestring != NULL))
                {
                    if (strcmp(type->valuestring, "OPENPORT") == 0)
                    {
                        cJSON *status = cJSON_GetObjectItemCaseSensitive(data, "status");
                        if (cJSON_IsNumber(status))
                        {
                            if (status->valueint == 1)
                            {
                                time(&startSeconds);
                                (void)printf("Starting openport\r\n");
                                sendCommand("openport 22 -d");
                                sendCommand("openport 80 -d");
                            }
                            else
                            {
                                startSeconds = 0;
                                (void)printf("Stoping openport\r\n");
                                sendCommand("openport -K");
                            }
                        }
                    }
                    else if (strcmp(type->valuestring, "BACNET") == 0)
                    {
                        (void)printf("You tryed to call BACet command but it is not supported yet!\r\n");
                        //do some code
                    }
                }
            }
            cJSON_Delete(json);
            //(void)printf("Received Binary message\r\nMessage ID: %s\r\n Correlation ID: %s\r\n Data: <<<%.*s>>> & Size=%d\r\n", messageId, correlationId, (int)buff_len, buff_msg, (int)buff_len);
        }
    }
    else
    {
        const char *string_msg = IoTHubMessage_GetString(message);
        if (string_msg == NULL)
        {
            (void)printf("Failure retrieving byte array message\r\n");
        }
        else
        {
            (void)printf("Received String Message\r\nMessage ID: %s\r\n Correlation ID: %s\r\n Data: <<<%s>>>\r\n", messageId, correlationId, string_msg);
        }
    }
    const char *property_value = "property_value";
    const char *property_key = IoTHubMessage_GetProperty(message, property_value);
    if (property_key != NULL)
    {
        printf("\r\nMessage Properties:\r\n");
        printf("\tKey: %s Value: %s\r\n", property_value, property_key);
    }
    g_message_recv_count++;

    return IOTHUBMESSAGE_ACCEPTED;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        (void)printf("Please provide the device connection string as the command input.\r\n");
        return 1;
    }

    IOTHUB_CLIENT_TRANSPORT_PROVIDER protocol;
    size_t messages_count = 0;
    const char *connectionString = argv[1];
    // const char *connectionString = argv[1];
    // Select the Protocol to use with the connection
#ifdef SAMPLE_MQTT
    protocol = MQTT_Protocol;
#endif // SAMPLE_MQTT
#ifdef SAMPLE_MQTT_OVER_WEBSOCKETS
    protocol = MQTT_WebSocket_Protocol;
#endif // SAMPLE_MQTT_OVER_WEBSOCKETS
#ifdef SAMPLE_AMQP
    protocol = AMQP_Protocol;
#endif // SAMPLE_AMQP
#ifdef SAMPLE_AMQP_OVER_WEBSOCKETS
    protocol = AMQP_Protocol_over_WebSocketsTls;
#endif // SAMPLE_AMQP_OVER_WEBSOCKETS
#ifdef SAMPLE_HTTP
    protocol = HTTP_Protocol;
#endif // SAMPLE_HTTP

    //sendReq();
    // Used to initialize IoTHub SDK subsystem
    (void)IoTHub_Init();

    IOTHUB_DEVICE_CLIENT_LL_HANDLE device_ll_handle;

    (void)printf("Creating IoTHub Device handle\r\n");

    // Create the iothub handle here
    device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(connectionString, protocol);
    if (device_ll_handle == NULL)
    {
        (void)printf("Failure createing Iothub device.  Hint: Check you connection string.\r\n");
    }
    else
    {
        // Set any option that are neccessary.
        // For available options please see the iothub_sdk_options.md documentation
        //bool traceOn = true;
        //IoTHubDeviceClient_LL_SetOption(device_ll_handle, OPTION_LOG_TRACE, &traceOn);
#ifdef SET_TRUSTED_CERT_IN_SAMPLES
        // Setting the Trusted Certificate.  This is only necessary on system with without
        // built in certificate stores.
        IoTHubDeviceClient_LL_SetOption(device_ll_handle, OPTION_TRUSTED_CERT, certificates);
#endif // SET_TRUSTED_CERT_IN_SAMPLES

#if defined SAMPLE_MQTT || defined SAMPLE_MQTT_WS
        //Setting the auto URL Decoder (recommended for MQTT). Please use this option unless
        //you are URL Decoding responses yourself.
        //ONLY valid for use with MQTT
        //  int keepalive = 300;

        // IoTHubDeviceClient_LL_SetOption(device_ll_handle, OPTION_KEEP_ALIVE, &keepalive);
        //IoTHubDeviceClient_LL_SetOption(device_ll_handle, OPTION_AUTO_URL_ENCODE_DECODE, &urlDecodeOn);
#endif

#ifdef SAMPLE_HTTP
        unsigned int timeout = 241000;
        // Because it can poll "after 9 seconds" polls will happen effectively // at ~10 seconds.
        // Note that for scalabilty, the default value of minimumPollingTime
        // is 25 minutes. For more information, see:
        // https://azure.microsoft.com/documentation/articles/iot-hub-devguide/#messaging
        unsigned int minimumPollingTime = 9;
        IoTHubDeviceClient_LL_SetOption(device_ll_handle, OPTION_MIN_POLLING_TIME, &minimumPollingTime);
        IoTHubDeviceClient_LL_SetOption(device_ll_handle, OPTION_HTTP_TIMEOUT, &timeout);
#endif // SAMPLE_HTTP

        if (IoTHubDeviceClient_LL_SetMessageCallback(device_ll_handle, receive_msg_callback, &messages_count) != IOTHUB_CLIENT_OK)
        {
            (void)printf("ERROR: IoTHubClient_LL_SetMessageCallback..........FAILED!\r\n");
        }
        else
        {
            (void)printf("Waiting for message to be sent to device\r\n");
            do
            {
                if (startSeconds > 0)
                {
                    time(&seconds);
                    if (seconds >= startSeconds + closeAfter)
                    {
                        (void)printf("Killing\r\n");
                        startSeconds = 0;
                        sendCommand("openport -K");
                    }
                }
                IoTHubDeviceClient_LL_DoWork(device_ll_handle);
                ThreadAPI_Sleep(10);

            } while (g_continueRunning);
        }

        // Clean up the iothub sdk handle
        IoTHubDeviceClient_LL_Destroy(device_ll_handle);
    }
    // Free all the sdk subsystem
    IoTHub_Deinit();

    printf("Press any key to continue");
    (void)getchar();

    return 0;
}
