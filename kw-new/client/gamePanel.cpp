#include <GamePanel.h>

GamePanel::GamePanel():
    hpVal(100),
    ammoVal(100),
    secsVal(0),
    minsVal(0) {
    qDebug() << "GamePanel";
    QLabel * hp = new QLabel("HP ");
    QLabel * ammo = new QLabel("AMMO ");
    hpValLabel = new QLabel("99");
    ammoValLabel = new QLabel("100");
    timerValLabel = new QLabel("0:00");

    int fontId = QFontDatabase::addApplicationFont("./fonts/digitalFont.ttf");
    if (fontId == 0) {
        font = new QFont(QFontDatabase::applicationFontFamilies(fontId).first(),48);
        hp -> setFont(* font);
        hpValLabel -> setFont(* font);
        timerValLabel -> setFont(* font);
        ammo -> setFont(* font);
        ammoValLabel -> setFont(* font);
    } else {
        qDebug() << "GamePanel" << (void*)this <<
              "::GamePanel:" << "Couldn't loaded game font"
                             << "./fonts/digitalFont.ttf";
    }

    hp -> setStyleSheet(panel);
    hpValLabel -> setStyleSheet(panel);
    timerValLabel -> setStyleSheet(panel);
    ammo -> setStyleSheet(panel);
    ammoValLabel -> setStyleSheet(panel);

    addWidget(hp);
    addWidget(hpValLabel);
    addStretch();
    addWidget(timerValLabel);
    addStretch();
    addWidget(ammo);
    addWidget(ammoValLabel);
}

GamePanel::~GamePanel() {
    qDebug() << "~GamePanel";
    delete font;
    delete timerValLabel;
    delete ammoValLabel;
    delete hpValLabel;
    QFontDatabase::removeAllApplicationFonts();
}

uint GamePanel::getAmmo() const {
    return ammoVal;
}

uint GamePanel::getHp() const {
    return hpVal;
}

uint GamePanel::getMins() const {
    return minsVal;
}

uint GamePanel::getSecs() const {
    return secsVal;
}

void GamePanel::setAmmo(uint ammo) {
    this -> ammoVal = ammo;
    ammoValLabel -> setText(QString().number(ammo));
}

void GamePanel::setHp(uint hp) {
    this -> hpVal = hp;
    hpValLabel -> setText(QString().number(hp));
}

void GamePanel::setMins(uint mins) {
    this -> minsVal = mins;
}

void GamePanel::setSecs(uint secs) {
    this -> secsVal = secs;
}