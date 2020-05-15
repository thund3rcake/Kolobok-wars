#ifndef NETDATACONTAINER_H
#define NETDATACONTAINER_H

#include<QtCore>

template <class DataType>

class NetDataContainer {
public:
    NetDataContainer() {}
    virtual ~NetDataContainer() {}
    explicit NetDataContainer(const DataType & option) {
        data_option = option;
        readen = false;
    }

    inline void setOption(const DataType & option) {
        data_option = option;
        readen = false;
    }
    inline DataType & getOption() {
        return data_option;
    }

    inline void setReaden() {
        readen = true;
    }
    inline bool isReaden() {
        if (readen) {
            return true;
        } else {
            return false;
        }
    }

private:
    DataType data_option;
    bool readen;

};

#endif // NETDATACONTAINER_H
