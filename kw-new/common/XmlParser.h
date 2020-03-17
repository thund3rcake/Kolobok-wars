#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QString>
#include <QMessageBox>
#include <QXmlDefaultHandler>
#include <Map.h>
#include <Entity.h>

class XmlHandler : public QXmlDefaultHandler
{
  public:
    XmlHandler(abstractNoAIMap& map, QString file);

    bool startElement (
                       const QString &namespaceURI,
                       const QString &localName,
                       const QString &qName,
                       const QXmlAttributes &attributes
                      );

    bool endElement   (
                       const QString &namespaceURI,
                       const QString &localName,
                       const QString &qName
                      );

    bool characters(const QString &str);
    bool fatalError(const QXmlParseException &exception);

    bool parseXML();

  private:
    XmlHandler();
    XmlHandler(const XmlHandler &rhs);
    XmlHandler& operator=(const XmlHandler &rhs);

    abstractNoAIMap& dest;
    QString currentText;
    QString filename;

    int entityID;

    PolygonEntity* curEntity;
    QPolygon polygon;

    bool isNewEntityDefined;
    bool isThereMapTag;
    bool isThereRespawnTag;
};



#endif // XMLPARSER_H