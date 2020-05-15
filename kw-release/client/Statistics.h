#ifndef STATISTICS_H
#define STATISTICS_H

#include <QObject>
#include <QLabel>
#include <QtGui>
#include<QHBoxLayout>

class Statistics: public QWidget {
  Q_OBJECT
  public:
    Statistics ( QWidget * parent = 0 );
    void updateStatistic ();

  private:
    Statistics();
    Statistics( const Statistics & rhs );
    Statistics & operator=( const Statistics & rhs );
};

#endif // STATISTICS_H
