#include <stdio.h>
#include <string.h>

//structure declaration

struct s_games
{
    char game_name[30];
    struct scheduled
    {
        char dates[20]; //in the format MM-DD-YY
        char times[20];
    }schld[3];
    int hourly_rate;
};
    
struct groundrecord
{
    char Gname[50];//ground name
    char city[30];
    char state[30];
    struct s_games games[3];
};

//sorting the data according to ground name and city

void merge_self_sorting(struct groundrecord g[],int l,int m,int n)
{
    int i,j,k;
    i=l;
    j=m+1;
    k=l;
    struct groundrecord c[10];
    
    while((i<=m) && (j<=n))
    {
        if(strcmp(g[i].Gname,g[j].Gname)==0)
        {
            if(strcmp(g[i].city,g[j].city)<0)
            {
                c[k]=g[i];
                k++;
                i++;
            }
            else
            {
                c[k]=g[j];
                k++;
                j++;
            }
        }
        else if(strcmp(g[i].Gname,g[j].Gname)<0)
        {
            c[k]=g[i];
            k++;
            i++;
        }
        else
        {
            c[k]=g[j];
            k++;
            j++;
        }
    }
    if(i<=m)
    {
        while(i<=m)
        {
            c[k]=g[i];
            k++;i++;
        }
    }
    else
    {
        while(j<=n)
        {
            c[k]=g[j];
            k++;j++;
        }
    }
    i=l;
    while(i<=n) //copying sorted elements from c to g
    {
        g[i]=c[i];
        i++;
    }
}

void mergesort_sorting(struct groundrecord g[],int l,int h)
{
    int m;
    if(l<h)
    {
        m=(l+h)/2;
        mergesort_sorting(g,l,m);
        mergesort_sorting(g,m+1,h);
        merge_self_sorting(g,l,m,h);
    }
    
}

void sorted_record(struct groundrecord g[])
{
    mergesort_sorting(g,0,7);
    
    for (int i=0;i<8;i++)
    {
        printf("%s\n",g[i].Gname);
        printf("%s\n",g[i].city);
        printf("%s\n",g[i].state);
        for(int j=0;j<3;j++)
        {
            printf("%s\n",g[i].games[j].game_name);
            printf("%d\n",g[i].games[j].hourly_rate);
            for(int k=0;k<3;k++)
            {
                printf("%s\t",g[i].games[j].schld[k].dates);
                printf("%s\t",g[i].games[j].schld[k].times);
                printf("   \t");
            }
            printf("\n");
        }
        printf("\n");
    }
} 

//sort according to games
void bubble_sortgames(struct groundrecord g[])
{
    mergesort_sorting(g,0,7);
    struct s_games temp;
    int i=0;
    int n=3;
    while(i<8)
    {
        int sort=0;
        for(int j=0;j<n-1 && sort!=1;j++)
        {
            sort=1;
            for(int k=0;k<n-j-1;k++)
            {
                if(strcmp(g[i].games[k].game_name,g[i].games[k+1].game_name)>0)
                {
                    temp=g[i].games[k];
                    g[i].games[k]=g[i].games[k+1];
                    g[i].games[k+1]=temp;
                    sort=0;
                }
            }
        }
        i++;
    }
}
//function 1
void getFixturesinCity(struct groundrecord g[],char ncity[],char date1[],char date2[])
{
    int value;
    int i=0;
    while(i<8)
    {
        if(strcmp(ncity,g[i].city)==0)
        {
            for(int j=0;j<3;j++)
            {
                for(int k=0;k<3;k++)
                {
                    if((strcmp(date1,g[i].games[j].schld[k].dates)<0)&&(strcmp(date2,g[i].games[j].schld[k].dates)>0))
                    {
                        printf("%s    ",g[i].Gname);
                        printf("%s\n",g[i].games[j].game_name);
                    }
                }
            }
            
        }
        i++;
    }
    
}

//sort according to date and time_n

