#include <stdio.h>
#include <stdlib.h>

struct structure {
        float latitude;
        float longitude;
        short altitude;
        char name[5];
        char misc;
};

int main()
{
        struct structure data;
        FILE *myFile;

        if ((myFile = fopen("tracks.dat", "rb")) == NULL) {
                printf("Could not open file");
                exit(1);
        }

        while(fread(&data, sizeof (data), 1, myFile) != 0) {
                printf("lat:%.1f long:%.1f alt:%hd", data.latitude, data.longitude, data.altitude);
                printf(" name:");
                for(int i=0;i<5;i++)
                        printf("%c", data.name[i]);

                if((data.misc & 3) == 0)
                        printf(" id:unknown");
                else if((data.misc & 3) == 1)
                        printf(" id:friend");
                else if((data.misc & 3) == 2)
                        printf(" id:foe");
                else if((data.misc & 3) == 3)
                        printf(" id:neutral");

                if(((data.misc & 12) >> 2) == 0)
                        printf(" cat:ship");
                else if(((data.misc & 12) >> 2) == 1)
                        printf(" cat:ground");
                else if(((data.misc & 12) >> 2) == 2)
                        printf(" cat:airplane");

                if(((data.misc & 48) >> 4) == 1)
                        printf(" engaged");

                printf("\n");
        }
        fclose(myFile);
        return(0);
} 
