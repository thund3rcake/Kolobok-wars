﻿/*
 *
 * Created on: 12.06.2013
 *
 * metaRegistrator.h
 * This file is part of HASP-Stat-Viewer, Kolobok-wars
 *
 * Copyright (C) 2013 - Ivan Penkin
 * grek.penkin@gmail.com
 *
 */

#ifndef METAREGISTRATOR_H_
#define METAREGISTRATOR_H_

#include <QMetaType>

template <class MetaType>
class MetaRegistrator {

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
bool MetaRegistrator<MetaType>::registered = false;


template <class MetaType>
inline MetaRegistrator<MetaType>::MetaRegistrator(const char * metaTypeName)
    :typeName(metaTypeName) {

  registrate();
}

template <class MetaType>
inline MetaRegistrator<MetaType>::MetaRegistrator(const MetaRegistrator<MetaType> & rhs)
    :typeName(rhs.typeName) {

  registrate();
}

template <class MetaType>
inline MetaRegistrator<MetaType> & MetaRegistrator<MetaType>::operator=
                                      (const MetaRegistrator<MetaType> & rhs) {

  typeName = rhs.typeName;
  registrate();

  return *this;
}

template <class MetaType>
inline void MetaRegistrator<MetaType>::registrate() {

  if (!registered) {
    qRegisterMetaType<MetaType>(typeName.toLocal8Bit().constData());
    qRegisterMetaTypeStreamOperators<MetaType>(typeName.toLocal8Bit().constData());
    registered = true;
  }
}

#endif /* METAREGISTRATOR_H_ */