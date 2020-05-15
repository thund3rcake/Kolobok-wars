#ifndef MAINMENUSTYLE_H_
#define MAINMENUSTYLE_H_


#include<QString>

namespace MainMenuStyle {

static const QString CanvasBg = \
    "background-color: rgba(255, 255, 255, 0);";

static const QString Label = \
    "QLabel { \
        font: bold; \
        font-size: 18px; \
        color: rgba(229, 229, 229, 255); \
        background-color: rgba(255, 255, 255, 0); }"
    "QLabel:hover { \
        font: bold; \
        font-size: 18px; \
        color: rgba(62, 62, 62, 255); \
        background-color: rgba(255, 255, 255, 0); }";

}
#endif /* MAINMENUSTYLE_H_ */