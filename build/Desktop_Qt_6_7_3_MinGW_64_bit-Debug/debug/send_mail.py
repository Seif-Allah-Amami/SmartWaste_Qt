import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

sender   = 'medrayenchihi44@gmail.com'
password = 'akuburqdfciomrsi'
receiver = 'medrayenchihi44@gmail.com'

msg = MIMEMultipart()
msg['From']    = sender
msg['To']      = receiver
msg['Subject'] = 'Contract Expiry Reminder - Action Required'

body = """Dear saaida,

This is an automated reminder from the ReGen Supplier Management System.

Your contract (khra) is due to expire on 2026-05-06.
Please take the necessary steps to renew or review it before the deadline.

Best regards,
ReGen Supplier Management System"""

msg.attach(MIMEText(body, 'plain'))

try:
    with smtplib.SMTP_SSL('smtp.gmail.com', 465) as server:
        server.login(sender, password)
        server.sendmail(sender, receiver, msg.as_string())
        print('Email sent successfully to medrayenchihi44@gmail.com')
except Exception as e:
    print(f'Failed to send email: {e}')
    exit(1)