void mergeself_datetime(struct groundrecord g[],int l,int m,int n)
{
    int i,j,k;
    i=l;
    j=m+1;
    k=l;
    struct groundrecord c[10];
    
    while((i<=m) && (j<=n))
    {
        if(strcmp(g[i].games[0].schld[0].dates,g[j].games[0].schld[0].dates)==0)
        {
            if(strcmp(g[i].games[0].schld[0].times,g[j].games[0].schld[0].times)>0)
            {
                c[k]=g[i];
                k++;
                i++;
            }
            else
            {
                c[k]=g[j];
                k++;
                j++;
            }
        }
        else if(strcmp(g[i].games[0].schld[0].dates,g[j].games[0].schld[0].dates)>0)
        {
            c[k]=g[i];
            k++;
            i++;
        }
        else
        {
            c[k]=g[j];
            k++;
            j++;
        }
    }
    if(i<=m)
    {
        while(i<=m)
        {
            c[k]=g[i];
            k++;i++;
        }
    }
    else
    {
        while(j<=n)
        {
            c[k]=g[j];
            k++;j++;
        }
    }
    i=l;
    while(i<=n) //copying sorted elements from c to g
    {
        g[i]=c[i];
        i++;
    }
    
}

void mergesort_datetime(struct groundrecord g[],int l,int h)
{
    int m;
    if(l<h)
    {
        m=(l+h)/2;
        mergesort_datetime(g,l,m);
        mergesort_datetime(g,m+1,h);
        mergeself_datetime(g,l,m,h);
    }
}

//function 2

void getFixturesSortedonDate(struct groundrecord g[])
{
    struct s_games temp_1;
    int i=0;
    int n=3;
    while(i<8)
    {
        int sort=0;
        for(int j=0;j<n-1 && sort!=1;j++)
        {
            sort=1;
            for(int k=0;k<n-j-1;k++)
            {
                if(strcmp(g[i].games[k].schld[0].dates,g[i].games[k+1].schld[0].dates)<0)
                {
                    temp_1=g[i].games[k];
                    g[i].games[k]=g[i].games[k+1];
                    g[i].games[k+1]=temp_1;
                    sort=0;
                }
            }
        }
        i++;
    }
    

    mergesort_datetime(g,0,7);
    for(int i=0;i<8;i++)
    {
        printf(" %s \n",g[i].Gname);
        for(int j=0;j<3;j++)
        {
            printf(" %s \n",g[i].games[j].game_name);
            for(int k=0;k<4;k++)
            {
                printf(" %s ",g[i].games[j].schld[k].dates);
                printf(" %s ",g[i].games[j].schld[k].times);
                printf("  \t");
            }
            printf(" \n ");
        }
        printf(" \n ");
    }
    
}

//sort according to state and city

void mergeself_statecity(struct groundrecord g[],int l,int m,int n)
{
    int i,j,k;
    i=l;
    j=m+1;
    k=l;
    struct groundrecord c[10];
    
    while((i<=m) && (j<=n))
    {
        if(strcmp(g[i].state,g[j].state)==0)
        {
            if(strcmp(g[i].city,g[j].city)<0)
            {
                c[k]=g[i];
                k++;
                i++;
            }
            else
            {
                c[k]=g[j];
                k++;
                j++;
            }
        }
        else if(strcmp(g[i].state,g[j].state)<0)
        {
            c[k]=g[i];
            k++;
            i++;
        }
        else
        {
            c[k]=g[j];
            k++;
            j++;
        }
    }
    if(i<=m)
    {
        while(i<=m)
        {
            c[k]=g[i];
            k++;i++;
        }
    }
    else
    {
        while(j<=n)
        {
            c[k]=g[j];
            k++;j++;
        }
    }
    i=l;
    while(i<=n) //copying sorted elements from c to g
    {
        g[i]=c[i];
        i++;
    }
}

