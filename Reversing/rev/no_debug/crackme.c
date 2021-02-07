#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/sendfile.h>
#include <sys/signal.h>
#include <unistd.h>

char* s;
char* k;
char key[] = "waRaSg47_NpGiS93niKQKtKQ7dihholA";
char enc_password[] = "\xbd\xb0\x6d\xbc\x68\x66\x63\xcf\x86\x72\x70\xe8\x73\x73\x07\x6f\xb9\x64";

void main_2()
{
	char buffer[256] = { 0 };
	char password[32];
	int fd = open("/dev/urandom", 0);
	read(fd, password, 32);
	close(fd);
	int bytes_read = 0;
	printf("Enter key: ");
	bytes_read = read(0, buffer, 255);
	if (bytes_read > 0)
		buffer[bytes_read - 1] = 0;
	if(memcmp(buffer, password, 31) == 0)
	{
		puts("Congrats you are a super eleet hacker, here is your flag: ");
		sendfile(1, open(buffer, 0), 0, 0x100);
	}
	else
	{
		puts("Wrong password");
	}
}

void __attribute__((constructor)) setup()
{
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	alarm(0x30);
	if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) < 0) {
		main_2();
		exit(0);
	}
}

void init(char* buffer, uint64_t len)
{
	s = malloc(256);
	k = malloc(256);
	char tmp;
	int j = 0;
	for (int i = 0; i < 256; i++) {
		s[i] = i;
		k[i] = buffer[i % len];
	}
	for (int i = 0; i < 256; i++) {
		j = (j + s[i] + k[i]) % 256;
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
	}
}

void rc4(char* buffer, uint64_t len)
{
	int i = 0, j = 0, t = 0;
	uint64_t k = 0;
	char tmp;
	for (k = 0; k < len; k++) {
		i = (i + 1) % 256;
		j = (j + s[i]) % 256;
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
		t = (s[i] + s[j]) % 256;
		buffer[k] ^= s[t];
	}
}

int check(char* buffer, size_t len)
{
	init(key, 32);
	rc4(enc_password, len);
	/*puts(buffer);*/
	for (int i = 0; i < len; i++) {
		if (buffer[i] != enc_password[i])
			return 0;
	}
	return 1;
}

int main()
{
	char buffer[256];
	printf("Enter key: ");
	size_t bytes_read = read(0, buffer, 255);
	if (bytes_read > 0)
		buffer[bytes_read - 1] = 0;
	if (check(buffer, bytes_read - 1)) {
		printf("Congrats here is your flag: ");
		sendfile(1, open("/flag", 0), 0, 0x100);
	} else {
		puts("Invalid key");
	}
	return 0;
}
