
#ifndef METAREGISTRATOR_H_
#define METAREGISTRATOR_H_

#include <QMetaType>
#include <CommonGlobal.h>

template <class MetaType>
class KW_COMMON_EXPORT MetaRegistrator {

  public:
    inline MetaRegistrator(const char * metaTypeName);
    inline explicit MetaRegistrator(const MetaRegistrator<MetaType> & rhs);
    inline MetaRegistrator<MetaType>& operator=(const MetaRegistrator<MetaType> & rhs);


  private:
    MetaRegistrator() {};
    inline void registrate();
    static bool registered;
    QString     typeName;
};

template<class MetaType>
bool KW_COMMON_EXPORT MetaRegistrator<MetaType>::registered = false;


template <class MetaType>
inline KW_COMMON_EXPORT MetaRegistrator<MetaType>::MetaRegistrator(const char * metaTypeName)
    :typeName(metaTypeName) {

  registrate();
}

template <class MetaType>
inline KW_COMMON_EXPORT MetaRegistrator<MetaType>::MetaRegistrator(const MetaRegistrator<MetaType> & rhs)
    :typeName(rhs.typeName) {

  registrate();
}

template <class MetaType>
inline KW_COMMON_EXPORT MetaRegistrator<MetaType> & MetaRegistrator<MetaType>::operator=
                                      (const MetaRegistrator<MetaType> & rhs) {

  typeName = rhs.typeName;
  registrate();

  return *this;
}

template <class MetaType>
inline void KW_COMMON_EXPORT MetaRegistrator<MetaType>::registrate() {

  if (!registered) {
    qRegisterMetaType<MetaType>(typeName.toLocal8Bit().constData());
    qRegisterMetaTypeStreamOperators<MetaType>(typeName.toLocal8Bit().constData());
    registered = true;
  }
}

#endif /* METAREGISTRATOR_H_ */
