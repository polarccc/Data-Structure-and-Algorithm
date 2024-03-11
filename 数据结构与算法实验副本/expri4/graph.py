import matplotlib.pyplot as plt

# 读取文本文件中的数据
with open('quick-time.txt', 'r') as file:
    lines = file.readlines()

x = []
y = []

# 解析每一行的数据
for line in lines:
    data = line.strip().split(' ')
    x.append(float(data[0]))
    y.append(float(data[1]))

# 绘制散点图
plt.scatter(x, y, color='red', label='Data Points')

# 绘制折线图
plt.plot(x, y, color='blue', label='Line')

plt.xlabel('x')
plt.ylabel('y')
plt.title('Line Chart')
plt.legend()
plt.show()
