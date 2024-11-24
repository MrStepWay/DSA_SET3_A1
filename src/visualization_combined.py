import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt

data = {
    0: {
        "file_path": "../data/big_rectangle_results_type_1.txt",
        "graph_label": "Большая прямоугольная область"
    },
    1: {
        "file_path": "../data/big_rectangle_results_type_2.txt",
        "graph_label": "Большая прямоугольная область "
    },
    2: {
        "file_path": "../data/small_rectangle_results_type_1.txt",
        "graph_label": "Меньшая прямоугольная область"
    },
    3: {
        "file_path": "../data/small_rectangle_results_type_2.txt",
        "graph_label": "Меньшая прямоугольная область "
    },
}

all_data = []

for i in range(4):
    x = []
    y = []
    with open(data[i]["file_path"], 'r') as file:
        for line in file:
            values = line.split()
            x.append(float(values[0]))
            y.append(float(values[1]))
    for xi, yi in zip(x, y):
        all_data.append({"X": xi, "Y": yi, "Graph": data[i]["graph_label"]})

df = pd.DataFrame(all_data)
sns.set_theme()
fig, axes = plt.subplots(1, 2, figsize=(14, 6))  # Два столбца, один ряд

sns.lineplot(data=df[df['Graph'].isin([data[0]["graph_label"], data[2]["graph_label"]])],
             x="X", y="Y", hue="Graph", ax=axes[0])
axes[0].set_title("Приближённое значение площади")
axes[0].set_xlabel("Количество точек")
axes[0].set_ylabel("Значение")
axes[0].grid(True, which='both', linestyle='--', linewidth=0.5)  # Настройка сетки
axes[0].minorticks_on()

sns.lineplot(data=df[df['Graph'].isin([data[1]["graph_label"], data[3]["graph_label"]])],
             x="X", y="Y", hue="Graph", ax=axes[1])
axes[1].set_title("Относительное отклонение приближенного значения")
axes[1].set_xlabel("Количество точек")
axes[1].set_ylabel("Значение")
axes[1].grid(True, which='both', linestyle='--', linewidth=0.5)  # Настройка сетки
axes[1].minorticks_on()

fig.tight_layout(pad=3)
plt.savefig("../images/combined_graphs.png", dpi=500)
