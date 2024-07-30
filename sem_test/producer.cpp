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
	// 创建有名信号量
	sem_t *sem_prod = sem_open(SEM_PROD, O_CREAT, 0644, 1);
	sem_t *sem_cons = sem_open(SEM_CONS, O_CREAT, 0644, 0);

	// 创建共享内存
	int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, BUFFER_SIZE);
	char *buffer = (char *)mmap(0, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

	for (int i = 0; i < 5; ++i) {
		sem_wait(sem_prod); // 等待生产者信号量
		snprintf(buffer, BUFFER_SIZE, "Message %d", i); // 写入数据
		std::cout << "Produced: " << buffer << std::endl;
		sem_post(sem_cons); // 发送消费者信号量
		sleep(1); // 模拟生产时间
	}

	// 清理
	munmap(buffer, BUFFER_SIZE);
	close(shm_fd);
	sem_close(sem_prod);
	sem_close(sem_cons);
	sem_unlink(SEM_PROD);
	sem_unlink(SEM_CONS);
	shm_unlink(SHM_NAME);

	return 0;
}
