#ifndef VERSIONS_H_
#define VERSIONS_H_

#include <QtCore>
#include <CommonGlobal.h>

namespace Net
{

static const qint16 ProtVersion = NET_VERSION;
static const qint16 ProtSubversion = NET_SUBVERSION;

static const int DataStreamVersion = QDataStream::Qt_4_0;

} /* namespace Net */

#endif /* VERSIONS_H_ */
