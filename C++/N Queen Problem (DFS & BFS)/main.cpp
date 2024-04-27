#include <iostream>
#include <vector>
#include <stack>
#include <memory>
#include <algorithm>
#include <chrono>
#include <queue>
#include <deque>

enum class Type
{
    DFS,
    BFS,
    DFS_OPTIMIZED,
    BFS_OPTIMIZED
};

struct Queen;
struct ReturnValues;

void solver(Type type, size_t n);
bool conflict_checker(const std::vector<Queen> &check_board);
auto generate_children(const std::vector<Queen> &base_board, size_t n) -> std::shared_ptr<std::vector<std::vector<Queen>>>;
bool is_same_board(const std::vector<Queen> &b1, const std::vector<Queen> &b2);
void print_board(const std::vector<Queen> &board);

auto dfs(std::vector<Queen> &start_board, size_t n);
auto bfs(std::vector<Queen> &start_board, size_t n);

auto dfs_optimized(std::vector<int> &start_board, size_t n);
auto bfs_optimized(std::vector<int> &start_board, size_t n);

bool conflict_checker(const std::vector<int> &check_board);
auto generate_children(const std::vector<int> &base_board, size_t n) -> std::shared_ptr<std::vector<std::vector<int>>>;
void print_board(const std::vector<int> &board);

/// *******************************************************************************************************************
int main()
{
    solver(Type::DFS, 4);
    solver(Type::BFS, 4);
    solver(Type::DFS_OPTIMIZED, 8);
    solver(Type::BFS_OPTIMIZED, 8);

    return 0;
}
/// *******************************************************************************************************************

struct Queen
{
    int x, y;
    Queen(int xx, int yy) : x(xx), y(yy) {}

    bool operator==(const Queen &other) const
    {
        return (this->x == other.x and this->y == other.y);
    }
};

struct ReturnValues
{
    size_t closed_size{}, open_size{};
    std::vector<Queen> solution;
    std::vector<int> solution_int;
};

auto dfs(std::vector<Queen> &start_board, size_t n)
{
    std::vector<std::vector<Queen>> closed;
    std::stack<std::vector<Queen>> open;

    open.push(start_board);

    while (not open.empty())
    {
        auto current_state = open.top();
        open.pop();

        if (current_state.size() == n and not conflict_checker(current_state))
        {
            return ReturnValues{closed.size(), open.size(), current_state};
        }

        size_t current_state_size = current_state.size();

        /// checking if new children can be generated
        if (current_state_size < n)
        {
            /// tmp' points to a vector of 'boards
            auto tmp = generate_children(current_state, n);

            /// checking if every child of 'current_state' is not already in 'closed
            for (const auto &element : *tmp)
            {
                auto closed_it = std::find_if(closed.begin(), closed.end(), [element](const std::vector<Queen> &c)
                                              { return is_same_board(element, c); });

                /// checking if 'element' is not in 'closed'. No need to check 'open' in DFS
                if (closed_it == closed.end())
                    open.push(element);
            }
        }
        closed.push_back(current_state);
    }
    return ReturnValues{};
}

auto bfs(std::vector<Queen> &start_board, size_t n)
{
    std::vector<std::vector<Queen>> closed;
    std::deque<std::vector<Queen>> open;

    open.push_back(start_board);

    while (not open.empty())
    {
        auto current_state = open.front();
        open.pop_front();

        if (current_state.size() == n and not conflict_checker(current_state))
            return ReturnValues{closed.size(), open.size(), current_state};

        /// idk why 'if (current_state.size() < n)' is causing memory leak
        size_t current_state_size = current_state.size();

        /// checking if new children can be generated
        if (current_state_size < n)
        {
            /// tmp' points to a vector of 'boards
            auto tmp = generate_children(current_state, n);

            /// checking if every child of 'current_state' is not already in 'closed
            for (const auto &element : *tmp)
            {

                auto closed_it = std::find_if(closed.begin(), closed.end(), [element](const std::vector<Queen> &c)
                                              { return is_same_board(element, c); });

                auto open_it = std::find_if(open.begin(), open.end(), [element](const std::vector<Queen> &c)
                                            { return is_same_board(element, c); });

                /// checks if 'element' isn't in 'closed' and 'open'
                if (closed_it == closed.end() and open_it == open.end())
                    open.push_back(element);
            }
        }
        closed.push_back(current_state);
    }
    return ReturnValues{};
}

auto dfs_optimized(std::vector<int> &start_board, size_t n)
{
    std::vector<std::vector<int>> closed;
    std::stack<std::vector<int>> open;

    open.push(start_board);

    while (not open.empty())
    {
        auto current_state = open.top();
        open.pop();

        if (current_state.size() == n and not conflict_checker(current_state))
            return ReturnValues{closed.size(), open.size(), std::vector<Queen>(), current_state};

        /// idk why 'if (current_state.size() < n)' is causing memory leak
        size_t current_state_size = current_state.size();

        /// checking if new children can be generated
        if (current_state_size < n)
        {
            /// tmp' points to a vector of 'boards
            auto tmp = generate_children(current_state, n);

            for (const auto &element : *tmp)
                open.push(element);
        }
        closed.push_back(current_state);
    }
    return ReturnValues{};
}

