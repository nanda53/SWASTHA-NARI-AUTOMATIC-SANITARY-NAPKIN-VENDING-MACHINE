import imaplib
import email


import serial

ser = serial.Serial('COM10', 115200) # Initialize serial communication at 9600 baud


# connect to the server and login
mail = imaplib.IMAP4_SSL('imap.gmail.com')
mail.login('*******@gmail.com', '*api password*')
while True:
    print("Searching")
    # select the inbox mailbox and retrieve the new messages
    mail.select('inbox', readonly=False)
    result, data = mail.search(None, 'UNSEEN')

    # loop through the new messages and print their subjects and bodies
    for num in data[0].split():
        result, data = mail.fetch(num, '(RFC822)')
        raw_email = data[0][1]
        email_message = email.message_from_bytes(raw_email)
        print(email_message['Subject'])
        if(email_message['Subject']=="****** KARNATAKA BANK- Transaction EMAIL Alert ******"):
            print(1)
            message = "1\n" # Define the message to send
            ser.write(message.encode('utf-8')) # Send the message over the serial port
# close the connection
mail.close()
mail.logout()
