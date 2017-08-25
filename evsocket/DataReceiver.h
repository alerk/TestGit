#ifndef DATARECEIVER_H
#define DATARECEIVER_H
#include "DataReceiveListener.h"

class DataReceiver : public DataReceiveListener {
    bool requestedClose;
public:
    DataReceiver();
    virtual ~DataReceiver();

    void onDataReceived(int n, char* buffer);
    bool isRequestedClose() { return requestedClose; }
};
#endif