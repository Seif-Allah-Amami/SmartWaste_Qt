#ifndef EMAILSENDER_H
#define EMAILSENDER_H

#include <QString>

class EmailSender
{
public:
    static bool sendMail(const QString& toEmail,
                         const QString& toName,
                         const QString& contractType,
                         const QString& expiryDate);
};

#endif // EMAILSENDER_H
