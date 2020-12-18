#ifndef TAXEL_LCD_H
#define TAXEL_LCD_H

#include <QObject>
#include <QLCDNumber>

#include <QDebug>

class Taxel_LCD : public QLCDNumber
{
    Q_OBJECT

public:
    explicit Taxel_LCD();
    ~Taxel_LCD();

signals:

};

#endif // TAXEL_LCD_H
