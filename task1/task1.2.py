from random import randrange

def check(a):
    for v in a:
        if v == 0:
            return True

    return False

people_count = [i for i in range(3, 21)]
people_count.extend([10**i for i in range(2, 6)])

# 0 - прародитель
# n+1 = people_count[i]

pokol_count = [i for i in range(1, 11)]

ans = [[0.0 for _ in range(len(pokol_count))] for _ in range(len(people_count))]
real_ans = [[0.0 for _ in range(len(pokol_count))] for _ in range(len(people_count))]

generate_count = 10000

for people_ind in range(len(people_count)):
    for pokol_ind in range(len(pokol_count)):
        n = people_count[people_ind]
        s = 2 ** pokol_count[pokol_ind] - 1
        real_ans[people_ind][pokol_ind] = ((n-3) / (n-1)) ** s
real_ans[0][0] = 1

for people_ind in range(len(people_count)):
    for pokol_ind in range(len(pokol_count)):
        cnt_vins = 0
        for iter in range(generate_count):
            cnt = 1
            tmp_used = [0]
            future_used = []

            for i in range(pokol_count[pokol_ind]):
                for elem in tmp_used:
                    used = [elem]
                    for j in range(2):
                        # генерируем среди всех кроме себя
                        x = randrange(people_count[people_ind]-1)
                        while x in used:
                            x = (x+1) % (people_count[people_ind])
                        used.append(x)
                        future_used.append(x)

                if check(future_used):
                    cnt = 0
                    break

                tmp_used = future_used
                future_used = []

            cnt_vins+=cnt

        ans[people_ind][pokol_ind] = cnt_vins / generate_count

def write_result(file, table):
    with open(file, 'w', encoding='utf-8') as f:
        COL_WIDTH = 10

        header = f"{'people_cnt':>{COL_WIDTH}} |"
        for pokol_ind in pokol_count:
            col_text = f"покол.{pokol_ind:2d}"
            header += f"{col_text:^{COL_WIDTH}} |"
        f.write(header + "\n")

        separator = "-" * (COL_WIDTH+1) + "+"
        for _ in range(len(pokol_count)):
            separator += "-" * (COL_WIDTH+1) + "+"
        f.write(separator + "\n")

        for i, people_ind in enumerate(people_count):
            line = f"{people_ind:>{COL_WIDTH}} |"
            for j in range(len(pokol_count)):
                line += f"  {table[i][j]:.4f}   |"
            f.write(line + "\n")


write_result('task1.2.result.txt', ans)

write_result('task1.2.analitic_result.txt', real_ans)

delta = [[abs(ans[i][j] - real_ans[i][j]) for j in range(len(pokol_count))]
         for i in range(len(people_count))]

write_result('task1.2.delta_results.txt', delta)