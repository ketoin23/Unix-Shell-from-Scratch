#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

#define SHELL_RL_BUFSZ 1024
#define delim " \t\r\n\a"
#define SHELL_TOK_BUFSZ 64

char *shell_readLine() {
	int bufsz = SHELL_RL_BUFSZ;
	int pos = 0;
	char *buffer = malloc(sizeof(char) * bufsz);
	int x;

	if(!buffer) {
		fprintf(stderr, "shell: allocation error\n");
		exit(EXIT_FAILURE);
	}

	while(1) {
		x = getchar();

		if(x == EOF || x == '\n') {
			buffer[pos] = '\0';
			return buffer;
		} else {
			buffer[pos] = x;
		}
		++pos;

		if(pos >= bufsz) {
			bufsz += SHELL_RL_BUFSZ;
			buffer = realloc(buffer, bufsz);
			if(!buffer) {
				fprintf(stderr, "shell: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

char **shell_splitLine(char *line) {
	int bufsz = SHELL_TOK_BUFSZ, pos = 0;
	char **tokens = malloc(bufsz * sizeof(char*));
	char *cur_token;

	if(!tokens) {
		fprintf(stderr, "shell: allocation error\n");
		exit(EXIT_FAILURE);
	}

	cur_token = strtok(line, delim);
	while(cur_token != NULL) {
		tokens[pos] = cur_token;
		++pos;

		if(pos >= bufsz) {
			bufsz += SHELL_TOK_BUFSZ;
			tokens = realloc(tokens, bufsz * sizeof(char*));
			if(!tokens) {
				fprintf(stderr, "shell: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		cur_token = strtok(NULL, delim);
	}

	tokens[pos] = NULL;
	return tokens;
}

int shell_launch(char **args) {
	pid_t pid, wpid;
	int status;

	pid = fork();
	if(pid == 0) {
		if(execvp(args[0], args) == -1) {
			perror("shell");
		}
		exit(EXIT_FAILURE);
	} else if(pid < 0) {
		perror("shell");
	} else {
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);

char *builtin_str[] = {
	"cd",
	"help",
	"exit"
};

int (*builtin_func[]) (char **) = {
	&shell_cd,
	&shell_help,
	&shell_exit
};

int shell_num_builtins() {
	return sizeof(builtin_str) / sizeof(char *);
}

int shell_cd(char **args) {
	if(args[1] == NULL) {
		fprintf(stderr, "shell: expected argument to \"cd\"\n");
	} else {
		if(chdir(args[1]) != 0) {
			perror("shell");
		}
	}
	return 1;
}

int shell_help(char **args) {
	printf("Welcom to ketoin's shell\n");
	printf("Type command names and their arguments, and hit enter.\n");
	printf("You can use any unix shell command such as ls, mkdir, cd, clear etc.\n");
	printf("The following commands are inbuilt:\n");

	for(int i = 0; i < shell_num_builtins(); i++) {
		printf(" %s\n", builtin_str[i]);
	}

	return 1;
}

int shell_exit(char **args) {
	return 0;
}

int shell_exec(char **args) {
	if(args[0] == NULL)
		return 1;

	for(int i = 0; i < shell_num_builtins(); i++) {
		if(strcmp(args[0], builtin_str[i]) == 0) {
			return (*builtin_func[i])(args);
		}
	}

	return shell_launch(args);
}

void main_loop(void) {
	char *line;
	char ** args;
	int status;

	do {
		printf("> ");
		line = shell_readLine();
		args = shell_splitLine(line);
		status = shell_exec(args);

		free(line);
		free(args);
	} while(status);
}

int main(int argc, char **argv) {

	main_loop();

	return EXIT_SUCCESS;
}