#ifndef SHAREDOBJECT_H
#define SHAREDOBJECT_H

#include <QtCore>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

//FOR REFERENCE:
//-------------
//QMutex mutex;
//mutex.lock();
//If another thread has locked the mutex then this call will block until that thread has unlocked it

//mutex.unlock();
//Unlocks the mutex

//QWaitCondition condition;
//condition.wait(mutex)
//Releases the mutex and waits on the wait condition.

//condition.wakeOne()
//Wakes one thread waiting on the wait condition.
//The thread that is woken up cannot be controlled or predicted.

//condition.wakeAll()
//Wakes all threads waiting on the wait condition.
//The order cannot be controlled or predicted.
//-------------

template <typename Data>
class SharedObject {
//Allows several threads to get secure access to Data
public:
    SharedObject() : readersCount(0), preparingToWrite(false) {}

    Data & get() {
        return data;
    }

    const Data & read() {
        return data;
    }

    void writeLock() {
        mutex.lock();
        preparingToWrite = true;
        while (readersCount != 0) {
            mutexUnlocked.wait(&mutex);
        }
    }

    void writeUnlock() {
        preparingToWrite = false;
        mutex.unlock();
        mutexUnlocked.wakeAll();
    }

    void readLock() {
        mutex.lock();
        while (preparingToWrite) {
            mutexUnlocked.wait(&mutex);
        }
        readersCount++;
        mutex.unlock();
    }

    void readUnlock() {
        mutex.lock();
        readersCount--;
        mutex.unlock();
        mutexUnlocked.wakeAll();
    }

private:   
    SharedObject(const SharedObject &obj): readersCount(0), preparingToWrite(false) {
        data(obj.data);
    }

    SharedObject & operator=(const SharedObject &obj) {
        data = obj.data;
    }


    Data data;

    qint32         readersCount;
    bool           preparingToWrite;
    QMutex         mutex;
    QWaitCondition mutexUnlocked;
};

#endif // SHAREDOBJECT_H

