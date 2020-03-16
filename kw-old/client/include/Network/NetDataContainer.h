/*
 *
 * Created on: 28.04.2012
 *
 * NetDataContainer.h
 * This file is part of kolobok-wars-client
 * 
 * Copyright (C) 2012 - Ivan Penkin, MIPT
 * grek.penkin@gmail.com
 *
 * kolobok-wars-client is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * kolobok-wars-client is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with kolobok-wars-client; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 *  
 */

#ifndef NETDATACONTAINER_H_
#define NETDATACONTAINER_H_


/*
 *
 * Warning!
 * OptionsContainer object should be removed manually
 * in GameEngine or other part of this project which
 * will receive a pointer to OptionsContainer object
 * by signal or by other method.
 * You must call QObject::connect function ONLY ONE
 * TIME else you can get freed memory in all functions
 * where you get the pointer to OptionsContainer
 * object by signal.
 *
 */

#include <QtCore>


template <class DataType>
class NetDataContainer
{
  public:
    NetDataContainer()
    {};

    ~NetDataContainer()
    {}

    explicit
    NetDataContainer( const DataType & option )
    {
      d_option = option;
      readen = false;
    }

    inline
    void setOption( const DataType & option )
    {
      d_option = option;
      readen = false;
    }

    inline
    DataType & getOption()
    {
      return d_option;
    }

    inline
    void setReaden()
    {
      readen = true;
    }

    inline
    bool isReaden()
    {
      if ( readen ) return true;
        else return false;
    };

  private:
    DataType d_option;

    bool     readen;
};



#endif /* NETDATACONTAINER_H_ */
