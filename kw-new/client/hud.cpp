#include<HUD.h>
#include<Utils.h>
#include<HUDStyleSheets.h>

HUD::HUD() :
    bottomPanel(new GamePanel()),
    console(new Console(this)),
    statistics(new Statistics(this)) {

    setStyleSheet("background-color: rgba(255, 255, 255, 0%);");
    setFixedSize(QSize(getDesktopSize().x() - 2, getDesktopSize().y() - 2));

    vLayout = new QVBoxLayout;
    setLayout(vLayout);

    topHLayout = new QHBoxLayout;
    topHLayout -> addWidget(console);
    topHLayout -> addStretch();

    vLayout -> addLayout(topHLayout);
    vLayout -> addStretch();
    vLayout -> addLayout(bottomPanel);

    statistics -> hide();
}

void HUD::updateConsole(
                                                        Player * player,
                                                        const QPointF & topLeft,
                                                        bool available
                                                        ) {
    console -> setPlayerPos(player -> getPosition().toPoint() * 100 / scale_x_100());
    console-> setHeading(player -> getHead());
    console -> setTopLeft(topLeft);
    console -> setAvailable(available);
}

void HUD::updConstFireTarget (const QPointF & target) {
    console -> setFireTarget(target);
}

HUD::~HUD() {
    delete bottomPanel;
}

void HUD::keyPressEvent(QKeyEvent *event) {
    if (event -> key() == Qt::Key_Tab) {
        statistics -> show();
        console -> hide();
    }
}

void HUD::keyReleaseEvent(QKeyEvent * event) {
    if (event -> key() == Qt::Key_Tab) {
        statistics -> hide();
        console -> show();
    }
}