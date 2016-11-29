#include <iostream>
#include <pthread.h>

#include "common.h"

using namespace std;

class BaseThreadClass
{
public:
    pthread_t *aThread;
    pthread_mutex_t *aMutex;
    virtual void initThread(void *func);
    virtual void joinThread();
};

void BaseThreadClass::initThread(void* func)
{
    int rc = pthread_create(&aThread, NULL, func, this);
    if(rc)
    {
        cout << "ERROR; return code from pthread_create() is " << rc << endl;
    }
}

class MainClass:BaseThreadClass
{
public:
    static void* run(void* obj);

};

void* MainClass::run(void* obj)
{
    cout << "MainClass do something" << endl;
}

class ReceiverClass
{
public:
    static void* run(void* obj);
    void onDataReceived(void);
};

void* ReceiverClass::run(void* obj)
{
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MAX_SIZE + 1];
    int must_stop = 0;

    /* initialize the queue attributes */
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    /* create the message queue */
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0644, &attr);
    CHECK((mqd_t)-1 != mq);

    do {
        ssize_t bytes_read;

        /* receive the message */
        bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
        CHECK(bytes_read >= 0);

        buffer[bytes_read] = '\0';
        if (! strncmp(buffer, MSG_STOP, strlen(MSG_STOP)))
        {
            must_stop = 1;
        }
        else
        {
            printf("Received: %s\n", buffer);
        }
    } while (!must_stop);

    /* cleanup */
    CHECK((mqd_t)-1 != mq_close(mq));
    CHECK((mqd_t)-1 != mq_unlink(QUEUE_NAME));

    return NULL;
}

int main(void)
{
    MainClass *objMain = new MainClass();
    ReceiverClass *objReceiver = new ReceiverClass();
    return 0;
}
