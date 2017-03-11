#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PLACE_COUNT 12

typedef struct _Seat
{
	int id;
	int taken;
	char first_name[80];
	char last_name[80];
} Seat;

int main()
{
	FILE *flightInfo = fopen("flight.bin", "rb");
	Seat arr[PLACE_COUNT];
	if (flightInfo == NULL)
	{
		for (int i = 0; i < PLACE_COUNT; i++)
		{
			arr[i].id = i + 1;
			arr[i].taken = 0;
			arr[i].first_name[0] = '\0';
			arr[i].last_name[0] = '\0';
		}
	}
	else
	{
		fread(arr, sizeof(Seat), PLACE_COUNT, flightInfo);
		fclose(flightInfo);
	}

	while (1)
	{
		char code;
		printf("a - Show the amount of unbooked places\n");
		printf("b - Show the list of unbooked places\n");
		printf("c - Show the list of booked places\n");
		printf("d - Book place\n");
		printf("e - Unbook place\n");
		printf("f - Quit\n\n");

		scanf(" %c", &code);
		getchar();
		switch (code)
		{
		case 'a':
		{
			int counter = 0;
			for (int i = 0; i < PLACE_COUNT; i++)
				if (!arr[i].taken)
					counter++;
			printf("%d\n", counter);
			break;
		}

		case 'b':
		{
			for (int i = 0; i < PLACE_COUNT; i++)
				if (!arr[i].taken)
					printf("%d\n", i + 1);
			break;
		}

		case 'c':
		{
			for (int i = 0; i < PLACE_COUNT; i++)
				if (arr[i].taken)
					printf("%d\n", i + 1);
			break;
		}

		case 'd':
		{
			int seatCode;
			char firstName[80];
			char lastName[80];
			char confirm;

			printf("Enter the seat code: ");
			scanf("%d", &seatCode);
			getchar();
			if (seatCode < 1 || seatCode > PLACE_COUNT)
			{
				printf("Error: invalid seat code\n");
				break;
			}
			if (arr[seatCode - 1].taken)
			{
				printf("Error: seat already booked\n");
				break;
			}

			printf("Enter your first name: ");
			scanf("%s", firstName);
			getchar();
			printf("Enter your last name: ");
			scanf("%s", lastName);
			getchar();

			printf("You want to book seat #%d for passenger %s %s. Press \'y\' to confirm booking.\n", seatCode, firstName, lastName);
			scanf("%c", &confirm);
			getchar();
			if (confirm == 'y')
			{
				arr[seatCode - 1].taken = 1;
				strcpy(arr[seatCode - 1].first_name, firstName);
				strcpy(arr[seatCode - 1].last_name, lastName);
			}
			break;
		}

		case 'e':
		{
			int seatCode;
			char firstName[80];
			char lastName[80];
			char confirm;

			printf("Enter the seat code: ");
			scanf("%d", &seatCode);
			getchar();
			if (seatCode < 1 || seatCode > PLACE_COUNT)
			{
				printf("Error: invalid seat code\n");
				break;
			}
			if (!arr[seatCode - 1].taken)
			{
				printf("Error: seat not booked\n");
				break;
			}
			
			printf ("Enter your first name: ");
                        scanf("%s", firstName);
                        getchar();
			if (strcmp(firstName, arr[seatCode - 1].first_name) != 0)
			{
                                printf("Error: incorrect first name\n");
                                break;
                        }	
                        printf("Enter your last name: ");
                        scanf("%s", lastName);
                        getchar();
			if (strcmp(lastName, arr[seatCode - 1].last_name) != 0)
                        {
                                printf("Error: incorrect last name\n");
                                break;
                        }

         		printf("You want to unbook seat #%d for passenger %s %s. Press \'y\' to confirm unbooking.\n", seatCode, firstName, lastName);
                        scanf("%c", &confirm);
                        getchar();
			if (confirm == 'y')
				arr[seatCode - 1].taken = 0;
			break;
		}

		case 'f':
		{
			FILE *outputFile = fopen("flight.bin", "wb");
			fwrite(arr, sizeof(Seat), PLACE_COUNT, outputFile);
			fclose(outputFile);
			return 0;
		}

		default:
			printf("Error: incorrect operation\n");
			break;
		}

		printf("\n");
	}
	return 0;
} 