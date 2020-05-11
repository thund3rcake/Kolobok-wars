#ifndef DERIVEDWINDOWS_H_
#define DERIVEDWINDOWS_H_

#include <BaseWindow.h>
#include <LanTab.h>
#include <FavoriteTab.h>
#include <WindowStyle.h>

class FindWindow : public Window
{
    Q_OBJECT

  public:
    explicit
    FindWindow( QWidget * parent = 0 );

    virtual
    ~FindWindow();

  private:
    FindWindow();
    FindWindow( const FindWindow & rhs );
    FindWindow & operator=( const FindWindow & rhs );


    QTabWidget  * findType;

    LanTab      * lan;
    FavoriteTab * fav;

  private slots:
    void onStartGame( const ServerAbout & connectionInfo );
    void catchError( int, QString );

  signals:
    void startGame( const ServerAbout & connectionInfo );
};

class OptionsWindow : public Window
{
    Q_OBJECT

  public:
    explicit
    OptionsWindow( QWidget * parent = 0 );

  private:
    OptionsWindow();
    OptionsWindow( const OptionsWindow & rhs );
    OptionsWindow & operator=( const OptionsWindow & rhs );
};


class QuitWindow : public Window
{
    Q_OBJECT

  public:
    explicit
    QuitWindow( QWidget * parent = 0 );

  private:
    QuitWindow();
    QuitWindow( const QuitWindow & rhs );
    QuitWindow & operator=( const QuitWindow & rhs );
};

class ErrorWindow: public Window
{
    Q_OBJECT

  public:
    explicit
    ErrorWindow( QWidget * parent = 0 );

    void setMessage( const QString & msg );

  private:
    ErrorWindow();
    ErrorWindow( const QuitWindow & rhs );
    ErrorWindow & operator=( const QuitWindow & rhs );

    QLabel * message;
};


#endif /* DERIVEDWINDOWS_H_ */
