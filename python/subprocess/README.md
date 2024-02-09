## subprocess module

subprocess 可以用于一些特殊情况下的测试

### 运行外部命令

```python
import subprocess
subprocess.run('ls')
```

### 指定 shell

`ls`在windows中不是可执行命令, 在执行`subprocess.run('ls')`时会显示traceback, 指定`shell=True`可以避免打印traceback

```python
import subprocess
subprocess.run('ls', shell=True)
```

### 传递命令行参数

1. 直接将命令行参数放在字符串中, 但是`shell=True`必须指定

    ``` python
    import subprocess
    subprocess.run('ls -la', shell=True)
    ```

2. 使用`list`分割命令行参数与命令

    ```python
    import subprocess
    subprocess.run(['ls', '-la'])
    ```

### 获取执行命令的输出

#### `capture_output=True`

``` python
import subprocess
p1 = subprocess.run(['ls', '-la'], capture_output=True)

print(p1.stdout)
```

在不指定`text=True`的情况下, 捕获到的输出是raw string, 没有经过转义

#### `stdout`

可以单独设置`stdout`参数, 来进行各种情况下的处理

1. 通过管道, 捕获子进程的输出

    ``` python
    import subprocess
    p1 = subprocess.run(['ls', '-la'], stdout=subprocess.PIPE, text=True)

    print(p1.stdout)
    ```

2. 重定向子进程的输出到文件

    ``` python
    import subprocess
    with open('output.txt', 'w') as f:
        p1 = subprocess.run(['ls', '-la'], stdout=f, text=True)
    ```

#### 处理 error

当subprocess运行的程序失败后, python并不会主动地抛出异常, 当subprocess运行的程序真的发生错误时, 有以下几种处理方式:

1. 当运行的程序失败后`returncode`一般不为0, 可以通过检查返回值来判断程序是否发生异常
2. 当程序发生错误时, 其可能在`stderr`中打印有关错误的信息, 如果捕获了`stderr`可以打印出来
3. 在`subprocess.run()`中使用参数`check=True`

> 忽略错误信息：
>     
> 在`subprocess.run()`中使用参数`stderr=subprocess.DEVNULL`, 将不会捕获`stderr`
> 

### 更改程序的输入

1. 直接将字符串作为输入传递给子进程

    ``` python
    import subprocess
    p1 = subprocess.run('cat', input='hello, world!', capture_output=True, text=True)
    print(p1.stdout)
    ```

2. 将另一个程序的输出作为输入

    ```python
    import subprocess

    # 启动另一个进程并将其输出作为输入传递给当前进程
    p1 = subprocess.run(["other_program"], stdout=subprocess.PIPE) # text=True 有用吗?
    p2 = subprocess.run(["my_program"], input=p1.stdout, text=True)
    print(p2.stdout)
    ```

    还可以直接使用管道

    ``` python
    import subprocess

    p1 = subprocess.run('other_program | my_program', shell=True, stdout=subprocess.PIPE, text=True)
    print(p1.stdout)
    ```

3. 也可以读取文件

    ``` python
    import subprocess

    # 将文件内容作为输入传递给子进程
    with open("test.py", "r") as f:
        subprocess.run(["cat"], input=f.read(), text=True)
    ```


### 程序的执行时间很长怎么办

`subprocess.run()`是阻塞的吗, 如果不是阻塞的就糟糕了, 程序还没输出完, 只能捕获部分的`stdout`

可以尝试下面的程序, 是否能捕获到全部的输出

``` cpp
#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

int main() {
  std::cout << '0' << std::endl;
  std::this_thread::sleep_for(1s);
  std::cout << '1' << std::endl;
  std::this_thread::sleep_for(2s);
  std::cout << '3' << std::endl;
  std::this_thread::sleep_for(4s);
  std::cout << '7' << std::endl;
}
```

``` python
import subprocess
p1 = subprocess.run(["./slow"], capture_output=True, text=True)
print(p1.stdout)
```