void mergesort_statecity(struct groundrecord g[],int l,int h)
{
    int m;
    if(l<h)
    {
        m=(l+h)/2;
        mergesort_statecity(g,l,m);
        mergesort_statecity(g,m+1,h);
        mergeself_statecity(g,l,m,h);
    }
}
// function 3
void isAvailable(char game_n[],char date_n[],char time_n[],struct groundrecord g[])
{
    mergesort_sorting(g,0,7);
    mergesort_statecity(g,0,7);
    int i=0;
    int count=0;
    int x=0;
    while(i<8)
    {
        int flag1=1;
        int flag=1;
        for(int j=0;j<3 && flag==1;j++)
        {
            if(strcmp(game_n,g[i].games[j].game_name)==0)
            {
                x++;
                flag=0;
                for(int k=0;k<3 && flag1==1;k++)
                {
                    if(strcmp(date_n,g[i].games[j].schld[k].dates)==0)
                    {
                        if(strcmp(time_n,g[i].games[j].schld[k].times)==0)
                        {
                           count=0;
                           flag1=0;
                        }
                        else
                        {
                            count=count+1;
                        }
                    }
                    else
                    {
                        count=count+1;
                    }
                }
                
                if(count!=0)
                {
                    printf("%s\n",g[i].Gname);
                    printf("%s\n",g[i].state);
                    printf("%s\n",g[i].city);
                    printf("\n");
                }
                
            }
        }
        i++;
    }
    if(x==0)
    {
        printf("enter a valid game");
    }
}
// search for ground name
int binsearch_Gname(struct groundrecord g[],int size,char ground_n[])
{
    int i,found,ret_value,lo,mid,hi;
    lo=0;hi=size-1;found=0;ret_value=-1;
    while((lo<=hi) && found==0)
    {
        mid=(lo+hi)/2;
        if(strcmp(ground_n,g[mid].Gname)==0)
        {
            found=1;
            ret_value=mid;
        }
        else if(strcmp(ground_n,g[mid].Gname)<0)
        {
            hi=mid-1;
        }
        else
        {
            lo=mid+1;
        }
    }
    return ret_value;
}

//function 4
void UniqueSports(struct groundrecord g[],char ground_n[],char city_n[])
{
    int val;
    mergesort_sorting(g,0,7);
    val=binsearch_Gname(g,8,ground_n);
    int flag2=1;
    int k=0;
    for(int j=0;j<3;j++)
    {
        flag2=1;
        int i=0;
        while(i<8 && flag2==1)
        {
            if(i!=val)
            {
                if(strcmp(g[i].city,city_n)==0)
                {
                    for(int k=0;k<3 &&flag2==1;k++)
                    {
                        if(strcmp(g[val].games[j].game_name,g[i].games[k].game_name)==0)
                        {
                            flag2=0;
                        }
                    }
                }
            }
            i++;
        }
        if(flag2==1)
        {
            k++;
            printf("%s\n",g[val].games[j].game_name);
        }
    }
    
}

//function 5
void FindLocationsForGameInTimeRange (char g_game[],char g_date1[],char g_date2[],char g_time[],struct groundrecord g[])
{
    mergesort_sorting(g,0,7);
    mergesort_statecity(g,0,7);
    int i=0;
    int count=0;
    int x=0;
    while(i<8)
    {
        int flag1=1;
        int flag=1;
        for(int j=0;j<3 && flag==1;j++)
        {
            if(strcmp(g_game,g[i].games[j].game_name)==0)
            {
                //x++;
                flag=0;
                for(int k=0;k<3 && flag1==1;k++)
                {
                    if(strcmp(g_date1,g[i].games[j].schld[k].dates)<0 && strcmp(g_date2,g[i].games[j].schld[k].dates)>0)
                    {
                        if(strcmp(g_time,g[i].games[j].schld[k].times)==0)
                        {
                           count=0;
                           flag1=0;
                        }
                        else
                        {
                            count=count+1;
                        }
                    }
                    else
                    {
                        count=count+1;
                    }
                }
                
                if(count!=0)
                {
                    printf("%s\n",g[i].Gname);
                    printf("%s\n",g[i].state);
                    printf("%s\n",g[i].city);
                    printf("\n");
                }
                
            }
        }
        i++;
    }
    //if(x==0)
    //{
       // printf("enter a valid game");
    //}
}

//function 6
void ClashOfMatches (struct groundrecord g[],char List_of_grounds[][30],char date_u[],char game_u[],int m)
{
    mergesort_sorting(g,0,7);
    int val;
    int count=0;
    int flag5;
    char e_Gname[10][20];
    int b=0;
    for(int a=0;a<m;a++)
    {
        flag5=1;
        val=binsearch_Gname(g,8,List_of_grounds[a]);
        for(int j=0;j<3 && flag5==1;j++)
        {
           if(strcmp(game_u,g[val].games[j].game_name)==0)
           {
               for(int k=0;k<3 && flag5==1;k++)
               {
                   if(strcmp(date_u,g[val].games[j].schld[k].dates)==0)
                   {
                       count++;
                       flag5=0;
                       strcpy(e_Gname[b],g[val].Gname);
                       b++;
                   }
               }
           }
        }
    }
    if(count==1)
    {
        printf("no clash of matches for given game in given grounds");
    }
    else
    {
        printf("there are clash of matches between the following ground for given game on given date\n");
        for(int h=0;h<b;h++)
        {
            printf("%s\t",e_Gname[h]);
        }
    }
    
}

