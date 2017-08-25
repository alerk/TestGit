// Client socket example
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <sys/socket.h>
#include <string.h>

#define DATA_PORT 65001

void eventcb(struct bufferevent *bev, short events, void *ptr)
{
    if (events & BEV_EVENT_CONNECTED) {
         /* We're connected to 127.0.0.1:8080.   Ordinarily we'd do
            something here, like start reading or writing. */
        struct evbuffer *input;
        char *line;
        char buf[1024];
        int i;
        input = bufferevent_get_input(bev);
        size_t n = evbuffer_get_length(input);
        if (0 == n) {
            printf("Nothing in the input buffer\n");
        } else {
            evbuffer_remove(input, buf, n);
            printf("Recv: (%d, %s)\n", n, buf);
        }
    } else if (events & BEV_EVENT_ERROR) {
         /* An error occured while connecting. */
    }
}

int main(void)
{
    struct event_base *base;
    struct bufferevent *bev;
    struct sockaddr_in sin;

    base = event_base_new();

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.128.5", &sin.sin_addr);
    sin.sin_port = htons(DATA_PORT);

    bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);

    bufferevent_setcb(bev, NULL, NULL, eventcb, NULL);

    if (bufferevent_socket_connect(bev,
        (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        /* Error starting connection */
        bufferevent_free(bev);
        return -1;
    }

    event_base_dispatch(base);
    return 0;
}