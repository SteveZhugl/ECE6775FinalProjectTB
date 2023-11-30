import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
from matplotlib.lines import Line2D

# Data for the bar plot (first subplot)
bar_data = {
    "x": ['I4 O20', 'I4 O8', 'I6 O20', 'I6 O8', 'I8 O20', 'I8 O8', 'Float',
          'I4 O20', 'I4 O8', 'I6 O20', 'I6 O8', 'I8 O20', 'I8 O8', 'Float',
          'I4 O20', 'I4 O8', 'I6 O20', 'I6 O8', 'I8 O20', 'I8 O8', 'Float',
          'I4 O20', 'I4 O8', 'I6 O20', 'I6 O8', 'I8 O20', 'I8 O8', 'Float'],
    "y": [7, 5, 10, 7, 12, 10, 40, 0, 0, 0, 0, 0, 0, 0, 3,3,3,3,3,3,2, 0,0,0,0,0,0,2],
    "Design": ["BRAM", "BRAM", "BRAM", "BRAM", "BRAM", "BRAM", "BRAM", "FF", "FF", "FF", "FF", "FF", "FF", "FF", "LUT", "LUT", "LUT", "LUT", "LUT", "LUT", "LUT", "DSP", "DSP", "DSP", "DSP", "DSP", "DSP", "DSP"]
}

# # Data for the line plot (second subplot)
line_data = {
    "x": ['I4 O20', 'I4 O8', 'I6 O20', 'I6 O8', 'I8 O20', 'I8 O8', 'Float'],
    "y": [772.583, 347.351, 46.46, 84.1797, 46.46, 84.1797, 0]
}

# Load data into DataFrame objects
df_bar = pd.DataFrame(bar_data)
df_line = pd.DataFrame(line_data)

new_palette = ['skyblue', 'lightgreen', 'lightcoral', 'gray', 'pink']

sns.set_context('notebook', font_scale=1.2)
sns.set_style('whitegrid')

# Create a figure with 1 row and 2 columns for subplots
fig, axs = plt.subplots(1, 2, figsize=[16, 6])

# Plot the first subplot (bar plot) on axs[0]
ax = sns.barplot(data=df_bar, x="x", y="y", hue="Design", palette=new_palette, ax=axs[0])
for p in ax.patches:
    ax.annotate(str(p.get_height()), (p.get_x() + p.get_width() / 2., p.get_height()), ha='center', va='center',
                xytext=(0, 5), textcoords='offset points', fontsize=8)

legend_elements = [Line2D([0], [0], color='skyblue', lw=10, label='Line'),
                   Line2D([0], [0], color='lightgreen', lw=10, label='Line'),
                   Line2D([0], [0], color='lightcoral', lw=10, label='Line'),
                   Line2D([0], [0], color='gray', lw=10, label='Line'),
                   Line2D([0], [0], color='pink', lw=10, label='Line')]
labels = ["BRAM", "FF", "LUT", "DSP"]
ax.legend(handles=legend_elements, labels=labels, loc='upper center', ncol=len(labels), bbox_to_anchor=(0.5, -0.15),
          fancybox=True)

ax.set_ylim(0, 45)
ax.set_title('Resource Usage across Data Precisions', fontsize=15)
ax.set_xlabel('Data Precision', fontsize=15)
ax.set_ylabel('Resource Usage (%)', fontsize=15)

# Plot the second subplot (line plot) on axs[1]
# Plot the second subplot (line plot) on axs[1]
axs[1].plot(df_line["x"], df_line["y"], marker='o', color='orange', linewidth=2, markersize=8)

# Labeling points on the line plot
for i, txt in enumerate(df_line["y"]):
    axs[1].annotate(f"{txt:.2f}", (df_line["x"][i], txt), textcoords="offset points", xytext=(0,5), ha='center', fontsize=8)

axs[1].set_title('Accuracy Difference Compared to Float', fontsize=15)
axs[1].set_xlabel('Data Precision', fontsize=15)
axs[1].set_ylabel('Accuracy (% Difference)', fontsize=15)
axs[1].set_ylim(0, 1000)

# Legend for the line plot
accuracy_legend = Line2D([0], [0], marker='o', color='w', markerfacecolor='orange', markersize=8, label='Accuracy (Line Plot)')
axs[1].legend(handles=[accuracy_legend], loc='upper right')


# Adjust layout and save the figure
plt.tight_layout()
plt.savefig("combined_plot.png")
