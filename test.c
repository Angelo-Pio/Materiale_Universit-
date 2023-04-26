#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

static int send_response(struct MHD_Connection *connection, const char* message) {
    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(message), (void*) message, MHD_RESPMEM_PERSISTENT);
    if (response == NULL) {
        return MHD_NO;
    }

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

static int request_handler(void *cls, struct MHD_Connection *connection,
                           const char *url, const char *method, const char *version,
                           const char *upload_data, size_t *upload_data_size, void **ptr) {
    const char *message = "Ciao";

    if (strcmp(method, MHD_HTTP_METHOD_GET) == 0) {
        return send_response(connection, message);
    } else {
        return send_response(connection, "Unsupported method");
    }
}

int main(int argc, char* argv[]) {
    struct MHD_Daemon *d;

    d = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                         &request_handler, NULL, MHD_OPTION_END);
    if (d == NULL) {
        return EXIT_FAILURE;
    }

    printf("Server running on port %d... Press enter to stop.\n", PORT);
    getchar();

    MHD_stop_daemon(d);
    return EXIT_SUCCESS;
}