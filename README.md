This program was made to secure image transfer from one person to another by a secret key preestabilished
by the sender and receiver.

This application can encrypt an image file with a .bmp extension 
by using the xorshift32 random number generator and the Durstenfeld shuffle,
based on the aforementioned secret key.

To decrypt, the application mirrors the encryption process.

In order to prove the efficiency of the encryption, there is a chiSquaredTest header to 
test the color channels to make sure they are equally proportioned amongst the encrypted image,
as to make decryption impossible for anyone but the persons who know the secret key.
