import random
import subprocess
import time

def generate_expression():
    """随机生成形如 'a op b' 的表达式"""
    operators = ['+', '-', '*', '/']
    a = random.randint(1, 100)  # 随机生成操作数 a
    b = random.randint(1, 100)  # 随机生成操作数 b
    op = random.choice(operators)  # 随机选择运算符
    if op == '/' and b == 0:  # 避免除以零
        b = random.randint(1, 100)
    return f"{a} {op} {b}"

if __name__ == "__main__":
    expression_count = 10  # 生成的表达式数量

    # 启动 C++ 程序，确保路径正确
    process = subprocess.Popen(
        ["/home/boran/Program/Cpp/bin/calulator"],
         # 替换为 C++ 程序的实际路径
        stdin=subprocess.PIPE, 
        stdout=subprocess.PIPE, 
        stderr=subprocess.PIPE,
        text=True  # 启用文本模式
    )

    # 生成并写入表达式
    expressions = [generate_expression() for _ in range(expression_count)]
    for expression in expressions:
        print(f"Generated Expression: {expression}")  # 打印生成的表达式
        process.stdin.write(expression + "\n")

    # 保持管道打开，等待一段时间
    process.stdin.flush()  # 刷新缓冲区，确保所有内容被写入
    time.sleep(1)  # 等待 1 秒

    # 写入退出标志
    process.stdin.write("quit\n")
    process.stdin.close()  # 关闭输入管道

    # 获取 C++ 程序的输出
    stdout, stderr = process.communicate()
    print("\nC++ Program Output:")
    print(stdout)  # 打印标准输出
    if stderr:
        print("\nC++ Program Errors:")
        print(stderr)  # 打印标准错误

