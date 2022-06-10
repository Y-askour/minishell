#include"minishell.h"

char    *display_prompt()
{
    char    *line;
    char    *prompt;

	prompt = "minishell$>";

	signal(SIGINT, signal_handler); //ctrl + c
	signal(SIGQUIT, SIG_IGN); //ctrl + '\'
	signal(SIGTSTP, SIG_IGN); //ctrl + z
	line = readline(prompt);
	if (!line || !ft_strncmp(line, "exit", 4))
	{
		printf("%s", "exit");
		exit(1);
	}
	if (line)
		add_history(line);//to save the line away in a history list of such lines
    rl_on_new_line();
    return (line);
}