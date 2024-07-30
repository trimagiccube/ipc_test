# Makefile

# 编译器
CXX = g++
# 编译选项
CXXFLAGS = -lrt -lpthread
# 源文件
SRCS = producer.cpp consumer.cpp
# 目标文件
OBJS = $(SRCS:.cpp=.o)
	# 可执行文件
TARGETS = producer consumer

# 默认目标
all: $(TARGETS)

# 生成可执行文件
producer: producer.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

consumer: consumer.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

# 生成目标文件
%.o: %.cpp
	$(CXX) -c $< $(CXXFLAGS)

# 清理目标
clean:
	rm -f $(OBJS) $(TARGETS)

# 伪目标
.PHONY: all clean
