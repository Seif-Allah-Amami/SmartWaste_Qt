#ifndef WASTE_H
#define WASTE_H

#include <QDate>
#include <QList>
#include <QString>

class Waste
{
public:
    Waste();
    Waste(int id,
          const QString &type,
          const QString &category,
          int quantity,
          double weightKg,
          const QDate &collectionDate,
          const QString &location,
<<<<<<< HEAD
          const QString &status);
=======
          const QString &status,
          int humidityPercent,
          int distanceCm);
>>>>>>> 5be580a (waste X Arduino)

    int id() const;
    QString type() const;
    QString category() const;
    int quantity() const;
    double weightKg() const;
    QDate collectionDate() const;
    QString location() const;
    QString status() const;
<<<<<<< HEAD
=======
    int humidityPercent() const;
    int distanceCm() const;
>>>>>>> 5be580a (waste X Arduino)

    void setId(int id);
    void setType(const QString &type);
    void setCategory(const QString &category);
    void setQuantity(int quantity);
    void setWeightKg(double weightKg);
    void setCollectionDate(const QDate &collectionDate);
    void setLocation(const QString &location);
    void setStatus(const QString &status);
<<<<<<< HEAD
=======
    void setHumidityPercent(int humidityPercent);
    void setDistanceCm(int distanceCm);
>>>>>>> 5be580a (waste X Arduino)

    bool create() const;
    bool update() const;
    static bool remove(int id);
    static QList<Waste> readAll();

private:
    int m_id;
    QString m_type;
    QString m_category;
    int m_quantity;
    double m_weightKg;
    QDate m_collectionDate;
    QString m_location;
    QString m_status;
<<<<<<< HEAD
=======
    int m_humidityPercent;
    int m_distanceCm;
>>>>>>> 5be580a (waste X Arduino)
};

#endif // WASTE_H
