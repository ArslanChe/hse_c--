#include "tests_checking.h"

#include <deque>
std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> submissions{};
    std::vector<std::string> checked;
    checked.reserve(queries.size());
    for (const auto& action : student_actions) {
        if (action.side == Side::Top) {
            submissions.push_front(action.name);
        } else {
            submissions.push_back(action.name);
        }
    }
    for (const auto& query : queries) {
        checked.push_back(submissions[query - 1]);
    }
    return checked;
}
