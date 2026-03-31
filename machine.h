#ifndef MACHINE_H
#define MACHINE_H

#include <QString>
#include <QSqlQueryModel>

class Machine {
public:
    Machine();
    Machine(const QString &name, const QString &type,
            const QString &location, const QString &date,
            const QString &status);

    bool ajouter();
    bool modifier(int id);
    static bool supprimer(int id);
    static QSqlQueryModel* afficher();
    static QSqlQueryModel* rechercher(const QString &filter, const QString &sortColumn);

private:
    QString m_name;
    QString m_type;
    QString m_location;
    QString m_date;
    QString m_status;
};

#endif // MACHINE_H
