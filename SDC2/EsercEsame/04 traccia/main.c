#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "common.h"
int ret;
void send_over_pipe(int write_desc, char* buf, size_t data_len) {

	/**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - scrivere sulla pipe tutti i data_len byte contenuti nel buffer buf
     * - gestire eventuali interruzioni ed errori
     * - assicurarsi che tutti i byte siano stati scritti
     */
    int written_bytes = 0;
    while(written_bytes < data_len){
        int ret = write(write_desc,buf + written_bytes,data_len - written_bytes );
        if(ret == -1 && errno == EINTR) continue;
        if(ret == -1) handle_error("Error reading from pipe");
        written_bytes += ret;
    }
    

}

int read_from_pipe(int read_desc, char* buf, size_t buf_len) {

	/**
	 * COMPLETARE QUI
     *
     * Obiettivi:
     * - leggere un messaggio dalla pipe e salvarlo nel buffer buf
     * - il valore di ritorno di questa funzione deve essere pari al numero di
     *   byte letto dalla pipe (incluso il delimitatore di fine messaggio)
     * - gestire eventuali chiusure della pipe da parte dell'altro processo come se fosse un errore
     * - gestire come un errore il caso in cui il messaggio sia troppo grande rispetto al buffer a disposizione
     * - gestire eventuali interruzioni ed errori
     *
     * Il delimitatore di fine messaggio è il terminatore di riga '\n'.
	 **/

    int read_bytes = 0;
    do
    {
        int ret = read(read_desc,buf + read_bytes,1);
        if(ret == -1 && errno == EINTR) continue;
        if(ret == -1) handle_error("Error reading from pipe");
        
        if(ret == 0) handle_error_en(-1,"Error pipe close");
        if(ret == buf_len) handle_error("message too big");

    } while (buf[read_bytes++] != '\n');

    return read_bytes;

}

void child_loop(int write_desc, int read_desc) {
    char buf[BUF_SIZE];

    int i;
    for (i = 0; i < NUM_MSG; ++i) {
        int num = rand() % MAX_NUM;
        sprintf(buf, "%d\n", num);
        send_over_pipe(write_desc, buf, strlen(buf));

        int bytes_read = read_from_pipe(read_desc, buf, sizeof(buf));
        buf[bytes_read-1] = '\0';
        printf("[Figlio] ricevuto msg #%d: %s\n", i, buf);
    }
}

void parent_loop(int read_desc, int write_desc) {
    char buf[BUF_SIZE];

    int i;
    for (i = 0; i < NUM_MSG; ++i) {
        int bytes_read = read_from_pipe(read_desc, buf, sizeof(buf));
        buf[bytes_read-1] = '\0';
        printf("[Padre] ricevuto msg #%d: %s\n", i, buf);

        int num = atoi(buf);
        sprintf(buf, "%d\n", 2*num);
        send_over_pipe(write_desc, buf, strlen(buf));
    }
}

int main(int argc, char* argv[]) {

    srand(SEED);

	/**
     * COMPLETARE QUI
     *
     * Obiettivi:
	 * - creare due pipe
     * - creare un processo figlio
     * - chiudere i descrittori di pipe non utilizzati nel padre e nel figlio
     * - il processo figlio chiama child_loop(), che prende come argomenti i
     *   descrittori di pipe per scrivere/leggere (vedere signature funzione)
     * - il processo padre chiama parent_loop(), che prende come argomenti i
     *   descrittori di pipe per leggere/scrivere (vedere signature funzione)
	 * - il padre deve attendere il termine del figlio prima di terminare a sua
     *   volta
	 * - chiudere i descrittori di pipe in fase di uscita
     * - gestire eventuali errori
     */

    int pipe1[2];
    int pipe2[2];

    ret = pipe(pipe1);
    if(ret < 0) handle_error("Error creating pipe1");
    ret = pipe(pipe2);
    if(ret < 0) handle_error("Error creating pipe2");

    int pid = fork();
    if(pid == -1){
        handle_error("Error creating child process");
    }
    if(pid == 0){
        close(pipe1[0]);
        close(pipe2[1]);

        child_loop(pipe1[1],pipe2[0]);

        close(pipe1[1]);
        close(pipe2[0]);

        _exit(0);
    }

    close(pipe1[1]);
    close(pipe2[0]);

    parent_loop(pipe1[0],pipe2[1]);


    int status;
    wait(status);

    close(pipe1[0]);
    close(pipe2[1]);
    return 0;
}
