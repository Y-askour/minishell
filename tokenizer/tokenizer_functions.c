#include"minishell.h"

char	*ft_strndup(char *str, int n)
{
	char	*ret;

	ret = (char *)malloc(n);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, str, n);
	return (ret);
}

char *is_wspace(t_token_list *tokens, char *line)
{
    int len;

    len = 0;
    while(strchr(" \t\f\r\v", line[len]))
        len++;
    add_back(tokens, ' ', WHSPACE);
    return (line + len);
}

char *is_redpip(t_token_list *tokens, char *line)
{
    if (*line == '>')
    {
        if (*(line + 1) == '>')
        {
            add_back(tokens, ">>", APPEND);
            return (line + 2);
        }
        add_back(tokens, ">", REDOUT);
        return (line + 1);
    }
    else if (*line == '<')
    {
        if (*(line + 1) == '<')
        {
            add_back(tokens, "<<", HEREDOC);
            return (line + 2);
        }
        add_back(tokens, "<", REDOUT);
        return (line + 1);
    }
    else
        add_back(tokens, "|", PIPE);
    return (line + 1);
}

char *is_word(t_token_list *tokens, char *line, char *stop)
{
    int len;

    len = 0;
    while(!strchr(stop, line[len]))
        len++;
    add_back(tokens, ft_strndup(line, len + 1), WORD);
    return(line + len);
}

char *after_dollar(t_token_list *tokens, char *line)
{
    int len;

    len = 0;
    while(ft_isalnum(line[len]))
        len++;
    add_back(tokens, ft_strndup(line, len + 1), WORD);
    return(line + len);
}

char *is_sign(t_token_list *tokens, char *line)
{
    if (*line == '~')
    {
        add_back(tokens, "~", TILDE);
        return(line + 1);
    }
    else if (*line == "$")
    {
        add_back(tokens, "$", DOLLAR);
        return (after_dollar(tokens, line + 1));
    }
}