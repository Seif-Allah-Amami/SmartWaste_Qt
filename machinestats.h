#ifndef MACHINESTATS_H
#define MACHINESTATS_H

#include <QDialog>
#include <QString>

class MachineGlobalStats : public QDialog
{
    Q_OBJECT
public:
    explicit MachineGlobalStats(QWidget *parent = nullptr);
};

class MachineSingleStats : public QDialog
{
    Q_OBJECT
public:
    explicit MachineSingleStats(const QString &id,
                                const QString &name,
                                const QString &type,
                                const QString &location,
                                const QString &purchaseDate,
                                const QString &status,
                                QWidget *parent = nullptr);
};

#endif // MACHINESTATS_H
