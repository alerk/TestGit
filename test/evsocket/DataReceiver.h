#ifndef DATARECEIVER_H
#define DATARECEIVER_H
#include "DataReceiveListener.h"

class DataReceiver : IDataReceiveListener{
    bool requestedClose;
public:
    DataReceiver();
    virtual ~DataReceiver();

    void onDataReceived(char* buffer);
    bool isRequestedClose() { return requestedClose; }
}
#endif