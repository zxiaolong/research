#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

void help()
{
	printf("Usage:\n");
	printf("-h --help, help message\n");
	printf("-d --debug [1-5], set print level\n");
	printf("-v --version, edgecli version\n");
	printf("-p --proto [1,2] IOT protocol version\n");
	printf("   --esam, use easm encrypt\n");
	printf("   --updated, run edgecli after edgecli updated\n");
}


int opts_parse(int argc, char * argv[])
{
    int c;
    int digit_optind = 0;

	/* variable */

    while (1) {
		static int flag;
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
            {"help",    no_argument, 		0,	'h'	},
            {"debug",	required_argument,  0,	'd'	},
            {"version",	no_argument,		0,  'v'	},
            {"proto",	required_argument,	0,	'p'	},
            {"test",  	no_argument, 		&flag, 	2	},
            {"test2",	no_argument, 		&flag,  3 	},
            {0,         0,                 	0,  0	}
        };

        c = getopt_long(argc, argv, "d:hvp:",
                long_options, &option_index);
        if (c == -1)
    	{
	        break;
    	}
		
        switch (c) {
            case 0:
                printf("option %s", long_options[option_index].name);
                if (optarg)
                    printf(" with arg %s", optarg);
                printf("\n");

				switch(flag) {
					case 2: 
						printf("test\n");
						break;
					case 3: 
						printf("test2\n");
						break;
				}
                break;
            case 'h':
                help();
				return 1;
                break;

            case 'd':
                printf("debug %s\n", optarg);
                break;

            case 'v':
                printf("Version: 1.0\n");
				return 1;
                break;

            case 'p':
                printf("proto %s\n", optarg);
                break;

            case '?':
				printf("output ?\n");
				help();
				return 1;
                break;

            default:
                printf("?? getopt returned character code 0%o ??\n", c);
        }
    }

    if (optind < argc) {
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
    }
	
	return 0;
}

int main(int argc, char *argv[])
{
	if(1 == opts_parse(argc, argv)) {
		exit(0);
	}
}
