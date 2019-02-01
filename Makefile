#注释以#号开头
#Makefile编写规则：
#main:main.c child.c
#     目标对象  不一定要有依赖对象
#     依赖对象  依赖对象主要用于判断目标对象是否是最新的
#     为了生成目标对象所执行的命令
#
#     [目标对象]:[依赖对象]（依赖对象主要用于判断目标对象是否是最新的）
#     [tab制表符]如何通过依赖对象生成目标对象的编译命令
#     
#     预定义变量
#     $@ 指目标对象
#     $^ 指所有依赖对象
#     $< 指所有依赖对象中的第一个
#
#     wildcard    获取文件名
#     $()  将括号中字符串当做命令处理，
#     	   命令的执行结果当做变量内容赋值给别的变量
#     .PHONY--声明一个伪对象
#         伪对象：不管是不是最新的，反正每次都要重新生成
#
#     makefile只为了生成第一个目标对象而存在，假如目标对象已经存在，
#     make会判断依赖对象和目标对象的时间，判断目标对象是否是最新的，
#     如果是最新的，则不需编译，直接退出，不是最新的则重新生成
#
#     但是makefile这个特性导致只生成一个程序，因此后边如果还有目标对象
#     是不会生成的
#     但是makefile有个其它的特性，如果这个依赖对象不存在，会在makefile中查找依赖关系
#     看能不能生成这个依赖对象，如果有则生成，没有则报错退出

SRC=$(wildcard ./*.c)
#obj=$(patsubst %.c, %.o, $(SRC)) #将.c文件转化成.o文件
.PHONY:test test1
ALL:test test1

test:$(SRC)
	gcc -o $@ $^
test1:$(SRC)
	gcc -o $@ $^

.PHONY:clean
clean:
	rm test test1
#./%.o:./%.c
	#gcc -c $< -o $@  #将当前文件下的所有.c文件生成.o文件
