#include<Console.h>
#include<Utils.h>

Console::Console(QWidget *parent) :
    QWidget(parent) {
    QWidget * consoleWidget = new QWidget;
    consoleWidget -> setStyleSheet(consoleBack);
    consoleWidget -> setFixedWidth(300);

    QVBoxLayout * console = new QVBoxLayout;

    playerPos.setText("Player position: ");
    topLeft.setText("Top left: ");
    available.setText("Available: ");
    heading.setText("Heading vector: ");
    fireTargt.setText("Fire target: ");
    intention.setText("Intention vector: ");

    consoleWidget -> setLayout(console);

//    playerPos.setStyleSheet(console);
//    topLeft.setStyleSheet(console);
//    available.setStyleSheet(console);
//    heading.setStyleSheet(console);
//    intention.setStyleSheet(console);
//    fireTargt.setStyleSheet(console);

    console -> addWidget(&playerPos);
    console -> addWidget(&topLeft);
    console -> addWidget(&available);
    console -> addWidget(&heading);
    console -> addWidget(&intention);
    console -> addWidget(&fireTargt);
    console -> addStretch();

    QVBoxLayout * consoleLayout = new QVBoxLayout;
    setLayout(consoleLayout);
    consoleLayout -> addWidget(consoleWidget);
}


void Console::setPlayerPos(const QPoint &pos) {
    playerPos.setText("Player Position: x" + QString().number(pos.x()) + " y" + QString().number(pos.y()));
}

void Console::setTopLeft(const QPointF &top) {
    topLeft.setText("Top Left: \n\tx" + QString().setNum(top.x(),'f',7) + "\n\ty" + QString().setNum(top.y(),'f',7) );
}

void Console::setAvailable(bool avail) {
    if (avail == true) {
        available.setStyleSheet(console);
        available.setText("Available: true");
      } else {
        available.setStyleSheet(consoleError);
        available.setText("Available: false");
      }
}

void Console::setHeading(const QVector2D &head) {
    heading.setText("Heading vector: \n\tx" + QString().setNum(head.x(), 'f', 4) + "\n\ty" + QString().setNum(head.y(), 'f', 4) );
}

void Console::setIntention ( const QVector2D & intn )
{
    intention.setText("Intention vector: \n\tx" + QString().setNum(intn.x(), 'f', 4) + "\n\ty" + QString().setNum(intn.y(), 'f', 4) );
}

void Console::setFireTarget ( const QPointF & trgt) {
    QPointF tmp = trgt*100/scale_x_100();
    fireTargt.setText("Fire target: \n\tx" + QString().setNum(tmp.x(), 'f', 4) + "\n\ty" + QString().setNum(tmp.y(), 'f', 4) );
}