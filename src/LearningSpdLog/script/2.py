import random
import sys
import string

def generate_expression():
    """随机生成形如 'a op b' 的合法表达式"""
    operators = ['+', '-', '*', '/', '?']
    a = random.randint(0, 100)  # 随机生成操作数 a
    b = random.randint(0, 100)  # 随机生成操作数 b
    op = random.choice(operators)  # 随机选择运算符

    return f"{a} {op} {b}"

def generate_random_string(length=10):
    """生成不包含括号的随机字符串"""
    characters = string.ascii_letters + string.digits + string.punctuation
    characters = characters.replace('(', '').replace(')', '')  # 移除括号
    return ''.join(random.choices(characters, k=length))

if __name__ == "__main__":
    # 默认生成 10 条表达式，可通过命令行参数指定条数
    count = int(sys.argv[1]) if len(sys.argv) > 1 else 10

    # 生成合法表达式或随机字符串
    for _ in range(count):
        # 10% 概率添加一个随机字符串
        if random.random() < 0.1:
            random_string = generate_random_string()
            print(random_string)
        else:
            print(generate_expression())
