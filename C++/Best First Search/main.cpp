#include <iostream>
#include <vector>
#include <stack>
#include <memory>
#include <algorithm>
#include <chrono>
#include <queue>


enum class Heuristic {H1, H2, H3};

struct ReturnValues;
struct State;

void solver(Heuristic h, size_t n);

auto best_first_search(State& start_state, size_t n, void (*heuristic_function)(State& state, size_t n));

void count_attacks(State& state, size_t n);
void construction_heuristic(State& state, size_t n);
void manhattan_distance(State& state, size_t n);

bool conflict_checker(const std::vector<int>& check_board);
auto generate_children(const State& base_state, size_t n);
void print_board(const std::vector<int>& board);



// *********************************************************************************************************************
int main()
{
    solver(Heuristic::H1, 8);
    solver(Heuristic::H2, 8);
    solver(Heuristic::H3, 8);

    return 0;
}
// *********************************************************************************************************************



struct State
{
    int h{};
    std::vector<int> board{};

    bool operator < (const State& other) const
    {
        return h > other.h;
    }
};


struct ReturnValues
{
    size_t closed_size{}, open_size{};
    std::vector<int> solution;
};


auto generate_children(const State& base_state, size_t n)
{
    /// (pointer to) vector that stores children of specific state (boards with queens)
    auto children = std::make_shared<std::vector<State>>(n, base_state);

    int y = 0;
    for (auto& element_x : *children)
    {
        element_x.board.push_back(y);
        ++y;
    }
    return children;
}


auto best_first_search(State& start_state, size_t n, void (*heuristic_function)(State& state, size_t n))
{
    std::vector<State> closed;
    std::priority_queue<State> open;

    open.push(start_state);

    while (not open.empty())
    {
        auto current_state = open.top();
        open.pop();

        if (current_state.board.size() == n and not conflict_checker(current_state.board))
            return ReturnValues{closed.size(), open.size(), current_state.board};

        /// checking if new children can be generated
        if (current_state.board.size() < n)
        {
            /// 'tmp' points to a vector of 'states'
            auto tmp = generate_children(current_state, n);

            /// checking if every child of 'current_state' is not already in 'closed
            for (auto& element : *tmp)
            {
                heuristic_function(element, n);
                open.push(element);
            }
        }
        closed.push_back(current_state);
    }
    return ReturnValues{};
}


void count_attacks(State& state, size_t n)
{
    for (int i = static_cast<int>(state.board.size() - 2); i >= 0; --i)
        if (state.board[i] == state.board.back() or std::abs(i - static_cast<int>(state.board.size() - 1)) == std::abs(state.board[i] - state.board.back()))
            state.h += n;
}


void construction_heuristic(State& state, size_t n)
{
    count_attacks(state, n);

    int board_middle = static_cast<int>(state.board.size() / 2);
    state.h += std::abs(board_middle - state.board.back());
}


void manhattan_distance(State& state, size_t n)
{
    count_attacks(state, n);
    for (int i = static_cast<int>(state.board.size() - 2); i >= 0; --i)
        state.h += std::abs(3 - std::abs(i - static_cast<int>(state.board.size() - 1)) + std::abs(state.board[i] - state.board.back()));
    state.h += static_cast<int>(n - state.board.size());
}


void solver(Heuristic h, size_t n)
{
    ReturnValues return_values;
    State state;

    auto start = std::chrono::high_resolution_clock::now();

    switch (h)
    {
        case Heuristic::H1:
            std::cout << "HEURISTIC H1\n";
            return_values = best_first_search(state, n, count_attacks);
            break;
        case Heuristic::H2:
            std::cout << "HEURISTIC H2\n";
            return_values = best_first_search(state, n, construction_heuristic);
            break;
        case Heuristic::H3:
            std::cout << "HEURISTIC H3\n";
            return_values = best_first_search(state, n, manhattan_distance);
            break;
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    double seconds = duration.count();

    for (const auto& element : return_values.solution)
        std::cout << element << ", ";
    std::cout << std::endl;
    print_board(return_values.solution);

    std::cout << "Statystyki:" << std::endl;
    std::cout << "dlugosc listy open: " << return_values.open_size << std::endl;
    std::cout << "dlugosc listy closed: " << return_values.closed_size << std::endl;
    std::cout << "czas wykonania: " << seconds << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;
}


bool conflict_checker(const std::vector<int>& check_board)
{
    for (int i = 0; i < check_board.size(); ++i)
        for (int j = i + 1; j < check_board.size(); ++j)
            if (check_board[i] == check_board[j] or std::abs(i - j) == std::abs(check_board[i] - check_board[j]))
                return true;
    return false;
}


void print_board(const std::vector<int>& board)
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