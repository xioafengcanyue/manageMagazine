#ifndef SQLTHREAD_H
#define SQLTHREAD_H

#include <QObject>
#include<QThread>
class SQLThread : public QThread
{
    Q_OBJECT
public:
    explicit SQLThread(QThread *parent = nullptr);
    void run();

signals:

public slots:
};

#endif // SQLTHREAD_H
