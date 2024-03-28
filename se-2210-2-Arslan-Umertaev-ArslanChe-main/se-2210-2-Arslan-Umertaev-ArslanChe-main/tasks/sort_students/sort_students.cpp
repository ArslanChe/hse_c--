#include "sort_students.h"

#include <tuple>

bool CompareStudentsName(Student first, Student second) {
    return std::tie(first.last_name, first.name, first.birth_date.year, first.birth_date.month, first.birth_date.day) <
           std::tie(second.last_name, second.name, second.birth_date.year, second.birth_date.month,
                    second.birth_date.day);
}

bool CompareStudentsDate(Student first, Student second) {
    return std::tie(first.birth_date.year, first.birth_date.month, first.birth_date.day, first.last_name, first.name) <
           std::tie(second.birth_date.year, second.birth_date.month, second.birth_date.day, second.last_name,
                    second.name);
}

void SortStudents(std::vector<Student>& students, SortKind sort_kind) {
    switch (sort_kind) {
        case SortKind::Date:
            std::sort(students.begin(), students.end(), CompareStudentsDate);
            break;
        case SortKind::Name:

            std::sort(students.begin(), students.end(), CompareStudentsName);
            break;
    }
}