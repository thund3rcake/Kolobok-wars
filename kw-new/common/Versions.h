#ifndef VERSIONS_H_
#define VERSIONS_H_

#include <QtCore>
#include <CommonGlobal.h>

namespace Net
{

static const qint16 KW_COMMON_EXPORT ProtVersion    = NET_VERSION;
static const qint16 KW_COMMON_EXPORT ProtSubversion = NET_SUBVERSION;

static const int KW_COMMON_EXPORT DataStreamVersion = QDataStream::Qt_4_0;

} /* namespace Net */

#endif /* VERSIONS_H_ */
