#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <pthread.h>
//void waktu(int menit,int detik);
int selesai = 0;

void shuffle(int cards[][4]);

void delay(ms)
{
	clock_t timeDelay= ms+ clock();
	while (timeDelay > clock());
}

void *counter()
{
	int detik, menit = 0,flag;
	while((!kbhit()&&flag==0) && menit != 2)
	{
		if (detik>59)
		{
			detik=0; ++menit;
		}
		
		delay(1000);
		detik +=1;
	}
	
	selesai = 1;
	printf("\nGame Over");
	exit(1);
}

int main ()
{
	int pair[4][4],status[4][4],c,d,h,i,j;
	int ans1,ans2,ans3,ans4;
	int menit,detik,flag;
	int scorer1,scorer2,scorer3,total_scorer;

	for(i=0; i<4; i++)
	{
        for(j=0; j<4; j++)
		{
            status[j][i]=0; //array ,inisisaliasi false semua
    	}
	}

	shuffle(pair);//buat acak angka 
	system("cls");
	
	printf("\n==================================================");
	printf("\n===                                            ===");
	printf("\n===      SELAMAT DATANG DI GAME MATCH UP       ===");
	printf("\n===                                            ===");
	printf("\n==================================================");
	printf("\n Syarat Bermain = ");
	printf("\n - Gantikan [#] dengan angka yang sama!!!");
	printf("\n - Jika [#] yang keluar angka yang berbeda maka ulangi hingga sama!!!");
	printf("\n - Pemain akan di berikan waktu 2 menit untuk menyelesaikan");
	printf("\n - Level Permainan di bagi menjadi 3 tahapan level yaitu :");
	printf("\n\t - Level 1 Pemain haru mengganti [#] dengan 6 angka yang sama");
	printf("\n\t - Level 2 Pemain haru mengganti [#] dengan 12 angka yang sama");
	printf("\n\t - Level 3 Pemain haru mengganti [#] dengan 16 angka yang sama");
	printf("\n\n\n Tekan terserah untuk memulai game!!!");
	
	getch();

	
	awal:
	system("cls");
    // buat contekan, buat debug

    printf("Contekan !!!! \n");
	for (c=0;c<=3;c++)
	{
    	for (d=0;d<=3;d++)
		{
		    printf("[%i]",pair[c][d]);
        }
        printf (" \n");
    }

    printf("\n");

    //end contekan
		
    printf("    1  2  3  4\n");
    for (c=0;c<=3;c++)
	{
    	printf("%d |",c+1);
    	
		for (d=0;d<=3;d++)
		{
            if(status[c][d]==0)
			{
                printf("[#]");
            }
            else if(status[c][d]==1)
				{
                	printf("[%i]",pair[c][d]);
                	h++;
            	}
        }
        printf (" \n");
	}

	if(h==6)
	{
	 	scorer1 = 25;
        goto step2;
	}
	 	step2 :
	if(h==12)
	{
		scorer2 = 25;
		goto step3;
	}
		step3 :
	if(h==16)
	{
		scorer3 = 50;
		goto score3;
	}
	pthread_t timer;
	pthread_create(&timer,NULL,counter,NULL);
		
	menit=0; detik=0; flag=0;


	printf ("Masukkan Baris Kotak Pertama  = ");
    scanf ("%d",&ans1);
    printf ("Masukkan Kolom Kotak Pertama  = ");
    scanf ("%d",&ans2);
    printf ("Masukkan Baris Kotak Kedua  = ");
    scanf ("%d",&ans3);
    printf ("Masukkan Kolom Kotak Kedua  = ");
    scanf ("%d",&ans4);

		printf ("\n");

    status[ans1-1][ans2-1] = 1;
    status[ans3-1][ans4-1] = 1;

	for(c=0;c<=3;c++)
	{
    	for (d=0;d<=3;d++)
		{
            if(status[c][d]==0)
			{
                printf("[#]");
            }
            else
			{
                printf("[%i]",pair[c][d]);
            }
        }
        printf (" \n");
    }
	 printf("\n");
	 Sleep(1000);

if(pair[ans1-1][ans2-1]!=pair[ans3-1][ans4-1])
		{
			status[ans1-1][ans2-1]=0;
			status[ans3-1][ans4-1]=0;
		}
else{
        status[ans1-1][ans2-1]=1;
        status[ans3-1][ans4-1]=1;
    }

	goto awal;
	score:
		printf("\nTahap 1 berhasil dengan score = 25");
	score2: 
		printf("\nTahap 2 berhasil dengan score = 25");
	score3:
		printf("\nTahap 3 berhasil dengan score = 50");
	total :
		total_scorer= scorer1+scorer2+scorer3;
		printf("\nTotal = %d + %d + %d= %d",scorer1,scorer2,scorer3,total_scorer);

	return 0;
}

void shuffle(int cards[][4])
{
    int start[16]={1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
    int s,x,r,c;
    for ( s=0; s<=20; s++)
    {
        for (x=0; x<16; x++)
        {
            srand((unsigned)time(NULL));
            int i=rand()%15+1;
            int temp=start[x];
            start[x]=start[i];
            start[i]=temp;
        }
    }
    int i=0;
    for (r=0; r<4; r++)
        {
            for (c=0; c<4; c++)
            {
                cards[r][c]=start[i];
                printf("cards[r][c]");
                i=i+1;
            }
            printf("/n");
        }
}
