#ifndef MAKE_UNIQUE_H
#define MAKE_UNIQUE_H

#include <memory>
#include <utility>

/**
 * @brief Creates a unique pointer to a new object.
 * @tparam T The type of object to create.
 * @tparam Args The types of arguments to pass to the object constructor.
 * @param args The arguments to pass to the object constructor.
 * @return A unique pointer to the created object.
 */
template <typename T, typename... Args>
std::unique_ptr<T> make_unique_ptr(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif // MAKE_UNIQUE_H