//function 7
void GiveListOfGroundsHavingAtLeastKMatches (struct groundrecord g[],char game_list[][20],char city_g[],char date_g[],int k,int n)
{
    int i=0;
    int flag4;
    int count=0;
    int x=0;
    while(i<8)
    {
        count=0;
        if(strcmp(city_g,g[i].city)==0)
        {
            for(int j=0;j<3;j++)
            {
                flag4=1;
                for(int m=0;m<n && flag4==1;m++)
                {
                    if(strcmp(g[i].games[j].game_name,game_list[m])==0)
                    {
                        for(int k=0;k<3 && flag4==1;k++)
                        {
                            if(strcmp(date_g,g[i].games[j].schld[k].dates)==0)
                            {
                                count++;
                                flag4=0;
                            }
                        }
                    }
                }
            }
        }
        if(count>=k)
        {
            x++;
            printf("%s\n",g[i].Gname);
        }
        i++;
    }
    if(x==0)
    {
        printf("no such ground is there");
    }
}

// sort according to price of game in ground
void mergeself_price(struct groundrecord g[],int l,int m,int n)
{
    int i,j,k;
    i=l;
    j=m+1;
    k=l;
    struct groundrecord c[8];
    
    while((i<=m) && (j<=n))
    {
        
        if(g[i].games[0].hourly_rate<g[j].games[0].hourly_rate)
        {
            c[k]=g[i];
            k++;
            i++;
        }
        else
        {
            c[k]=g[j];
            k++;
            j++;
        }
    }
    if(i<=m)
    {
        while(i<=m)
        {
            c[k]=g[i];
            k++;i++;
        }
    }
    else
    {
        while(j<=n)
        {
            c[k]=g[j];
            k++;j++;
        }
    }
    i=l;
    while(i<=n) //copying sorted elements from c to g
    {
        g[i]=c[i];
        i++;
    }
}
void mergesort_price(struct groundrecord g[],int l,int h)
{
    int m;
    if(l<h)
    {
        m=(l+h)/2;
        mergesort_price(g,l,m);
        mergesort_price(g,m+1,h);
        mergeself_price(g,l,m,h);
    }
}
//function 8
void SortOnPriceForAGame (struct groundrecord g[],char gamename[],char gdate[],char gtime[])
{
   struct groundrecord temp[8];
   int count=0;
   int flag3=1;
   int i=0;
   while(i<8)
   {
       flag3=1;
       for(int j=0;j<3 && flag3==1;j++)
       {
           if(strcmp(gamename,g[i].games[j].game_name)==0)
           {
               for(int k=0;k<3 && flag3==1;k++)
               {
                   if(strcmp(gdate,g[i].games[j].schld[k].dates)==0)
                   {
                       if(strcmp(gtime,g[i].games[j].schld[k].times)==0)
                       {
                           strcpy(temp[count].Gname,g[i].Gname);
                           strcpy(temp[count].city,g[i].city);
                           strcpy(temp[count].state,g[i].state);
                           temp[count].games[0]=g[i].games[j];
                           count++;
                           flag3=0;
                       }
                   }
                }
            }
       }
       i++;
   }
   
   mergesort_price(temp,0,count-1);
   for(int a=0;a<count;a++)
   {
       printf("%s\n",temp[a].Gname);
   }
   
}


