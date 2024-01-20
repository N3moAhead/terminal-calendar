#include <stdio.h>
#include <time.h>

void print_cols()
{
  printf("Mo Tu We Th Fr Sa Su\n");
}

int get_days_offset(int month, int year)
{
  if (month < 3) {
    month += 12;
    year--;
  }
  int k = year % 100;
  int j = year / 100;
  int day_of_week = (1 + 13 * (month + 1) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
  int iso_day_of_week = (day_of_week + 5) % 7;

  return iso_day_of_week;
}

void print_month_name(struct tm *now)
{
  char month_names[12][4] = {
      "Jan",
      "Feb",
      "Mar",
      "Apr",
      "May",
      "Jun",
      "Jul",
      "Aug",
      "Sep",
      "Oct",
      "Nov",
      "Dec",
  };
  printf("%s", month_names[now->tm_mon]);
}

int get_days_in_month(int month, int year)
{
  // Feburary is speacial causing to leap years
  if (month == 2) {
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
      return 29;
    else
      return 28;
  }
  int days[12] = {31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  return days[month - 1];
}

void print_days(struct tm *now)
{
  // Print offset
  int current_day_of_week = get_days_offset(now->tm_mon + 1, now->tm_year + 1900);
  for (int i = 0; i < current_day_of_week; i++) {
    printf("   ");
  }
  for (int i = 1; i <= get_days_in_month(now->tm_mon + 1, now->tm_year + 1900); i++) {
    if (i == now->tm_mday)
      printf("\x1b[7m%2d\x1b[0m ", i);
    else
      printf("%2d ", i);
    if (++current_day_of_week == 7)
    {
      printf("\n");
      current_day_of_week = 0;
    }
  }
  printf("\n");
}

int main()
{
  time_t t;
  struct tm *now;
  t = time(NULL);
  now = localtime(&t);

  printf("      ");
  print_month_name(now);
  printf("-%04d\n", now->tm_year + 1900);
  print_cols();
  print_days(now);
  return 0;
}