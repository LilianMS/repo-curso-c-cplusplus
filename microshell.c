#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

// Função para escrever uma mensagem de erro para stderr
void log_erro(char *str)
{
    while (*str)
        write(2, str++, 1);
}

// Função decoradora para log de execução de comando
void log_execucao(char **argv) {
    printf("[LOG] Executando comando: %s\n", argv[0]);
}

// Função para mudar o diretório atual
int cd(char **argv, int i)
{
    if (i != 2)
        return log_erro("error: cd: bad arguments\n"), 1;
    if (chdir(argv[1]) == -1)
        return log_erro("error: cd: cannot change directory to "), log_erro(argv[1]), log_erro("\n"), 1;
    return 0;
}

// Função para configurar o pipe
void set_pipe(int has_pipe, int *fd, int end)
{
	if (has_pipe && (dup2(fd[end], end) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
		log_erro("error: fatal\n"), exit(1);
}

// Função para executar um comando
int exec(char **argv, int i, char **envp)
{
    int has_pipe, fd[2], pid, status;

    has_pipe = argv[i] && !strcmp(argv[i], "|");

    // Se o comando for 'cd', execute-o
    if (!has_pipe && !strcmp(*argv, "cd"))
        return cd(argv, i);

    // Adiciona log de execução
    log_execucao(argv);

    if (has_pipe && pipe(fd) == -1)
        log_erro("error: fatal\n"), exit(1);

    if ((pid = fork()) == -1)
        log_erro("error: fatal\n"), exit(1);

    if (!pid)
    {
        argv[i] = 0;
        set_pipe(has_pipe, fd, 1);
        if (!strcmp(*argv, "cd"))
            exit(cd(argv, i));
        execve(*argv, argv, envp);
        log_erro("error: cannot execute "), log_erro(*argv), log_erro("\n"), exit(1);
    }

    waitpid(pid, &status, 0);
    set_pipe(has_pipe, fd, 0);
    return WIFEXITED(status) && WEXITSTATUS(status);
}

int main(int argc, char **argv, char **envp)
{
    int i = 0, status = 0;

    // Itera pelos argumentos
    while (argv[i])
    {
        argv += i + 1;
        i = 0;

        // Procura por pipes ou ponto e vírgula
        while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
            i++;

        // Se houver argumentos, executa-os
        if (i)
            status = exec(argv, i, envp);
    }
    return status;
}
