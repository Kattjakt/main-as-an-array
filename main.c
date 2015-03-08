#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
	// throw error if we don't get a string
	if (argc != 2) {
		fprintf(stderr, "usage: %s <text>\n", argv[0]);
		return -1;
	}

	// payload for (only) linux x64	
	int i, payload[] = {       
		0x55,   0x48,   0x89,   0xe5,   0xb8,   0x01,   0x00,   0x00,
	        0x00,   0xbb,   0x01,   0x00,   0x00,   0x00,   0x67,   0x8d,
        	0x35,   0x10,   0x00,   0x00,   0x00,   0xba,   0x00,   0x00,
        	0x00,   0x00,   0x0f,   0x05,   0xb8,   0x3c,   0x00,   0x00,
        	0x00,   0x31,   0xdb,   0x0f,   0x05,   0x0a, 	0x5d,   0xc3
	};					       

	// read string from cl-arguments and append a newline
	char *string = argv[1];
	string[strlen(string)] = '\n';
	string[strlen(string)+1] = '\0';	

	// override write() string size
	payload[22] = strlen(string);

	// just format and print everything to stdout
	printf("const char main[] = {");
	for (i=0; i < 39 + strlen(string) + 2; i++) {
		printf("%s\t0x%02X, ",
			(i % 4 != 0) ? "" : "\n",
			(i > 37 + strlen(string)-1) ? payload[i - strlen(string) - 1] :
			(i > 36) ? string[i - 37 ] : payload[i]
		);
	}
	printf("\n};\n");	

	return 0;
}
