from random import shuffle
import math

# проверяем подходит ли перестановка под условие
def is_valid(p):
    for i in range(len(p)):
        if p[i] == i:
            return False
    return True


people_count = [i for i in range(1, 11)]
people_count.extend([100, 1000, 10000])

ITERATIONS = 100000

ans = [0.0 for _ in range(len(people_count))]

for people_ind in range(len(people_count)):
    n = people_count[people_ind]

    cnt_vins = 0
    # перебор перестановок
    p = list(range(n))
    for _ in range(ITERATIONS):
        shuffle(p)

        if is_valid(p):
            cnt_vins += 1

    ans[people_ind] = (cnt_vins / ITERATIONS)**2


#выводим результаты
def write_result(file, result, name):
    with open(file, 'w', encoding='utf-8') as f:
        COL_WIDTH = 12

        f.write("people_count | " + name + "\n")
        f.write("-" * (COL_WIDTH+1) + "+" + "-" * (len(name)+1) + "\n")

        for i, n_val in enumerate(people_count):
            line = f"{n_val:>{COL_WIDTH}} | {result[i]:.6f}"
            f.write(line + "\n")


write_result('task2.3.result.txt', ans, "answer")

REAL_ANS = 1 / math.e**2
delta = [abs(ans[i] - REAL_ANS) for i in range(len(people_count))]

write_result('task2.3.delta_result.txt', delta, "delta")