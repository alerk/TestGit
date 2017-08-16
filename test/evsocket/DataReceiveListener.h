#ifndef DATARECEIVELISTENER_H
#define DATARECEIVELISTENER_H

/**
 * DataReceiveListener interface 
 */

class DataReceiveListener {
public:
    void onDataReceived(char* buffer) = 0;
}
#endif