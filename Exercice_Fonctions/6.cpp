#include <iostream>

bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int day_count(int month, int year) {
    if (month < 1 || month > 12 || year < 1) {
        return 0;
    }
    int days_in_month[] = { 31, 28 + (is_leap_year(year) ? 1 : 0), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return days_in_month[month - 1];
}

int main() {
    
    std::cout << day_count(1, 2020) << std::endl; // affiche 31
    std::cout << day_count(2, 2020) << std::endl; // affiche 29
    std::cout << day_count(2, 2021) << std::endl; // affiche 28
    std::cout << day_count(2021, 1) << std::endl; // affiche 0
    return 0;
}