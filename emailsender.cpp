#include "emailsender.h"
#include <QProcess>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QTextStream>

bool EmailSender::sendMail(const QString& toEmail,
                           const QString& toName,
                           const QString& contractType,
                           const QString& expiryDate)
{
    // Build the Python SMTP script dynamically
    QString script = QString(
                         "import smtplib\n"
                         "from email.mime.text import MIMEText\n"
                         "from email.mime.multipart import MIMEMultipart\n"
                         "\n"
                         "sender   = 'medrayenchihi44@gmail.com'\n"       // <-- replace with your Gmail
                         "password = 'akuburqdfciomrsi'\n"           // <-- replace with your App Password
                         "receiver = '%1'\n"
                         "\n"
                         "msg = MIMEMultipart()\n"
                         "msg['From']    = sender\n"
                         "msg['To']      = receiver\n"
                         "msg['Subject'] = 'Contract Expiry Reminder - Action Required'\n"
                         "\n"
                         "body = \"\"\"Dear %2,\n"
                         "\n"
                         "This is an automated reminder from the ReGen Supplier Management System.\n"
                         "\n"
                         "Your contract (%3) is due to expire on %4.\n"
                         "Please take the necessary steps to renew or review it before the deadline.\n"
                         "\n"
                         "Best regards,\n"
                         "ReGen Supplier Management System\"\"\"\n"
                         "\n"
                         "msg.attach(MIMEText(body, 'plain'))\n"
                         "\n"
                         "try:\n"
                         "    with smtplib.SMTP_SSL('smtp.gmail.com', 465) as server:\n"
                         "        server.login(sender, password)\n"
                         "        server.sendmail(sender, receiver, msg.as_string())\n"
                         "        print('Email sent successfully to %1')\n"
                         "except Exception as e:\n"
                         "    print(f'Failed to send email: {e}')\n"
                         "    exit(1)\n"
                         ).arg(toEmail).arg(toName).arg(contractType).arg(expiryDate);

    // Write script to a temp file
    QFile file("send_mail.py");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    out << script;
    file.close();

    // Execute the script
    QProcess process;
    process.start("python", QStringList() << "send_mail.py");
    process.waitForFinished(10000);
    return process.exitCode() == 0;
}
