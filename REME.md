

这是一个简单的类似python语言的解释器实现
PS:目前处于未完成状态,还在持续不断的维护更新

------

####语法介绍

1. 基本数据类型

​	1.整型 2.字符串 3.空值(null) 4.列表 5.元组 6.字典 7.集合 8.函数

​	字符串

```python
a = "hello"+"world"
b = str(123)
```

​	列表

```python
a = [1,2,"hcc",true]
b = a[0]
a.append("end")
a+=[4,5,6]
b = list(range(1,101))
```

​	元组

```python
l = [10,"que",false]
t = tuple(l)
print(t[1])
```

​	字典

```c++
d = dict()
d.insert("age",102)
d.insert(2,100)
a = d.find("age")
b = d["age"]
```

​	函数

```c++
def func(x,y){
    b = x*2
    c = y+3
    return x+y
}
```

​	

2. 基本算术运算和逻辑运算

​	1. 加减乘除乘方(+,-,*,/,^)

```python
(1+2)*53/4
```

​	2. 与或非(and / or / not)

```python
true and (not false) or 1>=3
```



3. 基本语句

​	1. if语句

```python
a = 10
b = 0
if a<=5 or a>=0 {
    a = 0
}
elif a<0 {
    b = a
}
else{
    print(a)
}
```

​	2. while语句

```c++
i = 0
sum = 0
while(i<=100){
    sum+=i
    i+=1
    continue
    break
}
```

 	3.for语句

```python
for i in [1,2,3]{
    print(i)
}
sum = 0
for i in range(1,101){
    sum += i
}
```

4.自定义数据类型

```python
class Node{
    def __init__(self,data_,next_){
        self.data = data_
        self.next = next_
    }
}
class MyList{
    def __init__(self){
        self.head = null
    }
    def insert(self,data){
        self.head = Node(data,head)
    }
    def show(self){
        cur = self.head
        while(cur){
            print(cur.data)
            cur = cur.next
        }
    }
}
ls = MyList()
ls.insert(1)
ls.insert(2)
ls.show()
```

-----

2.工作流程

![](C:\Users\86173\Desktop\工作流程.png)

3.虚拟机工作原理

虚拟机使用操作数栈作为临时变量的存放位置  



字节码由操作码和操作数构成



LOAD_CONST将常量表的数据压入操作数栈, 对应操作数为数据在常量表中的索引



LOAD_NAME将变量压入操作数栈



STORE_NAME将栈顶pop到对应的变量中



BINARY_ARIT取栈顶和次栈顶元素进行加法运算



LOAD_NAME,STORE_NAME 的操作数为数据在变量表中的索引.



以下用一小段代码演示流程

![](C:\Users\86173\Desktop\vmwork.png)

4.目标语言特性和目前完成情况





- [x] 编译时报错提示
- [x] 内置容器类型
- [x] 类成员函数
- [x] 类魔法函数

- [x] 基于迭代器的for循环
- [ ] 建立在CRT之上的内存分配和释放
- [ ] 自动垃圾收集
- [ ] 整数池优化
- [ ] 字符串池优化
- [ ] 模块导入
- [ ] 运行时报错提示
- [ ] 编译结果的保存及其序列化和反序列化

