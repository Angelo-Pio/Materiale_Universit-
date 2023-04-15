#include <stdio.h>

struct Data {
    unsigned int day;
    unsigned int month;
    int year;
};

int main(int argc, char const *argv[])
{
    unsigned int day;
    unsigned int month;
    int year;

    scanf("%u/%u/%d",&day,&month,&year);

    struct Data date;

    date.day = day;
    date.month = month;
    date.year = year;

    printf("%u-%u-%d\n",date.day,date.month,date.year);




    return 0;
}