auto bfs_optimized(std::vector<int> &start_board, size_t n)
{
    std::vector<std::vector<int>> closed;
    std::queue<std::vector<int>> open;

    open.push(start_board);

    while (not open.empty())
    {
        auto current_state = open.front();
        open.pop();

        if (current_state.size() == n and not conflict_checker(current_state))
        {
            return ReturnValues{closed.size(), open.size(), std::vector<Queen>(), current_state};
        }

        /// idk why 'if (current_state.size() < n)' is causing memory leak
        size_t current_state_size = current_state.size();

        /// checking if new children can be generated
        if (current_state_size < n)
        {
            /// tmp' points to a vector of 'boards
            auto tmp = generate_children(current_state, n);

            /// checking if every child of 'current_state' is not already in 'closed
            for (const auto &element : *tmp)
            {
                open.push(element);
            }
        }
        closed.push_back(current_state);
    }
    return ReturnValues{};
}

void solver(Type type, size_t n)
{
    ReturnValues return_values;

    std::vector<Queen> board;
    std::vector<int> board_optimized;

    auto start = std::chrono::high_resolution_clock::now();
    switch (type)
    {
    case Type::DFS:
        std::cout << "DFS" << std::endl;
        return_values = dfs(board, n);
        break;
    case Type::BFS:
        std::cout << "BFS" << std::endl;
        return_values = bfs(board, n);
        break;
    case Type::DFS_OPTIMIZED:
        std::cout << "DFS OPTIMIZED" << std::endl;
        return_values = dfs_optimized(board_optimized, n);
        break;
    case Type::BFS_OPTIMIZED:
        std::cout << "BFS OPTIMIZED" << std::endl;
        return_values = bfs_optimized(board_optimized, n);
        break;
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    double seconds = duration.count();

    if (type == Type::DFS or type == Type::BFS)
    {
        for (const auto &element : return_values.solution)
            std::cout << "(" << element.x << ", " << element.y << ") ";
        std::cout << std::endl;
        print_board(return_values.solution);
    }
    else
    {
        for (const auto &element : return_values.solution_int)
            std::cout << element << ", ";
        std::cout << std::endl;
        print_board(return_values.solution_int);
    }

    std::cout << "Statystyki:" << std::endl;
    std::cout << "dlugosc listy open: " << return_values.open_size << std::endl;
    std::cout << "dlugosc listy closed: " << return_values.closed_size << std::endl;
    std::cout << "czas wykonania: " << seconds << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;
}

bool conflict_checker(const std::vector<Queen> &check_board)
{
    for (size_t i = 0; i < check_board.size(); ++i)
        for (size_t j = i + 1; j < check_board.size(); ++j)
            if ((check_board[i].x == check_board[j].x) or
                (check_board[i].y == check_board[j].y) or
                (std::abs(check_board[i].x - check_board[j].x) == std::abs(check_board[i].y - check_board[j].y)))
                return true;
    return false;
}

bool conflict_checker(const std::vector<int> &check_board)
{
    for (int i = 0; i < check_board.size(); ++i)
        for (int j = i + 1; j < check_board.size(); ++j)
            if (check_board[i] == check_board[j] or std::abs(i - j) == std::abs(check_board[i] - check_board[j]))
                return true;
    return false;
}

auto generate_children(const std::vector<Queen> &base_board, size_t n) -> std::shared_ptr<std::vector<std::vector<Queen>>>
{
    /// (pointer to) vector that stores children of specific state (boards with queens)
    auto children = std::make_shared<std::vector<std::vector<Queen>>>((n * n) - base_board.size(), base_board);

    int prev_x = 0, prev_y = 0;
    for (auto &element : *children)
    {
        int x = prev_x;
        while (x < n)
        {
            for (int y = prev_y; y < n; ++y)
            {
                auto queen = std::find(element.begin(), element.end(), Queen(x, y));
                if (element.empty() or queen == element.end())
                {
                    element.emplace_back(x, y);
                    prev_y = (y + 1) % static_cast<int>(n);
                    prev_x = (y + 1 > n - 1) ? x + 1 : x;
                    break;
                }
            }
            break;
        }
    }
    return children;
}

auto generate_children(const std::vector<int> &base_board, size_t n) -> std::shared_ptr<std::vector<std::vector<int>>>
{
    /// (pointer to) vector that stores children of specific state (boards with queens)
    auto children = std::make_shared<std::vector<std::vector<int>>>(n, base_board);

    int y = 0;
    for (auto &element_x : *children)
    {
        element_x.push_back(y);
        ++y;
    }
    return children;
}

void print_board(const std::vector<Queen> &board)
{
    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board.size(); ++j)
        {
            /// checks for a 'Queen' at position (i, j)
            auto queen = std::find(board.begin(), board.end(), Queen(i, j));
            if (queen != board.end())
                std::cout << "[Q]";
            else
                std::cout << "[ ]";
        }
        std::cout << std::endl;
    }
}

void print_board(const std::vector<int> &board)
{
    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board.size(); ++j)
        {
            if (board[i] == j)
                std::cout << "[Q]";
            else
                std::cout << "[ ]";
        }
        std::cout << std::endl;
    }
}

bool is_same_board(const std::vector<Queen> &b1, const std::vector<Queen> &b2)
{
    if (b1.size() != b2.size())
        return false;

    return std::is_permutation(b1.begin(), b1.end(), b2.begin());
}
