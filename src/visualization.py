import seaborn as sns

data = {
    0: {
        "file_path": "../data/big_rectangle_results_type_1.txt",
        "graph_label": "Зависимость приближенного значения от количества точек",
        "line_label": "Приближенное значение площади",
        "save_path": "../images/big_rectangle_graph_type_1.png"
    },
    1: {
        "file_path": "../data/big_rectangle_results_type_2.txt",
        "graph_label": "Зависимость относительного отклонения приближенного значения от количества точек",
        "line_label": "Относительное отклонение приближенного значения",
        "save_path": "../images/big_rectangle_graph_type_2.png"
    },
    2: {
        "file_path": "../data/small_rectangle_results_type_1.txt",
        "graph_label": "Зависимость приближенного значения от количества точек",
        "line_label": "Приближенное значение площади",
        "save_path": "../images/small_rectangle_graph_type_1.png"
    },
    3: {
        "file_path": "../data/small_rectangle_results_type_2.txt",
        "graph_label": "Зависимость относительного отклонения приближенного значения от количества точек",
        "line_label": "Относительное отклонение приближенного значения",
        "save_path": "../images/small_rectangle_graph_type_2.png"
    },
}

for i in range(4):
    x = []
    y = []

    with open(data[i]["file_path"], 'r') as file:
        for line in file:
            values = line.split()
            x.append(float(values[0]))
            y.append(float(values[1]))

    sns.set_theme()
    sns.relplot(
        x=x,
        y=y,
        kind="line",
        height=6,
        aspect=1.5,
    ).set(
        title=data[i]["graph_label"],
        xlabel="Количество точек",
        ylabel="Значение"
    ).fig.savefig(data[i]["save_path"], dpi=500)
