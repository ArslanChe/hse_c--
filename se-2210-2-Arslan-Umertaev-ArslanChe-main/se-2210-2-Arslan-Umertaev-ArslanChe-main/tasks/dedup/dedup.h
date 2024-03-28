#include <memory>
#include <unordered_map>
#include <vector>

template <class T>
std::vector<std::unique_ptr<T>> Duplicate(const std::vector<std::shared_ptr<T>>& items) {
    std::vector<std::unique_ptr<T>> ans;
    ans.reserve(items.size());
    for (const auto& item : items) {
        ans.push_back(std::make_unique<T>(*item));
    }
    return ans;
}

template <class T>
std::vector<std::shared_ptr<T>> DeDuplicate(const std::vector<std::unique_ptr<T>>& items) {
    std::vector<std::shared_ptr<T>> ans;
    std::unordered_map<T, std::shared_ptr<T>> dop;
    for (const auto& item : items) {
        const T& value = *item;
        auto it = dop.find(value);
        if (it == dop.end()) {
            auto tmp = std::make_shared<T>(value);
            dop[value] = tmp;
            ans.push_back(tmp);
        } else {
            ans.push_back(it->second);
        }
    }

    return ans;
}
