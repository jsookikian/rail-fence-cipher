CPP = gcc
CPPFLAGS = -Wall -Werror -O3

CIPHER = railcipher.c


cipher: $(CIPHER)
	$(CPP) $(CPPFLAGS) $(CIPHER) -o cipher