void main()
{
    int n;
    //input of ground records
    //number of ground records are 8
    
    struct groundrecord g[8]=
    {
        {
            .Gname="chinnaswamy_stadium",.city="bangalore",.state="karnataka",
            .games[0].game_name="cricket",.games[0].hourly_rate=2000,.games[0].schld[0].dates="11-05-23",.games[0].schld[0].times="10-13",
            .games[0].schld[1].dates="11-15-23",.games[0].schld[1].times="10-13",.games[0].schld[2].dates="12-01-23",.games[0].schld[2].times="14-17",
            .games[1].game_name="football",.games[1].hourly_rate=1000,.games[1].schld[0].dates="11-15-23",.games[1].schld[0].times="14-17",
            .games[1].schld[1].dates="11-20-23",.games[1].schld[1].times="14-17",.games[1].schld[2].dates="12-05-23",.games[1].schld[2].times="14-17",
            .games[2].game_name="badminton",.games[2].hourly_rate=1000,.games[2].schld[0].dates="11-10-23",.games[2].schld[0].times="10-13",
            .games[2].schld[1].dates="11-24-23",.games[2].schld[1].times="14-17"
        },
        {
            .Gname="rajivgandhi_stadium",.city="hyderabad",.state="telangana",
            .games[0].game_name="cricket",.games[0].hourly_rate=1500,.games[0].schld[0].dates="11-12-23",.games[0].schld[0].times="10-13",
            .games[0].schld[1].dates="11-15-23",.games[0].schld[1].times="10-13",.games[0].schld[2].dates="12-05-23",.games[0].schld[2].times="14-17",
            .games[1].game_name="basketball",.games[1].hourly_rate=1000,.games[1].schld[0].dates="12-10-23",.games[1].schld[0].times="10-13",
            .games[1].schld[1].dates="12-20-23",.games[1].schld[1].times="14-17",.games[1].schld[2].dates="12-25-23",.games[1].schld[2].times="14-17"
        },
        {
            .Gname="mgr_stadium",.city="chennai",.state="tamilnadu",
            .games[0].game_name="football",.games[0].hourly_rate=1000,.games[0].schld[0].dates="11-18-23",.games[0].schld[0].times="10-13",
            .games[0].schld[1].dates="11-23-23",.games[0].schld[1].times="10-13",.games[0].schld[2].dates="12-01-23",.games[0].schld[2].times="14-17",
            .games[1].game_name="athletics",.games[1].hourly_rate=1000,.games[1].schld[0].dates="11-07-23",.games[1].schld[0].times="10-13",
            .games[1].schld[1].dates="11-17-23",.games[1].schld[1].times="14-17"
        },
        {
            .Gname="chepauk",.city="chennai",.state="tamilnadu",
            .games[0].game_name="cricket",.games[0].hourly_rate=1500,.games[0].schld[0].dates="12-15-23",.games[0].schld[0].times="10-13",
            .games[0].schld[1].dates="12-23-23",.games[0].schld[1].times="14-17",
            .games[1].game_name="rugby",.games[1].hourly_rate=1000,.games[1].schld[0].dates="12-07-23",.games[1].schld[0].times="10-13",
            .games[1].schld[1].dates="12-23-23",.games[1].schld[1].times="14-17"
        },
        {
            .Gname="rsi_ground",.city="bangalore",.state="karnataka",
            .games[0].game_name="football",.games[0].hourly_rate=1000,.games[0].schld[0].dates="11-15-23",.games[0].schld[0].times="9-12",
            .games[0].schld[1].dates="11-18-23",.games[0].schld[1].times="14-17",
            .games[1].game_name="athletics",.games[1].hourly_rate=1000,.games[1].schld[0].dates="12-07-23",.games[1].schld[0].times="10-13"
        },
        {
            .Gname="gachibowli",.city="hyderabad",.state="telangana",
            .games[0].game_name="cricket",.games[0].hourly_rate=1500,.games[0].schld[0].dates="11-12-23",.games[0].schld[0].times="14-17",
            .games[0].schld[1].dates="11-25-23",.games[0].schld[1].times="10-13",
            .games[1].game_name="tennis",.games[1].hourly_rate=1000,.games[1].schld[0].dates="11-14-23",.games[1].schld[0].times="10-13",
            .games[1].schld[1].dates="11-17-23",.games[1].schld[1].times="14-17"
        },
        {
            .Gname="vca_stadium",.city="nagpur",.state="maharashtra",
            .games[0].game_name="cricket",.games[0].hourly_rate=1500,.games[0].schld[0].dates="12-11-23",.games[0].schld[0].times="10-13",
            .games[0].schld[1].dates="12-15-23",.games[0].schld[1].times="10-13",.games[0].schld[2].dates="12-17-23",.games[0].schld[2].times="14-17"
        },
        {
            .Gname="sardarpatel_stadium",.city="adilabad",.state="telangana",
            .games[0].game_name="cricket",.games[0].hourly_rate=1000,.games[0].schld[0].dates="11-15-23",.games[0].schld[0].times="9-12",
            .games[0].schld[1].dates="11-19-23",.games[0].schld[1].times="10-13",.games[0].schld[2].dates="11-21-23",.games[0].schld[2].times="14-17",
            .games[1].game_name="vollyball",.games[1].hourly_rate=700,.games[1].schld[0].dates="12-14-23",.games[1].schld[0].times="9-12",
            .games[1].schld[1].dates="12-17-23",.games[1].schld[1].times="14-17"
        }
        
    };
     
        
    printf("available options for you are:\n");
    printf("1.sort the data on basis of ground-name and city\n");
    printf("2.Lists the games scheduled in the city sorted according to the ground name and sport name\n");
    printf("3.list of grounds sorted according to the date and time\n");
    printf("4.list of grounds available on the date and time sorted according to the state and city names\n");
    printf("5.List of sports taking place on a ground which are unique (do not happen on other grounds) in the city\n");
    printf("6.List of grounds (with their cities) where a particular game can be scheduled to be played at a particular time\n");
    printf("7.List all the clashing matches for a given game on a given date among the list-of-grounds input\n");
    printf("8.List of grounds in the city having atleast K matches in total on a given day for any of the games in the list\n");
    printf("9.List of grounds sorted based on the prices for the given game on given date and time.\n");
    
    printf("enter the number corresponding to your desired option");
    scanf("%d",&n);
    
  switch (n)
  {
    case 1:
        sorted_record(g);
        break;
    case 2:
    
        char ncity[30];
        char date_1[10],date_2[10];
        printf("enter the city name:");
        scanf("%s",ncity);
        printf("enter first date(in the for MM-DD-YY):");
        scanf("%s",date_1);
        printf("enter second date(in the for MM-DD-YY):");
        scanf("%s",date_2);
        
        bubble_sortgames(g);
        getFixturesinCity(g,ncity,date_1,date_2);
        break;
    
    case 3:
    
        getFixturesSortedonDate(g);
        break;
    
    case 4:
    
        char game_n[20];
        char date_n[10];
        char time_n[10];
        printf("enter name of game:");
        scanf("%s",game_n);
        printf("enter date(in the for MM-DD-YY):");
        scanf("%s",date_n);
        printf("enter time interval:");
        scanf("%s",time_n);
        
        isAvailable(game_n,date_n,time_n,g);
        break;
    
    case 5:
    
        char ground_n[30];
        char city_n[20];
        printf("enter ground name:");
        scanf("%s",ground_n);
        printf("enter city name:");
        scanf("%s",city_n);
        
        UniqueSports(g,ground_n,city_n);
        break;
    
    case 6:
    
        char g_game[20];
        char g_date1[10];
        char g_date2[10];
        char g_time[10];
        printf("enter name of game:");
        scanf("%s",g_game);
        printf("enter 1st date(in the for MM-DD-YY):");
        scanf("%s",g_date1);
        printf("enter 2nd date(in the for MM-DD-YY):");
        scanf("%s",g_date2);
        printf("enter time interval:");
        scanf("%s",g_time);
        
        FindLocationsForGameInTimeRange ( g_game, g_date1, g_date2,g_time, g);
        break;
    
    case 7:
    
        int m;
        char List_of_grounds[10][30];
        char date_u[10];
        char game_u[20];
        
        printf("enter the game name:");
        scanf("%s",game_u);
        printf("enter date(in the format MM-DD-YY):");
        scanf("%s",date_u);
        printf("enter the no of ground you want to check:");
        scanf("%d",&m);
        printf("enter ground names:");
        for(int a=0;a<m;a++)
        {
            scanf("%s",List_of_grounds[a]);
        }
        
        ClashOfMatches (g, List_of_grounds,date_u,game_u, m);
        break;
    
    case 8:
    
        char game_list[10][20];
        char date_g[10];
        char city_g[20];
        int k,n;
        printf("enter the value of k:");
        scanf("%d",&k);
        printf("enter city name:");
        scanf("%s",city_g);
        printf("enter the date:(in the format MM-DD-YY):");
        scanf("%s",date_g);
        printf("enter the no of games you want to search:");
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            scanf("%s",game_list[i]);
        }
        
        GiveListOfGroundsHavingAtLeastKMatches ( g,game_list,city_g, date_g, k, n);
        break;
    
    case 9:
    
       char gamename[30];
       char gdate[20];
       char gtime[20];
       printf("enter game name:");
       scanf("%s",gamename);
       printf("enter date(in the for MM-DD-YY):");
       scanf("%s",gdate);
       printf("enter time interval:");
       scanf("%s",gtime);
       
       SortOnPriceForAGame ( g,gamename,gdate,gtime);
       break;
  }  
    
}












