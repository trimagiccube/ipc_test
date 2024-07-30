#include <sys/mman.h>
#include <iostream>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

#define SEM_PROD "/sem_prod"
#define SEM_CONS "/sem_cons"
#define SHM_NAME "/my_shm"
#define BUFFER_SIZE 256

int main() {
	// 打开有名信号量
	sem_t *sem_prod = sem_open(SEM_PROD, 0);
	sem_t *sem_cons = sem_open(SEM_CONS, 0);

	// 打开共享内存
	int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
	char *buffer = (char *)mmap(0, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

	for (int i = 0; i < 5; ++i) {
		sem_wait(sem_cons); // 等待消费者信号量
		std::cout << "Consumed: " << buffer << std::endl; // 读取数据
		sem_post(sem_prod); // 发送生产者信号量
		sleep(1); // 模拟消费时间
	}

	// 清理
	munmap(buffer, BUFFER_SIZE);
	close(shm_fd);
	sem_close(sem_prod);
	sem_close(sem_cons);

	return 0;
}
