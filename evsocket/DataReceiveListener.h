#ifndef DATARECEIVELISTENER_H
#define DATARECEIVELISTENER_H

/**
 * DataReceiveListener interface 
 */

class DataReceiveListener {
public:
    virtual void onDataReceived(int n, char* buffer) = 0;
    virtual bool isRequestedClose() = 0;
};
#endif