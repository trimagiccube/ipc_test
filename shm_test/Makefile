# Makefile

# 编译器
CXX = gcc
# 编译选项
CXXFLAGS = -lrt -lpthread
# 源文件
SRCS = shmread.c shmwrite.c
# 目标文件
OBJS = $(SRCS:.c=.o)
	# 可执行文件
TARGETS = shmread shmwrite

# 默认目标
all: $(TARGETS)

# 生成可执行文件
shmread: shmread.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

shmwrite: shmwrite.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

# 生成目标文件
%.o: %.cpp
	$(CXX) -c $< $(CXXFLAGS)

# 清理目标
clean:
	rm -f $(OBJS) $(TARGETS)

# 伪目标
.PHONY: all clean
