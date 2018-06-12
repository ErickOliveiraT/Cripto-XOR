import smtplib
import config

def send_email(subject, msg):
    try:
        server = smtplib.SMTP('smtp.gmail.com:587')
        server.ehlo()
        server.starttls()
        server.login(config.EMAIL_ADDRESS, config.PASSWORD)
        message = 'Subject: {}\n\n{}'.format(subject, msg)
        server.sendmail(config.EMAIL_ADDRESS, config.EMAIL_DEST, message)
        server.quit()
        print("Success: Email sent!")
    except:
        print("Email failed to send.")

subject = "Your Decrypted Data - Cripto XOR"
msg = config.MSGE

send_email(subject, msg)