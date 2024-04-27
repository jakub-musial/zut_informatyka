import numpy as np
import matplotlib.pyplot as plt


def generate_population(pop: int, n: int) -> np.ndarray:
    population_list = []

    for _ in range(pop):
        individual_array = np.random.randint(0, n, size=n)
        population_list.append(individual_array)

    population_array = np.array(population_list)

    return population_array


def evaluate(P: np.ndarray) -> np.ndarray:
    evaluated_population = []

    for individual in P:
        attack_count = 0
        for i in range(individual.size - 1):
            for j in range(i + 1, individual.size):
                if individual[i] == individual[j] or abs(i - j) == abs(individual[i] - individual[j]):
                    attack_count += 1
        evaluated_population.append((individual, attack_count))

    evaluated_population = np.array(evaluated_population, dtype=object)
    return evaluated_population


def selection(P: np.ndarray, tournament_pool_size: int) -> np.ndarray:
    winners = []

    for _ in range(P.shape[0]):
        indexes = np.random.choice(P.shape[0], size=tournament_pool_size, replace=False)
        tournament_pool = P[indexes]
        min_index = np.argmin(tournament_pool[:, 1])
        winner = tournament_pool[min_index]
        winners.append(winner)

    return np.array(winners, dtype=object)


def cross(parent1: np.ndarray, parent2: np.ndarray) -> np.ndarray:
    offspring = parent1.copy()

    for i in range(offspring.size):
        if np.random.choice([0, 1]):
            offspring[i] = parent2[i]

    return offspring


def crossover(P: np.ndarray, pc: float) -> np.ndarray:
    P_crossover = P[:, 0]

    for i in range(0, P_crossover.size - 2, 2):
        if np.random.random() <= pc:
            P_crossover[i] = cross(P_crossover[i], P_crossover[i + 1])

    return P_crossover


def mutate(individual: np.ndarray) -> np.ndarray:
    indexes_to_mutate = np.random.choice(individual.size, size=np.random.randint(1, individual.size), replace=False)
    new_values = np.random.randint(0, individual.size, size=len(indexes_to_mutate))
    individual[indexes_to_mutate] = new_values
    return individual.tolist()


def mutation(P: np.ndarray, pm: float) -> np.ndarray:
    P_mutated = []

    for i in range(P.size):
        if np.random.random() <= pm:
            P_mutated.append(mutate(P[i]))
        else:
            P_mutated.append(P[i].tolist())

    P_mutated = np.array(P_mutated)
    return P_mutated


def draw_board(board: list) -> None:
    for y in range(len(board)-1, -1, -1):
        for x in range(len(board)):
            if board[x] == y:
                print("[Q]", end='')
            else:
                print("[ ]", end='')
        print()


def draw_function(X: list, Y: list, title: str, xlabel: str, ylabel: str) -> None:
    plt.plot(X, Y)
    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid(True)
    plt.show()


def draw_bars(X: list, Y: list) -> None:
    plt.bar(X, Y, color=np.random.rand(len(X), 3))
    plt.title('Zmienność średniej wartości funkcji przystosowania')
    plt.xlabel('Generacje')
    plt.ylabel('Wartość średnia przystosowania')
    plt.grid(axis='y')
    plt.show()


def evolution(n: int, pop: int, gen_max: int, tournament_pool_size: int, pm: float, pc: float) -> (np.ndarray, list, list, list):
    P = generate_population(pop, n)
    P = evaluate(P)
    best = P[np.argmin(P[:, 1])]

    gen = 0
    ff_max = 0

    X = [gen]
    Y = [best[1]]
    mean = [np.mean(P[:, 1])]

    while gen < gen_max and best[1] > ff_max:
        Pn = selection(P, tournament_pool_size)
        Pn = crossover(Pn, pc)
        Pn = mutation(Pn, pm)
        Pn = evaluate(Pn)
        best = Pn[np.argmin(Pn[:, 1])]
        gen += 1

        X.append(gen)
        Y.append(best[1])
        mean.append(np.mean([np.mean(Pn[:, 1])]))

    return best, X, Y, mean



experiment = [(2, 0.9), (2, 0.5), (2, 0.1), (5, 0.9), (5, 0.5), (5, 0.1)]

for e in experiment:
    best, X, Y, mean = evolution(n=6, pop=11, gen_max=10000, tournament_pool_size=e[0], pc=0.9, pm=e[1])

    print("\npm = ", e[1])
    print("\ntournament_pool_size = : ", e[0])
    print("\nLICZBA GENERACJI: ", len(X))
    print("\nNAJLEPSZY OSOBNIK: ", best[0])
    draw_board(best[0])
    print("\nLICZBA BIĆ: ", best[1])
    draw_function(X, Y, 'Wykres Zmienności Funkcji', 'Generacje', 'Wartości funkcji przystosowania')
    draw_function(X, mean, 'Zmienność średniej wartości funkcji przystosowania', 'Generacje', 'Wartość średnia przystosowania')
    draw_bars(X, mean)
    print("--------------------------------------------------------------------------\n")
