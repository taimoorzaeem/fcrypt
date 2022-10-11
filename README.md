# Fcrypt

A command line tool to encrypt and decrypt a file using a symmetric key.

This implementation uses a Vigenère Cipher with a little twist. It take one's complement after xoring which is also symmetric.

I have also append a dynamic key signature at the end of encrypted file which would detect and notify the user if a wrong key was used in decryption.

**To build:**

```
$ make
```

**To install:**

```
$ make
$ sudo make install
```

**Using the tool:**

To encrypt a file:

```
$ fcrypt -e <filename> <key-filename>
```

To decrypt the same file:

```
$ fcrypt -d <filename> <key-filename>
```

**To unistall:**
```
$ sudo make uninstall
```
