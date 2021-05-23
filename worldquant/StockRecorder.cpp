#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include <unordered_map>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
#include <pthread.h>

using namespace std;
typedef std::pair<string, long> StockPair;
class StockRecorder {
private:
    unordered_map<string, long> stocks;
    vector<StockPair> sortedData;
public:
    int nTop;
    pthread_t sortThread;
    pthread_mutex_t addMutex;
    pthread_cond_t addCond;
    void run();

    // Constructor + Destructor
    StockRecorder(long nTop);
    virtual ~StockRecorder();
    
    unordered_map<string, long> getStocks();
    int addStock(StockPair input);
    vector<StockPair> requestTopStock();
    void setTopStock(vector<StockPair> sortedData) {
        this->sortedData.clear();
        this->sortedData = sortedData;
    };
    static void* run(void* arg);
    void joinThread(void) {
        pthread_join(sortThread, NULL);
    }

};

StockRecorder::StockRecorder(long nTop) {
    this->nTop = nTop;
    if (pthread_create(&sortThread, NULL, &StockRecorder::run, this)!=0) {
        cout << "Failed to create sortThread" << std::endl;
    }
}

int StockRecorder::addStock(StockPair input) {
    pthread_mutex_lock(&addMutex);
    stocks[input.first] += input.second;
    pthread_mutex_unlock(&addMutex);
    pthread_cond_signal(&addCond);
    return 1;
}

unordered_map<string, long> StockRecorder::getStocks() {
    return this->stocks;
}

void* StockRecorder::run(void* arg) {
    StockRecorder* obj = (StockRecorder*) arg;
    // copy the data
    int counter = 0;
    while (counter < 50) {
        pthread_mutex_lock(&(obj->addMutex));
        while (obj->getStocks().size()==0) {
            pthread_cond_wait(&(obj->addCond), &(obj->addMutex));
        }
        unordered_map<string, long> stocks = obj->getStocks();
        pthread_mutex_unlock(&obj->addMutex);
        // Get top nTop from stocks
        vector<StockPair> sortedData(stocks.begin(), stocks.end());
        size_t sz = stocks.size();
        int n = (obj->nTop > sz-1 ? sz-1 : obj->nTop); // min(obj->nTop, sz-1);
        for (int i=0; i<n; i++) {
            for (int j=i+1; j<sz; j++) {
                if (sortedData[i].second < sortedData[j].second) {
                    // Swap i <-> j
                    swap(sortedData[i], sortedData[j]);
                }
            }
        }
        obj->setTopStock(sortedData);
        // Sleep 2 seconds
        counter++;
        sleep(2);
    }
    return NULL;
}

vector<StockPair> StockRecorder::requestTopStock() {
    return this->sortedData;
}

int main(void) {
    cout << "Hello again" << endl;
    StockRecorder *objTracker = new StockRecorder(3);
    // Test data
    vector<std::pair<string, long>> tmp{
        {"GOOG", 100},
        {"MSF", 200},
        {"FBK", 200},
        {"NETF", 200},
        {"GOOG", 300},
        {"AAPL", 100},
        {"MSF", 200},
        {"FBK", 200},
        {"NETF", 200},
        {"AAPL", 300},
        {"GOOG", 100},
        {"MSF", 200},
        {"AAPL", 200},
        {"NETF", 200},
        {"GOOG", 300}
    };
    for(int i=0; i<tmp.size(); i++) {
        objTracker->addStock(tmp[i]);
        if (i%10 == 0) {
            cout << "First request" << endl;
            vector<StockPair> result = objTracker->requestTopStock();
            for(auto stock: result) {
                cout << stock.first << ": " << stock.second << endl;
            }
            cout << "-------" << endl;
        }
    }
    vector<StockPair> result = objTracker->requestTopStock();
    cout << "Second request" << endl;
    for(auto stock: result) {
        cout << stock.first << ": " << stock.second << endl;
    }
    cout << "-------" << endl;

    // Wait for sort thread to finish
    objTracker->joinThread();
    delete objTracker;

    printf("==== Finished ====\n");
    return 0;
}
