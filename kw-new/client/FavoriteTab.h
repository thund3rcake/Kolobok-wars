#ifndef FAVORITETAB_H_
#define FAVORITETAB_H_

#include <QtGui>
#include<QPushButton>
#include<QTreeWidget>

class FavoriteTab : public QWidget
{
    Q_OBJECT

  public:
    explicit
    FavoriteTab( QWidget * parent = 0 );

    ~FavoriteTab();

  private:
    FavoriteTab();
    FavoriteTab( const FavoriteTab & rhs );
    FavoriteTab & operator=( const FavoriteTab & rhs );


    QPushButton   * favAddFav;
    QPushButton   * favConnect;
    QTreeWidget   * favSrv;
};


#endif /* FAVORITETAB_H_ */
